#include "List.hpp"
#include "msgassert.h"

int List::_id = 0;

List::List() {
  this->_id += 1;
  this->id = this->_id;

  this->size = 0;

  this->head = new ListCell();
  this->tail = this->head;
}

int List::length() {
  return this->size;
}

Player* List::getElement(int idx) {
  ListCell *cellPointer;

  cellPointer = this->setPosition(idx, false);

  return cellPointer->value;
}

void List::setElement(int idx, Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *cellPointer;

  cellPointer = this->setPosition(idx, false);
  cellPointer->value = value;
}

void List::pushFront(Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *newCell = new ListCell();

  newCell->value = value;
  newCell->next = this->head->next;
  this->head->next = newCell;

  this->size++;

  if(newCell->next == nullptr)
    this->tail = newCell;
}

void List::pushBack(Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *newCell = new ListCell();

  newCell->value = value;
  this->tail->next = newCell;
  this->tail = newCell;

  this->size++;
}

void List::pushPosition(int idx, Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *newCell = new ListCell();
  ListCell *cellPointer = this->setPosition(idx, true);

  newCell->value = value;
  newCell->next = cellPointer->next;
  cellPointer->next = newCell;

  this->size++;

  if(newCell->next == nullptr)
    this->tail = newCell;
}

Player* List::popFront() {
  errorAssert(this->size > 0, "Can't pop empty list");

  Player* aux;
  ListCell *cellPointer = this->head->next;

  this->head->next = cellPointer->next;
  this->size--;

  if(this->head->next == nullptr)
    this->tail = this->head;

  aux = cellPointer->value;
  delete cellPointer;  

  return aux;
}

Player* List::popEnd() {
  errorAssert(this->size > 0, "Can't pop empty list");

  Player* aux;
  ListCell *cellPointer = this->setPosition(this->size, true);

  cellPointer->next = nullptr;
  this->size--;

  aux = this->tail->value;
  delete this->tail;  

  this->tail = cellPointer;

  return aux;
}

Player* List::popPosition(int idx) {
  errorAssert(this->size > 0, "Can't pop empty list");

  Player* aux;
  ListCell *cellPointer = this->setPosition(idx, true);
  ListCell *cellPointerAux = cellPointer->next;

  cellPointer->next = cellPointerAux->next;
  this->size--;

  aux = cellPointerAux->value;
  delete cellPointerAux;  

  if(cellPointer->next == nullptr)
    this->tail = cellPointer;

  return aux;
}

Player* List::searchByName(std::string playerName) {
  errorAssert(!playerName.empty(), "Search name can't be empty");

  Player* aux = nullptr;
  ListCell *cellPointer = this->head->next;

  while (cellPointer != nullptr) {
    if(cellPointer->value->getName() == playerName) {
      aux = cellPointer->value;
    }
    cellPointer = cellPointer->next;
  }

  return aux;
}

void List::swapConsecutiveListCells(ListCell *fistCell, ListCell *secondCell, ListCell *cellBeforeFirst) {
  cellBeforeFirst->next = secondCell;
  fistCell->next = secondCell->next;
  secondCell->next = fistCell;

  if(fistCell->next == nullptr)
    this->tail = fistCell;
}

void List::bubbleSort() {
  ListCell *currentCell, *previousCell, *nextCell;

  for (int i = 0; i < this->size; i++) {
    currentCell = this->head->next;
    previousCell = this->head;
    for (int j = 0; j < this->size-1; j++) {
      nextCell = currentCell->next;
      if (currentCell->value->getName() > nextCell->value->getName())
        this->swapConsecutiveListCells(currentCell, nextCell, previousCell);
      previousCell = currentCell;
      currentCell = currentCell->next;
    }
  }
}

int List::forEachPlayerReduceMoney(int amount, bool &isOperationValid) {
  ListCell *it = this->head;
  for (int i = 0; i < this->size; i++) {
    it = it->next;
    it->value->decreaseMoneyBy(amount, isOperationValid);
    if(!isOperationValid)
      return i;
  }

  return -1;
}

void List::forEachPlayerRaiseMoney(int amount, int limitIdx) {
  ListCell *it = this->head;
  for (int i = 0; i < limitIdx + 1; i++) {
    it = it->next;
    it->value->increaseMoneyBy(amount);
  }
}

ListCell* List::setPosition(int idx, bool before) {
  errorAssert((idx >= 0) && (idx < this->size), "Invalid index while seting position on List");
  
  ListCell *cellPointer = this->head;
  
  for (int i = 0; i < idx; i++) {
    cellPointer = cellPointer->next;
  }

  if(!before)
    cellPointer = cellPointer->next;

  return cellPointer;
}

List::~List() {
  warnAssert(this->size > 0, "List has already been destoyed");
  ListCell *cellPointer = this->head->next;

  while (cellPointer != nullptr) {
    this->head->next = cellPointer->next;
    delete cellPointer;
    cellPointer = this->head->next;
  }
  
  this->tail = this->head;
  this->size = 0;
  
  delete this->head;
}