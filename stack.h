#pragma once
#include "circulararray.h"
#define tpt template <typename T>

template <typename T>
class StackArray : public CircularArray<T> { 
  public:
  StackArray();
  StackArray(int capacity);

  void push(T item);
  T pop();
  T top();
};

tpt
StackArray<T>::StackArray() {
  StackArray(0);
}

tpt
StackArray<T>::StackArray(int capacity) {
  this->array = new T[capacity];
  this->capacity = capacity;
  this->front = this->back = -1; 
  this->siz = 0;
}

tpt
void StackArray<T>::push(T item) {
  StackArray<T>::push_back(item);
}

tpt
T StackArray<T>::pop() {
  return StackArray<T>::pop_back(); 
}

tpt
T StackArray<T>::top() {
  if(StackArray<T>::is_empty()) 
    throw std::runtime_error("It's full");
  return this->array[this->front];
}