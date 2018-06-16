#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include "st.h"

void* handle_connection(void* s_) {
  st_netfd_t s = s_;

  char buf[512];
  st_read(s, buf, sizeof(buf), ST_UTIME_NO_TIMEOUT);

  static char resp[] =
    "HTTP/1.0 200 OK\r\n"
    "Content-type: text/html\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<H2>It worked!</H2>\n";
  st_write(s, resp, sizeof(resp) - 1, ST_UTIME_NO_TIMEOUT);

  st_netfd_close(s);
  return 0;
}

int main() {
  int ev = st_set_eventsys(ST_EVENTSYS_ALT);
  // check if the event notification mechanism is Mac OS X one.
  if (ev != 0) {
      fprintf(stderr, "%d", ev);
      exit(1);
  }

  st_init();
  st_randomize_stacks(1);

  int ret, sock = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(8086);
  ret = bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  ret = listen(sock, 16);

  st_netfd_t server = st_netfd_open_socket(sock);

  for(;;) {
    st_netfd_t c = st_accept(server, NULL, 0, ST_UTIME_NO_TIMEOUT);
    st_thread_create(handle_connection, c, 0, 0);
  }
}