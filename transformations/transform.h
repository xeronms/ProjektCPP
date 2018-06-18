#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "matrix.h"

class Transformation
{
protected:
    Matrix A;
    Matrix B;
public:
    Transformation(const Matrix &mat);
    Matrix transformation();
    virtual ~Transformation()=0;
};

class Translate_point: public Transformation
{
public:
    Translate_point(const Matrix& mat, const double &trans_x, const double &trans_y, const double &trans_z);
};

class Scale_point: public Transformation
{
public:
    Scale_point(const Matrix& mat, const double &s_x, const double &s_y, const double &s_z, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_point_X: public Transformation
{
public:
    Rotate_point_X(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_point_Y: public Transformation
{
public:
    Rotate_point_Y(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_point_Z: public Transformation
{
public:
    Rotate_point_Z(const Matrix& mat, const double &angle, const double &x_0, const double &y_0, const double &z_0);
};
#endif
