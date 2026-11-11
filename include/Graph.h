#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Adjacency_Matrix
{
public:
    int numVertices;
    int **matrix;

    Adjacency_Matrix(int n);
    ~Adjacency_Matrix();

    void add_edge(int start, int end);
    void remove_edge(int start, int end);
    bool has_edge(int start, int end);
    int degree(int node);
};

class Adjacency_List
{
public:
    unordered_map<string, vector<string>> list;
    int numVertices = 0;

    void add_edge(string a, string b);
    void remove_edge(string a, string b);
    bool has_edge(string a, string b);
    int solve_equation(string key);
};

#endif