HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://en.cppreference.com/w/cpp/numeric/random/srand
https://stackoverflow.com/questions/27024269/select-random-element-in-an-unordered-map
https://en.cppreference.com/w/cpp/numeric/random
https://www.cplusplus.com/
https://www.w3schools.com/CPP/default.asp
https://stackoverflow.com/questions/5616421/increment-mapstring-int-using-operator
Steven Haussmann



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?

O(m*(p^(w-1)))
The map structure's memory uses the number of unque words in the file in every instance,
as this a defining characteristic of what a map is. This is then multiplied by the 
average number of words to follow a particular word, but to the power of the number of 
windows minus 1. This is due to the fact that the window number represents the number of 
words that we find in a chain.

What is the order notation for performance (running time) of each of
the commands?

Load: O(n*logm) - Due to the while loop taking in every word in the text file, it uses n.
      Logm comes from the fact that a map's standard O notation is log of its size, which
      in this case is logm, where m is the number of unique words in the file.
Print: O(m*p^(w-1)) - The biggest map uses the number of unique words in the file, or m.
       this is then multiplied by p, the average number of words observed to follow a
       particular word, to the power of w-1, or the window size minus 1. This use of p
       and w basically represents how deep each inner map goes within the overarching map
       of unique words.
Generate: O(x*m*p^(w-1)) - Generate uses an x as a memory parameter as the command loops
                           based on the number of words to generate. It is then
                           m and p^(w-1) for the same reasons as print uses these. In
                           short, generate loops through the overarching map based on
                           m*p^(w-1).
Quit: O(1) - It just breaks if called.

EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


