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
    // NEED TO PERFORM POST ORDER DFS TO SOLVE THIS.

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
    
    return -1;
}