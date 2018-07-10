#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<iostream>
using std::string;

class Exceptions
{
    public:
        Exceptions();
        virtual ~Exceptions();
        virtual void print_exception()=0;
};

class Exception_file: public Exceptions
{
public:
    Exception_file();
    ~Exception_file();
    void print_exception();
};

class Exception_arg: public Exceptions
{
    unsigned nr;
public:
    Exception_arg(int _nr);
    ~Exception_arg();
    void print_exception();
};

class Exception_getset
{
public:
    string napis;
    Exception_getset()
    {
        napis="Macierz nie posiada takiego elementu";
    }
};

class Exception_add
{
public:
    string napis;
    Exception_add()
    {
        napis="Nie udalo sie dodac macierzy, rozne wymiary";
    }
};

class Exception_subtract
{
public:
    string napis;
    Exception_subtract()
    {
        napis="Nie udalo sie odjac macierzy, rozne wymiary";
    }
};

class Exception_multiply
{
public:
    string napis;
    Exception_multiply()
    {
        napis="Nie udalo sie pomnozyc macierzy, zle wymiary";
    }
};

class Exception_divide
{
public:
    string napis;
    Exception_divide()
    {
        napis="Nie wolno dzielic przez 0";
    }
};

class Exception_transformation
{
public:
    string napis;
    Exception_transformation()
    {
        napis="Nie ma takiego elementu\n";
    }
};
#endif // EXCEPTIONS_H
