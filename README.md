# comp_proj3
computational project n3


The original files made by Alejandro are: "particle.hpp", "PenningTrap.hpp" and "SourceFile.cpp".
I am rewriting "SourceFile.cpp" in a header file called "Source.hpp" and checking step by step that everything works on a main file called "mainTrap.cpp".


For this project 3 there is a src folder which contains four different .cpp files. Also a include folder which contains one .hpp file. And a script folder which has a matlab code .m to do the plots. 
In the header file there are all the functions used in the different problems (cpp files). There we can see the creation matrix function, the finder of the max value, the rotator and the jacobi eigensolver. The file "Problem2.cpp" has the code for problem 2, "prob4.cpp" has problem 3 and 4, besides file "Problem5" for the fifth and finally "prob6" contains the code for las problem 6. Note that as the armadillo library is used for this project the ejecution command written in the terminal should be g++ FILENAME.cpp -o FILENAME -larmadillo.


Penning Trap Particle Dynamics
---------------------------
There is a include folder which contains the hearder files .hpp. Also, a src folder which contains the .cpp files.

src
------------
Contains the headers Particle.hpp, PenningTrap.hpp and SourceFile.hpp files.

Particle.hpp
---------------
Includes the class Particle with its constructor and the properties of a single Particle.

PenningTrap.hpp
---------------
Includes the class PenningTrap with its constructor and the variables needed to run the methods. Some member functions like RK4 method or total force funcions are defined here.

PenningTrap9.hpp
---------------
Includes the class PenningTrap9 with its constructor and the variables needed to run problem 9. 

SourceFile.hpp
------------
Includes the definitions of the constructors Particle and PenningTrap and of every function used afterwards in the mainTrap.cpp file.


SourceFile9.hpp
------------
Includes functions used to perform problem 9.

include
------------
Includes the main program mainTrap.cpp file

mainTrap.cpp
------------
Main program where we use the classes. It simulates the motion of a single particle and two particles in the Penning trap using the Euler and RK4 methods over a specific duration, while calculating relative errors, error convergence rates,...

Build: g++ mainTrap.cpp -o mainTrap.exe -larmadillo 
Run: ./mainTrap.exe 

then: ./mainTrap.exe <1 or 0 to have interaction or not> <integer number of steps> <\"fe\"=Forward-Euero, \"rk\"=RK4, \"an\"=analytical solution>

