#include <iostream>
#include "Match.hpp"
#include "msgassert.h"

int Match::_id = 0;

Match::Match(int numberOfPlayers, int minimumAmountToPlay) {
  errorAssert(numberOfPlayers > 0, "Invalid number of players");
  errorAssert(minimumAmountToPlay >= 50, "Invalid value for Minimum Amount to Play, minimum of 50 units");

  this->_id += 1;
  this->id = this->_id;

  this->inMatchPlayers = new Vector<Player*>(numberOfPlayers);
  this->winners = new List();

  this->minimumAmountToPlay = minimumAmountToPlay;
  WRITEMEMLOG((long int) (&(this->minimumAmountToPlay)), sizeof(int), this->id);

  this->totalMatchMoneyAmount = 0;
  WRITEMEMLOG((long int) (&(this->totalMatchMoneyAmount)), sizeof(int), this->id);
}

void Match::addPlayerToMatch(Player *player) {
  errorAssert(player != NULL && player != nullptr, "Player instance wasn't initialized");

  this->inMatchPlayers->pushBack(player);
}

void Match::printMatch() {
  std::cout << "-------- Round "<< this->id << "--------" << std::endl;
  for (int i = 0; i < this->inMatchPlayers->length(); i++) {
    this->inMatchPlayers->getElement(i)->printPlayer();
  }
  std::cout << std::endl;
}

int Match::comparePlayersByCard(Player* firstPlayer, int firstCardIndexToCompare, Player* secondPlayer, int secondCardIndexToCompare) {
  int const FIRST_PLAYER_HAS_WON = 1;
  int const SECOND_PLAYER_HAS_WON = 2;
  int const NONE_OF_PLAYERS_WON = 0;
  
  if(firstPlayer->getPlayerCardByIndex(firstCardIndexToCompare) < secondPlayer->getPlayerCardByIndex(secondCardIndexToCompare))
    return SECOND_PLAYER_HAS_WON;
  else if(firstPlayer->getPlayerCardByIndex(firstCardIndexToCompare) > secondPlayer->getPlayerCardByIndex(secondCardIndexToCompare))
    return FIRST_PLAYER_HAS_WON;
  else
    return NONE_OF_PLAYERS_WON;
}

int Match::playerTieBreaker(Player* currentWinner, Player* challengerOfWinner) {
  int tieGame = currentWinner->gameInHand;

  int const NONE_OF_PLAYERS_WON = 0;

  int gameResultAux;

  switch (tieGame) { 
    case HIGH_CARD: 
      for (int i = HAND_DEFAULT_SIZE - 1; i >= 0; i--) {
        gameResultAux = this->comparePlayersByCard(currentWinner, i, challengerOfWinner, i);
        if(gameResultAux != NONE_OF_PLAYERS_WON)
          return gameResultAux;
      }

      return NONE_OF_PLAYERS_WON;
    case ONE_PAIR:
      for (int i = 1; i < HAND_DEFAULT_SIZE; i++) {
        // found currentWinner pair
        if(currentWinner->getPlayerCardByIndex(i) == currentWinner->getPlayerCardByIndex(i-1)) {
          for (int j = 1; j < HAND_DEFAULT_SIZE; j++) {
            // found challengerOfWinner pair
            if(challengerOfWinner->getPlayerCardByIndex(j) == challengerOfWinner->getPlayerCardByIndex(j-1)) {
              gameResultAux = this->comparePlayersByCard(currentWinner, i, challengerOfWinner, j);
              if(gameResultAux != NONE_OF_PLAYERS_WON)
                return gameResultAux;
            }
          }         

          // pairs comparsion already made, can exit for loop
          i = HAND_DEFAULT_SIZE;
        }
      }

      // search for greater card in general
      for (int i = HAND_DEFAULT_SIZE - 1; i >= 0; i--) {
        gameResultAux = this->comparePlayersByCard(currentWinner, i, challengerOfWinner, i);
        if(gameResultAux != NONE_OF_PLAYERS_WON)
          return gameResultAux;
      }

      return NONE_OF_PLAYERS_WON;      
    case TWO_PAIRS:
      gameResultAux = this->comparePlayersByCard(currentWinner, 3, challengerOfWinner, 3);
      if(gameResultAux != NONE_OF_PLAYERS_WON)
        return gameResultAux;
      else {
        gameResultAux = this->comparePlayersByCard(currentWinner, 1, challengerOfWinner, 1);
        if(gameResultAux != NONE_OF_PLAYERS_WON)
          return gameResultAux;
        else {
          for (int i = HAND_DEFAULT_SIZE - 1; i >= 0; i--) {
            gameResultAux = this->comparePlayersByCard(currentWinner, i, challengerOfWinner, i);
            if(gameResultAux != NONE_OF_PLAYERS_WON)
              return gameResultAux;
          }

          return NONE_OF_PLAYERS_WON;
        }
      }
    case THREE_KIND:
      gameResultAux = this->comparePlayersByCard(currentWinner, 2, challengerOfWinner, 2);
      if(gameResultAux != NONE_OF_PLAYERS_WON)
        return gameResultAux;
      else {
        for (int i = HAND_DEFAULT_SIZE - 1; i >= 0; i--) {
          gameResultAux = this->comparePlayersByCard(currentWinner, i, challengerOfWinner, i);
          if(gameResultAux != NONE_OF_PLAYERS_WON)
            return gameResultAux;
        }

        return NONE_OF_PLAYERS_WON;
      }
    case STRAIGHT:
      return this->comparePlayersByCard(currentWinner, 4, challengerOfWinner, 4);
    case FLUSH:
      return this->comparePlayersByCard(currentWinner, 4, challengerOfWinner, 4);
    case FULL_HOUSE:
      gameResultAux = this->comparePlayersByCard(currentWinner, 2, challengerOfWinner, 2);
      if(gameResultAux != NONE_OF_PLAYERS_WON)
        return gameResultAux;
      else {
        int currentWinnerNonTripleIndex;
        if(currentWinner->getPlayerCardByIndex(2) == currentWinner->getPlayerCardByIndex(1))
          currentWinnerNonTripleIndex = 4;
        else
          currentWinnerNonTripleIndex = 0;

        int challengerOfWinnerNonTripleIndex;
        if(challengerOfWinner->getPlayerCardByIndex(2) == challengerOfWinner->getPlayerCardByIndex(1))
          challengerOfWinnerNonTripleIndex = 4;
        else
          challengerOfWinnerNonTripleIndex = 0;

        return this->comparePlayersByCard(currentWinner, currentWinnerNonTripleIndex, challengerOfWinner, challengerOfWinnerNonTripleIndex);
      }  
    case FOUR_KIND:
      gameResultAux = this->comparePlayersByCard(currentWinner, 2, challengerOfWinner, 2);
      if(gameResultAux != NONE_OF_PLAYERS_WON)
        return gameResultAux;
      else {
        int currentWinnerNonQuadrupleIndex;
        if(currentWinner->getPlayerCardByIndex(0) == currentWinner->getPlayerCardByIndex(1))
          currentWinnerNonQuadrupleIndex = 4;
        else
          currentWinnerNonQuadrupleIndex = 0;

        int challengerOfWinnerNonQuadrupleIndex;
        if(challengerOfWinner->getPlayerCardByIndex(0) == challengerOfWinner->getPlayerCardByIndex(1))
          challengerOfWinnerNonQuadrupleIndex = 4;
        else
          challengerOfWinnerNonQuadrupleIndex = 0;

        return this->comparePlayersByCard(currentWinner, currentWinnerNonQuadrupleIndex, challengerOfWinner, challengerOfWinnerNonQuadrupleIndex);
      }  
    case STRAIGHT_FLUSH:
      return NONE_OF_PLAYERS_WON;
    case ROYAL_STRAIGHT_FLUSH:
      return NONE_OF_PLAYERS_WON;
    default:
      break;
  }

  return NONE_OF_PLAYERS_WON;
}

