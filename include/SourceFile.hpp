
#ifndef __SourceFile_hpp__   
#define __SourceFile_hpp__

#include "Particle.hpp"
#include "PenningTrap.hpp"

const double k_e=1.38935333e+5;


// Definition of the constructor Particle
Particle::Particle(double q, double m, arma::vec r, arma::vec v)
{
  // Use the input variables (q, m, r, v) to assign values to the class member variables (charge, mass, position, velocity)
  q_ = q;
  m_ = m;
  r_ = r;
  v_ = v;
}

// Definition of the constructor PenningTrap
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, bool do_interaction_in)
{
  // Use the input variables (B0_in, V0_in, d_in, do_interaction_in) to assign values to the class member variables (B0_, V0_, d_, do_interaction_)
  B0_ = B0_in;
  V0_ = V0_in;
  d_ = d_in;
  do_interaction_ = do_interaction_in;
}


//Now we are going to make all the definitions of the functions of PenningTrap

// Definition of add_particle function.
// Introduce a Particle type object called p_in to the end of the Penning Trap vector called Particle_.
void PenningTrap::add_particle(Particle p_in)
{
  Particle_.push_back(p_in);
}

// Definition of the external_E_field function
// This function gives the electrical field produced by a certain point r = (x, y, z)
arma::vec PenningTrap::external_E_field(arma::vec r,double t)
{
  // Obtain the E field from the potential V
  double potential = V0_;
  double ratio = potential / (d_ * d_);
  arma::vec E = {ratio * r(0), ratio * r(1), -2 * ratio * r(2)};

  return E;
}

// Definition of the external_B_field
// This function gives the magnetic field produced in a certain point r = (x, y, z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
  // As said in theory, the B field only has the z component
  arma::vec B = {0.0, 0.0, B0_};

  return B;
}

// Definition of the force_particle
// This function gives the force received by particle i caused by particle j
arma::vec PenningTrap::force_particle(int i, int j)
{
  if (i == j)
  {
    arma::vec force_particle(3, arma::fill::zeros);
    return force_particle;
  }
  else
  {
    // Set the Coulomb force between particle i and particle j
    arma::vec force_particle = arma::vec(3);

    arma::vec subst = Particle_[i].r_ - Particle_[j].r_;
    force_particle = k_e * Particle_[i].q_ * Particle_[j].q_ * (subst) / std::pow(arma::norm(subst), 3);
    // mass of particle i will be applied after in the method

    return force_particle;
  }
}

// Definition of the total_force_external
// This function gives the Lorentz force received by particle i caused by all EXTERNAL fields.
arma::vec PenningTrap::total_force_external(int i, double t) 
{
    // Lets compute the Lorentz force due to the B field and add the E field -> F = q(E + v x B)
    return Particle_[i].q_ * (external_E_field(Particle_[i].r_,t) + arma::cross(Particle_[i].v_, external_B_field(Particle_[i].r_))); // Added missing 'return' statement
  }


// Definition of the total_force_particles
// This function gives the total force on a single particle i caused from other particles.
// So we have to add each force created by each particle j in the Penning Trap.
arma::vec PenningTrap::total_force_particles(int i)
{
  arma::vec total_force_particles = arma::vec(3).fill(0.);
  if(do_interaction_){
    for (int j = 0; j < Particle_.size(); j++)
    {
      total_force_particles += force_particle(i, j); // add the force caused by each j particle
    }
  }
  return total_force_particles;
}

// Definition of the total_force
// This function gives the total force that a particle i receives from external fields and Coulomb forces from other particles in a time t.
arma::vec PenningTrap::total_force(int i, double t)
{
  arma::vec total_force = arma::vec(3).fill(0.);
  total_force = total_force_external(i,t) + total_force_particles(i);
  return total_force;
}

// Definition of analytical_func
// This function gives the analytical solution of a particle p_in, to use it for comparison
arma::vec PenningTrap::analytical_func(Particle p_in, double t) {
    // Extract particle properties
    double q_ = p_in.q_;
    double m_ = p_in.m_;
    arma::vec r_ = p_in.r_; 
    arma::vec v_ = p_in.v_;

    // Create variables to define the equations
    double w0 = q_ * B0_ / m_;
    double wz2 = 2 * q_ * V0_ / (m_ * d_ * d_);
    double wz = std::sqrt(wz2);
    double w_add = (w0 + std::sqrt(w0 * w0 - 2 * wz2)) / 2;
    double w_sub = (w0 - std::sqrt(w0 * w0 - 2 * wz2)) / 2;
    double A_add =  (v_(1) + w_sub * r_(0)) / (w_sub - w_add);
    double A_sub = -(v_(1) + w_add * r_(0)) / (w_sub - w_add);

    // Calculate the x, y, and z components of the analytical solution
    double x = A_add * std::cos(w_add * t) + A_sub * std::cos(w_sub * t);
    double y = - (A_add * std::sin(w_add * t) + A_sub * std::sin(w_sub * t));
    double z = r_(2) * std::cos(wz * t) + v_(2) / wz * std::sin(wz * t);

    // Create a vector f to represent the (x, y, z) components of the solution
    arma::vec f = arma::vec(3);
    f(0) = x;
    f(1) = y;
    f(2) = z;

    return f;
}



