/* Grupo 48
 *   Eva Gomes (37806)
 *   João Santos (40335)
 *   João Vieira (45677)
 */

#include "client_stub-private.h"
#include "inet-private.h"
#include "logger-private.h"

#include <unistd.h>

int network_connect(struct rtree_t* rtree) {
  if (rtree == NULL) {
    logger_error_invalid_arg("network_connect", "rtree", "NULL");
    return -1;
  }

  if ((rtree->primary_sockfd =
           server_connect(rtree->primary_server_ip_address, rtree->primary_server_port)) < 0) {
    return -1;
  }
  logger_info("Connected to primary server at %s:%d...\n", rtree->primary_server_ip_address,
              rtree->primary_server_port);

  if ((rtree->backup_sockfd =
           server_connect(rtree->backup_server_ip_address, rtree->backup_server_port)) < 0) {
    rtree->primary_sockfd = -1;
    close(rtree->primary_sockfd);
    return -1;
  }
  logger_info("Connected to backup server at %s:%d...\n", rtree->backup_server_ip_address,
              rtree->backup_server_port);

  return 0;
}

struct message_t* network_send_receive(struct rtree_t* rtree, struct message_t* msg) {
  if (rtree == NULL || msg == NULL || msg->msg == NULL) {
    logger_error_invalid_args("network_send_receive");
    return NULL;
  }

  int sockfd;
  switch (msg->msg->op_code) {
    case OP_SIZE:
    case OP_GET:
    case OP_GETKEYS:
    case OP_HEIGHT:
    case OP_VERIFY:
      sockfd = rtree->backup_sockfd;
      break;
    case OP_DEL:
    case OP_PUT:
      sockfd = rtree->primary_sockfd;
      break;
    default:
      logger_error("network_send_receive", "Unexpected error, unexpected op_code %d",
                   msg->msg->op_code);
      return NULL;
  }

  if (network_send_message(sockfd, msg) < 0) {
    return NULL;
  }
  return network_receive_message(sockfd);
}

int network_close(struct rtree_t* rtree) {
  if (rtree == NULL) {
    logger_error_invalid_arg("network_close", "rtree", "NULL");
    return -1;
  }
  int primary_res = rtree->primary_sockfd <= 0 ? 0 : close(rtree->primary_sockfd);
  int backup_res = rtree->backup_sockfd <= 0 ? 0 : close(rtree->backup_sockfd);
  return (primary_res < 0 || backup_res < 0) ? -1 : 0;
}
