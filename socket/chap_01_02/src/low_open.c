/*
 * 파일 열기
 * #include <sys/types.h>
 * #include <sys/stat.h>
 * #include <fcntl.h>
 *
 * int open(const char *path, int flag);
 * -> 성공 시 파일 디스크럽터, 실패 시 -1 반환
 *
 * flag에 전달 가능한 값
 * O_CREATE   : 필요시 파일을 생성
 * O_TRUNC    : 기존 데이터 전부 삭제
 * O_APPEND   : 기존 데이터 보존하고, 뒤에 이어서 저장
 * O_RDONLY   : Read 전용으로 파일 오픈
 * O_WRONLY   : Write 전용으로 파일 오픈
 * O_RDWR     : Read, Write 가능하게 파일 오픈
 */

/*
 * 파일 닫기
 *
 * #include <unistd.h>
 *
 * int close(int fd);
 * -> 성공 시 0, 실패 시 -1 반환
 *
 * 파일 디스크럽터를 인자로 전달하면 해당 파일이 닫히게 된다.
 * 소켓을 닫을 때도 사용
 */

/*
 * 파일에 데이터 쓰기
 *
 * #include <unistd.h>
 *
 * ssize_t write(int fd, const void *buf, size_t nbytes);
 * -> 성공 시 전달한 바이트 수, 실패 시 -1 반환
 *
 * 리눅스에서는 파일과 소켓을 동일하게 취급하므로, 소켓에도 데이터를 쓸 수 있다
 *
 * size_t   = unsigned int
 * ssize_t  = signed int
 */

#include "error_handling.h"
#include <errno.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
  printf("HELLO CHAP_01_02 \n");

  int fd;
  char buf[] = "HELLO!\n";

  fd = open("data.txt", O_TRUNC | O_WRONLY | O_CREAT, 0644);
  if (fd == -1) {
    error_handling("open() failed...");
  }

  printf("file descriptor: %d\n", fd);

  if (write(fd, buf, sizeof(buf)) == -1) {
    error_handling("write() failed...");
  }

  close(fd);
  return 0;
}
