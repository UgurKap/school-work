#include "Polynomial.h"
#include <iostream>

Polynomial::Polynomial(unsigned int degree, int *value)
{
    this->degree = degree;
    this->value = new int[degree + 1];
    for (int i = 0; i < degree + 1; i++)
    {
        this->value[i] = value[i];
    }
}

Polynomial::Polynomial(Polynomial const &r)
{
    delete[] value;
    degree = r.degree;
    value = new int[degree + 1];
    for (int i = 0; i < degree + 1; i++)
    {
        value[i] = r.value[i];
    }
}

const Polynomial Polynomial::operator+(const Polynomial &r)
{
    // Values for the new instance to be created
    int *values;
    unsigned int new_degree = 0;

    // Checking which one is greater
    if (degree > r.degree)
    {
        new_degree = degree;                // New instance should get the degree of the greater one
        int difference = degree - r.degree; // How much greater
        values = new int[degree + 1];

        // Since there is nothing in the second polynomial to add, we just put them directly into the new instance
        for (int i = 0; i < difference; i++)
        {
            values[i] = value[i];
        }

        // This is where the remaining entries are added
        for (int i = difference; i < degree + 1; i++)
        {
            values[i] = value[i] + r.value[i - difference];
        }
    }
    else
    {
        new_degree = r.degree;              // New instance should get the degree of the greater one
        int difference = r.degree - degree; // How much greater
        values = new int[r.degree + 1];

        // Since there is nothing in the second polynomial to add, we just put them directly into the new instance
        for (int i = 0; i < difference; i++)
        {
            values[i] = r.value[i];
        }

        // This is where the remaining entries are added
        for (int i = difference; i < r.degree + 1; i++)
        {
            values[i] = value[i - difference] + r.value[i];
        }
    }
    Polynomial temp(new_degree, values);
    return temp;
}

const Polynomial Polynomial::operator*(const Polynomial &r)
{
    // Determine the degree of the new polynomial and create an array with sufficient capacity
    unsigned int new_degree = degree + r.degree;
    int *values = new int[new_degree + 1];

    for (int i = 0; i < new_degree + 1; i++)
    {
        values[i] = 0;
    }

    // For every entry in the first array, multiply it with the seconds' all elements and put it in the correct place
    for (int i = 0; i < degree + 1; i++)
    {
        for (int j = 0; j < r.degree + 1; j++)
        {
            values[i + j] += this->value[i] * r.value[j];
        }
    }
    Polynomial temp(new_degree, values);
    return temp;
}

int *Polynomial::get_values()
{
    return value;
}

unsigned int Polynomial::get_degree()
{
    return degree;
}