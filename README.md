# mulithreaded-sort-benchmarking
An exploration of multithreading and object oriented design in C++.  Provides support for benchmarking runtime performance of multithreaded algorithms utilizing various thread quantities.  Abstract classes are provided for ease of extension to additional algorithms.

An explanation of the design decisions and results of the project may be found in "Project Report.pdf".  An explanation of the theory used may be found in the slides of "Course Project Presentation.pptx".

Notably, the performance achieved in this project exceeds that of the literature; a 40% reduction in runtime on a sample size of 2^16 was observed with the project code, whereas the literature indicated a mere 12.5% reduction in runtime under the same conditions (sample size, sorting algorithm, and number of threads used).  Page 5 of "Project Report.pdf" covers this in greater detail.
