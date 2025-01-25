#include <iostream>
#include <bitset>
#include <sstream>
#include <string>

using namespace std;

string hexToBinary(const string& hex) {
    string binary;
    for (char hexChar : hex) {
        int value = (hexChar <= '9') ? (hexChar - '0') : (toupper(hexChar) - 'A' + 10);
        for (int i = 3; i >= 0; --i) {
            binary.push_back((value & (1 << i)) ? '1' : '0');
        }
    }
    return binary;
}

string binaryToHex(const string& binary) {
    stringstream ss;
    for (size_t i = 0; i < binary.length(); i += 4) {
        int value = 0;
        for (size_t j = 0; j < 4 && i + j < binary.length(); ++j) {
            value = value * 2 + (binary[i + j] - '0');
        }
        ss << hex << value;
    }
    return ss.str();
}

string generateKeystream() {
    
    return "10101010101010101010101010101010"; 
}

string xorBinaryStrings(const string& a, const string& b) {
    string result;
    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(((a[i] - '0') ^ (b[i] - '0')) + '0');
    }
    return result;
}

int main() {
    string hexMessage = "7e5d7fff";
    string binaryMessage = hexToBinary(hexMessage);
    
    string keystream = generateKeystream();
    
    string binaryCiphertext = xorBinaryStrings(binaryMessage, keystream);
    string hexCiphertext = binaryToHex(binaryCiphertext);
    cout << "Ciphertext (Hex): " << hexCiphertext << endl;
    
    string decryptedBinaryMessage = xorBinaryStrings(binaryCiphertext, keystream);
    string decryptedHexMessage = binaryToHex(decryptedBinaryMessage);
    cout << "Decrypted Message (Hex): " << decryptedHexMessage << endl;
    
    return 0;
}
