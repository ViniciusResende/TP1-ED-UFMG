#ifndef MINIMUN_MONEY_AMOUNT_NEEDED
#define MINIMUN_MONEY_AMOUNT_NEEDED 50
#endif

#ifndef MAXIMUM_NUMBER_OF_WINNERS
#define MAXIMUM_NUMBER_OF_WINNERS 4
#endif

#ifndef MATCHH
#define MATCHH

#include <string>
#include <fstream>
#include "memlog.h"

#include "Card.hpp"
#include "Player.hpp"
#include "Vector.hpp"
#include "List.hpp"

class Match {
  public:  
    Match() : inMatchPlayers(nullptr), winners(nullptr) {};
    Match(int numberOfPlayers, int minimumAmountToPlay);

    void addPlayerToMatch(Player* player);
    void printMatch();
    void getGameResult(int totalPlayersInGame, std::ofstream &outFile);

    ~Match();
    Vector<Player*> *inMatchPlayers;
    List *winners;

  private:
    static int _id;
    int id;
    int minimumAmountToPlay;
    int totalMatchMoneyAmount;

    void setWinners(Player* winners[]);
    void getWinners();
    int getMaxHandInMatch();
    int playerTieBreaker(Player* currentWinner, Player* challengerOfWinner);
    int comparePlayersByCard(Player* firstPlayer, int firstPlayerCardIndexToCompare, Player* secondPlayer, int secondPlayerCardIndexToCompare);
};

#endif
