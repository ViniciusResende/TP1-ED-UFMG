#ifndef LISTH
#define LISTH

#include <string>

#include "memlog.h"
#include "ListCell.hpp"
#include "Player.hpp"

class ListCell;
class List {
  public:  
    List();

    int length();
		Player* warmUpList();
		Player* getElement (int idx);
		void setElement(int idx, Player* value);
    void pushFront(Player* value);
    void pushBack(Player* value);
    void pushPosition(int idx, Player* value);
    Player* popFront();
    Player* popEnd();
    Player* popPosition(int idx);
    Player* searchByName(std::string playerName);
    // void forEach(void (callback)(Player*));
    void forEachPlayerReduceMoney(int amount);

    ~List();

  private:
    static int _id;
    int id;
    int size;
    ListCell* head;
    ListCell* tail;

    ListCell* setPosition(int idx, bool before);
};

#endif
