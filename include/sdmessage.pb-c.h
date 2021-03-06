/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: sdmessage.proto */

#ifndef PROTOBUF_C_sdmessage_2eproto__INCLUDED
#define PROTOBUF_C_sdmessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _DataMessage DataMessage;
typedef struct _NullableString NullableString;
typedef struct _EntryMessage EntryMessage;
typedef struct _KeysMessage KeysMessage;
typedef struct _Message Message;


/* --- enums --- */

typedef enum _Message__OperationCode {
  MESSAGE__OPERATION_CODE__OP_BAD = 0,
  /*
   * Identifies the query tree_size in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_SIZE = 10,
  /*
   * Identifies the operation tree_del in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_DEL = 20,
  /*
   * Identifies the query tree_get in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_GET = 30,
  /*
   * Identifies the operation tree_put in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_PUT = 40,
  /*
   * Identifies the query tree_get_keys in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_GETKEYS = 50,
  /*
   * Identifies the query tree_height in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_HEIGHT = 60,
  /*
   * Identifies the query verify in a request message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_VERIFY = 70,
  /*
   * Identifies a failed query/operation in a response message_t. 
   */
  MESSAGE__OPERATION_CODE__OP_ERROR = 99
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MESSAGE__OPERATION_CODE)
} Message__OperationCode;

/* --- messages --- */

struct  _DataMessage
{
  ProtobufCMessage base;
  ProtobufCBinaryData data;
};
#define DATA_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&data_message__descriptor) \
    , {0,NULL} }


struct  _NullableString
{
  ProtobufCMessage base;
  char *str;
};
#define NULLABLE_STRING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&nullable_string__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  _EntryMessage
{
  ProtobufCMessage base;
  NullableString *key;
  DataMessage *value;
};
#define ENTRY_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&entry_message__descriptor) \
    , NULL, NULL }


struct  _KeysMessage
{
  ProtobufCMessage base;
  size_t n_keys;
  char **keys;
};
#define KEYS_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&keys_message__descriptor) \
    , 0,NULL }


typedef enum {
  MESSAGE__CONTENT__NOT_SET = 0,
  MESSAGE__CONTENT_KEY = 10,
  MESSAGE__CONTENT_VALUE = 20,
  MESSAGE__CONTENT_ENTRY = 30,
  MESSAGE__CONTENT_KEYS = 40,
  MESSAGE__CONTENT_INT_RESULT = 50,
  MESSAGE__CONTENT_OP_ID = 60
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MESSAGE__CONTENT)
} Message__ContentCase;

/*
 * A message
 * - sent by the client to the server representing a query or operation over the tree; or
 * - sent by the server to the client representing the response to a query or operation.
 */
struct  _Message
{
  ProtobufCMessage base;
  /*
   * Identifies the query/operation being requested/responded in this message; or
   * OP_ERROR if this is a response-message and the invoked query/operation failed.
   */
  Message__OperationCode op_code;
  Message__ContentCase content_case;
  union {
    char *key;
    DataMessage *value;
    EntryMessage *entry;
    KeysMessage *keys;
    int32_t int_result;
    /*
     * The unique identifier of the asynchronous operation that was requested. 
     */
    int32_t op_id;
  };
};
#define MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&message__descriptor) \
    , MESSAGE__OPERATION_CODE__OP_BAD, MESSAGE__CONTENT__NOT_SET, {0} }


/* DataMessage methods */
void   data_message__init
                     (DataMessage         *message);
size_t data_message__get_packed_size
                     (const DataMessage   *message);
size_t data_message__pack
                     (const DataMessage   *message,
                      uint8_t             *out);
size_t data_message__pack_to_buffer
                     (const DataMessage   *message,
                      ProtobufCBuffer     *buffer);
DataMessage *
       data_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   data_message__free_unpacked
                     (DataMessage *message,
                      ProtobufCAllocator *allocator);
/* NullableString methods */
void   nullable_string__init
                     (NullableString         *message);
size_t nullable_string__get_packed_size
                     (const NullableString   *message);
size_t nullable_string__pack
                     (const NullableString   *message,
                      uint8_t             *out);
size_t nullable_string__pack_to_buffer
                     (const NullableString   *message,
                      ProtobufCBuffer     *buffer);
NullableString *
       nullable_string__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   nullable_string__free_unpacked
                     (NullableString *message,
                      ProtobufCAllocator *allocator);
/* EntryMessage methods */
void   entry_message__init
                     (EntryMessage         *message);
size_t entry_message__get_packed_size
                     (const EntryMessage   *message);
size_t entry_message__pack
                     (const EntryMessage   *message,
                      uint8_t             *out);
size_t entry_message__pack_to_buffer
                     (const EntryMessage   *message,
                      ProtobufCBuffer     *buffer);
EntryMessage *
       entry_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   entry_message__free_unpacked
                     (EntryMessage *message,
                      ProtobufCAllocator *allocator);
/* KeysMessage methods */
void   keys_message__init
                     (KeysMessage         *message);
size_t keys_message__get_packed_size
                     (const KeysMessage   *message);
size_t keys_message__pack
                     (const KeysMessage   *message,
                      uint8_t             *out);
size_t keys_message__pack_to_buffer
                     (const KeysMessage   *message,
                      ProtobufCBuffer     *buffer);
KeysMessage *
       keys_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   keys_message__free_unpacked
                     (KeysMessage *message,
                      ProtobufCAllocator *allocator);
/* Message methods */
void   message__init
                     (Message         *message);
size_t message__get_packed_size
                     (const Message   *message);
size_t message__pack
                     (const Message   *message,
                      uint8_t             *out);
size_t message__pack_to_buffer
                     (const Message   *message,
                      ProtobufCBuffer     *buffer);
Message *
       message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   message__free_unpacked
                     (Message *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*DataMessage_Closure)
                 (const DataMessage *message,
                  void *closure_data);
typedef void (*NullableString_Closure)
                 (const NullableString *message,
                  void *closure_data);
typedef void (*EntryMessage_Closure)
                 (const EntryMessage *message,
                  void *closure_data);
typedef void (*KeysMessage_Closure)
                 (const KeysMessage *message,
                  void *closure_data);
typedef void (*Message_Closure)
                 (const Message *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor data_message__descriptor;
extern const ProtobufCMessageDescriptor nullable_string__descriptor;
extern const ProtobufCMessageDescriptor entry_message__descriptor;
extern const ProtobufCMessageDescriptor keys_message__descriptor;
extern const ProtobufCMessageDescriptor message__descriptor;
extern const ProtobufCEnumDescriptor    message__operation_code__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_sdmessage_2eproto__INCLUDED */
