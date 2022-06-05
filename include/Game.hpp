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
    
    /**
     * @brief Default constructor for Game class instance that initialize attributes with null values.
     */
    Game() : inGamePlayers(nullptr), inGameMatches(nullptr) {};
    /**
     * @brief Default constructor for Game class instance 
     *
     * @param numberOfMatches Number of matches that will have in the game.
     */
    Game(int numberOfMatches);

    /**
     * @brief Function responsible for adding a match in the game context (inGameMatches). 
     *
     * @param match Instance of a object from Match class
     */
    void addMatchToGame(Match match);
    /**
     * @brief This function is responsible for receiving info to create a player. Then, verify if this player is already in the game, 
     * in this case, its info is updated. Otherwise, a new instance of a player is created and added to the game context. 
     * By the end, the player instance, created or searched, is returned. 
     *
     * @param name Name of the current player
     * @param initialMoney Money that player will start the game with
     * @param initialHand Initial hand of cards that the player will start at its first match (Data Structure Type: Vector<Card>(5))
     * @param playerBet Bet made by the player at its first match
     * 
     * @return Returns a pointer to the player instance created or searched and updated.
     */
    Player* retrievePlayerInstance(std::string name, int initialPlayerMoneyAmount, int playerBet, Vector<Card> *playerHand);
    /**
     * @brief This function is responsible for charge the minimum amount to play (Pingo) 
     * of all players in the game context.
     *
     * @param minimumAmountToPlay The minimum amount to play required for a match (Pingo)
     */
    void chargeTheMinimunAmountToPlay(int minimumAmountToPlay);
  private: 
    /**
     * @brief Function responsible for adding a player in the game context (inGamePlayers). 
     *
     * @param player Instance of a object from Player class
     */
    void addPlayerToGame(Player *player);
};

#endif
