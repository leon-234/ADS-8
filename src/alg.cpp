// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include <string>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file)
        return;
    std::string word;
    while (!file.eof()) {
        int ch = file.get();
        if (std::isalpha(ch) && ch < 128) {
            word += std::tolower(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
        tree.insert(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto data = tree.getData();
    std::sort(data.begin(), data.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;

            return a.first < b.first;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& p : data) {
        std::cout << p.first << " " << p.second << std::endl;
        if (out)
            out << p.first << " " << p.second << '\n';
    }
    out.close();
}
