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
    virtual Transformation& operator=(const Transformation& other);
    virtual ~Transformation()=0;
};

class Translate: public Transformation
{
public:
    Translate(const double &trans_x, const double &trans_y, const double &trans_z);
    using Transformation::operator=;
};

class Scale: public Transformation
{
public:
    Scale(const double &s_x, const double &s_y, const double &s_z, const double &x_0, const double &y_0, const double &z_0);
    using Transformation::operator=;
};

class Rotate_X: public Transformation
{
public:
    Rotate_X(const double &angle, const double &x_0, const double &y_0, const double &z_0);
    using Transformation::operator=;
};

class Rotate_Y: public Transformation
{
public:
    Rotate_Y(const double &angle, const double &x_0, const double &y_0, const double &z_0);
    using Transformation::operator=;
};

class Rotate_Z: public Transformation
{
public:
    Rotate_Z(const double &angle, const double &x_0, const double &y_0, const double &z_0);
    using Transformation::operator=;
};

class All_transformations: public Transformation
{
    std::list<Transformation*> trans;
public:
    void Add_transformation(Transformation *t);
    void Create_transformation();
    void Create_reverse_transformation();
    Transformation& operator[](unsigned index);
    ~All_transformations();
};
#endif
