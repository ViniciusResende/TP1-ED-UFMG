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
    /**
     * @brief Default constructor for Player class instance 
     *
     * @param name Name of the current player
     * @param initialMoney Money that player will start the game with
     * @param initialHand Initial hand of cards that the player will start at its first match (Data Structure Type: Vector<Card>(5))
     * @param playerBet Bet made by the player at its first match
     */
    Player(std::string name, double initialMoney, Vector<Card> *initialHand, int playerBet);

    /**
     * @brief Setter function that is responsible for change the current card hand of player.
     *
     * @param handOfCards Hand of cards that the player will use in its next match (Data Structure Type: Vector<Card>(5))
     */
    void setPlayerHand(Vector<Card> *handOfCards);
    /**
     * @brief Getter function that is responsible for return a object of class Card 
     * that references a certain index of player hand.
     *
     * @param idx Index of card required in player hand.
     * @return Object of Card class that references idx of player hand.
     */
    Card getPlayerCardByIndex(int idx);
    /**
     * @brief Setter function responsible to edit player money attribute to a new value passed as parameter. 
     *
     * @param value New value to be assigned as player money.
     */
    void setMoney(double value);
    /**
     * @brief Function responsible to increase player money attribute by a value passed as parameter. 
     *
     * @param value Value to be increased at player money.
     */
    void increaseMoneyBy(double value);
    /**
     * @brief Function responsible to decrease player money attribute by a value passed as parameter. 
     *
     * @param value Value to be decreased at player money.
     */
    void decreaseMoneyBy(double value);
    /**
     * @brief Getter function responsible for returning the current money of a player. 
     *
     * @return Returns the value of the player money attribute.
     */
    double getMoney();
    /**
     * @brief Getter function responsible for returning the name of a player. 
     *
     * @return Returns the value of the player name attribute.
     */
    std::string getName();
    /**
     * @brief Setter function responsible to edit player playerBet attribute to a new value passed as parameter. 
     *
     * @param value New value to be assigned as player playerBet.
     */
    void setPlayerBet(int value);
    /**
     * @brief Getter function responsible for returning the current bet of a player. 
     *
     * @return Returns the value of the player playerBet attribute.
     */
    int getPlayerBet();
    /**
     * @brief Prints the player info into console, its attributes, and cards. 
     */
    void printPlayer();
    /**
     * @brief Function responsible for iterating over the player hand of cards and 
     * return an integer that references a certain game made by Poker cards. 
     * Besides, this returned value is also attributed to gameInHand player attribute.
     *
     * @return Returns the integer value of game in hand. 
     * [0: HIGH_CARD, 1: ONE_PAIR, 2: TWO_PAIRS, 3: THREE_KIND, 4: STRAIGHT, 5: FLUSH, 6: FULL_HOUSE, 7: FOUR_KIND, 8: STRAIGHT_FLUSH, 9: ROYAL_STRAIGHT_FLUSH]
     */
    int getGameInHand();
    int gameInHand = -1;
    /**
     * @brief Function responsible for returning a label that references the player's current game in hand. 
     *
     * @return Returns the label for game in hand.
     * [HC: HIGH_CARD, OP: ONE_PAIR, TP: TWO_PAIRS, TK: THREE_KIND, S: STRAIGHT, F: FLUSH, FH: FULL_HOUSE, FK: FOUR_KIND, SF: STRAIGHT_FLUSH, RSF: ROYAL_STRAIGHT_FLUSH, ERR: UNDEFINED_GAME]
     */
    const char* getGameLabel();

    bool operator<(const Player& other);

    /**
     * @brief Default destructor of the class, that will clean it up when called.
     */
    ~Player();

  private:
    static int _id;
    int id;
    std::string name;
    double money;
    int playerBet;
    Vector<Card> *hand = new Vector<Card>(HAND_DEFAULT_SIZE);

    /**
     * @brief Function responsible for iterating over the player hand of cards and 
     * return a boolean value that informs if there is a straight sequence in players hand. 
     *
     * @return Returns true if there is a straight sequence in players hand, and false if it's not. 
     */
    bool verifyStraight();
    /**
     * @brief Function responsible for iterating over the player hand of cards and 
     * return an integer that references a certain type of flush in a game of Poker. 
     * Besides, this returned value is also attributed to gameInHand player attribute.
     *
     * @return Returns the integer value of game in hand. 
     * [5: FLUSH, 8: STRAIGHT_FLUSH, 9: ROYAL_STRAIGHT_FLUSH]
     */
    int handleFlush();
    /**
     * @brief Function responsible for iterating over the player hand of cards and 
     * return an integer that references a certain type of repetition of cards (or no repetition) in a game of Poker. 
     * Besides, this returned value is also attributed to gameInHand player attribute.
     *
     * @return Returns the integer value of game in hand. 
     * [0: HIGH_CARD, 1: ONE_PAIR, 2: TWO_PAIRS, 3: THREE_KIND, 7: FOUR_KIND]
     */
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