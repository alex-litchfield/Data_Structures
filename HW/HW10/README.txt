HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

TA Steven Haussmann
https://www.geeksforgeeks.org/set-in-cpp-stl/
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| vector   | nlog(n)  |   n^2    |  nlog(n) | nlog(n)  |  nlog(n) | l^3*n^2  |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| list     |  nlog(n) |     n^2  |  nlog(n) |  nlog(n) |  nlog(n) |  l^3*n^2 |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| bst      |  nlog(n) | nlog(n)  |  nlog(n) |  nlog(n) |  nlog(n) |  l^3*n^2 |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| pq       |  nlog(n) |    X     |  nlog(n) |  nlog(n) |  nlog(n) |     X    |
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| hash     |     X    |     n    |     n    |    X     |      X   |  l^3*n^2 |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

Estimates: I beieve that in the place of n, for every function and data structure,
would go the number of items input into the data structure. As for l within the
longest substrings, i believe this refers to the number of characters within each
word.

vector_sort
    Time for 10,000 length 5 strings: 0.011992
    Time for 50,000 length 5 strings: 0.03952
    Time for 100,000length 5 strings: 0.079995
    Time for 500,000length 5 strings: 0.391998
vector_remove_duplicates
    Time for 5,000 length 3 strings: 0.235998
    Time for 10,000 length 3 strings: 0.811993
    Time for 20,000 length 3 strings: 2.69994
    Time for 50,000 length 3 strings: 11.055
vector_mode
    Time for 10,000 length 4 strings: 0.015037
    Time for 50,000 length 4 strings: 0.04369
    Time for 100,000 length 4 strings: 0.075995
    Time for 500,000 length 4 strings: 0.367998
vector_closest_pair
    Time for 10,000 8 digit ints: 0.007995
    Time for 50,000 8 digit ints: 0.043995
    Time for 100,000 8 digit ints: 0.071425
    Time for 500,000 8 digit ints: 0.335997
vector_first_sorted
    Time for 10,000 5 letter strings: 0.014248 (sorts first 50)
    Time for 50,000 5 letter strings: 0.031455 (sorts first 50)
    Time for 100,000 5 letter strings: 0.071996 (sorts first 50)
    Time for 500,000 5 letter strings: 0.36797 (sorts first 50)
vector_longest_substring
    Time for 500 20 letter strings: 1.36697
    Time for 1000 20 letter strings: 5.4837
    Time for 2000 20 letter strings: 21.888
    Time for 3000 20 letter strings: Command Terminated
list_sort
    Time for 10,000 5 letter strings: 0.015239
    Time for 50,000 5 letter strings: 0.067282
    Time for 100,000 5 letter strings: 0.127996
    Time for 500,000 5 letter strings: 0.676001
list_remove_duplicates
    Time for 5,000 3 letter strings: 0.371992
    Time for 10,000 3 letter strings: 1.30231
    Time for 20,000 3 letter strings: 4.31133
    Time for 50,000 3 letter strings: 17.8151
list_mode
    Time for 10,000 4 letter strings: 0.011995
    Time for 50,000 4 letter strings: 0.063302
    Time for 100,000 4 letter strings: 0.123663
    Time for 100,000 4 letter strings: 0.663996
list_closest_pair
    Time for 10,000 8 digit ints: 0.014678
    Time for 50,000 8 digit ints: 0.055394
    Time for 100,000 8 digit ints: 0.123996
    Time for 500,000 8 digit ints: 0.619227
list_first_sorted
    Time for 10,000 strings: 0.018933 (sorts first 50)
    Time for 50,000 strings: 0.055998 (sorts first 50)
    Time for 100,000 strings: 0.111994 (sorts first 50)
    Time for 500,000 strings: 0.703319 (sorts first 50)
list_longest_substring
    Time for 500 20 letter strings: 1.688
    Time for 1000 20 letter strings: 6.77106
    Time for 2000 20 letter strings: 27.7758
    Time for 2000 20 letter strings: Command terminated
bst_sort
    Time for 10,000 5 letter strings: 0.015992
    Time for 50,000 5 letter strings: 0.063996
    Time for 100,000 5 letter strings: 0.123831
    Time for 500,000 5 letter strings: 0.707611
