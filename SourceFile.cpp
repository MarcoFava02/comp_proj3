#include "Particle.hpp"
#include "PenningTrap.hpp"

#define k_e 1.3893533*1e5

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
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in)
{
  // Use the input variables (B0_in, V0_in, d_in) to assign values to the class member variables (B0, V0, d)
  B0 = B0_in;
  V0 = V0_in;
  d = d_in;
  // double k_e = 1.3893533 * 1e5; // Coulomb constant value (added missing semicolon)
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
arma::vec PenningTrap::external_E_field(arma::vec r)
{
  // To first obtain the E field, we have to know the potential V
  double potential = V0;
  double ratio = potential / (d * d);
  arma::vec E = {ratio * r(0), ratio * r(1), -2 * ratio * r(2)};

  return E;
}

// Definition of the external_B_field
// This function gives the magnetic field produced in a certain point r = (x, y, z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
  // As said in theory, the B field only has the k component
  arma::vec B = {0.0, 0.0, B0};

  return B;
}

// Definition of the force_particle
// This function gives the force received by particle i caused by particle j
arma::vec PenningTrap::force_particle(int i, int j)
{
  if (i == j)
  {
    arma::vec force_particle(3, arma::fill::zeros);
    return force_particle; // Added missing semicolon
  }
  else
  {
    // Set the Coulomb force between particle i and particle j
    arma::vec force_particle = arma::vec(3);

    arma::vec subst = Particle_[i].r_ - Particle_[j].r_;
    force_particle = k_e * Particle_[i].q_ * Particle_[j].q_ * (subst) / std::pow(arma::norm(subst), 3); // Added missing semicolon
    // mass of particle i will be applied after in the method

    return force_particle;
  }
}

// Definition of the total_force_external
// This function gives the sumatory/total Lorentz force received by particle i caused by all EXTERNAL fields
arma::vec PenningTrap::total_force_external(int i, double t) // Added missing 't' parameter
{
  // Add all
  for (int i = 0; i < Particle_.size(); i++) // Use a different variable name for the loop counter
  {
    // Lets compute the Lorentz force due to the B field and add the E field -> F = q(E + v x B)
    return Particle_[i].q_ * (external_E_field(Particle_[i].r_) + arma::cross(Particle_[i].v_, external_B_field(Particle_[i].r_))); // Added missing 'return' statement
  }
}

// Definition of the total_force_particles
// This function gives the total force on a single particle i caused from other particles.
// So we have to add each force created by each particle j in the Penning Trap.
arma::vec PenningTrap::total_force_particles(int i)
{
  arma::vec total_force_particles = arma::vec(3).fill(0.);
  for (int j = 0; j < Particle_.size(); j++) // Changed "i" to "j" as the loop counter
  {
    total_force_particles += force_particle(i, j);
  }
  return total_force_particles;
}

// Definition of the total_force
// This function gives the total force that a particle i receives from external fields and Coulomb forces from other particles in a time t.
arma::vec PenningTrap::total_force(int i, double t)
{
  return total_force_external(i, t) + total_force_particles(i);
}

