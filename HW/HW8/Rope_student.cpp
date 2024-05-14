/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	// if i have right subtree, find left most element of those
    if (ptr_->right != NULL) {
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) {
        ptr_ = ptr_->left;
      }
    } 
    else {
      // Keep going up as long as I'm my parent's right child
      while (ptr_->parent && ptr_->parent->right == ptr_) {
        ptr_ = ptr_->parent;
      }
      // Go up one more time
      ptr_ = ptr_->parent;
    }
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	if (!root) {
		return rope_iterator(NULL);
	}
    Node* p = root;
    while (p->left) {
		p = p->left;
	}
    return rope_iterator(p);
}

Rope::Rope(){
	size_=0; //total size of rope
	root=NULL; // root is top element of rope
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
//Constructor with node p as parameter
Rope::Rope(Node* p){
	root = p;
	size_= sizecheck(root);
}

//Destructor helper function
void Rope::destroy_rope(Node* p) {
  if (!p) return;
  this->destroy_rope(p->left);
  this->destroy_rope(p->right);
  delete p;
}

//Destructor
Rope::~Rope(){
	this->destroy_rope(root);
	root = NULL;
}

//Copy helper function
Node* Rope::copy_rope(const Node *old_root, Node *ptr1) {
  if (old_root != NULL) {
    Node* new_root = new Node();
    new_root->weight = old_root->weight;
    new_root->parent = ptr1;
    new_root->value = old_root->value;
    new_root->left = copy_rope(old_root->left, new_root);
    new_root->right = copy_rope(old_root->right, new_root);
    return new_root;
  }
  return NULL;
}

//Copy Constructor
Rope::Rope(const Rope &r) {
  root = copy_rope(r.root);
  size_ = r.size_;
}

//Assignment operator
Rope& Rope::operator= (const Rope& r){
	if (&r != this) {
      this->destroy_rope(root);
      root = this->copy_rope(r.root, NULL);
      size_ = r.size_;
    }
    return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
  //checks for an invalid index
  if (i>=size_) {
    return false;
  }
  //index the char that you need
  Node *temp = root; 
  while (true) {
    //if the temp node is pointing to a leaf node, we get the character within it.
    if (is_leaf(temp)) {
      c=temp->value[i];
      return true;
    }
    //when i is less than the weight of the node, we move to the left.
    else if (i<temp->weight) {
      temp=temp->left;
    }
    //when i is greater than or equal to the weight of the node, we move right.
    else if (i>=temp->weight) {
      i=i-temp->weight;
      temp=temp->right;
    }
  }
}

//checks the size of said node
int Rope::sizecheck(Node* node) {
  //Counts the size of all leaves below.
  if(node->left == NULL && node->right == NULL) {
    return node->weight;
  }
  if (node->left != NULL && node -> right != NULL) {
    return sizecheck(node->right) + sizecheck(node->left);
  } 
  if (node->left != NULL) {
    return sizecheck(node->left);
  }
  if (node->right != NULL) {
    return sizecheck(node->right);
  }
  return 0;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
  //attaches the two ropes together, making each root of the old ropes
  //become children of the new root of the combined version
  Node* right_node = copy_rope(r.root, NULL);
  Node* new_root = new Node;
  new_root -> parent = NULL;
  new_root -> right = right_node;
  new_root -> weight = this -> size_;
  right_node -> parent = new_root;
  new_root -> left = this -> root;
  this -> root -> parent = new_root;
  this -> root = new_root;
  this -> size_ = sizecheck(root);
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
  s=""; //ensures that string is cleared during each usage
  //when i=j, only put 1 character in the string
  if (i==j) {
    char c;
    index(i,c);
    s=c;
    return true;
  }
  //invalid check
  else if (i>j || i<0 || j>=size_) {
    return false;
  }
  //put any characters within the range into the string
  else {
    char c;
    for (int k=i; k<(j+1); k++) {
      index(k,c);
      s=s+c;
    }
    return true;
  }
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
  //Checks if the split is valid, and otherwise returns the current rope.
	if(i > size_ || i < 0) {
		return *this;
	}
	Node* temp = root;
	//While the root's left OR right values exist:
	while (temp->left != NULL || temp->right !=NULL) {
    //if the weight is bigger than i and left exists - move left
		if (temp->weight > i && temp->left !=NULL){
			temp = temp->left;
		}
    //if the weight is less than or equal to than i and right exists - move right
    //and update i value
		if (temp->weight <= i && temp->right != NULL){
      i = i-temp->weight;
			temp = temp->right;
		}
	}
	//To_edit is the node that will be created or disconnected.
	//Parental is the parent node of another.
  Node* to_edit;
  Node* parental;
	Node* left;
	Node* right;
	left = root;
	std::string full = temp->value;
	int split_index;
	//Check if we need to split the node
	if(i == 0){ //this means we DO NOT need to split
		parental = temp->parent;
    to_edit = temp;
		if(parental->right == temp) {
			parental->right = NULL;
		}
		if(parental->left == temp) {
			parental->left = NULL;
		}
    split_index = to_edit->weight;
		to_edit->parent = NULL;
	}
  //if node DOES need to be split, we do that, reassign 
  //parent nodes and assign substrings to the values of the new left and right nodes
	else { 
		to_edit = new Node;
		split_index = to_edit->weight - i;
    parental = temp->parent;
		to_edit->value = full.substr(i, split_index);
    temp->value = full.substr(0, i);
		temp->weight = temp->value.length();
	}
  //while the "parental" node is NOT the right node's parent, we move up
  //the rope by setting parental to parental's parent.
	while(parental->parent->right != parental) {
		parental = parental->parent;
	}
	//Updates and moves remainging nodes and their repective variables
  Node* ending_right = new Node;
	right = parental->right;
	right->parent = NULL;
  parental->weight = parental->weight - split_index;
	parental->right = NULL;
  ending_right->left = to_edit;
	ending_right->right = right;
	to_edit->parent = ending_right;
	ending_right->weight = sizecheck(ending_right->left);
	ending_right->parent = NULL;
	rhs.root = ending_right;
	rhs.size_ = sizecheck(ending_right);
	left = root;
	left->weight = sizecheck(left->left);
	size_ = sizecheck(left);
	return *this;
}