//Definition of evolve_forward_Euler
//This function solves equations of motion, evolving in time using the Euler forward method
void PenningTrap::evolve_forward_Euler(double dt, double t){
    for (int i = 0; i < Particle_.size(); i++)
    {
        std::vector <Particle> original_particle_vec_euler = Particle_;

        // The algorithm is y_i+1 = y_i + h*f_i
        Particle_[i].r_ = original_particle_vec_euler[i].r_ + dt * Particle_[i].v_;
        Particle_[i].v_ = original_particle_vec_euler[i].v_ + dt * total_force(i, t) / Particle_[i].m_; 
    }
}



// Definition of evolve_RK4
// This function solves equations of motion, evolving in time using the Runge-Kutta 4th order method
void PenningTrap::evolve_RK4(double dt, double t) {
    // Make a copy of the current state of particles to preserve their original values
    std::vector<Particle> original_particle_vec = Particle_;

    // Initialize arrays to store intermediate values for each RK4 step
    std::vector<arma::vec> kr1, kv1, kr2, kv2, kr3, kv3, kr4, kv4;

    // Perform the first RK4 step
    for (int i = 0; i < Particle_.size(); i++) {
        // Calculate the intermediate values k1r and k1v
        arma::vec k1r = dt * Particle_[i].v_;
        arma::vec k1v = dt * total_force(i, t) / Particle_[i].m_;

        // Store k1r and k1v in their respective arrays
        kr1.push_back(k1r);
        kv1.push_back(k1v);

        // Update the position and velocity of the particle using the intermediate values
        Particle_[i].r_ = original_particle_vec[i].r_ + 0.5 * k1r;
        Particle_[i].v_ = original_particle_vec[i].v_ + 0.5 * k1v;
    }

    // Perform the second RK4 step
    for (int i = 0; i < Particle_.size(); i++) {
        arma::vec k2r = dt * Particle_[i].v_;
        arma::vec k2v = dt * total_force(i, t + 0.5 * dt) / Particle_[i].m_;
        kr2.push_back(k2r);
        kv2.push_back(k2v);

        Particle_[i].r_ = original_particle_vec[i].r_ + 0.5 * k2r;
        Particle_[i].v_ = original_particle_vec[i].v_ + 0.5 * k2v;
    }

    // Perform the third RK4 step
    for (int i = 0; i < Particle_.size(); i++) {
        arma::vec k3r = dt * Particle_[i].v_;
        arma::vec k3v = dt * total_force(i, t + 0.5 * dt) / Particle_[i].m_;
        kr3.push_back(k3r);
        kv3.push_back(k3v);

        Particle_[i].r_ = original_particle_vec[i].r_ + k3r;
        Particle_[i].v_ = original_particle_vec[i].v_ + k3v;
    }

    // Perform the fourth and final RK4 step
    for (int i = 0; i < Particle_.size(); i++) {
        arma::vec k4r = dt * Particle_[i].v_;
        arma::vec k4v = dt * total_force(i, t + dt) / Particle_[i].m_;
        kr4.push_back(k4r);
        kv4.push_back(k4v);


        // Update the position and velocity of the particle using the weighted average of k values
        Particle_[i].r_ = original_particle_vec[i].r_ + (kr1[i] + 2.0 * kr2[i] + 2.0 * kr3[i] + kr4[i]) / 6.0;
        Particle_[i].v_ = original_particle_vec[i].v_ + (kv1[i] + 2.0 * kv2[i] + 2.0 * kv3[i] + kv4[i]) / 6.0;
    }
}



// Definition of rel_err
// This funcion computes the relative error of the particle Particle_[i] following the expected value of p_in 
double PenningTrap::rel_err(int i, Particle p_in, double t){
  // save the true position computed with the analytical function
  arma::vec true_pos = analytical_func(p_in,t);

  // compute the relative error on each cordinate as err_i = abs((true - approx)/true)
  double x = std::abs((true_pos(0)-Particle_[i].r_(0))/true_pos(0));
  double y = std::abs((true_pos(1)-Particle_[i].r_(1))/true_pos(1));
  double z = std::abs((true_pos(2)-Particle_[i].r_(2))/true_pos(2));
  arma::vec err = {x,y,z};
  return arma::norm(err); // compute the error as the norm of vector (err_x,err_y,err_z)
}



#endif /* SourceFile_hpp */