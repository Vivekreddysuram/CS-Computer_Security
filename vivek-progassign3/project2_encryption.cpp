
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

    std::string openssl_command = "openssl rsautl -encrypt -pubin -inkey " + std::string(argv[2]) + " -in " + std::string(argv[1]) + " -raw -hexdump -out symmetric.txt";
    system(openssl_command.c_str());

    openssl_command = "openssl enc -aes-256-cbc -salt -in plaintext.txt -out encrypted.txt -pass file:symmetric.txt";
    system(openssl_command.c_str());

    openssl_command = "openssl dgst -sha256 -sign " + std::string(argv[3]) + " -out signedcipher encrypted.txt";
    system(openssl_command.c_str());

    return 0;
}
