#include "transform.h"
#include <cmath>
using std::list;

Transformation::Transformation(): A(Matrix(4,4)),rA(Matrix(4,4)){}

Transformation& Transformation::operator=(const Transformation& other)
{
	A=other.A;
	rA=other.rA;
	return *this;
}

Transformation::~Transformation(){}

Matrix Transformation::operator*(const Matrix &point)
{
	return A*point;
}

Transformation::operator Matrix()
{
    return this->A;
}

Matrix Transformation::return_rA(){return rA;}

Translate::Translate(const double &trans_x, const double &trans_y, const double &trans_z)
{
	for(int i=1; i<=4; ++i)
	{
		A.set_el(i,i,1);
		rA.set_el(i,i,1);
	}
     
    A.set_el(1,4,trans_x);
    A.set_el(2,4,trans_y);
    A.set_el(3,4,trans_z);
    rA.set_el(1,4,-trans_x);
    rA.set_el(2,4,-trans_y);
    rA.set_el(3,4,-trans_z);
    
}

Scale::Scale(const double &s_x, const double &s_y, const double &s_z, const double &x_0, const double &y_0, const double &z_0)
{
    A.set_el(1,1,s_x);
    A.set_el(2,2,s_y);
    A.set_el(3,3,s_z);
    A.set_el(4,4,1);
    A.set_el(1,4, x_0*(1-s_x));
    A.set_el(2,4, y_0*(1-s_y));
    A.set_el(3,4, z_0*(1-s_z));
    
    rA.set_el(1,1,1/s_x);
    rA.set_el(2,2,1/s_y);
    rA.set_el(3,3,1/s_z);
    rA.set_el(4,4,1);
    rA.set_el(1,4, x_0*(1-1/s_x));
    rA.set_el(2,4, y_0*(1-1/s_y));
    rA.set_el(3,4, z_0*(1-1/s_z));
}

Rotate_X::Rotate_X(const double &angle, const double &x_0, const double &y_0, const double &z_0)
{
    A.set_el(1,1,1);
    A.set_el(2,2,cos(M_PI*angle/180));
    A.set_el(3,2,sin(M_PI*angle/180));
    A.set_el(2,3,-sin(M_PI*angle/180));
    A.set_el(3,3,cos(M_PI*angle/180));
    A.set_el(2,4,(-1)*y_0*cos(M_PI*angle/180)+z_0*sin(M_PI*angle/180)+y_0);
    A.set_el(3,4,(-1)*y_0*sin(M_PI*angle/180)-z_0*sin(M_PI*angle/180)+z_0);
    A.set_el(4,4,1);
    
    rA.set_el(1,1,1);
    rA.set_el(2,2,cos(M_PI*(-angle)/180));
    rA.set_el(3,2,sin(M_PI*(-angle)/180));
    rA.set_el(2,3,-sin(M_PI*(-angle)/180));
    rA.set_el(3,3,cos(M_PI*(-angle)/180));
    rA.set_el(2,4,(-1)*y_0*cos(M_PI*(-angle)/180)+z_0*sin(M_PI*(-angle)/180)+y_0);
    rA.set_el(3,4,(-1)*y_0*sin(M_PI*(-angle)/180)-z_0*sin(M_PI*(-angle)/180)+z_0);
    rA.set_el(4,4,1);
}

Rotate_Y::Rotate_Y(const double &angle, const double &x_0, const double &y_0, const double &z_0)
{
    A.set_el(1,1,cos(M_PI*angle/180));
    A.set_el(2,2,1);
    A.set_el(1,3,sin(M_PI*angle/180));
    A.set_el(3,3,cos(M_PI*angle/180));
    A.set_el(3,1,-sin(M_PI*angle/180));
    A.set_el(1,4,(-1)*x_0*cos(M_PI*angle/180)-z_0*sin(M_PI*angle/180)+x_0);
    A.set_el(3,4,x_0*sin(M_PI*angle/180)-z_0*cos(M_PI*angle/180)+z_0);
    A.set_el(4,4,1);
    
    rA.set_el(1,1,cos(M_PI*(-angle)/180));
    rA.set_el(2,2,1);
    rA.set_el(1,3,sin(M_PI*(-angle)/180));
    rA.set_el(3,3,cos(M_PI*(-angle)/180));
    rA.set_el(3,1,-sin(M_PI*(-angle)/180));
    rA.set_el(1,4,(-1)*x_0*cos(M_PI*(-angle)/180)-z_0*sin(M_PI*(-angle)/180)+x_0);
    rA.set_el(3,4,x_0*sin(M_PI*(-angle)/180)-z_0*cos(M_PI*(-angle)/180)+z_0);
    rA.set_el(4,4,1);
}

Rotate_Z::Rotate_Z(const double &angle, const double &x_0, const double &y_0, const double &z_0)
{
    A.set_el(1,1,cos(M_PI*angle/180));
    A.set_el(1,2,-sin(M_PI*angle/180));
    A.set_el(2,1,sin(M_PI*angle/180));
    A.set_el(2,2,cos(M_PI*angle/180));
    A.set_el(3,3,1);
    A.set_el(1,4,(-1)*x_0*cos(M_PI*angle/180)+y_0*sin(M_PI*angle/180)+x_0);
    A.set_el(2,4,(-1)*x_0*sin(M_PI*angle/180)-y_0*cos(M_PI*angle/180)+y_0);
    A.set_el(4,4,1);
    
    rA.set_el(1,1,cos(M_PI*(-angle)/180));
    rA.set_el(1,2,-sin(M_PI*(-angle)/180));
    rA.set_el(2,1,sin(M_PI*(-angle)/180));
    rA.set_el(2,2,cos(M_PI*(-angle)/180));
    rA.set_el(3,3,1);
    rA.set_el(1,4,(-1)*x_0*cos(M_PI*(-angle)/180)+y_0*sin(M_PI*(-angle)/180)+x_0);
    rA.set_el(2,4,(-1)*x_0*sin(M_PI*(-angle)/180)-y_0*cos(M_PI*(-angle)/180)+y_0);
    rA.set_el(4,4,1);
}

void All_transformations::Add_transformation(Transformation* t)
{
    trans.push_back(t);
}

void All_transformations::Create_transformation()
{
    for(int i=1; i<=4; ++i)
    {
		for (int j=1; j<=4; ++j)
		{
			if(i==j) A.set_el(i,j,1);
			else A.set_el(i,j,0);
		}
    }
    for(list<Transformation*>::iterator it=trans.begin(); it!=trans.end(); ++it)
	A=A*(**it);
}

void All_transformations::Create_reverse_transformation()
{
    for(int i=1; i<=4; ++i)
    {
		for (int j=1; j<=4; ++j)
		{
			if(i==j) A.set_el(i,j,1);
			else A.set_el(i,j,0);
		}
    }
    for(auto it=trans.rbegin(); it!=trans.rend(); ++it)
		A=A*((*it)->return_rA());
}

Transformation& All_transformations::operator[](unsigned index)
{
    auto it=trans.begin();
    for(unsigned i=1; i<index; ++i, ++it){}
    	return *(*it);
}

All_transformations::~All_transformations()
{
    for(list<Transformation*>::iterator it=trans.begin(); it!=trans.end(); ++it)
		delete *it;
}
