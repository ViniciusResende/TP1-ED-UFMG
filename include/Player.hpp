#ifndef HAND_DEFAULT_SIZE
#define HAND_DEFAULT_SIZE 5
#endif

#ifndef PLAYERH
#define PLAYERH

#include "memlog.h"
#include <string>

#include "Card.hpp"

class Player {
  public:  
    Player();
    Player(std::string name, double initialMoney, Card initialHand[HAND_DEFAULT_SIZE]);

    void setPlayerHand(Card initialHand[HAND_DEFAULT_SIZE]);
    Card getPlayerCardByIndex(int idx);
    void setMoney(double value);
    double getMoney();

    ~Player();

  private:
    static int _id;
    int id;
    std::string name;
    double money;
    Card hand[HAND_DEFAULT_SIZE];
};

#endif
