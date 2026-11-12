#include "../include/Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Adjacency_Matrix::Adjacency_Matrix(int n) : numVertices(n)
{
    // Dynamically allocate "matrix" to be an upper-right triangular matrix
    return;
}

Adjacency_Matrix::~Adjacency_Matrix()
{
    // Free dynamically allocated memory of the "matrix"
    return;
}

void Adjacency_Matrix::add_edge(int start, int end)
{
    return;
}

void Adjacency_Matrix::remove_edge(int start, int end)
{
    return;
}

bool Adjacency_Matrix::has_edge(int start, int end)
{
    return false;
}

int Adjacency_Matrix::degree(int node)
{
    return -1;
}

// ---------------------- TASK 2 ----------------------------------

void Adjacency_List::add_edge(string a, string b)
{
    return;
}

void Adjacency_List::remove_edge(string a, string b)
{
    return;
}

bool Adjacency_List::has_edge(string a, string b)
{
    return false;
}

int Adjacency_List::solve_equation(string key)
{
    // NEED TO PERFORM POST ORDER SEARCH TO SOLVE THIS.
    // FOR EACH KEY THAT IS AN OPERAND, GET THE INTEGER VALUE OF ITS TWO CHILDREN
    // AND THEN PERFORM THE RESPECTIVE OPERATION ON IT AND RETURN THE VALUE OF THAT OPERATION
    /*
         +
        / \
       /   \
      4     5

      a solve equation("+") in the above tree should get the values of the children 4 and 5
      and then add them to make 9 and return 9. 
    */

    // if (key == "+")
    // {
    // }
    // else if (key == "-")
    // {
    // }
    // else if (key == "*")
    // {
    // }
    // else if (key == "/")
    // {
    // }
    // else 
    // {
    //     Base Case
    //     If key is not an operand, ie not +, -, * or /, then it must be a number and return its integer value
    //     return stoi(key);
    // }
    
    return -1;
}