# Multi-Process Scheduler Comparison for Execution Time Evaluation

## Description:

 This C program evaluates and compares the execution times of processes scheduled under different scheduling policies by the Operating System, namely First-In-First-Out (FIFO), Round-Robin(RR) and OTHER. It achieves this by forking child processes, assigning each a specific scheduling policy, executing an external program, and measuring the elapsed times. The results are then printed and logged in a file for analysis and comparison of the performance characteristics under different scheduling policies. It then graphically depicts this comparison using a histogram plotted using the python library MatPlotLib.

## Compilation and Makefile:

- Users need to provide the 'make' command for the execution of the makefile. 
- The makefile compiles 'Counting.c' and 'Q2.c' and runs the executable 'Q2'.
- Since 'Q2.c' involves scheduling policies, they require a higher privilege level to run (use of the sudo command). 
  Thus, users need to input their WSL password to provide permission.
- Once 'Q2.c' is run, 'Data.txt' is automatically created. The makefile then runs the Python program 'Histogram.py',
  which automatically creates an image of the plot in PNG format.

## Inference/Conclusion:

  From the printed output as well as the plot, it is clear that the three processes have successfully been scheduled with their
  respective policies. The time of execution comes out to be in the order: FIFO < RR < OTHER. The repetition of execution of the
  program does not affect this order, thus the code is reproducible.