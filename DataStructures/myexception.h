/** @file myexception.h
    @brief Classe myexception
*/

// Vicen� Verge Mond�jar
// Usuari u1954010
// Pr�ctica 1

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>
#include <string>

using namespace std;

/** @class myexception
    @brief Classe que fa saltar les excepcions.
    @author Vicen� Verge
    @date 30/11/2018
*/

class myexception: public exception {
private:
  string _message;
public:
/**
    @brief Constructor al que se li dona un string
    @pre Cert
    @post Constructor amb un string introduit;
*/
  myexception(const string message);
/**<
    @brief Destructor
    @pre Cert
    @post Destructor
*/
  virtual ~myexception() throw();
/**<
    @brief Treu per pantalla l'string
    @pre Cert
    @post Treu per pantalla l'string
*/
  virtual const char* what() const throw();
      // Nota: trow() indica que aquest m�tode no llan�ar� cap excepci�
      //       (es cridar� std::unexpected si es produeix una excepci�)
};

#endif // MYEXCEPTION_H
