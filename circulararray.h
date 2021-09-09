#include <iostream>
using namespace std;
#define tpt template <class T>

tpt
struct CircularArray {
  T *array;
  int capacity;
  int back, front;
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

}

tpt
void CircularArray<T>::push_back(T data) {

}

tpt
void CircularArray<T>::insert(T data, int pos) {

}

tpt
T CircularArray<T>::pop_front() {

}

tpt
T CircularArray<T>::pop_back() {

}

tpt
bool CircularArray<T>::is_full() {

}

tpt
bool CircularArray<T>::is_empty() {

}

tpt
int CircularArray<T>::size() {

}

tpt
void CircularArray<T>::clear() {

}

tpt
T &CircularArray<T>::operator[](const int) {

}

tpt
void CircularArray<T>::sort() {

}

tpt
bool CircularArray<T>::is_sorted() {

}

tpt
void CircularArray<T>::reverse() {

}

tpt
string CircularArray<T>::to_string(string sep){
  string result = ""; 
  for (int i = 0; i < size(); i++)
    result += std::to_string((*this)[i]) + sep;
  return result;    
}
