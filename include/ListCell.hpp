#ifndef LISTCELLH
#define LISTCELLH

#include "memlog.h"
#include "List.hpp"
#include "Player.hpp"

class ListCell {
  public:  
    ListCell();

    ~ListCell();

  private:
    Player *value;
    ListCell *next;

  friend class List;
};

#endif
