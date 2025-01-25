#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

/********************************************/
/* Tables for initial and final permutation */
/********************************************/
// Define the permutation table P
char P[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Define the inverse permutation table IP_inverse
char IP_inverse[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

/*******************************/
/* Tables for the key schedule */
/*******************************/

// PC-1 table (initial key permutation)
char PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// PC-2 table (permutation for generating each subkey)
char PC2[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

char shift[16] = {
    1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1
};

/*********************************/
/* Tables for the round function */
/*********************************/

// expansion box
char E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Define S-box S
char S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Permutation function P used after S-box substitution
char Pbox[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};


/***********************************/
/* Permute functions for the keys */
/***********************************/

// Permute function for key
void permute_key(char* key, char* result) {
    for (int i = 0; i < 56; ++i)
        result[i] = key[PC1[i] - 1];
}

// Permute function for subkeys
void permute_subkey(char* key, int round, char* result) {
    for (int i = 0; i < 48; ++i)
        result[i] = key[(round * 2 + i - shift[round]) % 28];
}

/**************************************/
/* Functions for the Feistel rounds  */
/**************************************/

// Function to expand the input
void expand(char* input, char* result) {
    for (int i = 0; i < 48; ++i)
        result[i] = input[E[i] - 1];
}

// Function for XOR operation
void xor_operation(char* input1, char* input2, int size, char* result) {
    for (int i = 0; i < size; ++i)
        result[i] = (input1[i] != input2[i]) ? '1' : '0';
}

// Function to apply S-box substitution
void s_box(char* input, char* result) {
    for (int i = 0; i < 8; ++i) {
        int row = 2 * (input[i * 6] - '0') + (input[i * 6 + 5] - '0');
        int col = 8 * (input[i * 6 + 1] - '0') + 4 * (input[i * 6 + 2] - '0') + 2 * (input[i * 6 + 3] - '0') + (input[i * 6 + 4] - '0');
        int val = S[i][row][col];
        for (int j = 0; j < 4; ++j) {
            result[i * 4 + 3 - j] = (val % 2) + '0';
            val /= 2;
        }
    }
}

// Function to permute using P-box
void permute_pbox(char* input, char* result) {
    for (int i = 0; i < 32; ++i)
        result[i] = input[Pbox[i] - 1];
}

// Function for a single Feistel round
void feistel_round(char* input, char* subkey, char* result) {
    char expanded[48];
    expand(input, expanded);
    char temp[48];
    xor_operation(expanded, subkey, 48, temp);
    char after_sbox[32];
    s_box(temp, after_sbox);
    permute_pbox(after_sbox, result);
}

/************************************/
/* Encryption and decryption rounds */
/************************************/

// Function for encryption round
void encrypt_round(char* input, char* key, char* output) {
    char after_ip[64];
    for (int i = 0; i < 64; ++i)
        after_ip[i] = input[P[i] - 1];

    char left[32], right[32];
    memcpy(left, after_ip, 32);
    memcpy(right, after_ip + 32, 32);

    char subkeys[16][48];
    char permuted_key[56];
    permute_key(key, permuted_key);

    for (int round = 0; round < 16; ++round) {
        permute_subkey(permuted_key, round, subkeys[round]);
        char temp[32];
        memcpy(temp, right, 32);
        feistel_round(right, subkeys[round], right);
        xor_operation(left, right, 32, right);
        memcpy(left, temp, 32);
    }

    char combined[64];
    memcpy(combined, right, 32);
    memcpy(combined + 32, left, 32);

    for (int i = 0; i < 64; ++i)
        output[i] = combined[IP_inverse[i] - 1];
}

// Function for decryption round
void decrypt_round(char* input, char* key, char* output) {
    char after_ip[64];
    for (int i = 0; i < 64; ++i)
        after_ip[i] = input[P[i] - 1];

    char left[32], right[32];
    memcpy(left, after_ip, 32);
    memcpy(right, after_ip + 32, 32);

    char subkeys[16][48];
    char permuted_key[56];
    permute_key(key, permuted_key);

    for (int round = 15; round >= 0; --round) {
        permute_subkey(permuted_key, round, subkeys[round]);
        char temp[32];
        memcpy(temp, right, 32);
        feistel_round(right, subkeys[round], right);
        xor_operation(left, right, 32, right);
        memcpy(left, temp, 32);
    }

    char combined[64];
    memcpy(combined, right, 32);
    memcpy(combined + 32, left, 32);

    for (int i = 0; i < 64; ++i)
        output[i] = combined[IP_inverse[i] - 1];
}


int main() {
    // Example usage
    char plaintext_hex[] = "I am suram vivek reddy";
    char key_hex[] = "133457799BBCDFF1";

    // Convert hex to binary
    char plaintext_bin[65], key_bin[65];
    for (int i = 0; i < 16; ++i) {
        int val = (int)plaintext_hex[i];
        for (int j = 0; j < 4; ++j) {
            plaintext_bin[i * 4 + j] = (val % 2) + '0';
            val /= 2;
        }
    }
    plaintext_bin[64] = '\0';

    for (int i = 0; i < 16; ++i) {
        int val = (int)key_hex[i];
        for (int j = 0; j < 4; ++j) {
            key_bin[i * 4 + j] = (val % 2) + '0';
            val /= 2;
        }
    }
    key_bin[64] = '\0';

    cout << "Plaintext in binary: " << plaintext_bin << endl;
    cout << "Key in binary: " << key_bin << endl;

    // Perform encryption
    char encrypted[65];
    encrypt_round(plaintext_bin, key_bin, encrypted);
    encrypted[64] = '\0';
    cout << "Encrypted text (binary): " << encrypted << endl;

    // Perform decryption
    char decrypted[65];
    decrypt_round(encrypted, key_bin, decrypted);
    decrypted[64] = '\0';
    cout << "Decrypted text (binary): " << decrypted << endl;

    return 0;
}
