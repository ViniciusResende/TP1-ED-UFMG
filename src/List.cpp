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
  READMEMLOG((long int)(&(this->size)), sizeof(int), this->id);
  return this->size;
}

Player* List::getElement(int idx) {
  ListCell *cellPointer;

  cellPointer = this->setPosition(idx, false);
  READMEMLOG((long int)(&(cellPointer->value)), sizeof(Player*), this->id);

  return cellPointer->value;
}

void List::setElement(int idx, Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *cellPointer;

  cellPointer = this->setPosition(idx, false);
  cellPointer->value = value;
  WRITEMEMLOG((long int)(&(cellPointer->value)), sizeof(ListCell), this->id);
}

void List::pushFront(Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *newCell = new ListCell();

  newCell->value = value;
  newCell->next = this->head->next;
  this->head->next = newCell;

  WRITEMEMLOG((long int)(&(newCell)), sizeof(ListCell*), this->id);

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

  WRITEMEMLOG((long int)(&(newCell)), sizeof(ListCell*), this->id);

  this->size++;
}

void List::pushPosition(int idx, Player* value) {
  errorAssert(value != NULL && value != nullptr, "Player instance must be previously initialized");

  ListCell *newCell = new ListCell();
  ListCell *cellPointer = this->setPosition(idx, true);

  newCell->value = value;
  newCell->next = cellPointer->next;
  cellPointer->next = newCell;

  WRITEMEMLOG((long int)(&(newCell)), sizeof(ListCell*), this->id);

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

  READMEMLOG((long int)(&(aux)), sizeof(Player*), this->id);
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

  READMEMLOG((long int)(&(aux)), sizeof(Player*), this->id);
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

  READMEMLOG((long int)(&(aux)), sizeof(Player*), this->id);
  return aux;
}

Player* List::searchByName(std::string playerName) {
  errorAssert(!playerName.empty(), "Search name can't be empty");

  Player* aux = nullptr;
  ListCell *cellPointer = this->head->next;

  while (cellPointer != nullptr) {
    if(cellPointer->value->getName() == playerName) {
      aux = cellPointer->value;
    
      READMEMLOG((long int)(&(aux)), sizeof(Player*), this->id);
    }
    cellPointer = cellPointer->next;
  }

  return aux;
}

// void List::forEach(void (*callback)(Player*)) {
//   ListCell *it = this->head;
//   for (int i = 0; i < this->size; i++) {
//     it = it->next;
//     callback(it->value);
//   }
// }

void List::forEachPlayerReduceMoney(int amount) {
  ListCell *it = this->head;
  for (int i = 0; i < this->size; i++) {
    it = it->next;
    it->value->decreaseMoneyBy(amount);
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