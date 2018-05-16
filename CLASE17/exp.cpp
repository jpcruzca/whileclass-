#include<iostream>
#include<cmath>
double exp(double x, int n);
int main(void)
{
  double x=10;
  int n=10;
  for(int i=0; i<n; i++)
    {
      std::cout<<i<<"  "<<exp(x,i)<< std::endl;
    }
  std::cout<< exp(x,n) <<" "<< std::exp(-x) << std::endl;
  return 0; 
}
double exp(double x, int n)
{
  double r=0;
  if(n=0)
    r=1;
  else
    r+= exp(n-1)*(-x)/(n+1);
  return r;
}