bst_remove_duplicates
    Time for 5,000 3 letter strings: 0.019527
    Time for 10,000 3 letter strings: 0.023676
    Time for 20,000 3 letter strings: 0.035959
    Time for 50,000 3 letter strings: 0.063877
bst_mode
    Time for 10,000 4 letter strings: 0.015625
    Time for 50,000 4 letter strings: 0.055996
    Time for 100,000 4 letter strings: 0.11106
    Time for 500,000 4 letter strings: 0.519998
bst_closest_pair
    Time for 10,000 8 digit ints: 0.015761
    Time for 50,000 8 digit ints: 0.055756
    Time for 100,000 8 digit ints:  0.10399
    Time for 500,000 8 digit ints:  0.63997
bst_first_sorted
    Time for 10,000 5 letter strings: 0.015996 (sorts first 50)
    Time for 50,000 5 letter strings: 0.059995
    Time for 100,000 5 letter strings: 0.111997
    Time for 500,000 5 letter strings: 0.723997
bst_longest_substring
    Time for 500 20 letter strings: 2.21598
    Time for 1000 20 letter strings: 9.05
    Time for 2000 20 letter strings: Command Terminated
    Time for 3000 20 letter strings: Command terminated
hash_table_remove_duplicates
    Time for 5,000  3 letter strings: 0.015995
    Time for 10,000 3 letter strings: 0.015995
    Time for 20,000 3 letter strings: 0.023995
    Time for 50,000 3 letter strings: 0.035076
hash_table_mode
    Time for 10,000 4 letter strings: 0.011796
    Time for 50,000 4 letter strings: 0.031996
    Time for 100,000 4 letter strings: 0.063352
    Time for 500,000 4 letter strings: 0.259959
hash_table_longest_substring
    Time for 500 20 letter strings:  1.89179
    Time for 1000 20 letter strings: 7.57992
    Time for 2000 20 letter strings: Command terminated
    Time for 3000 20 letter strings: Command terminated
priority_queue_sort
    Time for 10,000 5 letter strings: 0.011953
    Time for 50,000 5 letter strings: 0.079995
    Time for 100,000 5 letter strings: 0.147996
    Time for 500,000 5 letter strings: 0.751996
priority_queue_mode
    Time for 10,000 4 letter strings: 0.019962
    Time for 50,000 4 letter strings: 0.075275
    Time for 100,000 4 letter strings: 0.135995
    Time for 500,000 4 letter strings: 0.744
priority_queue_closest_pair
    Time for 10,000 8 digit ints: 0.015995
    Time for 50,000 8 digit ints: 0.059995
    Time for 100,000 8 digit ints: 0.123997
    Time for 500,000 8 digit ints: 0.579104
priority_queue_first_sorted
    Time for 10,000 5 letter strings: 0.011961 (sorts first 50)
    Time for 50,000 5 letter strings: 0.027995 (sorts first 50)
    Time for 100,000 5 letter strings: 0.047948 (sorts first 50)
    Time for 500,000 5 letter strings: 0.192003 (sorts first 50)



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


My original predictions to the correct O notations were very different.
Upon my first attempt at filling out the chart, I only got 14 out of 30
correct. Of course, this was before I made a complete set of BST functions
or any PQ functions. Regardless, I have found that the times between each
function, regardless of the data structure, tend to be very close when
their O notation is the same within the chart. While these results were not
in themselves suprising, this homework, especially the chart and seeing all
the times through submitty, will certainly influence my choice in data
structures in the future. For example, hash tables can be extremly efficient
in the cases of removing duplicates and finding the mode. However, they
cannot complete 3 of the required tasks in a reasonable (or possible) way.
Priority queues were an interesting structure to see and fun to learn,
however I am still quite unsure of their usage in the real world. As far as 
I can see, they are just as efficient as every other data structure we have
used (excluding hash tables) when referring to common functions. Not to mention
they cannot perform two of the given operations. From what I have found thus far,
the most efficient data structures we have used were vectors, lists, and maps/sets
(BST). The only reason I might choose BSt over something else would be if I want
to remove duplicates more efficiently. If I were to want duplicates, I would
probably choose vectors as they are easier for me to use (even though lists would
just as valid of an answer).



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
