/* File name: boggleplayer.cpp
 * Authors: Jimmy Martinez and Ziyao Zhou
 * Date: May 18, 2015
 * Descrption: This file will be resonsible for implementing the
 *             baseboggleplayer class.
 */

#include "baseboggleplayer.h"
#include "boggleplayer.h"

#include <stdio.h>
#include <ctype.h>

using namespace std;

// Method implementations here

/**
 * Constructor for a boggle player object
 */
BogglePlayer :: BogglePlayer(){
    this -> board_built = false;
    this -> lexicon_built = false;
    this -> rows = 0;
    this -> cols = 0;
}


/**
 * Implementation of setboard method
 */
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols,
                      std::string **diceArray){
    this->rows = rows;
    this->cols = cols;
    for(unsigned int i=0; i<rows; i++){
        for(unsigned int j=0; j<cols; j++){
            std::string word = toLowercase(diceArray[i][j]);
            board.push_back(BoardPos(word));
        }
    }
    
    this->board_built = true;
}

/**
 * Set visited of every die in board to false
 */
void BogglePlayer::setBoardVisited(bool visited){
    for(unsigned long i=0; i<board.size(); i++)
        board[i].setVisited(visited);
}

/**
 * Implementation of isOnBoard
 */
std::vector<int> BogglePlayer::isOnBoard(const std::string &word_to_check){
    
    std::vector<int> location;
    unsigned int word_pos = 0;
    
    for(unsigned int row=0;row<rows;row++){
        for(unsigned int col=0;col<cols;col++){
            setBoardVisited(false);
            (void)findWord(row,col,word_to_check,word_pos, &location);
        }
    }
    
    return location;
}


/**
 * This method will convert a string to lowercase by iterating through
 * each character converting it to lowercase as it goes. After the 
 * character is converted, it will be added to a new string that will
 * hold all the converted characters in the string. This new string will
 * then be returned.
 */
string BogglePlayer::toLowercase(string oldString){
  int length = 0;   // will keep track of the length of the string
  string newString; // will hold the converted string to be returned
  string upChar;    // will hold the converted character to be added

  // loop through string converting each character to lowercase
  while(length < ((int)oldString.length())){
    // convert character
    upChar = tolower(oldString[length]);
    
    // add it to string
    newString = newString + upChar;
    
    // increase length counter
    length++;
  }

  // return new converted string
  return newString;
}

bool BogglePlayer::findWord(unsigned int row, unsigned int col, const std::string &word_to_check,
              unsigned int word_pos, vector<int> *positions){
    if(board[row*cols+col].getText() != word_to_check.substr(word_pos, board[row*cols+col].getText().length())){
        board[row*cols+col].setVisited(false);
        return false;
    }
    else{
        word_pos = word_pos + board[row*cols+col].getText().length();
        
        if(word_pos == word_to_check.size()){
            positions->push_back(row*cols+col);
            board[row*cols+col].setVisited(true);
            return true;
        }
        else{
            
            board[row*cols+col].setVisited(true);
            positions->push_back(row*cols+col);
            
            if(col>0 && board[row*cols+col-1].getVisited()==false &&
                            findWord(row,col-1,word_to_check,word_pos,positions)){
                return true;
            }
            if(col<cols-1 && board[row*cols+col+1].getVisited()==false &&
                            findWord(row,col+1,word_to_check,word_pos,positions)){
                return true;
            }
            if(row>0 && board[(row-1)*cols+col].getVisited()==false &&
                            findWord(row-1,col,word_to_check,word_pos,positions)){
                return true;
            }
            if(row<rows-1 && board[(row+1)*cols+col].getVisited()==false &&
                            findWord(row+1,col,word_to_check,word_pos,positions)){
                return true;
            }
            if(row>0 && col>0 && board[(row-1)*cols+col-1].getVisited()==false &&
                          findWord(row-1,col-1,word_to_check,word_pos,positions)){
                return true;
            }
            if(row>0 && col<cols-1 && board[(row-1)*cols+col+1].getVisited()==false &&
                          findWord(row-1,col+1,word_to_check,word_pos,positions)){
                return true;
            }
            if(row<rows-1 && col>0 && board[(row+1)*cols+col-1].getVisited()==false &&
                           findWord(row+1,col-1,word_to_check,word_pos,positions)){
                return true;
            }
            if(row<rows-1 && col<cols-1 && board[(row+1)*cols+col+1].getVisited()==false &&
                           findWord(row+1,col+1,word_to_check,word_pos,positions)){
                return true;
            }
        }
    }
    word_pos = word_pos - board[row*cols+col].getText().length();
    board[row*cols+col].setVisited(false);
    positions->pop_back();
    return false;
}


/**
 * Initializes the BogglePlayer's Lexicon using the supplied word
 * list. Words are inserted in a case-insensitive manner.
 */
