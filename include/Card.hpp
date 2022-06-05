#ifndef CARDRH
#define CARDRH

#include "memlog.h"
#include <string>

/**
 * @brief Util function that is defined as a Macro, and is used to switch two objects
 * of the class.
 */
#define SwapCard(A, B) { Card c = A; A = B; B = c; };

class Card {
  public:  
    Card();
    /**
     * @brief Default constructor for Card class instance 
     *
     * @param cardNumber Number of the card, from 1 (ace) to 13 (king)
     * @param cardSuit Suit of the card, Spades(E), Clubs(P), Hearths(C), Diamonds(O)
     */
    Card(int cardNumber, char cardSuit);

    /**
     * @brief Returns the number associated with the card instance.
     *
     * @return return the value of the class attribute "cardNumber" (1 - 13)
     */
    int getCardNumber();
    /**
     * @brief Returns the number associated with the card suit.
     *
     * @return return the value of the class attribute "cardSuit" (C, E, P or O)
     */
    char getCardSuit();
    /**
     * @brief Prints the card into console, follows the format of: cardNumber followed by cardSuit and an empty space " ". 
     */
    void printCard();
    /**
     * @brief Implements overload of logical operator minor ('<').
     * That will be used to order objects of the class.
     *
     * @param other Instance of another object of the class.
     * @return Returns true when the current object is 'minor' than other and 
     * returns false when the current object is 'greater' than other.
     */
    bool operator<(Card other);
    /**
     * @brief Implements overload of logical operator greater ('>').
     * That will be used to order objects of the class.
     *
     * @param other Instance of another object of the class.
     * @return Returns true when the current object is 'greater' than other and 
     * returns false when the current object is 'minor' than other.
     */
    bool operator>(Card other);
    /**
     * @brief Implements overload of logical operator equals ('==').
     * That will be used to compare objects of the class.
     *
     * @param other Instance of another object of the class.
     * @return Returns true when the current object is 'equal' other and 
     * returns false when the current object is 'different' from other.
     */
    bool operator==(Card other);

    /**
     * @brief Default destructor of the class, that will clean it up when called.
     */
    ~Card();

  private:
    static int _id;
    int id;
    int cardNumber;
    static char avaliableSuits[4];
    char cardSuit;
};

#endif

#ifndef HEARTHS
#define HEARTHS 'C'
#endif

#ifndef SPADE
#define SPADE 'E'
#endif

#ifndef DIAMONDS
#define DIAMONDS 'O'
#endif

#ifndef CLUBS
#define CLUBS 'P'
#endif