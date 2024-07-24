#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

// Function to read words from a file
std::vector<std::string> ReadWordsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

// Function to check if a word is in the dictionary and suggest corrections if not
void CheckSpelling(const std::vector<std::string> &document, const std::vector<std::string> &dictionary) {
    LinearProbing<std::string> hash_table;
    for (const auto &word : dictionary) {
        hash_table.Insert(word);
    }

    for (const auto &word : document) {
        int probes = 0;
        bool found = hash_table.Contains(word, probes);
        if (found) {
            std::cout << word << " is CORRECT\n";
        } else {
            std::cout << word << " is INCORRECT\n";
            // Suggest corrections (dummy implementation)
            std::cout << "** " << word << " -> correction1 ** case A\n";
            std::cout << "** " << word << " -> correction2 ** case B\n";
            std::cout << "** " << word << " -> correction3 ** case C\n";
        }
    }
}

// Wrapper function for spell checking
void testSpellingWrapper(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <document file> <dictionary file>\n";
        return;
    }

    std::string document_file = argv[1];
    std::string dictionary_file = argv[2];

    auto document = ReadWordsFromFile(document_file);
    auto dictionary = ReadWordsFromFile(dictionary_file);

    CheckSpelling(document, dictionary);
}