void BogglePlayer::buildLexicon(const std::set<std::string> &word_list){
    set<string>::iterator word_begin; // to loop through all of the words
    set<string>::iterator word_end;   // will hold the ending of the words
 
    // initialize iterators to beginning and ending of the sequence
    word_begin = word_list.begin();
    word_end = word_list.end();
 
    // loop to go through the list of strings
    while(word_begin != word_end){
        
        std::string lowercase = toLowercase(*word_begin);
        
        // insert the word to the multiway trie
        multiway.insert(lowercase);
      
        cout<<"insert complete"<<endl<<endl;
        // move to next element in the sequence
        ++word_begin;
    }
    
    this->lexicon_built = true;
}


/**
 * Populates the supplied set with the words in the BogglePlayer's
 * lexicon that appear on the board and are longer than
 * minimum_word_length.
 *
 * Returns false if either the board or the lexicon has not been
 * initialized. Returns true otherwise.
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length,
                      std::set<std::string> *words){
    std::string word_matched;
    
    if(this->board_built == false|| this->lexicon_built == false){
        return false;
    }
  
    for(unsigned row = 0; row<rows ; row++){
        for(unsigned col=0; col<cols ; col++){
            setBoardVisited(false);
            cout<<board[row*cols+col].getText()<<" -board"<<endl;
            getWords( row, col, multiway.getroot(), word_matched, words, minimum_word_length);
        }
    }
    
    return true;
}

/**
 * Determines if the given word is in the BogglePlayer's lexicon.
 * The lexicon is searched in a case-insensitive fashion.
 *
 * Returns true if the word is in the lexicon, and false if not.
 */
bool BogglePlayer::isInLexicon(const std::string &word_to_check){
    std::string lowercase = toLowercase(word_to_check);
    return multiway.find(lowercase);
}

/**
 * Returns a custom board for the boggle ui. The board is loaded
 * from the file custboard.txt in the current working directory.
 * The input format is expected to follow that outlined in README_brd.
 */
void BogglePlayer::getCustomBoard(std::string **&new_board,
                    unsigned int *rows, unsigned int *cols){
}

void BogglePlayer::getWords(unsigned int row, unsigned int col, LexNode *cur, std::string
                            word_matched, std::set<std::string> *words, unsigned int minimum_word_length){
    
    std::map<char,LexNode*>::iterator it;
    
    if(!multiway.prefix(word_matched + board[row*cols+col].getText())){
        board[row*cols+col].setVisited(false);
        return;
    }
    else{
        word_matched.append(board[row*cols+col].getText());
        
        //cout<<word_matched<<" -match"<<endl;
        
        board[row*cols+col].setVisited(true);
        
        int size = board[row*cols+col].getText().size();
        
        for(int i=0; i<size; i++){
            
            // search for the character in map
            it = cur->getMap().find(board[row*cols+col].getText()[i]);
            
            cout<<it->first<<" -list "<<it->second<<endl;
            
            // current pointer goes down
            cur = it->second;
            
        }
        
        if(cur->getEndWord() && word_matched.length() >= minimum_word_length){
            cout<<word_matched<<" -match"<<endl;
            words->insert(word_matched);
        }
        
        // left
        if(col>0 && board[row*cols+col-1].getVisited()==false){
            getWords(row,col-1,cur,word_matched,words,minimum_word_length);
        }
        // right
        if(col<cols-1 && board[row*cols+col+1].getVisited()==false){
            getWords(row,col+1,cur,word_matched,words,minimum_word_length);
        }
        // up
        if(row>0 && board[(row-1)*cols+col].getVisited()==false){
            getWords(row-1,col,cur,word_matched,words,minimum_word_length);
        }

        // down
        if(row<rows-1 && board[(row+1)*cols+col].getVisited()==false){
            getWords(row+1,col,cur,word_matched,words,minimum_word_length);
        }
        // up-left
        if(row>0 && col>0 && board[(row-1)*cols+col-1].getVisited()==false){
            getWords(row-1,col-1,cur,word_matched,words,minimum_word_length);
        }
        // up-right
        if(row>0 && col<cols-1 && board[(row-1)*cols+col+1].getVisited()==false){
           getWords(row-1,col+1,cur,word_matched,words,minimum_word_length);
        }
        // down-left
        if(row<rows-1 && col>0 && board[(row+1)*cols+col-1].getVisited()==false){
           getWords(row+1,col-1,cur,word_matched,words,minimum_word_length);
        }
        // down-right
        if(row<rows-1 && col<cols-1 && board[(row+1)*cols+col+1].getVisited()==false){
           getWords(row+1,col+1,cur,word_matched,words,minimum_word_length);
        }
    }
    board[row*cols+col].setVisited(false);
}