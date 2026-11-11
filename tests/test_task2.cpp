#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.h"
#include <string>
#include <algorithm>

// ---------------------------------------------------------
// TASK 2: ADJACENCY LIST TESTS (25 MARKS)
// ---------------------------------------------------------

TEST_CASE("t2_add_edge" * doctest::test_suite("task2")) {
    Adjacency_List l;
    l.add_edge("A", "B");
    
    // Inspect map directly
    bool found = std::find(l.list["A"].begin(), l.list["A"].end(), "B") != l.list["A"].end();
    CHECK(found == true);
    
    // Check it remains strictly directed
    bool reverse_found = std::find(l.list["B"].begin(), l.list["B"].end(), "A") != l.list["B"].end();
    CHECK(reverse_found == false);
}

TEST_CASE("t2_remove_edge" * doctest::test_suite("task2")) {
    Adjacency_List l;
    // Inject directly
    l.list["A"].push_back("B");
    
    l.remove_edge("A", "B");
    
    // Inspect map directly
    bool found = std::find(l.list["A"].begin(), l.list["A"].end(), "B") != l.list["A"].end();
    CHECK(found == false);
}

TEST_CASE("t2_has_edge" * doctest::test_suite("task2")) {
    Adjacency_List l;
    // Inject directly
    l.list["X"].push_back("Y");
    
    CHECK(l.has_edge("X", "Y") == true);
    CHECK(l.has_edge("Y", "X") == false); // Directed
}

TEST_CASE("t2_solve_equation" * doctest::test_suite("task2")) {
    Adjacency_List l;
    
    // Inject AST directly into map
    l.list["+"].push_back("*");
    l.list["+"].push_back("3");
    l.list["*"].push_back("2");
    l.list["*"].push_back("7");
    
    // CRITICAL FIX: Initialize leaf nodes as empty vectors so list.count(key) passes
    l.list["2"] = {};
    l.list["7"] = {};
    l.list["3"] = {};
    
    // (2 * 7) + 3 = 17
    CHECK(l.solve_equation("+") == 17);
    
    // Base Case Test
    Adjacency_List l2;
    l2.list["10"] = {}; // Initialize leaf node
    CHECK(l2.solve_equation("10") == 10);
}