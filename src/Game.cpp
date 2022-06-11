#include "Game.hpp"
#include "msgassert.h"

Game::Game(int numberOfMatches) {
  errorAssert(numberOfMatches > 0, "Invalid number of matches");

  this->inGamePlayers = new List();
  this->inGameMatches = new Vector<Match>(numberOfMatches);  
}

void Game::addMatchToGame(Match match) {
  this->inGameMatches->pushBack(match);
}

void Game::addPlayerToGame(Player *player) {
  this->inGamePlayers->pushFront(player);
}

Player* Game::retrievePlayerInstance(std::string name, int initialPlayerMoneyAmount, int playerBet, Vector<Card> *playerHand, int id) {
  Player* aux = this->inGamePlayers->searchByName(name);

  if(aux != nullptr) {
    aux->setPlayerHand(playerHand);
    aux->setPlayerBet(playerBet);
    return aux;
  }

  aux = new Player(name, initialPlayerMoneyAmount, playerHand, playerBet, id);
  this->addPlayerToGame(aux);

  return aux;
}

void Game::chargeTheMinimunAmountToPlay(int minimumAmountToPlay, bool &isOperationValid) {
  errorAssert(minimumAmountToPlay >= 50, "Invalid value for Minimum Amount to Play, minimum of 50 units");
  
  int indexOfError = this->inGamePlayers->forEachPlayerReduceMoney(minimumAmountToPlay, isOperationValid);

  if(indexOfError != -1) 
    this->inGamePlayers->forEachPlayerRaiseMoney(minimumAmountToPlay, indexOfError - 1);
}

void Game::giveBackTheMinimunAmountToPlay(int minimumAmountToPlay) {
  errorAssert(minimumAmountToPlay >= 50, "Invalid value for Minimum Amount to Play, minimum of 50 units");
  this->inGamePlayers->forEachPlayerRaiseMoney(minimumAmountToPlay, this->inGamePlayers->length() - 1);
}