// Definition of analytical_func
// This function gives the analytical solution of a particle p_in, to use it for comparison
arma::vec analytical_func(Particle p_in, double t) {
    // Extract particle properties
    double q_ = p_in.q_;
    double m_ = p_in.m_;
    double r_ = p_in.r_;
    double v_ = p_in.v_;

    // Create variables to define the equations
    double w0 = q_ * B0 / m_;
    double wz2 = 2 * q_ * V0 / m_ * d * d;
    double w_add = (w0 + std::sqrt(w0 * w0 - 2 * wz2)) / 2;
    double w_sub = (w0 - std::sqrt(w0 * w0 - 2 * wz2)) / 2;
    double A_add = (v_(1) + w_sub * r_(0)) / (w_sub - w_add);
    double A_sub = (v_(1) + w_add * r_(0)) / (w_sub - w_add);

    // Calculate the x, y, and z components of the analytical solution
    double x = A_add * std::cos(w_add * t) + A_sub * std::cos(w_sub * t);
    double y = -A_add * std::sin(w_add * t) + A_sub * std::sin(w_sub * t);
    double z = r_(2) * std::cos(std::sqrt(wz2) * t);

    // Create a vector f to represent the (x, y, z) components of the solution
    arma::vec f = arma::vec(3);
    f(0) = x;
    f(1) = y;
    f(2) = z;

    return f;
}
// Definition of evolve_RK4
// This function solves equations of motion, evolving in time using the Runge-Kutta 4th order method
void evolve_RK4(double dt, double t) {

    // Make a copy of all particles in the Penning trap, as we will need the original r and v for RK4
    std::vector <Particle> original_particle_vec = Particle_; // This means that each element of the new vector is an object of the Particle class

    // There are going to be 4 kr and 4 kv for each particle, so kr and kv are vectors with all the kr and kv of every particle
    arma::vec<arma::vec> kr1, kr2, kr3, kr4, kv1, kv2, kv3, kv4;

    //Notice from the theory that r derivative = v and v derivative = F/m. Being F the total_force function
    for (int i = 0; i < Particle_.size(); i++) {
        arma::vec kr1i = dt * Particle_[i].v_;
        arma::vec kv1i = dt * total_force(i, t) / Particle_[i].m_;

        // Add it to the kr1 and kv1 vectors
        kr1.push_back(kr1i);
        kv1.push_back(kv1i);
    }

    // Now let's update the position and velocity for each particle using kr1 and kv1
    for (int i = 0; i < Particle_.size(); i++) {

        Particle_[i].r_ = original_particle_vec[i].r_ + 0.5 * kr1[i];
        Particle_[i].v_ = original_particle_vec[i].v_ + 0.5 * kv1[i];
    }

    for (int i = 0; i < Particle_.size(); i++) {

        arma::vec kr2i = dt * Particle_[i].v_;
        arma::vec kv2i = dt * total_force(i, t + 0.5 * dt) / Particle_[i].m_;

        // Add it to the kr2 and kv2 vectors
        kr2.push_back(kr2i);
        kv2.push_back(kv2i);
    }

    // Now let's update the position and velocity for each particle using kr2 and kv2
    for (int i = 0; i < Particle_.size(); i++) {

        Particle_[i].r_ = original_particle_vec[i].r_ + 0.5 * kr2[i];
        Particle_[i].v_ = original_particle_vec[i].v_ + 0.5 * kv2[i];
    }

    for (int i = 0; i < Particle_.size(); i++) {

        arma::vec kr3i = dt * Particle_[i].v_;
        arma::vec kv3i = dt * total_force(i, t + 0.5 * dt) / Particle_[i].m_;

        // Add it to the kr3 and kv3 vectors
        kr3.push_back(kr3i);
        kv3.push_back(kv3i);
    }

    // Now let's update the position and velocity for each particle using kr3 and kv3
    for (int i = 0; i < Particle_.size(); i++) {

        Particle_[i].r_ = original_particle_vec[i].r_ + kr3[i];
        Particle_[i].v_ = original_particle_vec[i].v_ + kv3[i];
    }

    for (int i = 0; i < Particle_.size(); i++) {

        arma::vec kr4i = dt * Particle_[i].v_;
        arma::vec kv4i = dt * total_force(i, t + dt) / Particle_[i].m_;

        // Add it to the kr4 and kv4 vectors
        kr4.push_back(kr4i);
        kv4.push_back(kv4i);
    }

    // After computing all four kr and kv and updating r and v, perform the RK4 update of r and v
    for (int i = 0; i < Particle_.size(); i++) {

        Particle_[i].r_ = original_particle_vec[i].r_ + (kr1[i] + 2. * kr2[i] + 2. * kr3[i] + kr4[i]) / 6.;
        Particle_[i ].v_ = original_particle_vec[i].v_ + (kv1[i] + 2. * kv2[i] + 2. * kv3[i] + kv4[i]) / 6.;
    }

}

//Definition of evolve_forward_Euler
//This function solves equations of motion, evolving in time using the Euler forward method
void evolve_forward_Euler(double dt, double t){

    for (int i = 0; i < Particle_.size()-1; i++)
    {
        std::vector <Particle> original_particle_vec_euler = Particle_;

        // Algorithm is y_i+1 = y_i + h*f_i
        Particle_[i].r_ = original_particle_vec_euler[i].r_ + dt * Particle_[i].v_;
        Particle_[i].v_ = original_particle_vec_euler[i].v_ + dt * total_force(i, t) / Particle_[i].m_; 
    }
}


//THIS SHOULD BE IN ANOTHER main.cpp file
int main() 
{
  

  PenningTrap campo(1, 0.0025, 0.0005); // Supongamos que los valores de V0 y d se proporcionan aquí
  arma::vec r = arma::vec({20.0, 0.0, 20.0}); // Supongamos que se proporcionan valores iniciales para r
  
  arma::vec E = campo.external_E_field(r);
  arma::vec B = campo.external_B_field(r);


  std::cout << "E-field: " << E << std::endl;
  std::cout << "B-field: " << B << std::endl;

  
  return 0;
}

