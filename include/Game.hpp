#ifndef GAMEHH
#define GAMEHH

#include <string>

#include "memlog.h"

#include "Player.hpp"
#include "Match.hpp"
#include "Vector.hpp"
#include "List.hpp"

class Game {
  public:  
    List *inGamePlayers;
    Vector<Match> *inGameMatches;
    
    Game() : inGamePlayers(nullptr), inGameMatches(nullptr) {};
    Game(int numberOfMatches);

    void addMatchToGame(Match match);
    void addPlayerToGame(Player *player);
    Player* retrievePlayerInstance(std::string name, int initialPlayerMoneyAmount, int playerBet, Vector<Card> *playerHand);
    void chargeTheMinimunAmountToPlay(int minimumAmountToPlay);
    void getGameResult();
};

#endif
