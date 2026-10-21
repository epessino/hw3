#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  Heap(int m = 2, PComparator c = PComparator());
  ~Heap();
  void push(const T& item);
  T const & top() const;
  void pop();
  bool empty() const;
  size_t size() const;

private:
  std::vector<T> data_;
  int m_;
  PComparator comp_;

  void trickleUp(size_t idx);
  void trickleDown(size_t idx);
};

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m), comp_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  if (empty()) {
    throw std::underflow_error("top() called on empty heap");
  }
  return data_[0];
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if (empty()) {
    throw std::underflow_error("pop() called on empty heap");
  }
  data_[0] = data_.back();
  data_.pop_back();
  if (!data_.empty()) {
    trickleDown(0);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleUp(size_t idx)
{
  while (idx > 0) {
    size_t parent = (idx - 1) / m_;
    if (comp_(data_[idx], data_[parent])) {
      std::swap(data_[idx], data_[parent]);
      idx = parent;
    } else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t idx)
{
  size_t n = data_.size();
  while (true) {
    size_t first = m_ * idx + 1;
    if (first >= n) {
      break;
    }
    size_t best = first;
    for (size_t c = first + 1; c < first + m_ && c < n; ++c) {
      if (comp_(data_[c], data_[best])) {
        best = c;
      }
    }
    if (comp_(data_[best], data_[idx])) {
      std::swap(data_[idx], data_[best]);
      idx = best;
    } else {
      break;
    }
  }
}

#endif