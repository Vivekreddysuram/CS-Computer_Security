#include <iostream>
#include <bitset>
#include <vector>
#include <string>

std::bitset<48> expansionPermutation(const std::bitset<32>& input) {
    int expansionTable[48] = {
        31, 0, 1, 2, 3, 4,
        3, 4, 5, 6, 7, 8,
        7, 8, 9, 10, 11, 12,
        11, 12, 13, 14, 15, 16,
        15, 16, 17, 18, 19, 20,
        19, 20, 21, 22, 23, 24,
        23, 24, 25, 26, 27, 28,
        27, 28, 29, 30, 31, 0
    };

    std::bitset<48> output;
    for (int i = 0; i < 48; ++i) {
        output[i] = input[expansionTable[i]];
    }
    return output;
}

std::vector<std::bitset<64>> padMessage(const std::string& message) {

    size_t paddingLength = 8 - (message.size() % 8);
    paddingLength = paddingLength == 0 ? 8 : paddingLength;

    std::vector<std::bitset<64>> paddedBlocks;
    std::bitset<64> currentBlock;
    size_t blockIndex = 0;

    for (size_t i = 0; i < message.size(); ++i) {

        for (size_t bit = 0; bit < 8; ++bit) {
            currentBlock[blockIndex * 8 + bit] = (message[i] >> (7 - bit)) & 1;
        }
        blockIndex++;

        if (blockIndex == 8) {
            paddedBlocks.push_back(currentBlock);
            currentBlock.reset();
            blockIndex = 0;
        }
    }

    for (size_t i = 0; i < paddingLength; ++i) {
        for (size_t bit = 0; bit < 8; ++bit) {
            currentBlock[blockIndex * 8 + bit] = (paddingLength >> (7 - bit)) & 1;
        }
        blockIndex++;
    }

    paddedBlocks.push_back(currentBlock);

    return paddedBlocks;
}

int main(){

    std::string message = "Your message here";

    std::vector<std::bitset<64>> paddedMessage = padMessage(message);

    std::bitset<64> key(0x0A0B0C0D0E0F1011); 

    if (key.count() > 56) {
        std::cerr << "Error: Key length is greater than 56 bits" << std::endl;
        return 1;
    }

    for (auto& block : paddedMessage) {

        std::bitset<32> left(block.to_string().substr(0, 32), 0, 32);
        std::bitset<32> right(block.to_string().substr(32, 32), 0, 32);


        std::bitset<48> expandedRight = expansionPermutation(right);


        std::cout << "Expanded Block: " << expandedRight << std::endl;
    }

    return 0;
}

