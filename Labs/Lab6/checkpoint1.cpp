#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {
  Node<T> *p, *c, *n;
  p=NULL;
  c=input;
  while (c!=NULL) {
    n=c->ptr;
    c->ptr=p;
    p=c;
    c=n;
  }
  input=p;
}

template <class T>
void reverse2(Node<T>* &input) {
  //IDK HOW TO DO RECURSIVE WITHOT 
  Node<T> *p, *c, *n;
  p=NULL;
  c=input;
  if (c==NULL) {
    input=p;
  }
  else {
    n=c->ptr;
    c->ptr=p;
    p=c;
    c=n;
    reverse2(input->ptr);
  }
}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");
  std::cout<<std::endl;

  my_list->value = 1; 
  my_list->ptr->value = 2;
  my_list->ptr->ptr=NULL;
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");
  std::cout<<std::endl;

  my_list->value = 1; 
  my_list->ptr=NULL;
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");
  std::cout<<std::endl;

  std::cout << "List of size 0... is set to null" << std::endl;
  Node<int>* my_list2 = new Node<int>; 
  my_list2->ptr = NULL; //OR IS "ptr" switched with "value"?
  print(my_list2,"my_list before");
  reverse(my_list2);
  print(my_list2,"my_list after ");
  std::cout<<std::endl;

  //RECURSIVE TESTS

  Node<int>* my_list3 = new Node<int>; 
  my_list3->value = 1; 
  my_list3->ptr = new Node<int>;
  my_list3->ptr->value = 2;
  my_list3->ptr->ptr = new Node<int>;
  my_list3->ptr->ptr->value = 3;
  my_list3->ptr->ptr->ptr = new Node<int>;
  my_list3->ptr->ptr->ptr->value = 4;
  my_list3->ptr->ptr->ptr->ptr = NULL;
  print(my_list3,"my_list before");
  reverse2(my_list3);
  print(my_list3,"my_list after ");
  std::cout<<std::endl;

  my_list3->value = 1; 
  my_list3->ptr->value = 2;
  my_list3->ptr->ptr=NULL;
  print(my_list3,"my_list before");
  reverse2(my_list3);
  print(my_list3,"my_list after ");
  std::cout<<std::endl;

  my_list3->value = 1; 
  my_list3->ptr=NULL;
  print(my_list3,"my_list before");
  reverse2(my_list3);
  print(my_list3,"my_list after ");
  std::cout<<std::endl;

  std::cout << "List of size 0... is set to null" << std::endl;
  Node<int>* my_list4 = new Node<int>; 
  my_list4->ptr = NULL; //OR IS "ptr" switched with "value"?
  print(my_list4,"my_list before");
  reverse2(my_list4);
  print(my_list4,"my_list after ");
  std::cout<<std::endl;


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in Checkpoint 2!

}

// ===========================================================================
