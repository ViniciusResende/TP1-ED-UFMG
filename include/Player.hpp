#ifndef HAND_DEFAULT_SIZE
#define HAND_DEFAULT_SIZE 5
#endif

#ifndef PLAYERH
#define PLAYERH

#include "memlog.h"
#include <string>

#include "Vector.hpp"
#include "Card.hpp"

#define SwapPlayer(A, B) { Player* c = A; A = B; B = c; };

class Player {
  public:  
    Player();
    Player(std::string name, double initialMoney, Vector<Card> *initialHand, int playerBet);

    void setPlayerHand(Vector<Card> *initialHand);
    Card getPlayerCardByIndex(int idx);
    void setMoney(double value);
    void increaseMoneyBy(double value);
    void decreaseMoneyBy(double value);
    double getMoney();
    std::string getName();
    void setPlayerBet(int value);
    int getPlayerBet();
    void printPlayer();
    int getGameInHand();
    int gameInHand = -1;
    const char* getGameLabel();

    bool operator<(const Player& other);

    ~Player();

  private:
    static int _id;
    int id;
    std::string name;
    double money;
    int playerBet;
    Vector<Card> *hand = new Vector<Card>(HAND_DEFAULT_SIZE);

    int handleFlush();
    bool verifyStraight();
    int handleRepetitions();
};

#endif

#ifndef ROYAL_STRAIGHT_FLUSH
#define ROYAL_STRAIGHT_FLUSH 9
#endif

#ifndef STRAIGHT_FLUSH
#define STRAIGHT_FLUSH 8
#endif

#ifndef FOUR_KIND
#define FOUR_KIND 7
#endif

#ifndef FULL_HOUSE
#define FULL_HOUSE 6
#endif

#ifndef FLUSH
#define FLUSH 5
#endif

#ifndef STRAIGHT
#define STRAIGHT 4
#endif

#ifndef THREE_KIND
#define THREE_KIND 3
#endif

#ifndef TWO_PAIRS
#define TWO_PAIRS 2
#endif

#ifndef ONE_PAIR
#define ONE_PAIR 1
#endif

#ifndef HIGH_CARD
#define HIGH_CARD 0
#endif