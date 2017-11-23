// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: tensorflow/core/lib/core/error_codes.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "tensorflow/core/lib/core/error_codes.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace tensorflow {
namespace error {

namespace protobuf_tensorflow_2fcore_2flib_2fcore_2ferror_5fcodes_2eproto {


namespace {

const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;
namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "tensorflow/core/lib/core/error_codes.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      NULL, file_level_enum_descriptors, NULL);
}

GOOGLE_ATTRIBUTE_NOINLINE void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
}

GOOGLE_ATTRIBUTE_NOINLINE void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n*tensorflow/core/lib/core/error_codes.p"
      "roto\022\020tensorflow.error*\204\003\n\004Code\022\006\n\002OK\020\000\022"
      "\r\n\tCANCELLED\020\001\022\013\n\007UNKNOWN\020\002\022\024\n\020INVALID_A"
      "RGUMENT\020\003\022\025\n\021DEADLINE_EXCEEDED\020\004\022\r\n\tNOT_"
      "FOUND\020\005\022\022\n\016ALREADY_EXISTS\020\006\022\025\n\021PERMISSIO"
      "N_DENIED\020\007\022\023\n\017UNAUTHENTICATED\020\020\022\026\n\022RESOU"
      "RCE_EXHAUSTED\020\010\022\027\n\023FAILED_PRECONDITION\020\t"
      "\022\013\n\007ABORTED\020\n\022\020\n\014OUT_OF_RANGE\020\013\022\021\n\rUNIMP"
      "LEMENTED\020\014\022\014\n\010INTERNAL\020\r\022\017\n\013UNAVAILABLE\020"
      "\016\022\r\n\tDATA_LOSS\020\017\022K\nGDO_NOT_USE_RESERVED_"
      "FOR_FUTURE_EXPANSION_USE_DEFAULT_IN_SWIT"
      "CH_INSTEAD_\020\024B1\n\030org.tensorflow.framewor"
      "kB\020ErrorCodesProtosP\001\370\001\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 512);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "tensorflow/core/lib/core/error_codes.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

GOOGLE_ATTRIBUTE_NOINLINE void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_tensorflow_2fcore_2flib_2fcore_2ferror_5fcodes_2eproto

const ::google::protobuf::EnumDescriptor* Code_descriptor() {
  protobuf_tensorflow_2fcore_2flib_2fcore_2ferror_5fcodes_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_tensorflow_2fcore_2flib_2fcore_2ferror_5fcodes_2eproto::file_level_enum_descriptors[0];
}
bool Code_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 20:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace error
}  // namespace tensorflow

// @@protoc_insertion_point(global_scope)
