#include "gcp_server.h"
#include <stdio.h>

int
main ()
{
  ServerObject *gcp_server = server_object_new ();

  GMainLoop *loop;
  loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

  return 0;
}
