#include "transform.h"
#include <cmath>

Transformation::Transformation(const Matrix &mat): A(Matrix(4,4)), B(Matrix(mat)){}

Transformation::~Transformation(){}

Matrix Transformation::transformation()
{
	return A*B;
}

Translate_point::Translate_point(const Matrix& mat, const double &trans_x, const double &trans_y, const double &trans_z): Transformation(mat)
{
     for(int i=1; i<=4; ++i)
        A.set_el(i,i,1);

    A.set_el(1,4,trans_x);
    A.set_el(2,4,trans_y);
    A.set_el(3,4,trans_z);
}

Scale_point::Scale_point(const Matrix& mat, const double &s_x, const double &s_y, const double &s_z, const double &x_0, const double &y_0, const double &z_0): Transformation(mat)
{
    A.set_el(1,1,s_x);
    A.set_el(2,2,s_y);
    A.set_el(3,3,s_z);
    A.set_el(4,4,1);
    A.set_el(1,4, x_0*(1-s_x));
    A.set_el(2,4, y_0*(1-s_y));
    A.set_el(3,4, z_0*(1-s_z));
}

Rotate_point_X::Rotate_point_X(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0): Transformation(mat)
{
    A.set_el(1,1,1);
    A.set_el(2,2,cos(M_PI*angle/180));
    A.set_el(3,2,sin(M_PI*angle/180));
    A.set_el(2,3,-sin(M_PI*angle/180));
    A.set_el(3,3,cos(M_PI*angle/180));
    A.set_el(2,4,(-1)*y_0*cos(M_PI*angle/180)+z_0*sin(M_PI*angle/180)+y_0);
    A.set_el(3,4,(-1)*y_0*sin(M_PI*angle/180)-z_0*sin(M_PI*angle/180)+z_0);
    A.set_el(4,4,1);
}

Rotate_point_Y::Rotate_point_Y(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0): Transformation(mat)
{
    A.set_el(1,1,cos(M_PI*angle/180));
    A.set_el(2,2,1);
    A.set_el(1,3,sin(M_PI*angle/180));
    A.set_el(3,3,cos(M_PI*angle/180));
    A.set_el(3,1,-sin(M_PI*angle/180));
    A.set_el(1,4,(-1)*x_0*cos(M_PI*angle/180)-z_0*sin(M_PI*angle/180)+x_0);
    A.set_el(3,4,x_0*sin(M_PI*angle/180)-z_0*cos(M_PI*angle/180)+z_0);
    A.set_el(4,4,1);
}

Rotate_point_Z::Rotate_point_Z(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0): Transformation(mat)
{
    A.set_el(1,1,cos(M_PI*angle/180));
    A.set_el(1,2,-sin(M_PI*angle/180));
    A.set_el(2,1,sin(M_PI*angle/180));
    A.set_el(2,2,cos(M_PI*angle/180));
    A.set_el(3,3,1);
    A.set_el(1,4,(-1)*x_0*cos(M_PI*angle/180)+y_0*sin(M_PI*angle/180)+x_0);
    A.set_el(2,4,(-1)*x_0*sin(M_PI*angle/180)-y_0*cos(M_PI*angle/180)+y_0);
    A.set_el(4,4,1);
}
