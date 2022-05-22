#include "msgassert.h"
#include "ListCell.hpp"

ListCell::ListCell() {
  this->value = new Player();
  this->next = nullptr;
}

ListCell::~ListCell() {
  delete this->value;
}