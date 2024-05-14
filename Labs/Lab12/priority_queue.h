#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;
  // swapping elements up the heap to parents
  void percolate_up(int index){
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return; 
    int parent = (index - 1) / 2; 
    while (parent >= 0) {
      if (m_heap[parent] > m_heap[index]) {
          T temp = m_heap[parent];
          m_heap[parent] = m_heap[index];
          m_heap[index] = temp; 
          index = parent;
          parent = (index - 1) / 2; 
      }
      else 
        break; 
    }
  }
  void percolate_down(int index){
    if (index < 0 || index >= m_heap.size() || m_heap.size() == 1)
        return;
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int size = m_heap.size();
    int child; 
    while (left < size) {
      if (right < size && m_heap[right] < m_heap[left])
          child = right; 
      else 
          child = left; 
      if (m_heap[index] >= m_heap[child]) {
        int temp = m_heap[index]; 
        m_heap[index] = m_heap[child]; 
        m_heap[child] = temp;
        index = child; 
        left = (2*index)+1; 
        right = left+1; 
      }
      else 
        break; 
    }
  }

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    this->m_heap = values;
    int n = this->m_heap.size();
    for(int c = (n-1)/2; c >= 0; c--){
      percolate_down(c);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }
  //O(log n)
  void push( const T& entry )
  {
    m_heap.push_back(entry);
    percolate_up(m_heap.size()-1); 
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap[0] = m_heap.back(); 
    m_heap.pop_back(); 
    percolate_down(0); 
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }

  void heapify(std::vector<T> &heap) {
    for(int c = (heap.size()-1)/2; c >= 0; c--){
      percolate_down(c);
    }
  }

  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    int size = heap.size(); 
    int left, right; 
    if (size <= 1)
      return true; 
    for (int c = 0; c < size; c++) {
      left = (2*c)+1; 
      right = left+1; 
      //value must be less than or equal to value of both children 
      if ((left < size && heap[c] >= heap[left]) || 
        (right < size && heap[c] >= heap[right]))
          return false; 
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


  template <class T>
  void max_heapify(std::vector<T> & arr, int i, int size_)
  {
      int largest, l = (2*i) + 1, r = l + 1;

      if(l < size_ && arr[l] > arr[i])
          largest = l;
      else
          largest = i;

      if(r < size_ && arr[r] > arr[largest])
          largest = r;

      if(largest != i)
      {
          std::swap(arr[i], arr[largest]);
          max_heapify(arr, largest, size_);
      }
  }
  template <class T>
  void build_max_heap(std::vector<T> & arr)
  {
      for(int i = (arr.size() / 2); i >= 0; i--)
      max_heapify(arr, i, arr.size());
  }

  template <class T>
  //sort the data in place
  void heap_sort( std::vector<T> & v )
  {
    build_max_heap(v);
    int sz = v.size();
    for(int i = v.size() - 1; i > 0; i--)
    {
          std::swap(v[0], v[i]);
          sz--;
          max_heapify(v, 0, sz);
      }
  }


#endif