#include "SourceFile.hpp"


int main(int argc, char* argv[])
{

//checking the number of command-line arguments:
if(argc != 4){
    // Get the name of the executable file
    std::string executable_name = argv[0];

    // Give instruction on how to use the inputs
    std::cerr << "Error: Wrong number of input arguments." << std::endl;
    std::cerr << "Usage: " << executable_name << " <1 or 0 to have interaction or not> <integer number of steps> <\"fe\"=Forward-Euero, \"rk\"=RK4>" << std::endl;

    // Exit program with non-zero return code to indicate a problem
    return 1;   
}


//save the command-line arguments:
int do_interaction = atoi(argv[1]);     // bool var to decide if there is going to be interaction ("true") or not ("false") between the particles
int n_step = atoi(argv[2]);             // total number of steps we want the simulation run for
std::string method = argv[3];           // var that changes the method used for the simulation: "eu"=Forward-Euero, "rk"=Runge Kutta 4


//creating particle 1
float q1 = 1.;                          //units of e
double m1 = 40.078;                     //units u
arma::vec r01 = arma::vec{20, 0, 20};   //units mu m
arma::vec v01 = {0, 25, 0};             //units mu m / mu s

Particle particle1(q1,m1,r01,v01);


//creating particle 2
float q2 = 1.;                          //units of e
double m2 = 40.078;                     //units u
arma::vec r02 = arma::vec{25, 25, 0};   //units mu m
arma::vec v02 = {0, 40, 5};             //units mu m / mu s

Particle particle2(q2,m2,r02,v02);


//creating the penning trap
double B0 = 9.65e1;                     //units used above, corresponds to 1T
double V0 = 2.41e6;                     //units used above, corresponds to 25mV
double d  = 5.00e2;                     //units mu m

PenningTrap trap(B0, V0, d, do_interaction);


//insert particle1 and particle2 in the vector Particle_ inside trap
trap.add_particle(particle1);
trap.add_particle(particle2);



//some variables used to make run the simulation
double t_tot = 50.;                     //total time in mu s of the simulation
double dt = t_tot/n_step;               //stepsize
double t=0.;
bool do_rel_err = false;                //only for few simulations we are computing the relative error
if(do_rel_err){
    arma::vec rel_err;                  //declare the vector where to store the relative error
}
std::string filename;


//file name where to save all the data
if(do_interaction){
    filename = "data_inter_" + method + std::to_string(n_step) + ".txt";
}else if(!do_interaction){
    filename = "data_nointer_" + method + std::to_string(n_step) + ".txt";
}

// create and connect the output file stream
std::ofstream ofile;
ofile.open(filename);


// begin the simulation
for (int i=0; i<=n_step; i++){
    t = i*dt;
    
    if(!do_rel_err){
        // write time, position and velocity on the file
        ofile << t << " " << trap.Particle_[0].r_(0) << " " << trap.Particle_[0].r_(1) << " " << trap.Particle_[0].r_(2) 
                << " " << trap.Particle_[0].v_(0) << " " << trap.Particle_[0].v_(1) << " " << trap.Particle_[0].v_(2) 
                << " " << trap.Particle_[1].r_(0) << " " << trap.Particle_[1].r_(1) << " " << trap.Particle_[1].r_(2) 
                << " " << trap.Particle_[1].v_(0) << " " << trap.Particle_[1].v_(1) << " " << trap.Particle_[1].v_(2) << std::endl; 
        std::cout << t << " " << trap.Particle_[0].r_(0) << " " << trap.Particle_[0].r_(1) << " " << trap.Particle_[0].r_(2) << std::endl;
    }else if(do_rel_err){
        // write time and modulus of the relative error on the file
        ofile << t << " " << trap.rel_err(0,particle1,t) << std::endl;
    }

    // choose the method to update the position with
    if(method == "rk"){
        // update position with RK4 method
        trap.evolve_RK4(dt,t);
    }else if (method == "fe"){
        // update position with forward Euler method
        trap.evolve_forward_Euler(dt,t);
    }
    

}

// close the output file stream
ofile.close();

return 0;
}
