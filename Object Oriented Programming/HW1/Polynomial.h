#ifndef POLYNOMIAL_CLASS
#define POLYNOMIAL_CLASS

#include <iostream>

class Polynomial
{
  unsigned int degree;
  int *value;

public:
  Polynomial(unsigned int degree, int *value);
  Polynomial(Polynomial const &);
  friend std::ostream &operator<<(std::ostream &os, const Polynomial &r)
  {
    for (unsigned int i = 0; i < r.degree + 1; i++)
    {
      if (r.value[i] == 0)
        continue;

      if (i == r.degree)
      {
        if (r.value[i] > 0)
        {
          os << "+" << r.value[i] << std::endl;
        }
        else
        {
          os << r.value[i] << std::endl;
        }

        return os;
      }

      if (i == r.degree - 1)
      {
        if (r.value[i] > 0)
        {
          if (r.value[i] != 1)
            os << "+" << r.value[i] << "x ";
          else
            os << "+"
               << "x ";
        }
        else
        {
          if (r.value[i] != -1)
            os << r.value[i] << "x ";
          else
            os << "-x ";
        }

        continue;
      }

      if (r.value[i] < 0)
      {
        if (r.value[i] != -1)
          os << r.value[i] << "x^" << (r.degree - i) << " ";
        else
          os << "-x^" << (r.degree - i) << " ";
      }
      else
      {
        if (r.value[i] != 1)
          os << "+" << r.value[i] << "x^" << (r.degree - i) << " ";
        else
          os << "+x^" << (r.degree - i) << " ";
      }
    }
    return os;
  }                                               // Overload
  const Polynomial operator+(const Polynomial &); // Addition
  const Polynomial operator*(const Polynomial &); // Multiplication
  int *get_values();
  unsigned int get_degree();
};

#endif