HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  Alex Litchfield


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Steven Haussmann
Hayden
https://stackoverflow.com/questions/1854499/is-stringcompare-reliable-to-determine-alphabetical-order
https://www.cplusplus.com/
https://www.geeksforgeeks.org/c-plus-plus/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 13 >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order: O(max(ologo, q)) - Max value of either the times the for loop runs (q) or the 
number of the times the sort function returns something (ologo).

add_item: O(clog(c)) - The number of times the sort function returns something (clog(c))

print_orders_by_time: O(o*q) - The nested for loop runs based on the number of orders not
filled/expired times the number of items within the order.

print_orders_by_id: O(max(o*q, olog(o))) - Max value of either times the nested for loop 
runs (number of orders not filled/expired times the number of items within the order/(o*q)) 
or the number of times the sort function returns something (olog(o)).

print_kitchen_is_cooking: O(c) - Runs the for loop based on the number of food items are
still cooking (c).

print_kitchen_has_completed: O(d) - Runs the for loop based on the number of food items
are done being cooked (d).

run_until_next: O(timeUntilNextEvent*max(c, o*q, o, ) - Runs the number of minutes until
the next event (timeUntilNextEvent) times the maximum of food still being cooked (c), 
orders (o), and orders times items within said order (o*q).

run_for_time: O(runTime*max(c, o*q, o, ) - Runs the number of minutes given (runTime) 
times the maximum of food still being cooked (c), orders (o), and orders times items 
within said order (o*q).



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






