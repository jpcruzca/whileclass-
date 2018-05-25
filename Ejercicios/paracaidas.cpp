#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cstdlib>
const double g=-9.81,m=90,cd=0.225, eps=1e-10; 
double f(double t, std::vector<double> &y, double id);
void rk4(double ta, double tb, double h, std::vector<double> &y);
int main(void)
{
  const double h=0.001;
  const double to = 0;
  const double tf = 25;
  const int N=2;
  std::vector<double> y = {1000,0};
  rk4(to,tf,h, y);
  
}
double f(double t, std::vector<double> &y, double id)
{
  if(0==id)
    {
      return y[1];
    }
  else if(1==id)
    {
      return g+(cd/m)*std::pow(y[1],2);
    }
  else
    {
      std::cerr << " ERROR " << id << std::endl;
    }    
}
void rk4(double ta, double tb, double h, std::vector<double> & y)
{
  std::vector<double> k1, k2, k3, k4, aux;
  k1.resize(y.size());
  k2.resize(y.size());
  k3.resize(y.size());
  k4.resize(y.size());
  aux.resize(y.size());

  const int N = (tb-ta)/h;
  for (int nt = 0; nt < N; ++nt) {
    double t = ta + h*nt; 
    // k1
    for(int ii = 0; ii < y.size(); ++ii) {
      k1[ii] = h*f(t, y, ii);
    }
    // k2 aux
    for(int ii = 0; ii < y.size(); ++ii) {
      aux[ii] = y[ii] + k1[ii]/2;
    }
    //k2
    for(int ii = 0; ii < y.size(); ++ii) {
      k2[ii] = h*f(t+h/2, aux, ii);
    }
    // k3 aux
    for(int ii = 0; ii < y.size(); ++ii) {
      aux[ii] = y[ii] + k2[ii]/2;
    }
    //k3
    for(int ii = 0; ii < y.size(); ++ii) {
      k3[ii] = h*f(t + h/2, aux, ii);
    }
    // k4 aux
    for(int ii = 0; ii < y.size(); ++ii) {
      aux[ii] = y[ii] + k3[ii];
    }
    //k4
    for(int ii = 0; ii < y.size(); ++ii) {
      k4[ii] = h*f(t + h, aux, ii);
    }
    // write new y
    for(int ii = 0; ii < y.size(); ++ii) {
      y[ii] = y[ii] + (k1[ii] + 2*k2[ii] + 2*k3[ii] + k4[ii])/6.0;
    }
    std::cout << t << "\t" << y[0] << "\t" << y[1] << std::endl;
    if(std::fabs(y[0]<eps))
      break;
  }
}
