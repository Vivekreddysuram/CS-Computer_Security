#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Define the initial fill values for X, Y, and Z registers
bitset<19> X("1010010011000011100");
bitset<22> Y("0011011100100001111011");
bitset<23> Z("11101010001110111000010");

// Function to perform majority voting
bool majority(bool x, bool y, bool z) {
    return (x & y) | (x & z) | (y & z);
}

// Function to clock the registers and generate one keystream bit
bool generateKeystreamBit() {
    // Perform majority voting
    bool maj = majority(X[8], Y[10], Z[10]);
    
    // Clock X register
    bool newX = (X[13] ^ X[16] ^ X[17] ^ X[18]) ^ maj;
    X = (X >> 1);
    X[18] = newX;
    
    // Clock Y register
    bool newY = (Y[20] ^ Y[21]) ^ maj;
    Y = (Y >> 1);
    Y[21] = newY;
    
    // Clock Z register
    bool newZ = (Z[7] ^ Z[20] ^ Z[21] ^ Z[22]) ^ maj;
    Z = (Z >> 1);
    Z[22] = newZ;
    
    // Generate keystream bit
    return X[18] ^ Y[21] ^ Z[22];
}

// Function to generate the next 32 keystream bits and print the registers' contents
void generateKeystream() {
    cout << "Initial contents of registers:" << endl;
    cout << "X: " << X << endl;
    cout << "Y: " << Y << endl;
    cout << "Z: " << Z << endl;
    cout << "Keystream bits:" << endl;
    for (int i = 0; i < 32; ++i) {
        cout << generateKeystreamBit();
    }
    cout << endl;
    cout << "Final contents of registers after generating 32 keystream bits:" << endl;
    cout << "X: " << X << endl;
    cout << "Y: " << Y << endl;
    cout << "Z: " << Z << endl;
}

// Function to encrypt or decrypt a message using the provided keystream
string processMessage(const string& message, const string& keystream) {
    string result = "";
    size_t keystreamIndex = 0;
    for (char c : message) {
        string bitstring = bitset<8>(c).to_string();
        string output_bitstring = "";
        for (int i = 0; i < 8; ++i) {
            bool keystream_bit = keystream[keystreamIndex++] == '1'; // Get the next keystream bit
            bool input_bit = bitstring[i] - '0';
            bool output_bit = input_bit ^ keystream_bit;
            output_bitstring += (output_bit ? "1" : "0");
        }
        result += static_cast<char>(bitset<8>(output_bitstring).to_ulong());
    }
    return result;
}

int main() {
    // (a) Generate next 32 keystream bits and print registers' contents
    generateKeystream();

    // (b) Encrypt the message 7e5d7fff
    string plaintext = "7e5d7fff";
    cout << "Original plaintext: " << plaintext << endl;

    // Generate the keystream for encryption
    string keystream;
    for (int i = 0; i < 32; ++i) {
        keystream += generateKeystreamBit() ? '1' : '0';
    }

    // Encrypt the plaintext
    string ciphertext = processMessage(plaintext, keystream);
    cout << "Ciphertext: ";
    for (char c : ciphertext) {
        printf("%02X", static_cast<unsigned char>(c));
    }
    cout << endl;

    // Decrypt the ciphertext (which should yield the original plaintext)
    string decrypted_plaintext = processMessage(ciphertext, keystream);
    cout << "Decrypted plaintext: " << decrypted_plaintext << endl;

    return 0;
}
