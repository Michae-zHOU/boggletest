// Kyle Barron-Kraus <kbarronk>

#include <fstream>
#include <iostream>
#include <set>

#include "boggleplayer.h"
#include "StopWatch.hpp"

int main(int /* argc */, char ** /* argv */) {
    BogglePlayer bp;
    StopWatch<> sw;
    
    std::ifstream wordf("lex.txt");
    std::set<std::string> words;
    std::string word;
    while (wordf >> word)
        words.insert(word);

    std::ifstream boardf("brd.txt");
    int rows;
    int cols;
    boardf >> rows;
    boardf >> cols;

    std::string **board = new std::string*[rows];
    std::string pos;
    for (int row = 0; row < rows; row++) {
        board[row] = new std::string[cols];
        for (int col = 0; col < cols; col++) {
            boardf >> pos;
            board[row][col] = pos;
        }
    }

    std::cout << "Size of Lexicon: " << words.size() << " words" << std::endl;
    std::cout << "Size of Board: " << rows << "x" << cols << std::endl;
    std::cout << std::endl;

    std::cout << "Build Lexicon: " << std::flush;
    sw.start();
    bp.buildLexicon(words);
    std::cout << sw.elapsed() << " ms" <<std::endl;

    std::cout << "Build Board: " << std::flush;
    sw.start();
    bp.setBoard(rows, cols, board);
    std::cout << sw.elapsed() << " ms " << std::endl;
    
    std::set<std::string> all_words;

    std::cout << "getAllValidWords(): " << std::flush;
    sw.start();
    bp.getAllValidWords(2, &all_words);
    std::cout << sw.elapsed() << " ms " << std::endl;
    std::cout << "# Words Found: " << all_words.size() << std::endl;
    
    std::cout << "Repeated isOnBoard(): " << std::flush;
    sw.start();
    std::set<std::string> all_words2;
    for (auto it = words.begin(); it != words.end(); it++) {
        if (it->length() >= 2 && bp.isOnBoard(*it).size() != 0)
            all_words2.insert(*it);
    }
    std::cout << sw.elapsed() << " ms " << std::endl;
    std::cout << "# Words Found: " << all_words2.size() << std::endl;
    
    for (int row = 0; row < rows; row++) {
        delete[] board[row];
    }
    delete[] board;
    
    return EXIT_SUCCESS;
}