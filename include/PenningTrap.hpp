#ifndef __PenningTrap_hpp__   
#define __PenningTrap_hpp__


#include <stdio.h>
#include <armadillo>
#include <math.h>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>

#include "Particle.hpp"

class PenningTrap
{
    public:
        double B0_, V0_, d_;
        std::vector <Particle> Particle_;
        bool do_interaction_;
    

        //Constructor
        PenningTrap(double B0_in, double V0_in, double d_in, bool do_interaction_in);

        // Add a particle to the trap
        void add_particle(Particle p_in);

        // External electric field at point r=(x,y,z)
        arma::vec external_E_field(arma::vec r, double t);  

        // External magnetic field at point r=(x,y,z)
        arma::vec external_B_field(arma::vec r);  

        // Force on particle_i from particle_j
        arma::vec force_particle(int i, int j);

        // The total force on particle_i from the external fields
        arma::vec total_force_external(int i, double t);

        // The total force on particle_i from the other particles
        arma::vec total_force_particles(int i);

        // The total force on particle_i from both external fields and other particles
        arma::vec total_force(int i, double t);

        // Evolve the system one time step (dt) using Runge-Kutta 4th order
        void evolve_RK4(double dt, double t);

        // Evolve the system one time step (dt) using Forward Euler
        void evolve_forward_Euler(double dt, double t);

        // The analytical solution at time t
        arma::vec analytical_func(Particle p_in, double t);

        // The relative error compared to the analytical solution
        double rel_err(int i, Particle p_in, double t);



}; 




    
#endif /* PenningTrap_hpp */