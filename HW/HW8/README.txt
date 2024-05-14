HOMEWORK 8: ROPES


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.cplusplus.com/reference/string/string/substr/
https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
https://www.geeksforgeeks.org/count-the-nodes-of-the-given-tree-whose-weight-has-x-as-a-factor/
https://www.cplusplus.com/doc/tutorial/operators/
https://www.programiz.com/dsa/complete-binary-tree


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor: O(p) - The copy constructor is recursive in that it continues 
running until it hits a dead end, ie a leaf.

Construct from Node*: O(p) - The constructor utilizes the sizecheck function, 
which goes through every leaf and adds them up to get the size.

Index: O(p) - The index function keeps running until it hits a leaf, at which point 
it indexes (normal index) the value, which would be a value of O(1) in itself, 
meaning overall it is O(p).

Report: O(n) - The report function, in its worst case, goes through a for loop where
it adds each character requested into the given string. Therefore, if it were all
characters in the rope were requetsed, it would be O(n).

iterator operator++: O(p) - The operator++, whether moving up or down, will attempt
to find its way back to a leaf node, therefore being of O(p) in nearly all circumstances.

Split: O(p) - The split function uses two different while loops. The first while loops
attempts to locate the position of the split, resulting in O(p). The second attempts to
move back up the tree and cuts any ties with the left side, seperating the two trees.

Concat: O(p) - The constructor utilizes the sizecheck function, which goes through every
leaf and adds them up to get the size. If not for this it would be O(1).


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

I tested the index cases for if the index was the first character in a leaf's value, a 
middle characters in a leaf's value, and an ending character in a leaf's value.
Concat is pretty standard, so I didn't make another one as it would do the same as the
given test case. Report has the same reasoning. Copy and assignment are used enough
throughout the code that if something could have went wrong, it would have. Finally,
split was already shown to be able to make a node sprout two more leaves and successfuly
seperate the trees, as well as just break the trees apart in normal cases.

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

