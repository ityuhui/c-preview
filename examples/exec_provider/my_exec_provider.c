#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ENV_EXEC_CLIENT_CERTIFICATE_DATA "exec_client_certificate_data"
#define ENV_EXEC_CLIENT_PRIVATE_KEY "exec_client_private_key"

char token_template[] = "\
{\
  \"apiVersion\": \"client.authentication.k8s.io/v1beta1\",\
  \"kind\": \"ExecCredential\",\
  \"status\": {\
    \"token\": \"%s\"\
  }\
}";

char certificate_template[] = "\
{\
  \"apiVersion\": \"client.authentication.k8s.io/v1beta1\",\
  \"kind\": \"ExecCredential\",\
  \"status\": {\
    \"clientCertificateData\": \"%s\",\
    \"clientKeyData\": \"%s\"\
  }\
}";

int main(int argc, char *argv[])
{
    const char *clientCertificateData = secure_getenv(ENV_EXEC_CLIENT_CERTIFICATE_DATA);
    const char *clientPrivateKey = secure_getenv(ENV_EXEC_CLIENT_PRIVATE_KEY);

    if ((4 == argc) && argv[3]) {
        // token is passed by command line argument
        printf(token_template, argv[3]);
    } else if ((clientCertificateData) && strlen(clientCertificateData) > 0 && (clientPrivateKey) && strlen(clientPrivateKey) > 0) {
        // client certificate and private key are passed by environment variables
        printf(certificate_template, clientCertificateData, clientPrivateKey);
    } else {
        printf("Cannot get authentication data\n");
    }

    return 0;
}

