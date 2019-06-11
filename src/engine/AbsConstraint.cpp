
#include "AbsConstraint.h"
#include "ITableau.h"
#include "FloatUtils.h"
#include "AbsError.h"
#include "Debug.h"
#include "PiecewiseLinearCaseSplit.h"
#include "MStringf.h"
#include "Statistics.h"
#include "ConstraintBoundTightener.h"



AbsConstraint::AbsConstraint(unsigned b, unsigned f )
    //var names
    : _b( b )
    , _f( f )
    // one of our variables terminated
    , _haveEliminatedVariables( false )
{
    //bound tightening
    setPhaseStatus( PhaseStatus::PHASE_NOT_FIXED );
}

//TODO: add serialize?

PiecewiseLinearConstraint *AbsConstraint::duplicateConstraint() const
{
    AbsConstraint *clone = new AbsConstraint( _b, _f );
    *clone = *this;
    return clone;
}

void AbsConstraint::restoreState( const PiecewiseLinearConstraint *state )
{
    const AbsConstraint *abs = dynamic_cast<const AbsConstraint *>( state );
    *this = *abs;
}

void AbsConstraint::registerAsWatcher( ITableau *tableau )
{
    tableau->registerToWatchVariable( this, _b );
    tableau->registerToWatchVariable( this, _f );
}

void AbsConstraint::unregisterAsWatcher( ITableau *tableau )
{
    tableau->unregisterToWatchVariable( this, _b );
    tableau->unregisterToWatchVariable( this, _f );
}


/*
  The variable watcher notifcation callbacks, about a change in a variable's value or bounds.
*/
void AbsConstraint::notifyVariableValue( unsigned variable, double value)
{
    //todo: ask guy if its ok
    _assignment[variable] = value;
}

