#pragma once
#include "tvshow.h"
#include <iostream>
#include <cctype>

class TrieNode {
public:
    TrieNode* children[26];
    TVshow* show;

    TrieNode() : show(nullptr) {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    void insert(const std::string& name, TVshow* show) {
        TrieNode* current = root;

        for (char c : name) {
            // Convert the character to uppercase
            char uppercaseC = std::toupper(c);

            int index = uppercaseC - 'A';

            if (std::isspace(c)) {
                continue;
            }
            if (index < 0 || index >= 26) {
                continue;
            }

            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->show = show;
    }

    TVshow* find(const std::string& name) {
        TrieNode* current = root;

        for (char c : name) {
            // Convert the character to uppercase
            char uppercaseC = std::toupper(c);

            int index = uppercaseC - 'A';
            if (index < 0 || index >= 26 || !current->children[index]) {
                continue;
            }
            current = current->children[index];
        }

        return current->show;
    }

private:
    // Recursive function to delete nodes starting from the root
    void deleteTrie(TrieNode* node) {
        if (!node) {
            return;
        }

        for (int i = 0; i < 26; ++i) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }
};
