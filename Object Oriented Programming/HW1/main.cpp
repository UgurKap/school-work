#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "Polynomial.h"
#include "Vector.h"

using namespace std;

class Interface
{
    vector<Vector> vectors;
    vector<Polynomial> polynomials;
    unsigned int vector_size;
    unsigned int poly_size;

  public:
    Interface();
    void add_vector(int first, int second);
    void multiply_vector(int first, int second);
    void add_polynomial(int first, int second);
    void multiply_polynomial(int first, int second);
    void multiply_vector_scalar(int vec, int num);
    void print_polynomials_and_vectors();
    void print_menu();
};

Interface::Interface()
{
    ifstream vec_file;
    vec_file.open("Vector.txt");
    ifstream poly_file;
    poly_file.open("Polynomial.txt");
    if (!vec_file || !poly_file)
    {
        cerr << "Check the input files" << endl;
        exit(EXIT_FAILURE);
    }

    vec_file >> vector_size;
    for (int i = 0; i < vector_size; i++)
    {
        int a;
        vec_file >> a;
        int *val = new int[a];
        for (int j = 0; j < a; j++)
        {
            vec_file >> val[j];
        }
        vectors.push_back(Vector(a, val));
    }

    poly_file >> poly_size;
    for (int i = 0; i < poly_size; i++)
    {
        int a;
        poly_file >> a;
        int *val = new int[a];
        for (int j = 0; j < a + 1; j++)
        {
            poly_file >> val[j];
        }
        polynomials.push_back(Polynomial(a, val));
    }

    poly_file.close();
    vec_file.close();
}

void Interface::print_menu()
{
    cout << "Possible Actions:" << endl;
    cout << "1. Print Polynomial and Vector lists" << endl
         << "2. Do a polynomial operation" << endl
         << "3. Do a vector operation" << endl
         << "4. Help: Print possible actions" << endl
         << "0. Exit the program" << endl
         << endl;
}

void Interface::print_polynomials_and_vectors()
{
    cout << "Vectors:" << endl;
    for (unsigned int i = 0; i < vector_size; i++)
    {
        cout << i + 1 << ". " << vectors[i] << endl;
    }
    cout << endl
         << "Polynomials: " << endl;
    for (unsigned int i = 0; i < poly_size; i++)
    {
        cout << i + 1 << ". " << polynomials[i] << endl;
    }
}

void Interface::add_vector(int first, int second)
{
    vectors[first - 1] + vectors[second - 1];
}

void Interface::multiply_vector(int first, int second)
{
    vectors[first - 1] * vectors[second - 1];
}

void Interface::add_polynomial(int first, int second)
{
    cout << polynomials[first - 1] + polynomials[second - 1] << endl;
}

void Interface::multiply_polynomial(int first, int second)
{
    cout << polynomials[first - 1] * polynomials[second - 1] << endl;
}

void Interface::multiply_vector_scalar(int vec, int num)
{
    cout << vectors[vec - 1] * num << endl;
}

int main()
{
    Interface program;
    program.print_menu();
    int run = 0;
    do
    {
        if (run > 4 || run < 0)
        {
            cout << "Not an option" << endl
                 << endl;
        }
        else if (run == 4)
        {
            program.print_menu();
        }
        else if (run == 1)
        {
            program.print_polynomials_and_vectors();
        }
        else if (run == 2)
        {
            cout << "Which polynomial operation would you like to do?(+: Addition | *: Multiplication)" << endl;
            int first, second;
            char op;
            cin >> first >> op >> second;
            if (op == '+')
            {
                program.add_polynomial(first, second);
            }
            else if (op == '*')
            {
                program.multiply_polynomial(first, second);
            }
            else
            {
                cout << "Invalid operation" << endl;
            }
        }
        else if (run == 3)
        {
            cout << "Which vector operation would you like to do?(+:Addition | *:Scalar Multiplication | .: Dot Product)" << endl;
            int first, second;
            char op;
            cin >> first >> op >> second;
            if (op == '+')
            {
                program.add_vector(first, second);
            }
            else if (op == '.')
            {
                program.multiply_vector(first, second);
            }
            else if (op == '*')
            {
                program.multiply_vector_scalar(first, second);
            }
            else
            {
                cout << "Invalid operation" << endl;
            }
        }
        cout << "Enter an option: ";
        cin >> run;
        cout << endl;
    } while (run);
    return 0;
}