// Vicen� Verge Mond�jar
// Usuari u1954010
// Pr�ctica 1

#include "myexception.h"

myexception::myexception(const string message): _message(message) { }

myexception::~myexception() throw() {
}

const char* myexception::what() const throw() {
        return _message.c_str();
}
