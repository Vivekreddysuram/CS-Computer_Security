#include <iostream>
#include <bitset>
#include <vector>
#include <string>

std::bitset<48> expansionPermutation(const std::bitset<32>& input) {
    std::bitset<48> expanded;
    for (std::size_t i = 0; i < 48; ++i) {
        expanded[i] = input[i % 32];
    }
    return expanded;
}

std::bitset<32> sBoxSubstitution(const std::bitset<48>& input) {
    std::bitset<32> output;
    for (std::size_t i = 0; i < 8; ++i) {
        std::bitset<6> sixBits = (input.to_ullong() >> (42 - 6 * i)) & 0x3F;
        std::bitset<4> fourBits = (sixBits.to_ulong() % 16);
        output |= (fourBits.to_ulong() << (28 - 4 * i));
    }
    return output;
}

std::bitset<32> pBoxPermutation(const std::bitset<32>& input) {
    std::bitset<32> permuted;
    for (std::size_t i = 0; i < 32; ++i) {
        permuted[31 - i] = input[i];
    }
    return permuted;
}

std::vector<std::bitset<48>> generateSubkeys(const std::bitset<64>& key) {
    std::vector<std::bitset<48>> subkeys(16);
    for (std::size_t i = 0; i < 16; ++i) {
        std::bitset<48> subkey(i + 1);
        subkeys[i] = subkey;
    }
    return subkeys;
}

std::bitset<32> desFunction(std::bitset<32> R, const std::bitset<48>& subkey) {
    std::bitset<48> expandedR = expansionPermutation(R);
    std::bitset<48> xored = expandedR ^ subkey;
    std::bitset<32> sBoxOutput = sBoxSubstitution(xored);
    std::bitset<32> finalOutput = pBoxPermutation(sBoxOutput);
    return finalOutput;
}

std::bitset<64> desRound(std::bitset<64> input, const std::bitset<48>& subkey) {
    std::bitset<32> left(input.to_ullong() >> 32);
    std::bitset<32> right(input.to_ullong());
    std::bitset<32> newRight = desFunction(right, subkey) ^ left;
    return (std::bitset<64>(newRight.to_ulong()) << 32) | std::bitset<64>(right.to_ulong());
}

std::vector<std::bitset<64>> stringToBitsets(const std::string& str) {
    std::vector<std::bitset<64>> blocks;
    std::bitset<64> currentBlock;
    int bitIndex = 0;

    for (char c : str) {
        for (int i = 7; i >= 0; --i) {
            currentBlock[bitIndex++] = ((c >> i) & 1);
            if (bitIndex == 64) {
                blocks.push_back(currentBlock);
                currentBlock.reset();
                bitIndex = 0;
            }
        }
    }

    if (bitIndex > 0) {
        blocks.push_back(currentBlock);
    }

    return blocks;
}

std::vector<std::bitset<64>> desEncrypt(const std::vector<std::bitset<64>>& plaintextBlocks, const std::vector<std::bitset<48>>& subkeys) {
    std::vector<std::bitset<64>> encryptedBlocks;
    for (const auto& block : plaintextBlocks) {
        std::bitset<64> currentBlock = block;
        for (int i = 0; i < 16; ++i) {
            currentBlock = desRound(currentBlock, subkeys[i]);
        }
        encryptedBlocks.push_back(currentBlock);
    }
    return encryptedBlocks;
}

std::vector<std::bitset<64>> desDecrypt(const std::vector<std::bitset<64>>& encryptedBlocks, const std::vector<std::bitset<48>>& subkeys) {
    std::vector<std::bitset<64>> decryptedBlocks;
    for (const auto& block : encryptedBlocks) {
        std::bitset<64> currentBlock = block;
        for (int i = 15; i >= 0; --i) {
            currentBlock = desRound(currentBlock, subkeys[i]);
        }
        decryptedBlocks.push_back(currentBlock);
    }
    return decryptedBlocks;
}

std::string bitsetsToString(const std::vector<std::bitset<64>>& blocks) {
    std::string str;
    for (const auto& block : blocks) {
        for (int i = 0; i < 64; i += 8) {
            char c = 0;
            for (int j = 0; j < 8; ++j) {
                c |= ((block.test(i + 7 - j)) ? 1 : 0) << j;
            }
            str += c;
        }
    }
    return str;
}

int main() {
    std::string hexKey, asciiPlaintext;

    std::cout << "Enter the key in hexadecimal format: ";
    std::getline(std::cin, hexKey);
    std::bitset<64> key(std::stoull(hexKey, nullptr, 16));

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, asciiPlaintext);

    std::vector<std::bitset<48>> subkeys = generateSubkeys(key);
    std::vector<std::bitset<64>> plaintextBlocks = stringToBitsets(asciiPlaintext);
    std::vector<std::bitset<64>> encryptedBlocks = desEncrypt(plaintextBlocks, subkeys);

    std::cout << "Encrypted blocks (as unsigned long long for demonstration):" << std::endl;
    for (const auto& block : encryptedBlocks) {
        std::cout << block.to_ullong() << std::endl;
    }

    std::vector<std::bitset<64>> decryptedBlocks = desDecrypt(encryptedBlocks, subkeys);
    std::string decryptedMessage = bitsetsToString(decryptedBlocks);

    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}
