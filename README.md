# comp_proj3
computational project n3


The original files made by Alejandro are: "particle.hpp", "PenningTrap.hpp" and "SourceFile.cpp".
I am rewriting "SourceFile.cpp" in a header file called "Source.hpp" and checking step by step that everything works on a main file called "mainTrap.cpp".


For this project 3 there is a src folder which contains four different .cpp files. Also a include folder which contains one .hpp file. And a script folder which has a matlab code .m to do the plots. 
In the header file there are all the functions used in the different problems (cpp files). There we can see the creation matrix function, the finder of the max value, the rotator and the jacobi eigensolver. The file "Problem2.cpp" has the code for problem 2, "prob4.cpp" has problem 3 and 4, besides file "Problem5" for the fifth and finally "prob6" contains the code for las problem 6. Note that as the armadillo library is used for this project the ejecution command written in the terminal should be g++ FILENAME.cpp -o FILENAME -larmadillo.
