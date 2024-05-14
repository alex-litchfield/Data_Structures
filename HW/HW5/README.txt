HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.geeksforgeeks.org/
https://www.cplusplus.com/
Steven Haussmann

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  32 hours


TESTING & DEBUGGING STRATEGY:
std::cout, GDB, drmemory



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

Default Constructor: 
    UnrolledLL O(1)
    DS List same
    STL List same
Copy Constructor: 
    UnrolledLL O(  )
    DS List same
    STL List same
Operator= : 
    Unrolled O(1)
    DSList same
    STL List same
Destructor:
    Unrolled O( # of nodes )
    DSList O() same 
    STL List O() same
Size():
    Unrolled O(1) (c++ 11 used, would be the size itself in other versions)
    DSList O(1) same 
    STL List O() same
Empty():
    Unrolled O(1)
    DSList O() same 
    STL List O() same
Clear():
    Unrolled O( # of nodes )
    DSList O() same 
    STL List O() same
Front() - both styles:
    Unrolled O(1)
    DSList O() same 
    STL List O() same
Back() - both styles:
    Unrolled O(1)
    DSList O() same 
    STL List O() same
Push_front():
    Unrolled O( # of values in the node-1 )
    DSList O(1) due to only 1 value being in a node
    STL List O(1) due to only 1 value being in a node
Pop_front():
    Unrolled O( # of values in the node-2 )
    DSList O(1) due to only 1 value being in a node 
    STL List O(1) due to only 1 value being in a node
Push_back():
    Unrolled O(1)
    DSList O(1) same
    STL List O(1) same
Pop_back():
    Unrolled O( # of nodes )
    DSList O(1) same
    STL List O(1) same
Erase():
    Unrolled O( # of values in the mode minus 1 and minus the position in node's array that erasure occurs at)
    DSList O(1) due to only 1 value being in a node (no element shifting needs to occur)
    STL List O(1) due to only 1 value being in a node (no element shifting needs to occur)
Insert():
    Unrolled O( max( Max number of elements allowed to be in a node minus the position in the node's array that 
    inerstion occurs at, # of elements in the node minus 1 and minus the position in the node's array that insertion occurs at) )
    DSList O(1) due to only 1 value being in a node (no element shifting needs to occur) 
    STL List O(1) due to only 1 value being in a node (no element shifting needs to occur)
Begin():
    Unrolled O(1)
    DSList O() same 
    STL List O() same
End():
    Unrolled O(1)
    DSList O() same 
    STL List O() same
Print():
    Unrolled O()
    DSList Does not exist
    STL List Does not exist
Copy_list():
    Unrolled O( # of nodes times number of values within each node )
    DSList O( # of nodes in list ) due to only 1 value being in a node
    STL List O( # of nodes in list ) due to only 1 value being in a node
Destroy_list():
    Unrolled O( # of nodes in list ) - nodes can be deleted as a whole in every version
    DSList same
    STL List same

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


