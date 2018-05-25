#include<iostream>
#include<cmath>

struct Quaternion
{
  double x{0.0},y{0.0},z{0.0},w{0.0};
  void print(void);
  Quaternion operator+(Quaternion &a)
  {
    Quaternion r;
    r.x=x+a.x;
    r.y=y+a.y;
    r.z=z+a.z;
    r.w=w+a.w;
    return r;
  }
   Quaternion operator-(Quaternion &a)
  {
    Quaternion r;
    r.x=x-a.x;
    r.y=y-a.y;
    r.z=z-a.z;
    r.w=w-a.w;
    return r;
  }
   Quaternion operator*(Quaternion &a)
  {
    Quaternion r;
    r.x=x*a.x-y*a.y-z*a.z-w*a.w;
    r.y=x*a.y+y*a.x+z*a.w-w*a.z;
    r.z=z+a.y;
    r.w=w+a.y;
    return r;
  }
};
int main()
{
  Quaternion q1,q2;
  q1.x=1;
  q1.y=2;
  q1.z=3;
  q1.w=0;
  
  q2.x=0;
  q2.y=2;
  q2.z=-3.4;
  q2.w=-1;
  Quaternion q3;
  q3=q1+q2;
  q3.print();
  q3=q1-q2;
  q3.print();
  q3=q1*q2;
  q3.print();
}
void Quaternion::print(void) 
{
  std::cout<<"("<< x <<" , "<< y<< " , " <<z<<" , " <<w<<")"<< std::endl;
  
}
