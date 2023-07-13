Step 0.1: If there are any previous files named output.txt, delete them.
STep 0.2: There should be an input.tex already present in the current directory with the values of number of points and number of threads written. Since it is not a part of deliverables, I didn't submit any such file. Make an input.tex before running the program.

FOR PTHREADS IMPLEMENTATION

Step 1: Compile the code using the following command
g++ -std=c++11 Assgn2Srcpthread-CS21BTECH11022.cpp -lpthread -lm

Step 2: Execute the executable using the following command
./a.out

Now the current directory will have a file output.txt. It will contain the results as mentioned. 
NOTE: It will show the output as (0) or (1). 
0 refers to boolean zero, which means it is invalid.
1 refers to boolean 1 which mean that particular row/ col/ subgrid is valid.

FOR openMP IMPLEMENTATION
Step 1: Compile the code using the following command
g++ -std=c++11 Assgn2SrcOpenMP-CS21BTECH11022.cpp -fopenmp -lm

Step 2: Execute the executable using the following command
./a.out
Now the current directory will have a file output.txt. It will contain the results as mentioned. 
NOTE: It will show the output as (0) or (1). 
0 refers to boolean zero, which means it is invalid.
1 refers to boolean 1 which mean that particular row/ col/ subgrid is valid.

Thank you.