#include "mdsimul.h"

// function implementations
void material_properties(std::vector<Particle> & balls)
{
  std::mt19937 gen; // random generator: Mersenne-Twister
  gen.seed(1); // control the seed
  std::uniform_real_distribution<> dis(0.5*RAD, 1.0*RAD); // radii between R/2 and R
  
  // set radii randomly
  for(auto & body : balls){
    body.rad=dis(gen);
    body.mass=RHO*4*M_PI*body.rad*body.rad*body.rad/3;
  }
}

void initial_conditions(std::vector<Particle> & balls)
{
  // special condition
  
  // set up uniformly on a 2d grid

  // put on the 2d grid
  const int NX=L/(2*RAD);
  for(int id=0; id<balls.size(); ++id){
    int ix=id%NX; int iy=id/NX;
    balls[id].Rx = RAD + ix*2*RAD;
    balls[id].Ry = RAD + iy*2*RAD;
    balls[id].Rz = 0.0;
  }

  // initial velocity could be random, for now everything going up
  std::mt19937 gen; // random generator: Mersenne-Twister
  gen.seed(1); // control the seed
  std::uniform_real_distribution<> dis(0, 2*M_PI); // radii between R/2 and R
  const double V0 = 0.23;
  for(auto & body : balls){
    body.Vx = V0*std::cos(dis(gen));
    body.Vy = V0*std::sin(dis(gen));
  }
}
void compute_force(std::vector<Particle> & balls)
{
  for(auto & body : balls){
    // reset force
    body.Fx = body.Fy = body.Fz = 0.0;

    // add gravitational force
    body.Fy += body.mass*G; // G is already negative

    // add force with bottom wall
    double delta = body.rad - body.Ry;
    if (delta > 0) {
      body.Fy += K*delta;
    }

    // left wall
    delta = body.rad - body.Rx;
    if (delta > 0) {
      body.Fx += K*delta;
    }

    // right wall
    delta = body.rad + body.Rx - L;
    if (delta > 0) {
      body.Fx -= K*delta;
    }

    // top wall
    delta = body.rad + body.Ry - L;
    if (delta > 0) {
      body.Fy -= K*delta;
    }

    
  }

  // force with other particles
  for(int id = 0; id < balls.size(); ++id) {
    for(int jd = id+1; jd < balls.size(); ++jd) {
      double Rij[3], Nij[3];
      Rij[0] = balls[jd].Rx - balls[id].Rx;
      Rij[1] = balls[jd].Ry - balls[id].Ry;
      Rij[2] = balls[jd].Rz - balls[id].Rz;
      double rij = std::sqrt(Rij[0]*Rij[0] + Rij[1]*Rij[1] + Rij[2]*Rij[2]);
      Nij[0] = Rij[0]/rij;
      Nij[1] = Rij[1]/rij;
      Nij[2] = Rij[2]/rij;
      double delta = balls[id].rad + balls[jd].rad - rij;
      if (delta > 0){
        balls[jd].Fx += K*delta*Nij[0]; 
        balls[jd].Fy += K*delta*Nij[1]; 
        balls[jd].Fz += K*delta*Nij[2]; 
        balls[id].Fx -= K*delta*Nij[0]; 
        balls[id].Fy -= K*delta*Nij[1]; 
        balls[id].Fz -= K*delta*Nij[2]; 
      }
    }
  }
    
    

}

void start_integration(std::vector<Particle> & balls)
{
  for(auto & body : balls){
    body.Vx -= 0.5*body.Fx*DT/body.mass;
    body.Vy -= 0.5*body.Fy*DT/body.mass;
    body.Vz -= 0.5*body.Fz*DT/body.mass;
  }
}

void integrate(std::vector<Particle> & balls)
{
  // use simple leap-frog
  for(auto & body : balls){
    body.Vx += body.Fx*DT/body.mass;
    body.Vy += body.Fy*DT/body.mass;
    body.Vz += body.Fz*DT/body.mass;
    body.Rx += body.Vx*DT;
    body.Ry += body.Vy*DT;
    body.Rz += body.Vz*DT;
  }
}

void print_info(const std::vector<Particle> & balls, const double & time)
{
  // here we print something useful
  // for now is just a test
  std::cerr.precision(16);
  std::cerr.setf(std::ios::scientific);
  
  std::cerr << time
            << "\t" << balls[0].Rx
            << "\t" << balls[0].Ry 
            << "\t" << balls[0].Rz 
            << "\t" << balls[0].Vx 
            << "\t" << balls[0].Vy 
            << "\t" << balls[0].Vz 
            << "\n";
}

void start_gnuplot(void)
{
  std::cout << "set parametric\n"; 
  std::cout << "set trange [0:2*pi]\n"; 
  std::cout << "set size ratio -1\n"; 
  std::cout << "unset key\n"; 
  std::cout << "set xrange [" << -0.02*L << ":" << 1.02*L << "]\n"; 
  std::cout << "set yrange [" << -0.02*L << ":" << 1.02*L << "]\n"; 
}

void print_gnuplot(const std::vector<Particle> & balls)
{
  std::cout << "plot ";
  for (const auto & body : balls) {
    std::cout << body.Rx << " + " << body.rad << "*cos(t), " 
              << body.Ry << " + " << body.rad << "*sin(t), "; 
  }
  std::cout << "0, 0 ";
  std::cout << std::endl;
}