void AbsConstraint::notifyLowerBound( unsigned variable, double bound)
{
    if ( _statistics )
        _statistics->incNumBoundNotificationsPlConstraints();

    if ( _lowerBounds.exists( variable ) && !FloatUtils::gt( bound, _lowerBounds[variable] ) )
        return;

    _lowerBounds[variable] = bound;

    if ( (variable == _f || variable == _b) && FloatUtils::isPositive( bound ) )
        setPhaseStatus( PhaseStatus::PHASE_POSITIVE );

    if ( isActive() && _constraintBoundTightener )
    {
        unsigned partner = ( variable == _f ) ? _b : _f;

        if ( bound >=0 )
        {
            if ( _lowerBounds.exists( partner ) )
            {
                double otherLowerBound = _lowerBounds[partner];
                if ( bound > otherLowerBound )
                    _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
            else
            {
                _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
        }
        else if ( bound < 0 )
        {
            if ( _lowerBounds.exists( partner ) )
            {
                double otherLowerBound = _lowerBounds[partner];
                if ( bound > otherLowerBound )
                    _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
            else
            {
                _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
        }
    }
}

void AbsConstraint::notifyUpperBound(  unsigned variable, double bound )
{
    if ( _statistics )
        _statistics->incNumBoundNotificationsPlConstraints();

    if ( _upperBounds.exists( variable ) && !FloatUtils::lt( bound, _upperBounds[variable] ) )
        return;

    _upperBounds[variable] = bound;

    if ( ( variable == _f || variable == _b ) && FloatUtils::isNegative( bound ) )
        setPhaseStatus( PhaseStatus::PHASE_NEGATIVE );

    if ( isActive() && _constraintBoundTightener )
    {
        unsigned partner = ( variable == _f ) ? _b : _f;

        if ( _lowerBounds.exists( partner ) )
            {
                double otherLowerBound = _lowerBounds[partner];
                if ( bound < otherLowerBound )
                    _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
            else
            {
                _constraintBoundTightener->registerTighterLowerBound( partner, bound );
            }
        }
    }
}


bool AbsConstraint::participatingVariable(unsigned variable ) const
{
    return ( variable == _b ) || ( variable == _f );
}

List<unsigned> AbsConstraint::getParticipatingVariables() const
{
    return List<unsigned>( { _b, _f } );
}

bool AbsConstraint::satisfied() const
{
    if ( !( _assignment.exists( _b ) && _assignment.exists( _f ) ) )
        throw AbsError( AbsError::PARTICIPATING_VARIABLES_ABSENT );

    double bValue = _assignment.get( _b );
    double fValue = _assignment.get( _f );

    // Possible violations:
    //   1. f is negative
    //   2. f is positive, abs(b) and f are disequal

    if ( FloatUtils::isNegative( fValue ) )
        return false;

    return FloatUtils::areEqual( FloatUtils::abs(bValue), fValue, GlobalConfiguration::ABS_CONSTRAINT_COMPARISON_TOLERANCE);

}


List<PiecewiseLinearConstraint::Fix> AbsConstraint::getPossibleFixes() const
{
    ASSERT( !satisfied() );
    ASSERT( _assignment.exists( _b ) );
    ASSERT( _assignment.exists( _f ) );

    double bValue = _assignment.get( _b );
    double fValue = _assignment.get( _f );

    ASSERT( !FloatUtils::isNegative( fValue ) );

    List<PiecewiseLinearConstraint::Fix> fixes;

    // Possible violations:
    //   1. f is positive, b is positive, b and f are disequal
    //   2. f is positive, b is negative, -b and f are disequal

    if ( FloatUtils::isPositive( fValue ) ) {
        fixes.append(PiecewiseLinearConstraint::Fix(_b, fValue));
        fixes.append(PiecewiseLinearConstraint::Fix(_f, abs(bValue)));
    }

    return fixes;
}



List<PiecewiseLinearConstraint::Fix> AbsConstraint::getSmartFixes( __attribute__((unused)) ITableau *tableau ) const
{
    return getPossibleFixes();
}


List<PiecewiseLinearCaseSplit> AbsConstraint::getCaseSplits() const
{
    if ( _phaseStatus != PhaseStatus::PHASE_NOT_FIXED )
        throw AbsError( AbsError::REQUESTED_CASE_SPLITS_FROM_FIXED_CONSTRAINT );

    List<PiecewiseLinearCaseSplit> splits;
    splits.append( getNegativeSplit() );
    splits.append( getPositiveSplit() );

    //TODO: add some heuristic
    return splits;
}


PiecewiseLinearCaseSplit AbsConstraint::getNegativeSplit() const {
    // Negative phase: b <=0, b + f = 0
    PiecewiseLinearCaseSplit negativePhase;

    //b <= 0
    negativePhase.storeBoundTightening(Tightening(_b, 0.0, Tightening::UB));

    //b + f = 0
    Equation negativeEquation(Equation::EQ);
    negativeEquation.addAddend(1, _b);
    negativeEquation.addAddend(1, _f);
    negativeEquation.setScalar(0);
    negativePhase.addEquation(negativeEquation);

    return negativePhase;
}

PiecewiseLinearCaseSplit AbsConstraint::getPositiveSplit() const {
    // Positive phase: b >= 0, b - f = 0
    PiecewiseLinearCaseSplit positivePhase;

    //b >= 0
    positivePhase.storeBoundTightening(Tightening(_b, 0.0, Tightening::LB));

    //b - f = 0
    Equation positiveEquation(Equation::EQ);
    positiveEquation.addAddend(1, _b);
    positiveEquation.addAddend(-1, _f);
    positiveEquation.setScalar(0);
    positivePhase.addEquation(positiveEquation);

    return positivePhase;
}


bool AbsConstraint::phaseFixed() const
{
    return _phaseStatus != PhaseStatus::PHASE_NOT_FIXED;
}

PiecewiseLinearCaseSplit AbsConstraint::getValidCaseSplit() const
{
    ASSERT( _phaseStatus != PhaseStatus::PHASE_NOT_FIXED );

    if ( _phaseStatus == PhaseStatus::PHASE_POSITIVE )
        return getPositiveSplit();

    return getNegativeSplit();
}


void AbsConstraint::eliminateVariable(__attribute__((unused)) unsigned variable, __attribute__((unused)) double fixedValue ){}

void AbsConstraint::updateVariableIndex( __attribute__((unused)) unsigned oldIndex, __attribute__((unused)) unsigned newIndex ) {}

bool AbsConstraint::constraintObsolete() const
{
    return true;
}

void AbsConstraint::getEntailedTightenings( __attribute__((unused)) List<Tightening> &tightenings ) const {}

void AbsConstraint::getAuxiliaryEquations( __attribute__((unused)) List<Equation> &newEquations ) const {}


String AbsConstraint::serializeToString() const
{
    // Output format is: Abs,f,b
    return Stringf( "Abs,%u,%u", _f, _b );
}





void AbsConstraint::setPhaseStatus( PhaseStatus phaseStatus )
{
    _phaseStatus = phaseStatus;
}