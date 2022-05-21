#include "Vector.hpp"
#include "msgassert.h"
#include "Card.hpp"
#include "Player.hpp"

template<typename T>
int Vector<T>::_id = 0;

template<typename T>
Vector<T>::Vector(int size) {
  errorAssert(size > 0, "Null Vector dimension");

  this->size = size;

  this->_id += 1;
  this->id = this->_id;

  this->value = (T*) malloc(this->size * sizeof(T));
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
}

template<typename T>
T Vector<T>::getElement(int idx) {
  errorAssert((idx >= 0) && (idx < this->size), "Invalid Vector index");

  READMEMLOG((long int) (&(this->value[idx])), sizeof(T), this->id);
  return this->value[idx];
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