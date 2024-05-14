HOMEWORK 3: CONNECT FOUR


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.educative.io/edpresso/how-to-find-the-length-of-an-array-in-cpp
https://stackoverflow.com/questions/21833933/c-equivalence-to-self-objectpython
https://www.tutorialspoint.com/cplusplus/cpp_copy_constructor.htm
TA: Steven Haussmann


Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  36



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four) O(n) or O(m)

insert (including checking for connected four) O(n+m) or (2n)

numTokensInColum O(1)

numTokensInRow O(n)

numColumns O(1)

numRows O(1)

print O(n*m)

clear O(2m)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used a combination of Dr. Memory (for memory leaks) and std::cout to help me keep track of variables to keep them
in bounds, especially in for loops. My corner cases were tested by my student designed tests. They made sure the
boundaries of the board could have tokens added to them AND that win conditions could be found when a token was
added to a boundary.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

