/* Grupo 48
 *   Eva Gomes (37806)
 *   João Santos (40335)
 *   João Vieira (45677)
 */

#include "inet-private.h"
#include "logger-private.h"
#include "network_server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void _handle_SIGINT_signal(int signal) {
  logger_debug("Caught signal %d\n", signal);
}

int main(int argc, char** argv) {

  signal(SIGINT, _handle_SIGINT_signal);
  signal(SIGPIPE, SIG_IGN);

  if (argc != 2) {
    errno = EINVAL;
    fprintf(stderr, "Invalid number of arguments\n");
    printf("Usage: ./tree_server <port>\n");
    printf(" E.g.: ./tree_server 9000\n");
    return -1;
  }

  int port = htons(atoi(argv[1]));
  if (port == 0) {
    errno = EINVAL;
    fprintf(stderr, "Invalid argument \"%s\"\n", argv[1]);
    return -1;
  }

  int listening_socket = network_server_init(port);
  if (listening_socket < 0) {
    return -1;
  }

  network_main_loop(listening_socket);

  network_server_close();
  return close(listening_socket);
}
