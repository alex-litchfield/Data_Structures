//NOTE: These are not necesssarily 100% correct or optimal
//They are simply what we typed in Lecture during Spring 2018.

//12 pm
template <class T> bool is_there(Node<T>* head, const T& x){

  for(Node<T>* p = head; p!=NULL; p = p->ptr){
    if(p->value == x){
      return true;
    }
  }
  return false;
}

template <class T>
void push_front(Node<T>* & head, T const& value){
  //if(!head){
  //If list is empty
  if(head == NULL){
    head = new Node<T>;
    head->value = value;
    head->ptr = NULL;
  }
  else{
    Node<T>* tmp = new Node<T>;
    tmp->value = value;
    tmp->ptr = head;
    head = tmp;
  }
}

template <class T>
void push_back(Node<T>* & head, T const& value){
  //if(!head){
  //If list is empty
  if(head == NULL){
    head = new Node<T>;
    head->value = value;
    head->ptr = NULL;
  }
  else{
    Node<T>* tmp = head;
    while(tmp->ptr){
      tmp = tmp->ptr;
    }
    tmp->ptr = new Node<T>;
    tmp->ptr->value = value;
    tmp->ptr->ptr = NULL;

    //Alternate
    tmp->ptr = new Node<T>;
    tmp = tmp->ptr;
    tmp->value = value;
    tmp->ptr = NULL;
  }
}

// 2pm lecture
template <class T> bool is_there(Node<T>* head, const T& x){

  Node<T>* tmp;
  for(tmp=head; tmp!=NULL; tmp=tmp->ptr){
    if(tmp->value == x){
      return true;
    }
  }
  return false;
}

template <class T> void push_front(Node<T>* & head, T const& value){
  Node<T>* tmp = new Node<T>;
  tmp->value = value;
  tmp->ptr = NULL;

  //If empty
  //if(head == NULL){
  if(!head){
    head = tmp;
  }
  else{
    tmp->ptr = head;
    head = tmp;
  }
}

// ALTERNATE
  Node<T>* tmp = new Node<T>;
  tmp->value = value;
  tmp->ptr = head;
  head=tmp;
}

template <class T> void push_back(Node<T>* & head, T const& value){
  Node<T>* tmp = new Node<T>;
  tmp->value = value;
  tmp->ptr = NULL;

  Node<T>* p = head; //For finding end of list

  if(!p){ //Empty list
    head = tmp;
    return;
  }

  while( p->ptr != NULL ) { p = p->ptr; }

  p->ptr = tmp;
}
