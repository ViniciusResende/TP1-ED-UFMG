#include "Player.hpp"
#include "msgassert.h"

int Player::_id = 0;

Player::Player() {}

Player::Player(std::string name, double initialMoney, Vector<Card> *initialHand) {
  errorAssert(!name.empty(), "Invalid name provided");
  errorAssert(initialMoney >= 0, "Initial money can't be negative");
  
  this->_id += 1;
  this->id = this->_id;

  this->name = name;
  WRITEMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  
  this->money = initialMoney;
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);


  this->hand = initialHand;
}

void Player::setPlayerHand(Vector<Card> *currentHand) {
  this->hand = currentHand;
}

Card Player::getPlayerCardByIndex(int idx) {
  errorAssert((idx >= 0) && (idx < HAND_DEFAULT_SIZE), "Invalid hand index");
  Card cardHolder = this->hand->getElement(idx);
  READMEMLOG((long int) (&(cardHolder)), sizeof(Card), this->id);

  return cardHolder;
}

void Player::setMoney(double value) {
  errorAssert(value >= 0, "Money value can't be negative");

  this->money = value;
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
}

double Player::getMoney() {
  READMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
  return this->money;
}

std::string Player::getName() {
  READMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  return this->name;
}

Player::~Player() {
  warnAssert(this->id != -1, "Player instance has already been destroyed");

  this->money = this->id = -1;
  this->name = "";
}