// first element in list (or only element)
if (head == p) { 
  head = p -> next;
  delete p;
  //} else if (p->next == NULL) { // last element in list
  //q -> next = NULL;
  //delete p;
} else {
  // general case
  q -> next = p-> next;
  delete p;
}


// Node*<T> my_original_list is 1, -3, 7
// Node*<T> my_new_list = NULL;
//First call CopyAll(my_original_list, my_new_list)   my_new_list is NULL
//Next call CopyAll( my_original_list->next, my_new_list->next )     my_new_list has 1
//Next call CopyAll( my_original_list->next->next, my_new_list->next->next )     my_new_list has 1, -3
//Next call CopyAll( my_original_list->next->next->next, my_new_list->next->next->next )     my_new_list has 1, -3, 7
//Next call CopyAll( my_original_list->next->next->next->next, my_new_list->next->next->next->next )  "old_head" is NULL

template <class T> 
void CopyAll(Node<T>* old_head,  Node<T>*& new_head) {
  if (old_head == NULL) {
    new_head = NULL;
  } else {
    new_head = new Node<T>;
    new_head -> value = old_head -> value;
    CopyAll( old_head->next, new_head -> next  );
  }
}





template <class T> void RemoveAll(Node<T>* head) {
  if (head == NULL) {
    // do nothing
  } else {
    /*    if (head->next == NULL) {
      delete head;
      head = NULL;
      return;
    } 
    */
    RemoveAll(head->next);
    delete head;
    //head = NULL;
  }
}



// the double linked insert code
Node<T>* tmp = new Node<T>(15);
tmp->next = p->next;    // 15 -> 3
p->next = tmp;          // 1 -> 15
tmp->next->prev = tmp;  // 3 -> 15
tmp->prev = p;          // 15 -> 1
// still need to write the corner cases...  



// the double linked remove code
p->prev->next = p->next; // 13 -> 3
p->next->prev = p->prev; // 3 -> 13
delete p;
// still need to write the corner cases...  

// what if p == head?
// p->prev->next     (NULL)->next
// dereferencing NULL -> crash