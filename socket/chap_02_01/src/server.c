/*
 *** 소켓의 프로토콜과 그에 따른 데이터 전송 특성
 *
 ** Protocol
 * => 통신 규약
 *
 ** 소켓의 생성
 * #include <sys/socket.h>
 *
 * int socket(int domain, int type, int protocol);
 * -> 성공 시 파일 디스크럽터, 실패 시 -1 반환
 * domain   : 소켓이 사용할 프로토콜 체계 정보 전달
 * type     : 소켓의 데이터 전송방식에 대한 정보 전달
 * protocol : 프로토콜 정보 전달
 */

/*
 ** Protocol family(domain)
 *
 * PF_INET  : IPv4
 * PF_INET6 : IPv6
 * PF_LOCAL : 로컬 통신을 위한 UNIX 프로토콜 체계
 * PF_PACKET: Low Level 소켓을 위한 프로토콜 체계
 * PF_IPX   : IPX 노벨 프로토콜 체계
 */

/*
 ** Type
 * => 소켓의 데이터 전송방식
 *
 * 연결지향형 소켓 (SOCK_STREAM)
 *  => 데이터를 순차적으로 전달함
 *
 * 비 연결지향형 소켓 (SOCK_DGRAM)
 *  => 순서의 상관 없이 전달
 */

/*
 ** protocol (세 번째 인자)
 *  => 하나의 프로토콜 체계 안에 데이터의 전송방식이 동일한 프로토콜이 둘 이상
 *존재하는 경우 사용
 *  => 소켓의 데이터 전송방식은 같지만, 그 안에서 프로토콜이 나뉘는 경우
 *  => IPv4 프로토콜 체계에서 동작하는 연결지향형 데이터 소켓(TCP 소켓)
 *    int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
 *
 *  => IPv4 프로토콜 체계에서 동작하는 비 연결지향형 데이터 소켓(UDP 소켓)
 *    int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
 */

#include "error_handling.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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