int Match::getMaxHandInMatch() {
  int currentAnalizedHand, greaterHand = 0;

  for (int i = 0; i < this->inMatchPlayers->length(); i++) {
    currentAnalizedHand = this->inMatchPlayers->getElement(i)->gameInHand;
    if(currentAnalizedHand > greaterHand)
      greaterHand = currentAnalizedHand;
  }

  return greaterHand;
}

void Match::getWinners() {
  int greaterHandInMatch = this->getMaxHandInMatch();

  Player *it;
  for (int i = 0; i < this->inMatchPlayers->length(); i++) {
    it = this->inMatchPlayers->getElement(i);
    if(it->gameInHand == greaterHandInMatch)
      this->winners->pushBack(it);
  }

  int const FIRST_PLAYER_HAS_WON = 1;
  int const SECOND_PLAYER_HAS_WON = 2;
  
  if(this->winners->length() != 1) {
    int tieWinner;
    int i = 0;
    while (i < (this->winners->length() - 1)) {
      tieWinner = this->playerTieBreaker(this->winners->getElement(i), this->winners->getElement(i+1));
      if(tieWinner == FIRST_PLAYER_HAS_WON) {
        this->winners->popPosition(i+1);        
      } else if(tieWinner == SECOND_PLAYER_HAS_WON) {
        for (int j = i; j >= 0; j--) {
          Player *test = this->winners->popFront();
          i--;
        }        
        i++;
      } else {
        i++;
      }
    }
  }
}

void Match::getGameResult(int totalPlayersInGame, std::ofstream &outFile) {
  errorAssert(this->inMatchPlayers->vectorIsFullfilled(), "Players vector wasn't fully filled yet");
  errorAssert(outFile, "Output came with NULL value");

  int totalNumberOfPlayers = this->inMatchPlayers->length();

  Player* it;
  for (int i = 0; i < totalNumberOfPlayers; i++) {
    it = this->inMatchPlayers->getElement(i);

    it->decreaseMoneyBy(it->getPlayerBet());

    this->totalMatchMoneyAmount += it->getPlayerBet();
    WRITEMEMLOG((long int) (&(this->totalMatchMoneyAmount)), sizeof(int), this->id);

    it->getGameInHand();
  }  

  READMEMLOG((long int) (&(this->minimumAmountToPlay)), sizeof(int), this->id);
  this->totalMatchMoneyAmount += totalPlayersInGame * this->minimumAmountToPlay;

  this->getWinners();

  int quantityOfWinners = this->winners->length();
  double amountToWinners = this->totalMatchMoneyAmount/quantityOfWinners;
  
  for (int i = 0; i < quantityOfWinners; i++) {
    this->winners->getElement(i)->increaseMoneyBy(amountToWinners);
  }

  outFile << quantityOfWinners << " " << amountToWinners << " ";
  outFile << this->winners->getElement(0)->getGameLabel() << std::endl;

  for (int i = 0; i < quantityOfWinners; i++)
    outFile << this->winners->getElement(i)->getName() << std::endl;
}

Match::~Match() {
  warnAssert(this->id == -1, "Match has already been destroyed");
  this->id = -1;
  this->minimumAmountToPlay = 0;
  this->totalMatchMoneyAmount = 0;
}