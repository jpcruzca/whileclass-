#include<iostream>
#include<cmath>

struct Complex
{
  double x{0.0},y{0.0};
  void print(void);
  double real(void);
  double imaginario(void);
  double norma(void);
  double angle(void);
  double seno(const Complex &rhf);
  Complex operator+(Complex &a)
  {
    Complex r;
    r.x=x+a.x;
    r.y=y+a.y;
    return r;
  }
   Complex operator-(Complex &a)
  {
    Complex r;
    r.x=x-a.x;
    r.y=y-a.y;
    return r;
  }
   Complex operator*(Complex &a)
  {
    Complex r;
    r.x=x*a.x-y*a.y;
    r.y=x*a.y+y*a.x;
    return r;
  }
  Complex operator/(Complex &a)
  {
    Complex r;
    r.x=(x*a.x-y*a.y)/(a.y*a.y+a.x*a.x);
    r.y=x*a.y+y*a.x/(a.y*a.y+a.x*a.x);
    return r;
  }
};
int main()
{
  Complex z1,z2,z3,z4;
  z1.x=9.8;
  z1.y=12;
  z2.x=17.8;
  z2.y=-12;
  z3.x=-17.4;
  z3.y=12.36;
    
  z1.print();
  z1.real();
  z4=z1*z2;
  z4.print();
  z4=z1/z2;
  z4.print();
  seno(z4);

}
void Complex::print(void)//de esta forma se hace la funcion print sepa que los datos se encuentran la struct 
{
  std::cout<<"("<< x <<" , "<< y<< ")"<< std::endl;
  
}
double Complex::real(void)
{
  return x;
}
double Complex::imaginario(void)
{
  return y;
}
double Complex::norma(void)
{
  //return std::sqrt(x*x+y*y);
  return std::hypot(x,y);//calcula la norma de xy y
}
double Complex::angle(void)
{
  return std::atan2(y,x);//calcula la norma de xy y
}
Complex Complex::seno(const Complex & rhf)
{
  Complex r;
  r.x=std::sin(x)*std::cosh(x);
  r.y=std::cos(x)*std::sinh(x);
  return rhf;
}
