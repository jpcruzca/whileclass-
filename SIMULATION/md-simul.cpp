#include "md-simul.h"

void initial_conditions(Particle & body)
{
  body.Rx=4;
  body.Ry = 50.3698;
  body.Vx = 50.3698;
  body.Vy= 3;

  body.rad = 0.235;
  body.mass = 0.29698;
}

void compute_force(Particle & body)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

  // gravitational force
  body.Fy += body.mass*G;

  // force with ground
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    body.Fy -= 1.9876*body.Vy; 
  }
  double delta1 = body.rad+ body.Ry -30.0;// UPER WALL 
  if (delta1 > 0) {
    body.Fy -= K*delta1;
    body.Fy -= 1.9876*body.Vy; 
  }
  //force with wall 
  double delta2 = body.rad+body.Rx-30.0;
  if (delta2 > 0) {
    body.Fx -= 100.0*delta2;
    body.Fx -= 1.9876*body.Vx; 
  }
   double delta22 = body.rad - body.Rx;
  if (delta22 > 0) {
    body.Fx += K*delta22;
    //body.Fy -= 1.9876*body.Vy; 
  }
   //force with wall 
  double delta3 = body.rad+body.Rz-30.0;
  if (delta3 > 0) {
    body.Fz -= 100.0*delta3;
    //body.Fz -= 1.9876*body.Vz; 
  }
   double delta33 = body.rad - body.Rz;
  if (delta33 > 0) {
    body.Fz += K*delta33;
    //body.Fz -= 1.9876*body.Vz; 
  }
}

void start_integration(Particle & body, const double & dt)
{
  body.Vx -= body.Fx*dt/(2*body.mass);
  body.Vy -= body.Fy*dt/(2*body.mass);
  body.Vz -= body.Fz*dt/(2*body.mass);
}

  void time_integration(Particle & body, const double & dt)
{
  // leap-frog
  body.Vx += body.Fx*dt/(body.mass);
  body.Vy += body.Fy*dt/(body.mass);
  body.Vz += body.Fz*dt/(body.mass);
  body.Rx += body.Vx*dt; 
  body.Ry += body.Vy*dt; 
  body.Rz += body.Vz*dt; 
}

void print(Particle & body, double time)
{
  std::cout << time << "  " 
            << body.Rx << "  "
            << body.Ry << "  "
            << body.Rz << "  "
            << body.Vx << "  "
            << body.Vy << "  "
            << body.Vz << "  "
            << "\n";
}
