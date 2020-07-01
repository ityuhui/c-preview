#ifndef _AUTH_PLUGIN_H
#define _AUTH_PLUGIN_H

typedef struct auth_plugin_t {
    char *name;
    bool (*get_token)();
    bool (*is_expired)();
    bool (*refresh)();
} auth_plugin_t;

auth_plugin_t* create_auth_plugin(const char *);
void free_auth_plugin(auth_plugin_t*);

#endif /* _AUTH_PLUGIN_H */