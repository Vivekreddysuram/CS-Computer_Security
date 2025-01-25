#include <iostream>
#include <bitset>

std::bitset<32> pBoxPermutation(const std::bitset<32>& input) {
    int pBoxTable[32] = {
        15, 6, 19, 20, 28, 11, 27, 16,
        0, 14, 22, 25, 4, 17, 30, 9,
        1, 7, 23, 13, 31, 26, 2, 8,
        18, 12, 29, 5, 21, 10, 3, 24
    };

    std::bitset<32> output;
    for (int i = 0; i < 32; ++i) {
        output[i] = input[pBoxTable[i]];
    }
    return output;
}

int main() {
    std::bitset<32> input("11010111001010001001011010100011"); 

    std::bitset<32> output = pBoxPermutation(input);

    std::cout << "P-box Output: " << output.to_string() << std::endl;

    return 0;
}
