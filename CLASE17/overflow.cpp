#include<iostream>
typedef double real;//renombra el tipo de dato;
int main(void)
{
  int N=1080;
  real x=1,y=1;
  for(int i=1; i<N; i++)
    {
      x /= (6.0);
      std::cout<< i << " "<< x <<std::endl; 
    }

  for(int ii=0;ii <N; ii++)
    {
      y *= (6.0);
      std::cout<< ii << " "<< y <<std::endl; 
    }
  
  
  return 0;
  
}
