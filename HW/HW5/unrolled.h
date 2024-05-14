#ifndef unrolled_h_
#define unrolled_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
const int NUM_ELEMENTS_PER_NODE = 6; //The max size of a node at all times

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  //Constructor 1 (No input value)
  Node() {
    next_=NULL;
    prev_=NULL;
    node_size=0;
  }
  //Constructor 2 (Input value for first value in node)
  Node(const T& v) {
    node_content[0]=v;
    next_=NULL;
    prev_=NULL;
    node_size=1;
  }

  // REPRESENTATION
  T node_content[NUM_ELEMENTS_PER_NODE]; //node array: holds contents of node
  int node_size;
  Node<T>* next_;
  Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL){
    ptr_=p;
    array_position=0;
  }
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*() {
    return (ptr_->node_content)[array_position];
  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter (added before a value is assigned)
    array_position++;
    if ( array_position>=ptr_->node_size) { 
      //we must move to a new node and were previously on the last value of the previous node's array
      ptr_ = ptr_->next_;
      array_position = 0;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { 
    // post-increment, e.g., iter++ (added after a value is assigned)
    list_iterator<T> temp(*this);
    array_position++;
    if ( array_position >= ptr_->node_size) { 
      //we must move to a new node and were previously on the last value of the previous node's array
      ptr_ = ptr_->next_;
      array_position = 0;
    }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (array_position==0) { 
      //we must move to a new node and were previously on the first value of the next node's array
      ptr_ = ptr_->prev_;
      array_position = ptr_->node_size-1;
    }
    else { //we are still on the same node
      array_position--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (array_position==0) {
      //we must move to a new node and were previously on the first value of the next node's array
      ptr_ = ptr_->prev_;
      array_position = ptr_->node_size-1;
    }
    else { //we are still on the same node
      array_position--;
    }
    return temp;
  }
  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    if (ptr_==NULL && r.ptr_==NULL) {
        return true;
    }
    return ptr_ == r.ptr_;
  }
  bool operator!=(const list_iterator<T>& r) const {
    if (ptr_==NULL && r.ptr_==NULL) {
      return false;
    }
    return ptr_ != r.ptr_;
  }
private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  //keeps track of the position within the node_contents (starts at 0)
  int array_position; 
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const {
    return head_->node_content[0];  
  }
  T& front() {
    return head_->node_content[0];
  }
  const T& back() const {
    return tail_->node_content[tail_->node_size-1];
  }
  T& back() {
    return tail_->node_content[tail_->node_size-1];
  }

  // modify the linked list structure
  void push_front(const T& v); //Adds given value to front of list, pushing all others 
  //forwards by 1 position
  void pop_front(); //Destroys first value in the list, pushing all others backwards by
  //1 position
  void push_back(const T& v); //Adds given value to end of the list
  void pop_back(); //Destroys the last value in the list

  iterator erase(iterator itr); //erases a givin value within the list
  iterator insert(iterator itr, const T& v); //inserts a value into the list, pushing 
  //all other values in front of it forwards by 1 position
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }
  void print(std::ostream& output); //prints contents of list

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};
// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) { //Adds given value to front of list,
  // pushing all others forwards by 1 position
  if (!head_)  {
    // initially empty list as a special case
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
  } 
  else {  // normal case: at least one node already
    if ((*head_).node_size==NUM_ELEMENTS_PER_NODE) { //if the first node's array is full
      Node<T>* newp = new Node<T>(v);
      newp->next_ = head_;
      head_->prev_ = newp;
      head_ = newp;
    }
    else { //if the first node's array is NOT full
      head_->node_size++;
      // shift elements forward
      for (int i = head_->node_size; i>0; i--) {
        head_->node_content[i] = head_->node_content[i-1];
      }
      head_->node_content[0] = v; //uses 0 instead of null
    }
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_front() { //Destroys first value in the list, pushing all 
  //others backwards by 1 position
  Node<T>* oldp = head_;
  if (head_ == tail_) {
    // special case: deleting the last node
    head_ = tail_;
  } 
  else { // normal case: more than 1 node currently exists
    if (head_->node_size!=1) { //if the first node's array has more than 1 value
      //shift elements backwards
      for (int i = 0; i<(head_->node_size-1); i++) {
        head_->node_content[i]=head_->node_content[i+1];
      }
      (head_->node_content)[head_->node_size-1] = 0; //uses 0 instead of null
      head_->node_size--;
    }
    else { //first node's array has 1 value
      head_ = head_->next_;
      delete oldp;
    }
  }
  --size_;
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) { //Adds given value to end of the list
  if (!tail_) { // special case: initially empty list
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
  } 
  else { // at least one node already
    if ((*tail_).node_size==NUM_ELEMENTS_PER_NODE) { //if the last node's array is full
      Node<T>* newp = new Node<T>(v);
      newp->prev_ = tail_;
      tail_->next_ = newp;
      tail_ = newp;
    }
    else { //if the last node's array is NOT full
      tail_->node_content[tail_->node_size] = v;
      tail_->node_size++;
    }
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() { //Destroys the last value in the list
  Node<T>* oldp = tail_;
  if (head_ == tail_) {
    // special case: deleting the last node
    head_ = tail_;
  } 
  else {    // normal case: more than 1 node currently exists
    if (tail_->node_size!=1) { //if the last node's array has more than 1 value
      (tail_->node_content)[tail_->node_size-1]=0; //uses 0 instead of null
      tail_->node_size--;
    }
    else { //last node's array has 1 value
      tail_->prev_->next_ = NULL;
      tail_ = tail_->prev_;
      delete oldp;
    }
  }
  --size_;
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right) { 
  return !(left==right); 
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) { 
  //erases a givin value within the list
  assert (size_ > 0);
  iterator result(itr.ptr_);
  if(itr.array_position==NUM_ELEMENTS_PER_NODE-1 || (itr.array_position==0 && itr.ptr_->node_size==1) ) {
    result.ptr_ = itr.ptr_->next_;
  } 
  else {
    result.array_position = itr.array_position+1;
  }
  // One node left in the list and one value in the node
  if (itr.ptr_ == head_ && head_ == tail_ && itr.ptr_->node_size == 1) {
    head_ = tail_ = NULL;
    delete itr.ptr_;
    --size_;
  }
  // Removing the head in a list with one value in the node
  else if (itr.ptr_ == head_ && itr.ptr_->node_size == 1) {
    head_ = head_->next_;
    head_->prev_ = NULL;
    delete itr.ptr_;
    --size_;
  }
  // Removing the tail in a list with one value in the node
  else if (itr.ptr_ == tail_ && itr.ptr_->node_size == 1) {
    tail_ = tail_->prev_;
    tail_->next_ = NULL;
    delete itr.ptr_;
    --size_;
  }
  // Normal remove
  else {
    if(itr.ptr_->node_size == 1) {  //removing a node with one value in it (not tail or head)
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
      iterator result2 (itr.ptr_->next_);
      delete itr.ptr_;
      --size_;
      return result2;
    } 
    else if (itr.array_position<(itr.ptr_->node_size)) { //removing a value within a node (more values remain)
      for (int i = itr.array_position; i<(itr.ptr_->node_size-1); i++) {
        itr.ptr_->node_content[i]=itr.ptr_->node_content[i+1];
      }
      if (itr.array_position>0 && itr.array_position!=itr.ptr_->node_size-1) {
        itr.ptr_->node_content[itr.ptr_->node_size-1] = 0; //uses zero instead of NULL
      }
      itr.ptr_->node_size--;
      --size_;
      result.array_position = itr.array_position;
    }
  }
  return result;
}

template <class T>//done
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  //inserts a value into the list, pushing all other values in front of it forwards
  //by 1 position
  ++size_ ;
  Node<T>* p;
  if(itr.ptr_->node_size == NUM_ELEMENTS_PER_NODE) { //inserting in a full node
    p = new Node<T>(v);
    p->node_size--;
    p->prev_ = itr.ptr_;
    p->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = p;
    itr.ptr_->next_ = p;
    if (itr.ptr_ == tail_) {
      tail_ = p;
    }
    int spot_counter=0; //spots which were replaced with zero
    for (int i = itr.array_position; i<NUM_ELEMENTS_PER_NODE; i++) {
      p->node_content[spot_counter] = itr.ptr_->node_content[i];
      itr.ptr_->node_content[i] = 0; //uses 0 instead of null
      spot_counter++;
      itr.ptr_->node_size--;
      p->node_size++;
    }
    itr.ptr_->node_content[itr.array_position] = v;
    itr.ptr_->node_size++;
  } 
  else { // inserting into a node which is not yet filled
    itr.ptr_->node_size++;
    for(int i=itr.ptr_->node_size-1;i>itr.array_position;i--) {
      itr.ptr_->node_content[i] = itr.ptr_->node_content[i-1];
    }
    itr.ptr_->node_content[itr.array_position] = v;
  }
  iterator result(itr.ptr_);
  result.array_position=itr.array_position;
  return iterator(result);
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = NULL;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>();
  for(int i = 0; i<old.head_->node_size; i++) {
    head_->node_size++;
    head_->node_content[i] = old.head_->node_content[i];
  }
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>();
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    for(int i = 0; i<old_p->node_size; i++) {
        tail_->node_size++;
        tail_->node_content[i] = old_p->node_content[i];
    }
    old_p = old_p->next_;
  }
}

template <class T>
void UnrolledLL<T>::destroy_list() {
  while (head_) {
    Node<T>* p = head_;
    head_ = head_->next_;
    delete p;
  }
  head_ = tail_ = NULL;
  size_ = 0;
}

//prints everything in the list by sending it to the ostream
template <class T>
void UnrolledLL<T>::print(std::ostream& output)
{
  UnrolledLL<T>::iterator order_it;
  output << "UnrolledLL, size: " << size_ << std::endl;
  int numbers_printed = 0;
  for (order_it = iterator(head_); order_it != iterator(NULL); order_it++) {
    if (numbers_printed == 0) {
      output << " node:[" << order_it.ptr_->node_size << "]";
    }
    output << " " << *order_it;
    numbers_printed++;
    if (numbers_printed==order_it.ptr_->node_size) {
      output << std::endl;
      numbers_printed = 0;
    }
  }
}

#endif