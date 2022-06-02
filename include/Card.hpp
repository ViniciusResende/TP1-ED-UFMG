#ifndef CARDRH
#define CARDRH

#include "memlog.h"
#include <string>

#define SwapCard(A, B) { Card c = A; A = B; B = c; };

class Card {
  public:  
    Card();
    Card(int cardNumber, char cardSuit);

    int getCardNumber();
    char getCardSuit();
    void printCard();
    bool operator<(Card other);
    bool operator>(Card other);
    bool operator==(Card other);


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