#include <iostream>
#include <bitset>

std::bitset<4> sBox1Substitution(const std::bitset<6>& input) {
    int sBox1[4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };
    int row = (input[5] << 1) | input[0];

    int column = (input[4] << 3) | (input[3] << 2) | (input[2] << 1) | input[1];

    int sBoxValue = sBox1[row][column];

    return std::bitset<4>(sBoxValue);
}

int main() {
    std::bitset<6> input("011011"); 

    std::bitset<4> output = sBox1Substitution(input);

    std::cout << "S-box Output: " << output << std::endl;

    return 0;
}
