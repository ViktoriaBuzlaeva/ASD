// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_graph_adjacency_m/graph_adjacency_m.h"

#define EPSILON 0.000001

TEST(TestGraphAdjacencyMLib, can_create_unweighted_unoriented) {
    std::vector<std::pair<int, int>> edges = { {0,1}, {1,2}, {0,3}, {3,4} };
    ASSERT_NO_THROW(GraphAdjacencyM<int> g(edges, false));
}

TEST(TestGraphAdjacencyMLib, can_create_unweighted_oriented) {
    std::vector<std::pair<int, int>> edges = { {0,1}, {1,2}, {0,3}, {3,4} };
    ASSERT_NO_THROW(GraphAdjacencyM<int> g(edges, true));
}

TEST(TestGraphAdjacencyMLib, can_create_weighted_unoriented) {
    std::vector<std::pair<std::pair<int, int>, int>> edges =
    { {{0,1}, 3}, {{1,2}, 5}, {{0,3}, 7}, {{ 3,4 }, 9} };
    ASSERT_NO_THROW(GraphAdjacencyM<int> g(edges, false));
}

TEST(TestGraphAdjacencyMLib, can_create_weighted_oriented) {
    std::vector<std::pair<std::pair<int, int>, int>> edges =
    { {{0,1}, 3}, {{1,2}, 5}, {{0,3}, 7}, {{ 3,4 }, 9} };
    ASSERT_NO_THROW(GraphAdjacencyM<int> g(edges, true));
}

TEST(TestGraphAdjacencyMLib, can_add_edge_unweighted) {
    std::vector<std::pair<int, int>> edges = { {0,1}, {1,2}, {3,4} };
    GraphAdjacencyM<int> g(edges, false);
    ASSERT_NO_THROW(g.add_edge(0, 2));
    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_TRUE(g.has_edge(2, 1));
    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_TRUE(g.has_vertex(2));

    ASSERT_NO_THROW(g.add_edge(3, 0));
    EXPECT_TRUE(g.has_edge(3, 0));
    EXPECT_TRUE(g.has_edge(0, 3));
    EXPECT_TRUE(g.has_vertex(0));
}

TEST(TestGraphAdjacencyMLib, can_add_edge_weighted) {
    std::vector<std::pair<std::pair<int, int>, int>> edges =
    { {{0,1}, 3}, {{1,2}, 5}, {{ 3,4 }, 9} };
    GraphAdjacencyM<int> g(edges, false);
    ASSERT_NO_THROW(g.add_edge(0, 3, 100));
    EXPECT_TRUE(g.has_edge(0, 3));
    EXPECT_TRUE(g.has_edge(3, 0));
    EXPECT_TRUE(g.has_vertex(0));
    EXPECT_TRUE(g.has_vertex(3));
}

TEST(TestGraphAdjacencyMLib, throw_when_try_add_edge_with_non_exist_vertices) {
    GraphAdjacencyM<int> g({ {0,1} }, false);
    ASSERT_ANY_THROW(g.add_edge(2, 3));
}

TEST(TestGraphAdjacencyMLib, can_delete_edge_unoriented) {
    GraphAdjacencyM<int> g({ {0,1}, {1,0}, { 1,2 }, {0,3}, {3,4} }, false);
    ASSERT_NO_THROW(g.delete_edge(0, 1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 0));
}

TEST(TestGraphAdjacencyMLib, can_delete_edge_oriented) {
    GraphAdjacencyM<int> g({ {0,1}, {1,0}, {1,2}, {0,3}, {3,4} }, true);
    ASSERT_NO_THROW(g.delete_edge(0, 1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_TRUE(g.has_edge(1, 0));
}

TEST(TestGraphAdjacencyMLib, throw_when_try_delete_edge_with_non_exist_vertices) {
    GraphAdjacencyM<int> g({ {0,1}, {1,0}, { 1,2 }, {0,3}, {3,4} }, false);
    ASSERT_ANY_THROW(g.delete_edge(5, 3));
}

TEST(TestGraphAdjacencyMLib, throw_when_try_delete_edge_with_non_exist_edges) {
    GraphAdjacencyM<int> g({ {0,1}, { 1,2 }, {0,3}, {3,4} }, true);
    ASSERT_ANY_THROW(g.delete_edge(1, 0));
}

TEST(TestGraphAdjacencyMLib, can_delete_vertex_edges_unoriented) {
    GraphAdjacencyM<int> g({ {0,1}, {1,2}, {0,3}, {3,4} }, false);

    ASSERT_NO_THROW(g.delete_vertex_edges(1));
    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 0));
    EXPECT_FALSE(g.has_edge(1, 2));
    EXPECT_FALSE(g.has_edge(2, 1));
}

TEST(TestGraphAdjacencyMLib, can_delete_vertex_edges_oriented) {
    GraphAdjacencyM<int> g({ {0,1}, {1,2}, {0,3}, {3,4} }, true);

    ASSERT_NO_THROW(g.delete_vertex_edges(1));
    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 2));
    EXPECT_FALSE(g.has_edge(1, 0));
}

TEST(TestGraphAdjacencyMLib, throw_when_try_delete_non_exist_vertex) {
    GraphAdjacencyM<int> g({ {0,1}, {1,2} }, false);
    ASSERT_ANY_THROW(g.delete_vertex_edges(3));
}
