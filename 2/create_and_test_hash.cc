#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

// Function to test the hash table implementation
template <typename HashTable>
void TestHashTable(const std::vector<std::string> &words,
                   const std::vector<std::string> &queries, HashTable &hash_table) {
    for (const auto &word : words) {
        hash_table.Insert(word);
    }

    int number_of_elements = hash_table.getNumberOfElements();
    int size_of_table = hash_table.getSize();
    double load_factor = hash_table.getLoadFactor();
    int collisions = hash_table.getCollisions();
    double avg_collisions = hash_table.getAvgCollisions();

    std::cout << "number_of_elements: " << number_of_elements << "\n";
    std::cout << "size_of_table: " << size_of_table << "\n";
    std::cout << "load_factor: " << load_factor << "\n";
    std::cout << "collisions: " << collisions << "\n";
    std::cout << "avg_collisions: " << avg_collisions << "\n\n";

    for (const auto &query : queries) {
        int probes = 0;
        bool found = hash_table.Contains(query, probes);
        std::cout << query << " " << (found ? "Found" : "Not_Found") << " " << probes << "\n";
    }
}

// Wrapper function to test different hash table implementations
void testWrapperFunction(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <words file> <query file> <hash type> [<R-value>]\n";
        return;
    }

    std::string words_file = argv[1];
    std::string query_file = argv[2];
    std::string hash_type = argv[3];

    auto words = ReadWordsFromFile(words_file);
    auto queries = ReadWordsFromFile(query_file);

    if (hash_type == "linear") {
        LinearProbing<std::string> hash_table;
        TestHashTable(words, queries, hash_table);
    } else if (hash_type == "quadratic") {
        QuadraticProbing<std::string> hash_table;
        TestHashTable(words, queries, hash_table);
    } else if (hash_type == "double" && argc == 5) {
        int r_value = std::stoi(argv[4]);
        DoubleHashing<std::string> hash_table(r_value);
        TestHashTable(words, queries, hash_table);
    } else {
        std::cerr << "Invalid hash type or missing R-value for double hashing.\n";
    }
}
