#include "Vector.hpp"
#include "msgassert.h"
#include "Card.hpp"
#include "Player.hpp"
#include "Match.hpp"

template<typename T>
int Vector<T>::_id = 0;

template<typename T>
Vector<T>::Vector(int size) {
  errorAssert(size > 0, "Null Vector dimension");

  this->size = size;

  this->_id += 1;
  this->id = this->_id;

  this->value = (T*) malloc(this->size * sizeof(T));

  this->lastInputedIndex = -1;
}

template<typename T>
int Vector<T>::length() {
  READMEMLOG((long int)(&(this->size)), sizeof(int), this->id);
  return this->size;
}

template<typename T>
T Vector<T>::warmUpVector() {  
  T aux = this->value[0];
  READMEMLOG((long int)(&(this->value[0])), sizeof(T), this->id);

  for (int i=1; i<this->size; i++){
    aux = this->value[i];
    READMEMLOG((long int)(&(this->value[i])), sizeof(T), this->id);
  }

  return aux;
}

template<typename T>
void Vector<T>::setElement(int idx, T value) {
  errorAssert((idx >= 0) && (idx < this->size), "Invalid Vector index");

  this->value[idx] = value;
  WRITEMEMLOG((long int) (&(this->value[idx])), sizeof(T), this->id);

  if(idx > this->lastInputedIndex)
    this->lastInputedIndex = idx;
}

template<typename T>
void Vector<T>::pushBack(T value) {
  errorAssert(this->lastInputedIndex < this->size, "Alocated Vector is already full");

  this->lastInputedIndex += 1;
  this->value[this->lastInputedIndex] = value;
  WRITEMEMLOG((long int) (&(this->value[this->lastInputedIndex])), sizeof(T), this->id);
}

template<typename T>
T Vector<T>::getElement(int idx) {
  errorAssert((idx >= 0) && (idx < this->size), "Invalid Vector index");

  READMEMLOG((long int) (&(this->value[idx])), sizeof(T), this->id);
  return this->value[idx];
}

template<>
void Vector<Card>::sortVector() {
  int Min;

  for (int i = 0; i < this->size - 1; i++) {
    Min = i;

    for (int j = i + 1; j < this->size; j++) {
      if(this->value[j] < this->value[Min])
        Min = j;
    }
    Swap(this->value[i], this->value[Min]);
  }
}

template<typename T>
Vector<T>::~Vector() {
  warnAssert(this->size > 0, "Vector has already been destoyed");

  this->id = this->size = -1;

  free(this->value);
}

template class Vector<int>;
template class Vector<Card>;
template class Vector<Player>;
template class Vector<Player*>;
template class Vector<Match>;