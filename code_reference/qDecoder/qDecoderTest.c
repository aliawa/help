#include "qDecoder.h"

#define CONF_FILE		"repro.conf"

int main(void) {
  Q_Entry *conf;
  char *protocol, *host, *port, *user;

  /* Open configuration file */
  if(!(conf = qfDecoder(CONF_FILE))) qError("Configuration file(%s) not found.", CONF_FILE);

  /* Get variable */
  protocol = qfValue(conf, "enum-suffix");
  host     = qfValue(conf, "tls-domain");
  port     = qfValue(conf, "alg-address");
  user     = qfValue(conf, "cert-path");

  qfValueAdd(conf, "color", "black");
  qfValueRemove(conf, "log-level");
  qfSave(conf, "blu.conf");
  
  
  /* Print out */
  qContentType("text/plain");
  printf("Protocol : %s\n", protocol);
  printf("Host     : %s\n", host);
  printf("Port     : %s\n", port);
  printf("User     : %s\n", user);

  /* Deallocate parsed entries */
  qfFree(conf);

  return 0;
}
