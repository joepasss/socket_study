/*
 * #include <sys/socket.h>
 * int socket(int domain, int type, int protocol);
 *
 * 성공 시, 파일 디스크럽터, 실패 시 -1 반환
 *
 * socket 함수로 소켓 생성 가능함
 */

/*
 * #include <sys/socket.h>
 * int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
 *
 * 성공 시 0, 실패 시 -1 반환
 * socket 함수로 생성된 소켓을 bind (initalize) 해주는 역할
 */

/*
 * #include <sys/socket.h>
 * int listen(int sockfd, int backlog);
 *
 * 성공 시 0, 실패 시 -1 반환
 * bind로 initalize된 소켓을 연결요청이 가능한 상태로 만듦
 */

/*
 * #include <sys/socket.h>
 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 *
 * 성공 시 파일 디스크럽터, 실패 시 -1 반환
 * 연결요청시 수락하는 함수
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

int main(int argc, char *argv[]) {
  int serv_sock, clnt_sock;

  struct sockaddr_in serv_addr, clnt_addr;
  socklen_t clnt_addr_size;

  char *message = "Hello world!";

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) {
    error_handling("socket() error!");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handling("bind() error");
  }

  if (listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }

  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

  if (clnt_sock == -1) {
    error_handling("accept() error");
  }

  write(clnt_sock, message, strlen(message));
  close(clnt_sock);
  close(serv_sock);

  return 0;
}
