#include "Particle.hpp"
#include "PenningTrap.hpp"
#include "Source.hpp"

int main(){

    //creating particle 1
    int q1 = 1; //units of e
    double m1 = 5.48e-4; //units u
    arma::vec r01 = arma::vec{20, 0, 20}; //units mu m
    arma::vec v01 = {0, 25, 0}; //units mu m / mu s

    Particle particle1(q1,m1,r01,v01);


    //creating particle 2
    int q2 = 1; //units of e
    double m2 = 5.48e-4; //units u
    arma::vec r02 = arma::vec{25, 25, 0}; //units mu m
    arma::vec v02 = {0, 40, 5}; //units mu m / mu s

    Particle particle2(q2,m2,r02,v02);


    //creating the penning trap
    double B0 = 9.65e1; //units used above, corrisponds to 1T
    double V0 = 2.41e6; //units used above, corrisponds to 25mV
    double d  = 5.00e2;    //units mu m

    PenningTrap trap(B0, V0, d);

    
    //insert particle1 and particle2 in the vector Particle_ inside trap
    trap.add_particle(particle1);       // std::cout << trap.Particle_[0].q_ << "\n";
    trap.add_particle(particle2);

    
    //computing E and B for a certain r --omit this
    arma::vec r = arma::vec{1,0,0};
    arma::vec E = trap.external_E_field(r);     //std::cout << "E: " << E << "\n";
    arma::vec B = trap.external_B_field(r);     //std::cout << "B: " << B << "\n";    


    //compute the force between particle_i and particle_j
    for(int i = 0; i<trap.Particle_.size(); i++)
    {
        for(int j = 0; j<trap.Particle_.size(); j++)
        {
            arma::vec force = trap.force_particle(i,j);
            std::cout << "Force received by particle " << i << " caused by particle " << j << ": \n" << force <<std::endl;
        }
    }


    return 0;
}

// std::cout << trap.B0 << "\n" << trap.V0 << "\n" << trap.d << std::endl;

    // std::cout << "B0: " << trap.B0 << "\n";
    // std::cout << "V0: " << trap.V0 << "\n";
    // std::cout << "d: " << trap.d << "\n";
