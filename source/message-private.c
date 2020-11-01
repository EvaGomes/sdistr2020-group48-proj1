#include "message-private.h"
#include "data-private.h"
#include "data.h"
#include "entry.h"
#include "sdmessage.pb-c.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE_OF_DATA_MESSAGE = sizeof(DataMessage);
const int SIZE_OF_ENTRY_MESSAGE = sizeof(EntryMessage);
const int SIZE_OF_KEYS_MESSAGE = sizeof(KeysMessage);
const int SIZE_OF_MESSAGE = sizeof(Message);
const int SIZE_OF_MESSAGE_T = sizeof(struct message_t);
const int SIZE_OF_NULLABLE_STRING = sizeof(NullableString);

DataMessage* data_to_msg(struct data_t* dataStruct) {
  if (dataStruct == NULL) {
    return NULL;
  }
  DataMessage* msg = malloc(SIZE_OF_DATA_MESSAGE);
  if (msg == NULL) {
    fprintf(stderr, "\nERR: data_to_msg: malloc failed\n");
    return NULL;
  }
  data_message__init(msg);
  msg->data.len = dataStruct->datasize;
  msg->data.data = copy(dataStruct->data, dataStruct->datasize);
  return msg;
}

struct data_t* msg_to_data(DataMessage* msg) {
  if (msg == NULL) {
    return NULL;
  }
  int datasize = msg->data.len;
  void* data = copy(msg->data.data, datasize);
  return data_create2(datasize, data);
}

NullableString* string_to_msg(char* string) {
  if (string == NULL) {
    return NULL;
  }
  NullableString* msg = malloc(SIZE_OF_NULLABLE_STRING);
  if (msg == NULL) {
    fprintf(stderr, "\nERR: string_to_msg: malloc failed\n");
    return NULL;
  }
  nullable_string__init(msg);
  msg->str = strdup(string);
  return msg;
}

char* msg_to_string(NullableString* msg) {
  if (msg == NULL) {
    return NULL;
  }
  return strdup(msg->str);
}

EntryMessage* entry_to_msg(struct entry_t* entry) {
  if (entry == NULL) {
    return NULL;
  }
  EntryMessage* msg = malloc(SIZE_OF_ENTRY_MESSAGE);
  if (msg == NULL) {
    fprintf(stderr, "\nERR: entry_to_msg: malloc failed\n");
    return NULL;
  }
  entry_message__init(msg);
  msg->key = string_to_msg(entry->key);
  msg->value = data_to_msg(entry->value);
  return msg;
}

struct entry_t* msg_to_entry(EntryMessage* msg) {
  if (msg == NULL) {
    return NULL;
  }
  char* key = msg_to_string(msg->key);
  struct data_t* value = msg_to_data(msg->value);
  return entry_create(key, value);
}

int _keys_count(char** keys) {
  int index = 0;
  while (keys[index] != NULL) {
    index += 1;
  }
  return index;
}

KeysMessage* keys_to_msg(char** keys) {
  if (keys == NULL) {
    return NULL;
  }
  KeysMessage* msg = malloc(SIZE_OF_KEYS_MESSAGE);
  if (msg == NULL) {
    fprintf(stderr, "\nERR: keys_to_msg: malloc failed\n");
    return NULL;
  }
  keys_message__init(msg);
  int keys_count = _keys_count(keys);
  msg->n_keys = keys_count;
  if (keys_count == 0) {
    return msg;
  }

  msg->keys = malloc(keys_count * sizeof(NullableString*));
  for (int i = 0; i < keys_count; ++i) {
    msg->keys[i] = string_to_msg(keys[i]);
  }
  return msg;
}

char** msg_to_keys(KeysMessage* msg) {
  if (msg == NULL) {
    return NULL;
  }
  int n_keys = msg->n_keys;
  char** keys = malloc((n_keys + 1) * sizeof(char*));
  for (int i = 0; i < n_keys; ++i) {
    keys[i] = msg_to_string(msg->keys[i]);
  }
  keys[n_keys] = NULL;
  return keys;
}

struct message_t* message_create() {
  Message* msg = malloc(SIZE_OF_MESSAGE);
  if (msg == NULL) {
    fprintf(stderr, "\nERR: message_create: malloc 1 failed\n");
    return NULL;
  }
  message__init(msg);

  struct message_t* message = malloc(SIZE_OF_MESSAGE_T);
  if (message == NULL) {
    fprintf(stderr, "\nERR: message_create: malloc 2 failed\n");
    free(msg);
    return NULL;
  }
  message->msg = msg;

  return message;
}

void message_destroy(struct message_t* message) {
  if (message != NULL) {
    if (message->msg != NULL) {
      message__free_unpacked(message->msg, NULL);
    }
    free(message);
  }
}