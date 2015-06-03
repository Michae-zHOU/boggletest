/* File name: boggleutil.cpp
 * Authors: Jimmy Martinez and Ziyao Zhou
 * Date: May 18, 2015
 * Descrption: This file will define all supported files and classes */

#include "boggleutil.h"
#include <iostream>

using namespace std;
/**
 * Constructs a BoardPos with the given text. Text must have been
 * sanitized by the caller.
 */
BoardPos::BoardPos(const std::string &text):text(text){
}

/**
 * Returns the characters on this BoardPos.
 */
const std::string& BoardPos::getText() const{
    return text;
}

/**
 * Returns whether this BoardPos has been visited or not.
 */
bool BoardPos::getVisited() const{
    return this->visited;
}

/**
 * Sets whether this BoardPos has been visited or not.
 */
void BoardPos::setVisited(bool visited){
    this->visited = visited;
}


void Lexicon::insert(std::string &word){
    LexNode* currNode = this->root;
    unsigned long i = 0;
    std::map<char,LexNode *>::iterator it;
    
    while(word[i]){
        
        it = currNode->children.find(word[i]);

        if(it == currNode->children.end()){
            LexNode* aNode = new LexNode();
            currNode->children.insert(std::make_pair(word[i],aNode));
            currNode = aNode;
        }
        if(word.size() == i+1){
            currNode->setEndWord(true);
            break;
        }
        
        i++;
    }
}

bool Lexicon::find(std::string &word){
    LexNode* currNode = this->root;
    unsigned long i = 0;
    std::map<char,LexNode *>::iterator it;
    
    while(word[i]){
        it = currNode->children.find(word[i]);
        if(it == currNode->children.end()){
            return false;
        }
        
        currNode = it->second;
        
        if(word.size() == i+1){
            break;
        }
        i++;
    }
    
    if(currNode->getEndWord() == true){
        return true;
    }
    else{
        return false;
    }
}

bool Lexicon::prefix(std::string str){
    LexNode* currNode = root;
    
    for(unsigned long size=0; size!=str.size(); size++){
        char currChar = str[size];
        
        if(currNode->getMap()[currChar] != 0)
            currNode = currNode->getMap()[currChar];
        else
            return false;
    }
    
    if(currNode != 0)
        return true;
    else
        return false;
}

void LexNode::setEndWord(bool end){
    this->endword = end;
}

bool LexNode::getEndWord(){
    return this->endword;
}

