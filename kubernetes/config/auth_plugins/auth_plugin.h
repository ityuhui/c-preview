#ifndef _AUTH_PLUGIN_H
#define _AUTH_PLUGIN_H

typedef struct auth_plugin_t {
    char *name;
    int (*get_token)(kubeconfig_t*);
    bool (*is_expired)(kubeconfig_t*);
    int (*refresh)(kubeconfig_t*);
} auth_plugin_t;

auth_plugin_t* create_auth_plugin(const char *);
void free_auth_plugin(auth_plugin_t*);

#endif /* _AUTH_PLUGIN_H */