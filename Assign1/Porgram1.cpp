#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstring>

const int myDebug = 0;

void insertionSortDescending(std::vector<char>& letters, std::vector<int>& frequency, int n);
std::map<char, int> display_frequency_analysis(std::string ciphertext, int optionSelected);
void guess_key_decrypt_ciphertext(std::string ciphertext, std::vector<char> englishFreq, int optionSelected);
void decrypt_ciphertext_given_key(std::string ciphertext, std::string userKey);

void insertionSortDescending(std::vector<char>& letters, std::vector<int>& frequency, int n) {
    int i, key, j;
    char letterKey;

    for (i = 1; i < n; i++) {
        key = frequency[i];
        letterKey = letters[i];
        j = i - 1;

        while (j >= 0 && frequency[j] < key) {
            frequency[j + 1] = frequency[j];
            letters[j + 1] = letters[j];
            j = j - 1;
        } 
        frequency[j + 1] = key;
        letters[j + 1] = letterKey;
    } 
} 

std::map<char, int> display_frequency_analysis(std::string ciphertext, int optionSelected) {
    std::map<char, int> ciphertextFreq;

    for(int i = 0; i < 26; ++i) {
        ciphertextFreq['A' + i] = 0;
    }

    for(int i = 0; i < ciphertext.size(); ++i) {   
        if(isalpha(ciphertext[i]))
            ciphertextFreq[ciphertext[i]]++;
    }
    if(optionSelected == 1) {
        std::cout << "Ciphertext Frequency Analysis" << std::endl;

        for(auto const & element : ciphertextFreq) {
            std::cout << "Char =  " << element.first << " Count =  " << element.second << std::endl;
        }

    }

    return ciphertextFreq;
} 

void guess_key_decrypt_ciphertext(std::string ciphertext, std::vector<char> englishFreq, int optionSelected) {
    std::map<char, int> ciphertextFreq = display_frequency_analysis(ciphertext, optionSelected);
    std::vector<char> letters;
    std::vector<int> frequency;
    char oldKey[26];
    char bestKey[26];
    int t1 = 0;
    int t2 = 0;
    char key[26];
    char plaintext[ciphertext.size()];
    int wordCount = 0;
    int bestWordCount = 0;
    char* substring;
    char temp;
    std::string line;

    for(int i = 0; i < englishFreq.size(); ++i) {
        letters.push_back('A' + i);
        frequency.push_back(ciphertextFreq['A' + i]);
    }

    insertionSortDescending(letters, frequency, 26);

    for(int i = 0; i < 26; ++i) {
        oldKey[i] = englishFreq[i];
    } 
    while(t1 < 24) {   
        for(int i = 0; i < englishFreq.size(); ++i) {
            key[letters[i] - 'A'] = englishFreq[i];
        } 
        for(int i = 0; i < ciphertext.size(); ++i) {
            if(isalpha(ciphertext[i]))
                plaintext[i] = key[ciphertext[i] - 'A'];
        } 
        wordCount = 0;

        if(optionSelected == 1) {
            std::ifstream dict("dictionary.txt");
            dict.seekg(0, dict.beg);
            while(std::getline(dict, line, '\n')) {   
                substring = std::strstr(plaintext, line.data());

                while(substring) {
                    wordCount += line.length();
                    substring = std::strstr(&plaintext[substring - plaintext + 1], line.data());
                }
            }
            dict.clear();
        }

        if(wordCount > bestWordCount) {
            for(int i = 0; i < englishFreq.size(); ++i) {
                bestKey[i] = englishFreq[i];
            }
            bestWordCount = wordCount;
        }
        if(t2 == 24) {   
            for(int i = 0; i < englishFreq.size(); ++i) {
                englishFreq[i] = oldKey[i];
            } 
            t1++;
            t2 = t1;
        }

        temp = englishFreq[t2];
        englishFreq[t2] = englishFreq[t2 + 1];
        englishFreq[t2 + 1] = temp;

        t2++;
    } 
    std::cout << "Discovered the key" << std::endl;

    std::string keyString(key);
    decrypt_ciphertext_given_key(ciphertext, keyString);

} 

void decrypt_ciphertext_given_key(std::string ciphertext, std::string userKey) {
    std::string plaintext{ciphertext.begin(), ciphertext.end()};

    std::cout << "Decrypting ciphertext using key '" << userKey << "'\n" << std::endl;
    std::cout << "Decrypted ciphertext:" << std::endl;
    for(int i = 0; i < ciphertext.size(); ++i) {
        if(isalpha(ciphertext[i])) {
            plaintext[i] = userKey[ciphertext[i] - 'A'];
            std::cout << plaintext[i];
        }
    } 
    std::cout << std::endl;
} 

int main() {
    int optionSelected{}; 

    std::string ciphertext{};
    std::string userKey{};

    std::string english {"ETAOINSHRDLCUMWFGYPBVKJXQZ"};
    std::vector<char> englishFreq {english.begin(), english.end()};

    std::ifstream inFile{};
    std::stringstream strStream{};

    inFile.open("ciphertext.txt");
    strStream << inFile.rdbuf();
    ciphertext = strStream.str();

    inFile.close();

    std::cout << "\nOPTIONS" << std::endl;
    std::cout << "1.) Display the frequency analysis of ciphertext" << std::endl;
    std::cout << "2.) Random decrypted ciphertext using the key" << std::endl;
    std::cout << "3.) Decrypt ciphertext using the key" << std::endl;
    std::cout << "4.) Exit" << std::endl;

    std::cout << "\nPlease select an option (1, 2, 3, or 4): ";
    std::cin >> optionSelected;

    while(optionSelected != 4) {
        switch(optionSelected) {
            case 1:
                std::cout << "\nOption 1" << std::endl;
                display_frequency_analysis(ciphertext, optionSelected);
                break;
            case 2:
                std::cout << "\nOPTION 2" << std::endl;
                guess_key_decrypt_ciphertext(ciphertext, englishFreq, optionSelected);
                break;
            case 3:
                std::cout << "\nOPTION 3" << std::endl;
                std::cout << "Decrypting Using Key" << std::endl;
   
                std::cout << "Please enter your key: ";
                std::cin >> userKey;
                std::cout << std::endl;
                decrypt_ciphertext_given_key(ciphertext, userKey);

                break;
            default:
                std::cout << "Please select a valid option! (1, 2, 3, or 4)" << std::endl;
        }
        
        std::cout << "\nOPTIONS" << std::endl;
        std::cout << "1.) Display the frequency analysis of ciphertext" << std::endl;
        std::cout << "2.) Random decrypted ciphertext using the key" << std::endl;
        std::cout << "3.) Decrypt ciphertext using the key" << std::endl;
        std::cout << "4.) Exit" << std::endl;
        std::cout << "\nPlease select an option (1, 2, 3, or 4): ";
        std::cin >> optionSelected;
    } 

    return 0;
}