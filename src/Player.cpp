#include <iostream>
#include "Player.hpp"
#include "msgassert.h"

int Player::_id = 0;

Player::Player() {}

Player::Player(std::string name, double initialMoney, Vector<Card> *initialHand, int playerBet) {
  errorAssert(!name.empty(), "Invalid name provided");
  errorAssert(initialMoney >= 0, "Initial money can't be negative");
  errorAssert(playerBet % 50 == 0, "Player bet must be a multiple of 50");
  errorAssert(playerBet > 0, "Player bet must be a positive and not null value");
  errorAssert(initialHand->length() == HAND_DEFAULT_SIZE, "Invalid size for hand of cards");
  
  this->_id += 1;
  this->id = this->_id;

  this->name = name;
  WRITEMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  
  this->money = initialMoney;
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);

  this->playerBet = playerBet;
  WRITEMEMLOG((long int) (&(this->playerBet)), sizeof(int), this->id);

  this->hand = initialHand;
}

void Player::setPlayerHand(Vector<Card> *currentHand) {
  errorAssert(currentHand->length() == HAND_DEFAULT_SIZE, "Invalid size for hand of cards");

  delete this->hand;
  this->hand = currentHand;
}

Card Player::getPlayerCardByIndex(int idx) {
  errorAssert((idx >= 0) && (idx < HAND_DEFAULT_SIZE), "Invalid hand card index");

  Card cardHolder = this->hand->getElement(idx);
  READMEMLOG((long int) (&(cardHolder)), sizeof(Card), this->id);

  return cardHolder;
}

void Player::setMoney(double value) {
  errorAssert(value >= 0, "Money value can't be negative");

  this->money = value;
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
}

void Player::increaseMoneyBy(double value) {
  errorAssert((this->money + value) >= 0, "Increasing money by a negative value that will cause negative Player money");
  warnAssert(value >= 0, "You should't use increaseMoneyBy method with negative values, use decreaseMoneyBy method instead");

  this->money += value;
  READMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
}

void Player::decreaseMoneyBy(double value) {
  errorAssert((this->money - value) >= 0, "You can't decrease more money than player have");
  warnAssert(value >= 0, "You should't use decreaseMoneyBy method with negative values, use increaseMoneyBy method instead");

  this->money -= value;
  READMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
  WRITEMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
}

double Player::getMoney() {
  READMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
  return this->money;
}

void Player::setPlayerBet(int value) {
  errorAssert(value >= 0, "Player bet value can't be negative");
  errorAssert(playerBet % 50 == 0, "Player bet must be a multiple of 50");

  this->playerBet = value;
  WRITEMEMLOG((long int) (&(this->playerBet)), sizeof(int), this->id);
}

int Player::getPlayerBet() {
  READMEMLOG((long int) (&(this->playerBet)), sizeof(int), this->id);
  return this->playerBet;
}

std::string Player::getName() {
  READMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  return this->name;
}

void Player::printPlayer() {
  READMEMLOG((long int) (&(this->id)), sizeof(int), this->id);
  READMEMLOG((long int) (&(this->name)), sizeof(std::string), this->id);
  READMEMLOG((long int) (&(this->money)), sizeof(double), this->id);
  READMEMLOG((long int) (&(this->gameInHand)), sizeof(int), this->id);

  std::cout << "ID: " << this->id << std::endl;
  std::cout << "Name: " << this->name << std::endl;
  std::cout << "Money: " << this->money << std::endl;
  std::cout << "Game: " << this->gameInHand << " Hand: ";
  for (int i = 0; i < HAND_DEFAULT_SIZE; i++) {
    this->hand->getElement(i).printCard();
  }
  std::cout << std::endl;
}

bool Player::verifyStraight() {
  int currentIndex = 1;

  // logic that handles cases where there is a A that can be used as the greatest card
  if(this->getPlayerCardByIndex(0).getCardNumber() == 1 && this->getPlayerCardByIndex(1).getCardNumber() == 10)
    currentIndex = 2;

  while (currentIndex < HAND_DEFAULT_SIZE) {
    if((this->getPlayerCardByIndex(currentIndex).getCardNumber() - this->getPlayerCardByIndex(currentIndex - 1).getCardNumber()) != 1)
      return false;
    currentIndex++;
  }

  return true;
}


