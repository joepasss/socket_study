/*
 * #include <sys/socket.h>
 * int connect (int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
 * 성공 시 0, 싪패 시 -1 return
 *
 * 서버에 연결 요청을 진행하는 함수
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char **argv) {
  int sock, str_len;
  struct sockaddr_in serv_addr;
  char message[1024];

  if (argc != 3) {
    printf("Usage: %s <IP> <port>\n", argv[0]);
    exit(1);
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

  str_len = read(sock, message, sizeof(message) - 1);
  if (str_len == -1) {
    error_handling("read() error");
  }

  message[str_len] = '\0';

  printf("Message from server : %s \n", message);
  close(sock);
  return 0;
}
