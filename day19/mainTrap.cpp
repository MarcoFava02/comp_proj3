
#include "SourceFile.hpp"

int main(){

      
    const double V0=2.41e+6;
    const double B0=9.65e+1;
    const double d=500.;

    

    
    //creating particle 1
    double q1 = 1.; //units of e
    double m1 = 40.078; //units u
    arma::vec r01 = arma::vec{20., 0., 20.}; //units mu m
    arma::vec v01 = {0., 25., 0.}; //units mu m / mu s

    Particle particle1(q1,m1,r01,v01);


    //creating particle 2
    double q2 = 1.; //units of e
    double m2 = 40.078; //units u
    arma::vec r02 = arma::vec{25., 25., 0.}; //units mu m
    arma::vec v02 = {0., 40., 5.}; //units mu m / mu s

    Particle particle2(q2,m2,r02,v02);


    PenningTrap trap(B0, V0, d);

    
    //insert particle1 and particle2 in the vector Particle_ inside trap
    trap.add_particle(particle1);       // std::cout << trap.Particle_[0].q_ << "\n";
    trap.add_particle(particle2);

    
    

    //compute the force between particle_i and particle_j
    for(int i = 0; i<trap.Particle_.size(); i++)
    {
        for(int j = 0; j<trap.Particle_.size(); j++)
        {
            arma::vec force = trap.force_particle(i,j);
            std::cout << "Force received by particle " << i << " caused by particle " << j << ": \n" << force <<std::endl;
        }
    }

    float t_tot = 50.;
    int n_step = 4000;
    float dt = t_tot/n_step;
    float t=0;

    

    for (int i=0; i<n_step; i++){
        trap.evolve_forward_Euler(dt,t);
        
        std::cout << trap.Particle_[1].r_ << std::endl;
        //We could have also use the method Forward Euler instead:
            //PenningTrap1.evolve_forward_Euler(dt);
        
         trap.evolve_RK4(dt,t);
        
        std::cout << "RK4"<<trap.Particle_[1].r_ <<std::endl;
        //We could have also use the method Forward Euler instead:
            //PenningTrap1.evolve_forward_Euler(dt);
        
        //Update the actual time of the system and printing it with the position z of the particle
        t+=dt;
    }


    

    //computing E and B for a certain r --omit this
    arma::vec r = arma::vec{1,0,0};
    arma::vec E = trap.external_E_field(r, t);     //std::cout << "E: " << E << "\n";
    arma::vec B = trap.external_B_field(r);     //std::cout << "B: " << B << "\n";    



    return 0;
}

// std::cout << trap.B0 << "\n" << trap.V0 << "\n" << trap.d << std::endl;

    // std::cout << "B0: " << trap.B0 << "\n";
    // std::cout << "V0: " << trap.V0 << "\n";
    // std::cout << "d: " << trap.d << "\n";
