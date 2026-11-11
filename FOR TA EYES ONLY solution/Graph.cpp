#include "../include/Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Adjacency_Matrix::Adjacency_Matrix(int n) : numVertices(n)
{
    // MEANT TO BE AN UPPER RIGHT TRIANGULAR MATRIX.
    matrix = new int *[numVertices - 1];
    for (int i = 0; i < numVertices - 1; i++)
    {
        matrix[i] = new int[numVertices - i - 1];

        for (int j = 0; j < numVertices - i - 1; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

Adjacency_Matrix::~Adjacency_Matrix()
{
    // free each row
    for (int i = 0; i < numVertices - 1; i++)
    {
        delete[] matrix[i];
    }

    // free whole matrix
    delete[] matrix;
    matrix = nullptr;
    numVertices = 0;
}

void Adjacency_Matrix::add_edge(int start, int end)
{
    // MUST INCLUDE BOUNDARY CHECKING
    if (start < 0 || start >= numVertices)
        return;
    if (end < 0 || end >= numVertices)
        return;
    if (start == end)
        return;

    if (start > end)
    {
        swap(start, end);
    }

    matrix[start][end - start - 1] = 1;
}

void Adjacency_Matrix::remove_edge(int start, int end)
{
    // MUST INCLUDE BOUNDARY CHECKING
    if (start < 0 || start >= numVertices)
        return;
    if (end < 0 || end >= numVertices)
        return;
    if (start == end)
        return;

    if (start > end)
    {
        swap(start, end);
    }

    matrix[start][end - start - 1] = 0;
}

bool Adjacency_Matrix::has_edge(int start, int end)
{
    // MUST INCLUDE BOUNDARY CHECKING
    if (start < 0 || start >= numVertices)
        return false;
    if (end < 0 || end >= numVertices)
        return false;

    if (start == end)
    {
        return false;
    }

    if (start > end)
    {
        swap(start, end);
    }

    return matrix[start][end - start - 1] == 1;
}

int Adjacency_Matrix::degree(int node)
{
    int count = 0;
    // Horizontal count first
    for (int j = node + 1; j < numVertices; j++)
    {
        count += matrix[node][j - node - 1];
    }

    // vertical count next
    for (int i = 0; i < node; i++)
    {
        count += matrix[i][node - i - 1];
    }

    return count;
}

// ---------------------- TASK 2 ----------------------------------

void Adjacency_List::add_edge(string a, string b)
{
    list[a].push_back(b);
}

void Adjacency_List::remove_edge(string a, string b)
{
    if (list.count(a))
    {
        auto it = find(list[a].begin(), list[a].end(), b);
        if (it != list[a].end())
        {
            list[a].erase(it);
        }
    }
}

bool Adjacency_List::has_edge(string a, string b)
{
    if (list.count(a))
    {
        auto it = find(list[a].begin(), list[a].end(), b);
        return it != list[a].end();
    }
    return false;
}

int Adjacency_List::solve_equation(string key)
{
    // NEED TO PERFORM POST ORDER DFS TO SOLVE THIS.

    // check if key exists. this should never run tho. key should always be valid
    if (!list.count(key))
        return 0;

    auto &vec = list[key];

    // if node is a leaf node, it must be an integer and it must
    // now have its string value like "3" be returned as 3
    if (vec.empty())
    {
        return stoi(key);
    }

    else
    {
        int val1 = solve_equation(vec[0]);
        int val2 = solve_equation(vec[1]);

        if (key == "+")
        {
            return val1 + val2;
        }
        else if (key == "-")
        {
            return val1 - val2;
        }
        else if (key == "*")
        {
            return val1 * val2;
        }
        else if (key == "/")
        {
            return val1 / val2;
        }
    }
}