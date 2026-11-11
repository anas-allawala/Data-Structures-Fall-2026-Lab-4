#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.h"

// ---------------------------------------------------------
// TASK 1: ADJACENCY MATRIX TESTS (25 MARKS)
// ---------------------------------------------------------

TEST_CASE("t1_add_edge" * doctest::test_suite("task1")) {
    Adjacency_Matrix m(5);
    m.add_edge(0, 1);
    
    // Check internal array state using the jagged index formula: [start][end - start - 1]
    CHECK(m.matrix[0][1 - 0 - 1] == 1); // matrix[0][0]
    
    // Bounds checking
    m.add_edge(-1, 5); // Should not crash
}

TEST_CASE("t1_remove_edge" * doctest::test_suite("task1")) {
    Adjacency_Matrix m(5);
    // Inject directly into the structure using the jagged index formula
    m.matrix[0][1 - 0 - 1] = 1;
    
    m.remove_edge(0, 1);
    
    // Check internal array state directly
    CHECK(m.matrix[0][0] == 0);
}

TEST_CASE("t1_has_edge" * doctest::test_suite("task1")) {
    Adjacency_Matrix m(5);
    // Inject directly to test only the has_edge function
    m.matrix[2][4 - 2 - 1] = 1; // matrix[2][1]
    
    CHECK(m.has_edge(2, 4) == true);
    // has_edge should internally swap 4 and 2 and still find it
    CHECK(m.has_edge(4, 2) == true); 
    CHECK(m.has_edge(0, 0) == false);
}

TEST_CASE("t1_degree" * doctest::test_suite("task1")) {
    Adjacency_Matrix m(5);
    // Inject edges manually using the jagged index formula
    m.matrix[0][1 - 0 - 1] = 1; // Edge 0-1
    m.matrix[1][2 - 1 - 1] = 1; // Edge 1-2
    m.matrix[1][3 - 1 - 1] = 1; // Edge 1-3
    
    CHECK(m.degree(1) == 3);
    CHECK(m.degree(0) == 1);
    CHECK(m.degree(4) == 0);
}