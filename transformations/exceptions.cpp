#include "exceptions.h"
#include <iostream>
using namespace std;

Exceptions::Exceptions(){}
Exceptions::~Exceptions(){}

Exception_file::Exception_file(){}
Exception_file::~Exception_file(){}

void Exception_file::print_exception()
{
    cout<<"Nie udalo sie otworzyc pliku\n";
}

Exception_arg::Exception_arg(int _nr): nr(_nr){}
Exception_arg::~Exception_arg(){}

void Exception_arg::print_exception()
{
    cout<<"Niepoprawna ilosc argumentow w linii numer: "<<nr<<endl;
}
