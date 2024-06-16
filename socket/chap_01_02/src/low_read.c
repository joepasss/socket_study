/*
 * 파일 읽기
 *
 * #include <unistd.h>
 *
 * ssize_t read(int fd, void *buf, size_t nbytes);
 * -> 성공 시 수신한 바이트 수(파일의 끝을 만나면 0), 실패 시 -1 반환
 */

#include "error_handling.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char **argv) {
  printf("HELLO CHAP_01_02 \"low_read\" \n");

  int fd;
  char buf[BUF_SIZE];

  fd = open("data.txt", O_RDONLY);
  if (fd == -1) {
    error_handling("open() failed...");
  }

  printf("file descriptor: %d \n", fd);

  if (read(fd, buf, sizeof(buf)) == -1) {
    error_handling("read() failed...");
  }

  printf("file data: %s", buf);
  close(fd);

  return 0;
}
