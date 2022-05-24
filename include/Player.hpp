#ifndef HAND_DEFAULT_SIZE
#define HAND_DEFAULT_SIZE 5
#endif

#ifndef PLAYERH
#define PLAYERH

#include "memlog.h"
#include <string>

#include "Vector.hpp"
#include "Card.hpp"

class Player {
  public:  
    Player();
    Player(std::string name, double initialMoney, Vector<Card> *initialHand);

    void setPlayerHand(Vector<Card> *initialHand);
    Card getPlayerCardByIndex(int idx);
    void setMoney(double value);
    double getMoney();
    std::string getName();

    ~Player();

  private:
    static int _id;
    int id;
    std::string name;
    double money;
    Vector<Card> *hand = new Vector<Card>(HAND_DEFAULT_SIZE);
};

#endif
