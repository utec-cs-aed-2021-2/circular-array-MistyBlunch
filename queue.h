#pragma once
#include <exception>
#include <iostream>
#include "circulararray.h"

#define tpt template <typename T>

tpt
class QueueArray : public CircularArray<T> { 
  public:
  QueueArray();
  QueueArray(int capacity);

  void callme();
  void enqueue(T item);
  T dequeue();
  T peek();
};

tpt
QueueArray<T>::QueueArray() {
  QueueArray(0);
}

tpt
QueueArray<T>::QueueArray(int capacity) {
  this->array = new T[capacity];
  this->capacity = capacity;
  this->front = this->back = -1; 
  this->siz = 0;
}

tpt
void QueueArray<T>::callme() {
  cout << "QueueArray" << endl;
}

tpt
void QueueArray<T>::enqueue(T item) {
  QueueArray<T>::push_back(item);
}

tpt
T QueueArray<T>::dequeue() {
  QueueArray<T>::pop_front(); 
}

tpt
T QueueArray<T>::peek() {
  if(QueueArray<T>::is_empty()) 
    throw std::runtime_error("It's full");
  return this->array[this->front];
}