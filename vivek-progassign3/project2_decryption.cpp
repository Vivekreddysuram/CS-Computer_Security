
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <encrypted_message_file> <public.pem> <privatekey.pem>\n";
        return 1;
    }

    std::string openssl_command = "openssl dgst -sha256 -verify " + std::string(argv[2]) + " -signature " + std::string(argv[1]) + " encrypted.txt";
    system(openssl_command.c_str());

    openssl_command = "openssl enc -d -aes-256-cbc -in encrypted.txt -out decrypted.txt -pass file:" + std::string(argv[3]);
    system(openssl_command.c_str());

    return 0;
}
