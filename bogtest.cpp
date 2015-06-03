/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  string wordA("a");
  string wordX("x");
  //lex.insert(wordA);
  //lex.insert("z");
  
  string word("bi");
  
  lex.insert("cak");
  lex.insert("ghm");
  lex.insert(word);
  lex.insert("dbc");
    
  string row0[] = {"D","C","e","f"};
  string row1[] = {"b","A","g","h"};
  string row2[] = {"i","k","l","m"};
  string* board[] = {row0,row1,row2};
  set<string> words;
  vector<int> locations;

  p->buildLexicon(lex);

  p->setBoard(3,4,board);
    
  if(!p->isInLexicon("cak")) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }
    
  if(!p->getAllValidWords(0,&words)) {
        std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
        return -1;
  }
    cout<<"heh"<<endl;
    set<string>::iterator it;
    for(it = words.begin();it==words.end();it++){
        cout<<*it<<endl;
    }
  
    return 0;
    
  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }

  if(p->isOnBoard(wordX).size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);
  if(locations.size() != 1 || locations[0] != 3) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  }
   
  
  if(!p->getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  }
    
  if(words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  }
    
  delete p;
  return 0;

}
