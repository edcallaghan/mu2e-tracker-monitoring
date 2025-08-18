// Ed Callaghan
// Basic wrapper of stl-based-heap used as a queue
// August 2025

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <algorithm>
#include <mutex>
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
    size_t size();
    void push(T, priority_t=0);
    T pop();

  protected:
    std::vector< Pair<T> > buffer;
    KeyedComparison<T> compare;
    std::mutex mutex;

  private:
    /**/
};

template<typename T>
PriorityQueue<T>::PriorityQueue(size_t size){
  this->buffer.reserve(size);
  std::make_heap(this->buffer.begin(), this->buffer.end(), this->compare);
}

template<typename T>
size_t PriorityQueue<T>::size(){
  std::lock_guard guard(this->mutex);
  auto rv = this->buffer.size();
  return rv;
}

template<typename T>
void PriorityQueue<T>::push(T item, priority_t priority){
  std::lock_guard guard(this->mutex);
  auto pair = std::make_pair(priority, item);
  this->buffer.push_back(pair);
  std::push_heap(this->buffer.begin(), this->buffer.end(), this->compare);
}

template<typename T>
T PriorityQueue<T>::pop(){
  std::lock_guard guard(this->mutex);
  std::pop_heap(this->buffer.begin(), this->buffer.end(), this->compare);
  T rv = this->buffer.back().second;
  this->buffer.pop_back();
  return rv;
}

#endif
