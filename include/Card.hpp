#ifndef HEARTHS
#define HEARTHS 'C'
#endif

#ifndef DIAMONDS
#define DIAMONDS 'O'
#endif

#ifndef CLUBS
#define CLUBS 'P'
#endif

#ifndef SPADE
#define SPADE 'E'
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
