#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/binary.h"

#define KUBE_CONFIG_TEMPFILE_NAME_TEMPLATE "/tmp/kubeconfig-XXXXXX"

static bool is_cert_or_key_base64_encoded(const char* data)
{
    if (NULL == strstr(data, "BEGIN")) {
        return true;
    } else {
        return false;           // e.g. "-----BEGIN CERTIFICATE-----\n...\n-----END CERTIFICATE-----"
    }
}

char* kubeconfig_mk_cert_key_tempfile(const char* data)
{
    static char fname[] = "kubeconfig_mk_tempfile()";

    const char* cert_key_data = NULL;
    int cert_key_data_bytes = 0;

    bool is_data_base64_encoded = is_cert_or_key_base64_encoded(data);
    if (true == is_data_base64_encoded) {
        int decoded_bytes = 0;
        char* b64decode = base64decode(data, strlen(data), &decoded_bytes);
        if (!b64decode || 0 == decoded_bytes) {
            fprintf(stderr, "%s: Base64 decodes failed.\n", fname);
            return NULL;
        }
        cert_key_data = b64decode;
        cert_key_data_bytes = decoded_bytes;
    } else {                    // plain text, no need base64 decode
        cert_key_data = data;
        cert_key_data_bytes = strlen(cert_key_data);
    }

    char tempfile_name_template[] = KUBE_CONFIG_TEMPFILE_NAME_TEMPLATE;
    int fd = mkstemp(tempfile_name_template);
    if (-1 == fd) {
        fprintf(stderr, "%s: Creating temp file for kubeconfig failed with error [%s]\n", fname, strerror(errno));
        return NULL;
    }

    int rc = write(fd, cert_key_data, cert_key_data_bytes);
    close(fd);
    if (true == is_data_base64_encoded && cert_key_data) {
        free((char*)cert_key_data);   // cast "const char *" to "char *" 
        cert_key_data = NULL;
    }
    if (-1 == rc) {
        fprintf(stderr, "%s: Writing temp file failed with error [%s]\n", fname, strerror(errno));
        return NULL;
    }

    return strdup(tempfile_name_template);
}

void kubeconfig_rm_tempfile(const char* filename)
{
    if (filename) {
        unlink(filename);
    }
}