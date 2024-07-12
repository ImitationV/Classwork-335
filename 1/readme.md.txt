# Readme.md

Project Overview
In this project, I implemented the Points2D class to manage sequences of 2D points using templates to support integer and double datatypes. I focused on implementing the "big five" (destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator) and overloading the + and [] operators to provide comprehensive functionality for the class. The class supports dynamic memory management to handle sequences of arbitrary size efficiently.

Current Status
My implementation of the Points2D class is complete. I tested the program with the given test inputs and the program is working correctly. All required functionalities, including the "big five," stream operators, and operator overloading, have been tested and validated. The code compiles successfully. 

Note
I changed line 5 from #include <points2d.h> to #include "points2d.h". Using angle brackets (<>) caused errors when running the test files, and this was the only solution I found to resolve the issue.