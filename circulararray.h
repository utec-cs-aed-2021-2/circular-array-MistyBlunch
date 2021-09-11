#include <iostream>
#include <exception>
#include "selectionSort.h"
#include "countingSort.h"

using namespace std;

#define tpt template <typename T>

tpt
struct CircularArray {
  T *array;
  int capacity;
  int back, front, siz;
  int next(int);
  int prev(int);

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
  this->siz = 0;
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
    front = next(front);

  for(int i=size(); i>front; i--) 
    array[i] = array[i-1];

  array[front] = data;
  back = next(back);
  siz++;
}

tpt
void CircularArray<T>::push_back(T data) {
  if(is_full()) 
    throw std::runtime_error("It's full");

  if(is_empty())
    front = next(front);

  back = next(back);
  array[back] = data;
  siz++;
}


tpt
void CircularArray<T>::insert(T data, int pos) {
  if(is_full()) 
    throw std::runtime_error("It's full");

  else if(pos == 0 || (is_empty() && pos == 0)) 
    push_front(data);

  else if(pos<0 || pos>siz || is_empty()) 
    throw std::runtime_error("Out of bounds");

  else if(pos == next(back)) 
    push_back(data);

  else {
    T* tmp = new T[capacity];

    for(int i=front; i<=size(); i++) {
      if(i == pos) 
        tmp[i] = data;
      else if(i > pos)
        tmp[i] = array[prev(i)];
      else 
        tmp[i] = array[i];
      
      cout << "tmp[i]" << tmp[i] << endl;
    }

    array = tmp;
    siz++;
    back = next(back);
  }
}

tpt
T CircularArray<T>::pop_front() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  int tmp = array[front];

  if(size() == 1) {
    front = -1;
    back = -1;
  } else {
    for(int i=front; i<size()-1; i++) {
    array[i] = array[next(i)];
  }
    back = prev(back);
  }
  siz--;
  return tmp;
}

tpt
T CircularArray<T>::pop_back() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  int tmp = array[back]; 

  if(size() == 1) {
    front = -1;
    back = -1;
  } else 
    back = prev(back);

  siz--;
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
  return siz;
}

tpt
void CircularArray<T>::clear() {
  T* tmp = new T[capacity];
  array = tmp;
  front = -1;
  back = -1;
  siz = 0;
}

tpt
T &CircularArray<T>::operator[](const int index) {
  if(index >= size() || index < 0) 
    throw std::runtime_error("Index out of bounds");
  return array[index];
}

tpt
void CircularArray<T>::sort() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");
  if(size() < 9999)
    selectionSort(array, size());
  else
    countingSort(array, size());
}

tpt
bool CircularArray<T>::is_sorted() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");

  bool sorted = true;
  for(int i=front; i<size()-1; i++) {
    if(array[i] > array[i+1]) sorted = false;
  }

  return sorted;
}

tpt
void CircularArray<T>::reverse() {
  if(is_empty()) 
    throw std::runtime_error("It's empty");
  T* tmp = new T[capacity];
  for(int i=size()-1, j=0; i>=0; i--, j++) {
    tmp[j] = array[i];
  }
  array = tmp;
}

tpt
string CircularArray<T>::to_string(string sep){
  string result = ""; 
  for(int i=front; i<size(); i++)
    result += std::to_string((*this)[i]) + sep;
  return result;    
}
