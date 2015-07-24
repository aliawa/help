

#include <openssl/ssl.h>


int SSL_CTX_set_ssl_version(SSL_CTX *ctx, const SSL_METHOD *method);

int SSL_set_ssl_method(SSL *s, const SSL_METHOD *method);

const SSL_METHOD *SSL_get_ssl_method(SSL *ssl);



