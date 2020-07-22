#ifndef _SIMPLE_HTTP_CLIENT_H
#define _SIMPLE_HTTP_CLIENT_H

#ifdef  __cplusplus
extern "C" {
#endif

    int shc_get_request(const char *, const sslConfig_t *);

#ifdef  __cplusplus
}
#endif
#endif                          /* _SIMPLE_HTTP_CLIENT_H */