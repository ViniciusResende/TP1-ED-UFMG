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
    /**
     * @brief Default constructor for Match class instance that initialize attributes with null values.
     *
     */
    Match() : inMatchPlayers(nullptr), winners(nullptr) {};
    /**
     * @brief Default constructor for Match class instance 
     *
     * @param numberOfPlayers Number of players that will participate in a certain match.
     * @param minimumAmountToPlay The minimum amount to play required for this match (Pingo)
     */
    Match(int numberOfPlayers, int minimumAmountToPlay);

    /**
     * @brief Function responsible for adding a player in the match context (inMatchPlayers). 
     *
     * @param player Instance of a object from Player class
     */
    void addPlayerToMatch(Player* player);
    /**
     * @brief Prints the match info into console, its attributes, and players. 
     *
     */
    void printMatch();
    /**
     * @brief Function responsible for iterating over the players in a match and determining the winners. 
     * At the same time, it will charge the players for their bets and the minimum amount to play, 
     * and by the end share the accumulated pot with the winners.
     *
     * @param totalPlayersInGame Number of players that are participating of the game (global context).
     * @param outFile A reference to an output file of ofstream type, to print the game result.
     */
    void getGameResult(int totalPlayersInGame, std::ofstream &outFile);

    /**
     * @brief Default destructor of the class, that will clean it up when called.
     *
     */
    ~Match();
    Vector<Player*> *inMatchPlayers;
    List *winners;

  private:
    static int _id;
    int id;
    int minimumAmountToPlay;
    int totalMatchMoneyAmount;

    /**
     * @brief Function responsible for iterating over the players in a match and determining the winners.
     * Setting this value to winners Match attribute.
     *
     */
    void getWinners();
    /**
     * @brief Function responsible for iterating over the players in a match and determining greater game in their hands. 
     * This value is posteriorly returned.
     *
     * @return Returns the integer value of greater game in players hands.
     * [0: HIGH_CARD, 1: ONE_PAIR, 2: TWO_PAIRS, 3: THREE_KIND, 4: STRAIGHT, 5: FLUSH, 6: FULL_HOUSE, 7: FOUR_KIND, 8: STRAIGHT_FLUSH, 9: ROYAL_STRAIGHT_FLUSH]
     */
    int getMaxHandInMatch();
    /**
     * @brief Function responsible for break a tie between two players with the same game in hand. 
     * Posteriorly, a value indicating the tie winner is returned.
     *
     * @param currentWinner Pointer to a the first player object to have the tie broken 
     * @param challengerOfWinner Pointer to a the second player object to have the tie broken 
     * 
     * @return Returns the integer value of one to indicate the win of the first player, 
     * two to indicate the win of the second one, and zero to indicate that the tie couldn't be broken.
     * [0: NONE_OF_PLAYERS_WON, 1: FIRST_PLAYER_HAS_WON, 2: SECOND_PLAYER_HAS_WON]
     */
    int playerTieBreaker(Player* currentWinner, Player* challengerOfWinner);
    /**
     * @brief Function responsible for comparing two players by a certain card index for each. 
     * Posteriorly, a value indicating the tie winner is returned.
     *
     * @param firstPlayer Pointer to a the first player object to be compared 
     * @param firstPlayerCardIndexToCompare Integer that indicates the index of the first player card to be compared 
     * @param secondPlayer Pointer to a the second player object to be compared
     * @param secondPlayerCardIndexToCompare Integer that indicates the index of the second player card to be compared 
     * 
     * @return Returns the integer value of one to indicate the win of the first player, 
     * two to indicate the win of the second one, and zero to indicate that the comparison wasn't conclusive.
     * [0: NONE_OF_PLAYERS_WON, 1: FIRST_PLAYER_HAS_WON, 2: SECOND_PLAYER_HAS_WON]
     */
    int comparePlayersByCard(Player* firstPlayer, int firstPlayerCardIndexToCompare, Player* secondPlayer, int secondPlayerCardIndexToCompare);
};

#endif
