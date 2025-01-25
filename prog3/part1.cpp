#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>
#include <iostream>
#include <fstream>

// Function to extract and save the public key
void extract_public_key(X509* cert, const char* filename) {
    EVP_PKEY* pkey = X509_get_pubkey(cert);
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        std::cerr << "Unable to open file for writing public key\n";
        return;
    }
    PEM_write_PUBKEY(fp, pkey);
    fclose(fp);
    EVP_PKEY_free(pkey);
}

// Function to extract and save the private key
void extract_private_key(PKCS12* p12, const char* filename, const char* pass) {
    EVP_PKEY* pkey;
    X509* cert;
    STACK_OF(X509)* ca = nullptr;

    if (!PKCS12_parse(p12, pass, &pkey, &cert, &ca)) {
        std::cerr << "Error parsing PKCS12 file. Check password?\n";
        return;
    }

    FILE* fp = fopen(filename, "w");
    if (!fp) {
        std::cerr << "Unable to open file for writing private key\n";
        return;
    }
    PEM_write_PrivateKey(fp, pkey, nullptr, nullptr, 0, nullptr, nullptr);
    fclose(fp);

    EVP_PKEY_free(pkey);
    X509_free(cert);
    if (ca) sk_X509_pop_free(ca, X509_free);
}

int main() {
    const char* certfile = "your_certificate.pem";
    const char* p12file = "your_pkcs12_file.p12";
    const char* password = "your_p12_password";  // Adjust as necessary

    // Load the certificate
    FILE* fp = fopen(certfile, "r");
    if (!fp) {
        std::cerr << "Failed to open certificate file\n";
        return 1;
    }
    X509* cert = PEM_read_X509(fp, nullptr, nullptr, nullptr);
    fclose(fp);

    // Load the PKCS12 file
    fp = fopen(p12file, "r");
    if (!fp) {
        std::cerr << "Failed to open PKCS12 file\n";
        return 1;
    }
    PKCS12* p12 = d2i_PKCS12_fp(fp, nullptr);
    fclose(fp);

    // Extract and save the public key
    extract_public_key(cert, "pubkey.pem");

    // Extract and save the private key
    extract_private_key(p12, "privkey.pem", password);

    // Clean up
    X509_free(cert);
    PKCS12_free(p12);

    return 0;
}
