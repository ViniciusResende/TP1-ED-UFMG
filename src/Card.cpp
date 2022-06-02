#include <iostream>
#include "Card.hpp"
#include "msgassert.h"

#define MAXIMUM_CARD_NUMBER 13

int Card::_id = 0;
char Card::avaliableSuits[4] = {HEARTHS, DIAMONDS, CLUBS, SPADE};

int retrieveRandomCardNumber() {
  return rand() % MAXIMUM_CARD_NUMBER + 1;
}

char retrieveRandomCardSuit(char avaliableSuits[4]) {
  return avaliableSuits[rand() % 4];
}

Card::Card() : Card(retrieveRandomCardNumber(), retrieveRandomCardSuit(this->avaliableSuits)) {
  
}

Card::Card(int cardNumber, char cardSuit) {
  errorAssert(cardNumber > 0 && cardNumber <= 13, "Invalid card number");
  errorAssert((cardSuit == HEARTHS) || (cardSuit == DIAMONDS) || (cardSuit == CLUBS) || (cardSuit == SPADE), "Invalid card SUIT");

  this->_id += 1;
  this->id = this->_id;

  this->cardNumber = cardNumber;
  WRITEMEMLOG((long int) (&(this->cardNumber)), sizeof(int), this->id);
  
  this->cardSuit = cardSuit;
  WRITEMEMLOG((long int) (&(this->cardSuit)), sizeof(char), this->id);
}

int Card::getCardNumber() {
  READMEMLOG((long int) (&(this->cardNumber)), sizeof(int), this->id);
  return this->cardNumber;
}

char Card::getCardSuit() {
  READMEMLOG((long int) (&(this->cardSuit)), sizeof(char), this->id);
  return this->cardSuit;
}

void Card::printCard() {
  READMEMLOG((long int) (&(this->cardNumber)), sizeof(int), this->id);
  READMEMLOG((long int) (&(this->cardSuit)), sizeof(char), this->id);
  
  std::cout << this->cardNumber << this->cardSuit << " ";
}

bool Card::operator<(Card other) {
  if(this->cardNumber < other.cardNumber && this->cardNumber != other.cardNumber) 
    return true;

  // if((this->cardNumber == other.cardNumber) && (this->cardSuit < other.cardSuit))
  //   return true;

  return false;
}

bool Card::operator>(Card other) {
  return (!(*(this) < other)) && !(*(this) == other);
}

bool Card::operator==(Card other) {
  if((this->cardNumber == other.cardNumber))
    return true;

  return false;
}

Card::~Card() {
  warnAssert(this->id != -1, "Card instance has already been destroyed");

  this->id = -1;

  this->cardNumber = 0;
  this->cardSuit = 'Z';
}