int Player::handleFlush() {
  if(!(this->verifyStraight()))
    return FLUSH;

  if(this->getPlayerCardByIndex(HAND_DEFAULT_SIZE - 1).getCardNumber() == 13 && this->getPlayerCardByIndex(0).getCardNumber() == 1)
    return ROYAL_STRAIGHT_FLUSH;
    
  return STRAIGHT_FLUSH;
}

int Player::handleRepetitions() {
  int numberOfPairs = 0;
  
  bool thereIsTriple = false;
  bool thereIsQuadruple = false;

  char lastAdded = 'D'; // Will receive 'P' when lastAdded is a pair, and 'T' when it were a Triple or 'D' for default
  
  for (int i = 1; i < HAND_DEFAULT_SIZE; i++) {
    if(this->getPlayerCardByIndex(i).getCardNumber() == this->getPlayerCardByIndex(i-1).getCardNumber()) {
      switch (lastAdded) {
        case 'P':
          numberOfPairs--;
          thereIsTriple = true;
          lastAdded = 'T';
          break;

        case 'T':
          thereIsTriple = false;
          thereIsQuadruple = true;        
          break;
        
        default:
          numberOfPairs++;
          lastAdded = 'P';
          break;
      }
    } else 
      lastAdded = 'D';
  }

  if(thereIsQuadruple)
    return FOUR_KIND;

  if(thereIsTriple && numberOfPairs == 1)
    return FULL_HOUSE;

  if(thereIsTriple)
    return THREE_KIND;

  if(numberOfPairs == 1)
    return ONE_PAIR;

  if(numberOfPairs == 2)
    return TWO_PAIRS;

  return HIGH_CARD;
}

int Player::getGameInHand() {
  errorAssert(this->hand->vectorIsFullfilled(), "Can't get game in hand when Vector isn't full filled");

  // this array will store the number of repetitions of the suits in order HEARTHS, SPADE, DIAMONDS, CLUBS
  int cardsSuitRecurrence[4] = {0, 0, 0, 0};

  for (int i = 0; i < HAND_DEFAULT_SIZE; i++) {
    switch (this->getPlayerCardByIndex(i).getCardSuit()) {
      case HEARTHS:
        cardsSuitRecurrence[0]++;
        break;
      case SPADE:
        cardsSuitRecurrence[1]++;
        break;
      case DIAMONDS:
        cardsSuitRecurrence[2]++;
        break;
      case CLUBS:
        cardsSuitRecurrence[3]++;
        break;
    }
  }

  for (int i = 0; i < 4; i++) {
    if(cardsSuitRecurrence[i] == HAND_DEFAULT_SIZE) {
      this->gameInHand = this->handleFlush();
      return this->gameInHand;
    }
  }

  if(this->verifyStraight()) {
    this->gameInHand = STRAIGHT;
    return this->gameInHand;
  }
  
  this->gameInHand = this->handleRepetitions();
  return this->gameInHand;
}

const char* Player::getGameLabel() {
  warnAssert(this->gameInHand != -1, "gameInHand is undefined by the time of getGameLabel call");

  switch (this->gameInHand) {
    case HIGH_CARD:
      return "HC";
    case ONE_PAIR:
      return "OP";
    case TWO_PAIRS:
      return "TP";
    case THREE_KIND:
      return "TK";
    case STRAIGHT:
      return "S";
    case FLUSH:
      return "F";
    case FULL_HOUSE:
      return "FH";
    case FOUR_KIND:
      return "FK";
    case STRAIGHT_FLUSH:
      return "SF";
    case ROYAL_STRAIGHT_FLUSH:
      return "RSF";  
    default:
      return "ERR";
  }
}

bool Player::operator<(const Player& other) {
  return this->money < other.money;
}

Player::~Player() {
  warnAssert(this->id != -1, "Player instance has already been destroyed");

  this->money = this->id = this->playerBet = -1;
  this->name = "";
  delete this->hand;
}