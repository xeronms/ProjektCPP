#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "matrix.h"
#include <list>

class Transformation
{
protected:
    Matrix A;
    Matrix rA;
public:
    Transformation();
    Matrix operator*(const Matrix &point);
    operator Matrix();
    virtual Matrix return_rA();
    virtual Transformation& operator[](unsigned index);
    virtual Transformation& operator=(const Transformation& other);
    virtual ~Transformation()=0;
    virtual void Create_transformation();
    virtual void Create_reverse_transformation();
};

class Translate: public Transformation
{
public:
    Translate(const double &trans_x, const double &trans_y, const double &trans_z);
};

class Scale: public Transformation
{
public:
    Scale(const double &s_x, const double &s_y, const double &s_z, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_X: public Transformation
{
public:
    Rotate_X(const double &angle, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_Y: public Transformation
{
public:
    Rotate_Y(const double &angle, const double &x_0, const double &y_0, const double &z_0);
};

class Rotate_Z: public Transformation
{
public:
    Rotate_Z(const double &angle, const double &x_0, const double &y_0, const double &z_0);
};

class All_transformations: public Transformation
{
    std::list<Transformation*> trans;
public:
    void Add_transformation(Transformation *t);
    Transformation& operator[](unsigned index);
    All_transformations& operator=(const All_transformations& other);
    void Create_transformation();
    void Create_reverse_transformation();
};
#endif
