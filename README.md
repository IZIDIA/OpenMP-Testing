# OpenMP-Testing
Acquaintance with the basic elements of the OpenMP parallelization technology.

-Task 1. Public and private variables in OpenMP: the reduction parameter.
A) Write a program in which two threads in parallel calculate the sum of numbers from 1 to N. Distribute the work among the threads using the if statement of the C language. 
To add the results of calculating threads, use the OpenMP reduction parameter. Perform calculations for N  {1,2,5,10,100,1000}
Input data: integer N - the number of numbers.
Output:
each thread outputs its partial sum in the format
"[Thread_Number]: Sum = <partial_Sum>",
the total amount is displayed once in the format “Sum = <amount>”.

-Task 2. Public and private variables in OpenMP: the reduction parameter.
B) Modify the program so that it works for k threads. Show how the program works for N {2,10,100,1000}, k {2,4,8,16}.
Input data: integer k - the number of threads, integer N - the number of numbers.
[0]: Sum = 1
[1]: Sum = 2
[2]: Sum = 0
Sum = 3

-Task 3. Parallelization of loops in OpenMP: the program "Sum of numbers"
Explore the OpenMP directive for parallel execution of a for loop. Write a program in which k threads calculate the sum of numbers from 1 to N in parallel. 
Distribute the work among the threads using the OpenMP for directive. Show how the program works for N {2,10,100,1000}, k {2,4,8,16}.
Input data: integer k - the number of threads, integer N - the number of numbers.
Output data: each thread displays its partial sum in the format "[Thread_Number]: Sum = <partial_sum>", once the total amount is displayed in the format "Sum = <sum>".

-Task 4. Parallelizing loops in OpenMP: the schedule parameter
Examine the schedule parameter of the for directive. Modify the program "Sum of numbers" from task 3 in such a way that an additional message is displayed on the screen about which thread is performing which iteration of the loop:
[<Thread number>]: calculation of the iteration number <Iteration number>.

-Task 5. Parallelizing loops in OpenMP: the schedule parameter
Calculate the number π with the required accuracy ε
To calculate the integral, use the left rectangle method.
Investigate the dependence of the running time of the algorithm on the number of flows {k = 1,2,3,…, 20} and the desired accuracy 
(ε = 0.001, 0.0001, 0.00001,…, 0.000000001,… - stop when the time of the last calculation exceeded 2 minutes). 
Show the resulting dependence on the graph.
