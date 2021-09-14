#pragma once
#include <iostream>
#include <exception>
#include "selectionSort.h"
#include "countingSort.h"

using namespace std;

#define tpt template <typename T>

tpt
class CircularArray {
  protected:
    T *array;
    int capacity;
    int back, front;
    int next(int);
    int prev(int);

  public:
    CircularArray();
    CircularArray(int capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](const int);
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");
};

tpt
CircularArray<T>::CircularArray() {
  CircularArray(0);
}

tpt
CircularArray<T>::CircularArray(int capacity) {
  this->array = new T[capacity];
  this->capacity = capacity;
  this->front = this->back = -1;
}

tpt
CircularArray<T>::~CircularArray() {
  delete[] array;
}

tpt
int CircularArray<T>::prev(int index) {
  return (index == 0) ? capacity - 1 : index - 1;
}

tpt
int CircularArray<T>::next(int index) {
  return (index + 1) % capacity;
}

tpt
void CircularArray<T>::push_front(T data) {
  if(is_full()) 
    throw std::runtime_error("It's full");
    
  if(is_empty()) 
    front = back = 0;
  else
    front = prev(front);
    
  array[front] = data;
}

tpt
void CircularArray<T>::push_back(T data) {
  if(is_full()) 
    throw std::runtime_error("It's full");
    
  if(is_empty())
    front = back = 0;
  else
    back = next(back);
  
  array[back] = data;
}


tpt
void CircularArray<T>::insert(T data, int pos) {
  pos--;
  if(is_full()) 
    throw std::runtime_error("It's full");

  if(pos < 0 || pos > size()) 
    throw std::runtime_error("Out of bounds");

  if(pos == prev(front)) {
    push_front(data);
    return;
  }

  if(pos == next(back)) {
    push_back(data);
    return;
  }

  if(is_empty()) {
    front = back = pos;
    array[pos] = data;
  }

  if(front <= back) {
    if(back < pos || pos < front)
      throw std::runtime_error("Out of bounds");
  } else {
    if(front > pos && pos > back)
      throw std::runtime_error("Out of bounds");
  }
  
  for(int i = next(back), j = back; i != prev(front); i = prev(i), j = prev(j)) {
    if(i == pos) {
      array[i] = data;
      i = prev(i);
      break;
    }
    array[i] = array[j];
  }
  back = next(back);
}

tpt
T CircularArray<T>::pop_front() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");
  
  T &tmp = array[front];

  if(back == front) {
    front = back = -1;
    return tmp;
  }
  
  front = next(front);
  return tmp;
}

tpt
T CircularArray<T>::pop_back() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  T &tmp = array[back]; 

  if(back == front) {
    front = back = -1;
    return tmp;
  }

  back = prev(back);
  return tmp;
}

tpt
bool CircularArray<T>::is_full() {
  return next(back) == front;
}

tpt
bool CircularArray<T>::is_empty() {
  return (front == -1 && back == -1);
}

tpt
int CircularArray<T>::size() {
  if(is_empty()) 
    return 0;

  if(front == back) 
    return 1;

  if(front > back)
    return (capacity - front) + (back + 1);
  else
    return back - front + 1;
}

tpt
void CircularArray<T>::clear() {
  delete [] array;
  T* tmp = new T[capacity];
  array = tmp;
  front = -1;
  back = -1;
}

tpt
T &CircularArray<T>::operator[](const int index) {
  if(index >= size() || index < 0) 
    throw std::runtime_error("Index out of bounds");

  int tmp = front;
    for (int i=0; i<index; i++){
        tmp = next(tmp);
    }
  return array[tmp];
}

tpt
void CircularArray<T>::sort() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  T arr[size()];

  arr[0] = array[front];
  for(int i = next(front), j = 1; i != next(back); i = next(i), j++)
    arr[j] = array[i];

  if(size() < 100)

    selectionSort(arr, size());
  else
    countingSort(arr, size());
  
  for(int i = 0, j = front; i < size(); i++, j = next(j)) {
    array[j] = arr[i];
  }
}

tpt
bool CircularArray<T>::is_sorted() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  bool sorted = true;
  for(int i = front; i != back; i = next(i)) {
    if(array[i] > array[next(i)]) {
      sorted = false;
      break;
    }
  }

  return sorted;
}

tpt
void CircularArray<T>::reverse() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");
  
  T* tmp = new T[capacity];
  
  tmp[front] = array[back];

  for(int i = prev(back), j = next(front); j != next(back); i = prev(i), j = next(j)) {
    tmp[j] = array[i];
  }

  delete [] array;
  array = tmp;
}

tpt
string CircularArray<T>::to_string(string sep){
  string result = "";
  result += std::to_string(array[front]) + sep;
  for(int i=next(front); i != next(back); i = next(i))
    result += std::to_string(array[i]) + sep;
  return result;    
}
