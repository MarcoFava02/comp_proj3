# comp_proj3


Basic functioning of a Penning trap on singly-charged ions
---------------------------
This is the repository for Project 3 with an include folder containing the header files .hpp. Also, an src folder which contains the .cpp files and finally a script folder which contains phyton .py and matlab .m codes.

include
------------
Contains the header files Particle.hpp, PenningTrap.hpp, PenningTrap9.hpp, SourceFile.hpp and SourceFile9.hpp files.

Particle.hpp
---------------
Includes the class Particle with its constructor and the properties of a single Particle.

PenningTrap.hpp
---------------
Includes the class PenningTrap with its constructor and the variables needed to run problem 8. Some member functions like RK4 method or total force functions are defined here.

PenningTrap9.hpp
---------------
Includes the class PenningTrap9 with its constructor and the variables needed to run problem 9.

SourceFile.hpp
------------
Includes the definitions of the constructor Particle and constructor PenningTrap and every function used afterwards in the mainTrap.cpp file.


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
Run: ./mainTrap.exe <1 or 0 to have interaction or not> <integer number of steps> <"fe"=Forward-Euero, "rk"=RK4> 
The first argument is to turn on/off coulomb interaction, the second argument is to set the number of steps and the third argument is to choose the method to evolve the system with.

mainTrap9.cpp
------------
Main program to perform problem 9.

Build: g++ -O2 mainTrap9.cpp -o mainTrap9.exe -larmadillo 
Run: ./mainTrap9.exe <1 or 0 to have interaction or not> <F=10*f> <1 or 0 to make the zoom or not>
The first argument is to turn on/off coulomb interaction, the second argument is to set the value of the parameter f to then compute the voltage and the third argument is to make a zoom for only certain frequencies.

script
------------
This folder contains phyton and matlab codes 

plot.py
------------
There are four phyton codes to perform the plots in problems 8 and 9.

plot8.py
------------
Program to perform the plots of problem 8, from the letter "a" to "d"

Usage: python plot8.py <true/false/both to have interaction or not or both> <integer number of steps> <fe=Forward-Euler, rk=RK4> <letter of a problem a to d>
The first three arguments are used to find the file name that changes based on the different simulations, the fourth argument is to run just one of the problems treated in this code.

plot8e.py
------------
Program to perform the plots of problem 8, letter e

Usage: python plot8.py <fe=Forward-Euler, rk=RK4, an=analytical solution>
The argument is used to find the file name that changes based on the different simulations.

plot9.py and plot9b.py
------------
Programs to perform the plots of problem 9

Usage:   python plot9.py
         python plot9b.py

graphs_appendix.m
------------
Contains the Matlab code to plot the graphs in the appendix of the report.

Usage: run the only section of the code you want the plot of.


