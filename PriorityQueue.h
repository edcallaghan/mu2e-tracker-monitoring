// Ed Callaghan
// Basic wrapper of stl-based-heap used as a queue
// August 2025

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <algorithm>
#include <utility>
#include <vector>

using priority_t = unsigned int;

template<typename T>
struct KeyedComparison{
  template<typename U>
  using Pair = std::pair<priority_t, U>;
  bool operator()(Pair<T> lhs, Pair<T> rhs){
    return lhs.first < rhs.first;
  }
};

template<typename T>
class PriorityQueue{
  public:
    template<typename U>
    using Pair = std::pair<priority_t, U>;

    PriorityQueue(size_t);
    void push(T, priority_t=0);
    T pop();

  protected:
    std::vector< Pair<T> > buffer;
    KeyedComparison<T> compare;

  private:
    /**/
};

template<typename T>
PriorityQueue<T>::PriorityQueue(size_t size){
  this->buffer.reserve(size);
  std::make_heap(this->buffer.begin(), this->buffer.end(), this->compare);
}

template<typename T>
void PriorityQueue<T>::push(T item, priority_t priority){
  auto pair = std::make_pair(priority, item);
  this->buffer.push_back(pair);
  std::push_heap(this->buffer.begin(), this->buffer.end(), this->compare);
}

template<typename T>
T PriorityQueue<T>::pop(){
  std::pop_heap(this->buffer.begin(), this->buffer.end(), this->compare);
  T rv = this->buffer.back().second;
  this->buffer.pop_back();
  return rv;
}

#endif
