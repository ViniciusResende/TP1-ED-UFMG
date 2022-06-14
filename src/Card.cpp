#include <iostream>
#include "Card.hpp"
#include "msgassert.h"

#define MAXIMUM_CARD_NUMBER 13


Card::Card(int cardNumber, char cardSuit, int id) {
  errorAssert(cardNumber > 1 && cardNumber <= 14, "Invalid card number");
  errorAssert((cardSuit == HEARTHS) || (cardSuit == DIAMONDS) || (cardSuit == CLUBS) || (cardSuit == SPADE), "Invalid card SUIT");

  this->id = id;

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