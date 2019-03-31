#ifndef VECTOR_CLASS
#define VECTOR_CLASS

#include <iostream>

class Vector
{
  unsigned int size;
  int *value;

public:
  Vector(unsigned int size, int *value);
  Vector(Vector const &);
  void operator+(const Vector &); // Addition
  void operator*(const Vector &); // Dot Product
  const Vector operator*(const int &);    // Multiplication with a scalar
  friend std::ostream &operator<<(std::ostream &os, const Vector &r)
  {
    if (r.value == NULL)
    {
      os << "Vector sizes does not match" << std::endl;
      return os;
    }
    os << "(";
    for (int i = 0; i < r.size - 1; i++)
    {
      os << r.value[i] << ", ";
    }
    os << r.value[r.size - 1] << ")" << std::endl;
  } // Overload
  int *get_values();
  unsigned int get_size();
};

#endif