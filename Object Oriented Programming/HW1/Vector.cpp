#include "Vector.h"
#include <iostream>

Vector::Vector(unsigned int size, int *value)
{
    if (size != 0)
    {
        this->size = size;
        this->value = new int[size];
        for (int i = 0; i < size; i++)
        {
            this->value[i] = value[i];
        }
    }
    else
    {
        this->size = 0;
        this->value = NULL;
    }
}

Vector::Vector(Vector const &r)
{
    if (this->value != NULL)
    {
        delete[] this->value;
        this->value = NULL;
        value = NULL;
        size = 0;
    }

    if (r.size != 0)
    {
        this->size = r.size;
        this->value = new int[r.size];
        for (int i = 0; i < r.size; i++)
        {
            this->value[i] = r.value[i];
        }
    }
}

void Vector::operator+(const Vector &r)
{
    if (size != r.size)
    {
        std::cout << "Sizes does not match" << std::endl;
        return;
    }

    int *values = new int[size];

    for (int i = 0; i < size; i++)
    {
        values[i] = value[i] + r.value[i];
    }

    Vector temp(size, values);
    std::cout << temp << std::endl;
}

void Vector::operator*(const Vector &r)
{
    if (size != r.size)
    {
        std::cout << "Sizes does not match" << std::endl;
        return;
    }
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += value[i] * r.value[i];
    }
    std::cout << sum << std::endl;
}

const Vector Vector::operator*(const int &r)
{
    int *values = new int[size];
    for (int i = 0; i < size; i++)
    {
        values[i] = value[i] * r;
    }
    Vector temp(size, values);
    return temp;
}

int *Vector::get_values()
{
    return value;
}

unsigned int Vector::get_size()
{
    return size;
}