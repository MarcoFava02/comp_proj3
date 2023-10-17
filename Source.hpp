#ifndef __Source_hpp__
#define __Source_hpp__


#define k_e 1.3893533*1e5

// DEFINITION OF THE CONSTRUCT Particle
Particle::Particle(double q, double m, arma::vec r, arma::vec v)
{
  // Use the input variables (q, m, r, v) to assign values to the class member variables (charge, mass, position, velocity)
  q_ = q;
  m_ = m;
  r_ = r;
  v_ = v;
}


// DEFINITION OF THE CUNSTRUCT PenningTrap
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in)
{
  // Use the input variables (B0_in, V0_in, d_in) to assign values to the class member variables (B0, V0, d)
  B0 = B0_in;
  V0 = V0_in;
  d = d_in;
}


//NOW WE ARE GOING TO MAKE ALL THE DEFINITIONS OF THE FUNCTIONS OF PenningTrap

// DEFINITION OF add_particle FUNTION
// Introduce a Particle type object called p_in to the end of the Penning Trap vector called Particle_.
void PenningTrap::add_particle(Particle p_in)
{
Particle_.push_back(p_in);
}


// DEFINITION OF THE external_E_field FUNCTION
// This function gives the electric field produced by a certain point r = (x, y, z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
  // Compute the electric as -grad(V)
  double ratio = V0 / (d * d);
  arma::vec E = {ratio * r(0), ratio * r(1), -2 * ratio * r(2)};
  return E;
}


// DEFINITION OF THE external_b_field FUNCTION
// This function gives the magnetic field produced in a certain point r = (x, y, z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
  // As said in theory, the B field only has the k component
  arma::vec B = {0.0, 0.0, B0};
  return B;
}


// DEFINITION OF THE force_particle
// This function gives the force received by particle i caused by particle j
arma::vec PenningTrap::force_particle(int i, int j)
{
  if (i == j)
  {
    arma::vec force(3, arma::fill::zeros);     // the force is 0 if particle i = particle j
    return force;
  }
  else
  {
    // Set the Coulomb force between particle i and particle j
    arma::vec force = arma::vec(3);
    arma::vec dr = Particle_[i].r_ - Particle_[j].r_;
    force = k_e * Particle_[i].q_ * Particle_[j].q_ * (dr) / std::pow(arma::norm(dr), 3);
    return force;
  }
}


#endif