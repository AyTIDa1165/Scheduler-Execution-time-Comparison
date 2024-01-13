Programming Logic:

- The parent PID is stored in the beginning. The number of processors is set to 1 to make the output more comprehensible.
- Start time is initiated before the fork. It is common for all three future child processes.
- 'fork()' is called in a for loop, which is run for 3 iterations, creating 3 child processes of the parent process.
- It is ensured via parent PID that fork() does not allow the parent process to undergo forking to create child processes.
- PIDs of all three child processes are stored, both in the respective child processes and the parent process.
- Once the for loop terminates, each child process is assigned a scheduling policy using 'sched_setscheduler'. Since
  SCHED_OTHER policy is a default policy for any program with niceness set to zero as the default, it does not require explicit setting.
- Both SCHED_RR and SCHED_FIFO are set to the default priority '50'.
- 'execl()' function is used for all three children, and the executable 'Counting' is given as the path.
- The parent function enters a while loop, which calls 'waitpid()' to check the termination of child processes. Upon termination of
  a child process, it calls the explicitly defined function 'return_endtimer()', which stores the end time.
- Using start time and end time, elapsed time is calculated and written in a text file called 'Data.txt'.
- The Python program 'Histogram.py' makes use of the imported numpy and matplotlib libraries and reads 'Data.txt' to produce a
  histogram of scheduling policies versus time of execution (plotted in different colors).

Compilation and Makefile:

- Users need to provide the 'make' command for the execution of the makefile. 
- The makefile compiles 'Counting.c' and 'Q2.c' and runs the executable 'Q2'.
- Since 'Q2.c' involves scheduling policies, they require a higher privilege level to run (use of the sudo command). 
  Thus, users need to input their password to provide permission.
- Once 'Q2.c' is run, 'Data.txt' is automatically created. The makefile then runs the Python program 'Histogram.py',
  which automatically creates an image of the plot in PNG format. Since WSL does not have a GUI, the plot could not 
  be directly shown and hence was saved as an image in the directory.

Inference/Conclusion:

  From the printed output as well as the plot, it is clear that the three processes have successfully been scheduled with their
  respective policies. The time of execution comes out to be in the order: FIFO < RR < OTHER. The repetition of execution of the
  program does not affect this order, thus the code is reproducible.
