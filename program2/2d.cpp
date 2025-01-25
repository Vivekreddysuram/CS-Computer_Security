#include <iostream>
#include <bitset>
#include <vector>
#include <array>

template<size_t N>
std::bitset<N> circularLeftShift(const std::bitset<N>& input, unsigned int shifts) {
    std::bitset<N> shifted = input;
    for (unsigned int i = 0; i < shifts; ++i) {
        bool leftmostBit = shifted[N - 1];
        shifted <<= 1;
        shifted[0] = leftmostBit;
    }
    return shifted;
}

std::vector<std::bitset<48>> generateSubkeys(const std::bitset<56>& key) {

    int PC1_Left[28] = {
        49, 42, 35, 28, 21, 14, 7,
        0, 50, 43, 36, 29, 22, 15,
        8, 1, 51, 44, 37, 30, 23,
        16, 9, 2, 52, 45, 38, 31
    };
    int PC1_Right[28] = {
        55, 48, 41, 34, 27, 20, 13,
        6, 54, 47, 40, 33, 26, 19,
        12, 5, 53, 46, 39, 32, 25,
        18, 11, 4, 24, 17, 10, 3
    };


    std::bitset<28> LK, RK;
    for (int i = 0; i < 28; ++i) {
        LK[i] = key[PC1_Left[i]];
        RK[i] = key[PC1_Right[i]];
    }

    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    int PC2[48] = {
        13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9,
        22, 18, 11, 3, 25, 7, 15, 6, 26, 19, 12, 1,
        12, 23, 2, 8, 18, 26, 1, 11, 22, 16, 4, 19,
        15, 20, 10, 27, 5, 24, 17, 13, 21, 7, 0, 3
    };

    std::vector<std::bitset<48>> subkeys;


    for (int round = 0; round < 16; ++round) {

        LK = circularLeftShift(LK, shifts[round]);
        RK = circularLeftShift(RK, shifts[round]);

        std::bitset<56> combined;
        for (int i = 0; i < 28; ++i) {
            combined[i] = RK[i];
            combined[i + 28] = LK[i];
        }

        std::bitset<48> subkey;
        for (int i = 0; i < 48; ++i) {
            subkey[i] = combined[PC2[i]];
        }

        subkeys.push_back(subkey);
    }

    return subkeys;
}

int main() {

    std::bitset<56> key(std::string("0001001100110100010101110111100110011011101111001101111111110001"));


    std::vector<std::bitset<48>> subkeys = generateSubkeys(key);

    for (int i = 0; i < subkeys.size(); ++i) {
        std::cout << "Subkey " << i + 1 << ": " << subkeys[i].to_string() << std::endl;
    }

    return 0;
}
