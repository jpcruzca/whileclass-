#include<iostream>
#include<cmath>
const double G=-9.8;
const double K=253.3;
struct Particle
{
  double rad = 0.0;
  double mass = 0.0;
  double Rx = 0.0, Ry = 0.0, Rz = 0.0;
  double Vx = 0.0, Vy = 0.0, Vz = 0.0;
  double Fx = 0.0, Fy = 0.0, Fz = 0.0;
};

void initial_conditions(Particle & body);
void compute_force(Particle & body);
void time_integration(Particle & body, const double & dt);
void start_integration(Particle & body, const double & dt);
void print(Particle & body, double time);
int main()
{
  Particle ball;
  
  // start system
  initial_conditions(ball);
  compute_force(ball);
  start_integration(ball, DT);
  print(ball, 0.0);
  
  // evolve
  for(int istep = 0; istep < NSTEPS; ++istep) {
    time_integration(ball, DT);
    compute_force(ball);
    print(ball, istep*DT);
  }
  
  return 0;

}
void compute_force(Particle & body, const double dt)
{
  // reset force
  body.Fx = body.Fy = body.Fz = 0.0;

  // gravitational force
  body.Fy += body.mass*G;
 // force with ground
  double delta = body.rad - body.Ry;
  if (delta > 0) {
    body.Fy += K*delta;
    //body.Fy -= 1.9876*body.Vy; 

}
void initial_conditions(Particle & body)
{
  body.Ry = 1.6598;
  body.Vx = 0.23698;

  body.rad = 0.235;
  body.mass = 0.29698;
}
void start_integration(Particle & body, const double & dt)
{
  
}

void time_integration(Particle & body, const double & dt)
{
  body.Rx = body.Rx+body.Vx*dt+body.Fx*dt*dt*0.5/body.mass;
  body.Ry = body.Ry+body.Vy*dt+body.Fy*dt*dt*0.5/body.mass;
  body.Rz = body.Rz+body.Vz*dt+body.Fz*dt*dt*0.5/body.mass;

  body.Vx= body.Vx+dt*body.Fx/mass;
  body.Vy= body.Vy+dt*body.Fy/mass;
  body.Vz= body.Vz+dt*body.Fz/mass;
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
