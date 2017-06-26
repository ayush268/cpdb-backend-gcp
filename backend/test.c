#include "gcp.h"
#include <stdio.h>
// #include <string.h>

int
main (int argc, char **argv)
{
  GCPObject *gcp = gcp_object_new ();
  GError *error = NULL;
  gchar *access_token = g_malloc (150);
  gint expires_in;
  gboolean res = get_access_token (&access_token, &expires_in, &error);
  g_assert (res == TRUE);
  // g_print ("%ld\n", strlen (access_token));
  // if (get_access_token (&access_token, &expires_in, &error))
  //   g_print ("%s\n", access_token);
  // else
  //   g_print ("get_access_token() failed!\n");
  // GList *printers = gcp_object_get_printers (gcp, access_token);

  GHashTableIter iter;
  gpointer key, value;

  // give "ALL" as third param to get a list of all printers intead of only active printers
  // give NULL as third param to get a list of only active printers
  GHashTable *printers = gcp_object_get_printers (gcp, access_token, "ALL");


  // while(printers != NULL)
  // {
    // g_print ("%s\n", (gchar *)printers->data);
    // printers = printers->next;
  // }


  g_hash_table_iter_init (&iter, printers);
  while (g_hash_table_iter_next (&iter, &key, &value))
  {
      g_print ("%s => %s\n\n", (gchar *)key, (gchar *)value);
  }

  gchar *uid = g_malloc (50);
  g_print ("Enter uid of printer to get printer options:\n");
  scanf ("%s", uid);
  // g_print ("%s\n", uid);
  // const gchar *uid = "__google__docs";
  GHashTable *printer_options = gcp_object_get_printer_options (gcp, uid, access_token);
  g_assert (printer_options != NULL);
  g_hash_table_iter_init (&iter, printer_options);
  while (g_hash_table_iter_next (&iter, &key, &value))
  {
      GList *values = (GList *)value;
      g_print ("%s\n", (gchar *)key);
      while (values != NULL)
      {
        g_print ("\t%s\n", (gchar *)values->data);
        values = values->next;
      }
      g_print ("\n\n");
  }


  // g_print ("%s\n", printer_options);

  g_object_unref (gcp);
  return 0;
}
