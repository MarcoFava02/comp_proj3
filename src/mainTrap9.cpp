#include "SourceFile9.hpp"


int main(int argc, char* argv[])
{
//checking the number of command-line arguments:
if(argc != 4){
    // Get the name of the executable file
    std::string executable_name = argv[0];

    std::cerr << "Error: Wrong number of input arguments." << std::endl;
    std::cerr << "Usage: " << executable_name << " <1 or 0 to have interaction or not> <F=10*f> <1 or 0 to make the zoom or not>" << std::endl;

    // Exit program with non-zero return code to indicate a problem
    return 1;   
}


//save the command-line arguments:
int do_interaction = atoi(argv[1]);     // bool var to decide if there is going to be interaction ("true") or not ("false") between the particles
int F = atoi(argv[2]);                  // use F=10*f to be more practicle while inserting the number and to call the file
int zoom = atoi(argv[3]);               // bool var to decide if we decide to have a zoom on a certain frequency


//prepare the simulation:
//penning trap's parameters
double B0 = 9.65e1;     //units used above, corrisponds to 1T
double V0 = 2.41e6;     //units used above, corrisponds to 25mV
double d  = 5.00e2;     //units mu m
double f = static_cast<double>(F)/10;
double wV;              //wV will be insert in a loop and change between wV_min and wV_max with steps of dwV
double wV_min = 0.2;    //units MHz
double wV_max = 2.5;    //units MHz
double dwV = 0.02;      //stepsize of wV
double n_wV = (wV_max - wV_min)/dwV; //number of steps

//if we want to zoom, change the frequency boundaries 
if(zoom){
    wV_min = 0.64;   //units MHz
    wV_max = 0.74;   //units MHz
    n_wV = 115;     //number of steps
    dwV = (wV_max - wV_min)/n_wV; //stepsize of wV
}

//print the frequency's range
std::cout << "--- frequency's range: ["<< wV_min <<","<< wV_max <<"] ---" << std::endl;


//particles' parameters
float q = 1;        //units of e
float m = 40.078;   //units amu
int n_part = 100;   //number of particles
double frac;        //fraction of particles inside the trap

//parameters to evolve the system
double n_step = 4000;           //number of steps
double t_tot = 500.;            //total time in mu s of the simulation
double dt = t_tot/n_step;       //stepsize
double t=0.;

//create and connect the output file stream to save the data
std::string filename = "outsider_" + std::to_string(F) + ".txt";

//change the name of the file if we want the zoom
if(zoom){
    if(do_interaction){
        filename = "outsider_zoom" + std::to_string(F) + "_iter.txt";
    }else{
        filename = "outsider_zoom" + std::to_string(F) + "_noiter.txt";
    }
}
std::ofstream ofile;
ofile.open(filename);


//begin the simulations 
for(int i=0; i<=n_wV; i++){

    wV = wV_min + i*dwV;

    // create the trap with the current wV and insert 100 particles with random pos and vel
    PenningTrap trap(B0, V0, f, wV, d, do_interaction);
    for(int i=0; i<n_part; i++){
        trap.add_particle_random(q,m);
    }

    // simulate the system evolution
    for(int i=0; i<=n_step; i++){
        t = i*dt;

        // evolve the system with RK4 method
        trap.evolve_RK4(dt,t);
    }

    //save the fraction of particles inside the trap
    ofile << wV << " " << trap.count_inside() << std::endl;
    frac = trap.count_inside()/n_part;
    std::cout << i << " " << wV << " " << frac << std::endl;
}

ofile.close();

return 0;
}