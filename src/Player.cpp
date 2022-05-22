#include "Player.hpp"
#include "msgassert.h"

int Player::_id = 0;

Player::Player() {}

Player::Player(std::string name, double initialMoney, Card initialHand[HAND_DEFAULT_SIZE]) {
  errorAssert(!name.empty(), "Invalid name provided");
  errorAssert(initialMoney >= 0, "Initial money can't be negative");
  
  this->_id += 1;
  this->id = this->_id;

  this->name = name;
  WRITEMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  
  this->money = initialMoney;
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);


  for(int i = 0; i < HAND_DEFAULT_SIZE; i++) {
    this->hand[i] = initialHand[i];
    WRITEMEMLOG((long int) (&(this->hand[i])), sizeof(double), this->id);
  }
}

void Player::setPlayerHand(Card currentHand[HAND_DEFAULT_SIZE]) {
  for(int i = 0; i < HAND_DEFAULT_SIZE; i++) {
    this->hand[i] = currentHand[i];
    WRITEMEMLOG((long int) (&(this->hand[i])), sizeof(Card), this->id);
  }
}

Card Player::getPlayerCardByIndex(int idx) {
  errorAssert((idx >= 0) && (idx < HAND_DEFAULT_SIZE), "Invalid hand index");
  READMEMLOG((long int) (&(this->hand[idx])), sizeof(Card), this->id);

  return this->hand[idx];
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