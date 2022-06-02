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

Player* Game::retrievePlayerInstance(std::string name, int initialPlayerMoneyAmount, int playerBet, Vector<Card> *playerHand) {
  Player* aux = this->inGamePlayers->searchByName(name);

  if(aux != nullptr) {
    aux->setPlayerHand(playerHand);
    aux->setPlayerBet(playerBet);
    return aux;
  }

  aux = new Player(name, initialPlayerMoneyAmount, playerHand, playerBet);
  this->addPlayerToGame(aux);

  return aux;
}

void Game::chargeTheMinimunAmountToPlay(int minimumAmountToPlay) {
  errorAssert(minimumAmountToPlay >= 50, "Invalid value for Minimum Amount to Play, minimum of 50 units");
  // void chargeAmountFromPlayer(Player* current) {
  //   current->
  // }

  // Player* it;
  // for (int i = 0; i < this->inGamePlayers->length(); i++) {
  //   it = this->inGamePlayers->getElement(i);
  //   it->decreaseMoneyBy(minimumAmountToPlay);
  // }
  // auto test = [minimumAmountToPlay] (Player *current) {
  //   current->decreaseMoneyBy(minimumAmountToPlay);
  // };
  this->inGamePlayers->forEachPlayerReduceMoney(minimumAmountToPlay);
}