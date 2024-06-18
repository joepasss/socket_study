#include "error_handling.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int sock;
  struct sockaddr_in serv_addr;
  char msg[1024];
  int str_len = 0;
  int idx = 0, read_len = 0;

  if (argc != 3) {
    printf("Usage: %s <IP> <port> \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    error_handling("socket() error");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handling("connect() error");
  }

  while ((read_len = read(sock, &msg[idx++], 1))) {
    if (read_len == -1) {
      error_handling("read() error");
    }

    str_len += read_len;
  }

  printf("Message from server: %s \n", msg);
  printf("Function read call count: %d \n", str_len);

  close(sock);
  return 0;
}
