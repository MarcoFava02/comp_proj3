# comp_proj3


Basic functioning of a Penning trap on singly-charged ions
---------------------------
This is the repository for project 3 which has a include folder which contains the hearder files .hpp. Also, a src folder which contains the .cpp files and finally a script folder which contains phyton .py and matlab .m codes.

include
------------
Contains the headers Particle.hpp, PenningTrap.hpp, PenningTrap9.hpp, SourceFile.hpp and SourceFile9.hpp files.

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

src
------------
Includes the main program mainTrap.cpp file

mainTrap.cpp
------------
Main program where we use the classes. It simulates the motion of a single particle and two particles in the Penning trap using the Euler and RK4 methods over a specific duration, while calculating relative errors, error convergence rates,...

Build: g++ mainTrap.cpp -o mainTrap.exe -larmadillo 
Run: ./mainTrap.exe 
HOWWWWWW????!!
then: ./mainTrap.exe <1 or 0 to have interaction or not> <integer number of steps> <\"fe\"=Forward-Euero, \"rk\"=RK4, \"an\"=analytical solution>

mainTrap9.cpp
------------
Main program to perform problem 9.

Build: g++ mainTrap9.cpp -o mainTrap9.exe -larmadillo 
Run: ./mainTrap.exe HOWWWWWW??

script
------------
This folder contains phyton and matlab codes 

plot.py
------------
There are four phyton codes to perform the plots in problems 8 and 9

grafici_appendix.m
------------
Contains the matlab code for making the 3D graphs 



