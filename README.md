# Multi-Process Scheduler Comparison for Execution Time Evaluation
This C program evaluates and compares the execution times of processes scheduled under different scheduling policies by the Operating System, namely First-In-First-Out (FIFO), Round-Robin(RR) and OTHER. It achieves this by forking child processes, assigning each a specific scheduling policy, executing an external program, and measuring the elapsed times. The results are then printed and logged in a file for analysis and comparison of the performance characteristics under different scheduling policies. It then graphically depicts this comparison using a histogram plotted using the python library MatPlotLib.
