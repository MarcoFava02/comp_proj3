
#ifndef __Particle_hpp__   
#define __Particle_hpp__


#include <stdio.h>
#include <armadillo>
#include <cmath>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>

class Particle
{
    public:
        double q_, m_;
        arma::vec r_, v_;
        

    //Constructor
    Particle(double q, double m, arma::vec r, arma::vec v);
}; 

#endif /* Particle_hpp */