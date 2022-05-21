#ifndef HEARTHS
#define HEARTHS 'H'
#endif

#ifndef DIAMONDS
#define DIAMONDS 'D'
#endif

#ifndef CLUBS
#define CLUBS 'C'
#endif

#ifndef SPADE
#define SPADE 'S'
#endif

#ifndef CARDRH
#define CARDRH

#include "memlog.h"
#include <string>


class Card {
  public:  
    Card();
    Card(int cardNumber, char cardSuit);

    int getCardNumber();
    char getCardSuit();


    ~Card();

  private:
    static int _id;
    int id;
    int cardNumber;
    static char avaliableSuits[4];
    char cardSuit;
};

#endif
