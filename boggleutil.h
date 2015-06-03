// Kyle Barron-Kraus <kbarronk>

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <cctype>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>


/**
 * Class that represents a position on the Boggle Board.
 *
 * Each position contains its sanitized string that represents the
 * characters on that board position, as well as a boolean that
 * marks the board position as visited by a given search algorithm.
 */
class BoardPos {
  public:
    /**
     * Constructs a BoardPos with the given text. Text must have been
     * sanitized by the caller.
     */
    BoardPos(const std::string &text);

    /**
     * Returns the characters on this BoardPos.
     */
    const std::string &getText() const;
    
    /**
     * Returns whether this BoardPos has been visited or not.
     */
    bool getVisited() const;

    /**
     * Sets whether this BoardPos has been visited or not.
     */
    void setVisited(bool visited);

  private:
    /**
     * The characters that this BoardPos contains.
     */
    const std::string text;

    /**
     * Whether this BoardPos has been visited or not.
     */
    bool visited;
};

class LexNode {
    friend class Lexicon;
private:
    // Map of letters to the child LexNodes nodes corresponding to those letters
    std::map <char, LexNode *> children;
    
    // A field to indicate end of word
    bool endword;
    
public:
    LexNode(){
        this->endword = false;
    };
    
    
    std::map <char, LexNode *> getMap(){
        return children;
    }
    
    void setEndWord(bool end);
    
    bool getEndWord();
};

/**
 * Implement class for Trie
 */
class Lexicon {
private:
    // Pointer to the root of multiway-trie
    LexNode *root;
    
public:
    // Constructor
    Lexicon(){
        root = new LexNode();
    }
    
    LexNode* getroot(){
        return root;
    }
    bool prefix(std::string str);
    
    // Method to insert a word to Lexicon
    void insert (std::string &word);
    
    // Method to check if a word exists in the Lexicon
    bool find (std::string &word);

};




#endif // BOGGLEUTIL_H
