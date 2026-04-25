// Copyright 2026 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_graph_adjacency_l/graph_adjacency_l.h"

#define EPSILON 0.000001

TEST(TestGraphAdjacencyLLib, can_create_unweighted_unoriented) {
    std::vector<std::pair<int, int>> edges = { {0,1}, {1,2}, {0,3}, {3,4} };
    ASSERT_NO_THROW(GraphAdjacencyL<int> g(edges, false));
}

TEST(TestGraphAdjacencyLLib, can_create_unweighted_oriented) {
    std::vector<std::pair<int, int>> edges = { {0,1}, {1,2}, {0,3}, {3,4} };
    ASSERT_NO_THROW(GraphAdjacencyL<int> g(edges, true));
}

TEST(TestGraphAdjacencyLLib, can_create_weighted_unoriented) {
    std::vector<std::pair<std::pair<int, int>, int>> edges =
        { {{0,1}, 3}, {{1,2}, 5}, {{0,3}, 7}, {{ 3,4 }, 9} };
    ASSERT_NO_THROW(GraphAdjacencyL<int> g(edges, false));
}

TEST(TestGraphAdjacencyLLib, can_create_weighted_oriented) {
    std::vector<std::pair<std::pair<int, int>, int>> edges =
        { {{0,1}, 3}, {{1,2}, 5}, {{0,3}, 7}, {{ 3,4 }, 9} };
    ASSERT_NO_THROW(GraphAdjacencyL<int> g(edges, true));
}

TEST(TestGraphAdjacencyLLib, can_add_edge_unweighted) {
    std::vector<std::pair<int, int>> empty;
    GraphAdjacencyL<int> g(empty, false);
    ASSERT_NO_THROW(g.add_edge(1, 2));
    EXPECT_TRUE(g.has_edge(1, 2));
    EXPECT_TRUE(g.has_edge(2, 1));
    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_TRUE(g.has_vertex(2));

    ASSERT_NO_THROW(g.add_edge(1, 0));
    EXPECT_TRUE(g.has_edge(1, 0));
    EXPECT_TRUE(g.has_edge(0, 1));
    EXPECT_TRUE(g.has_vertex(0));
}

TEST(TestGraphAdjacencyLLib, can_add_edge_weighted) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    GraphAdjacencyL<int> g(edges, false);
    ASSERT_NO_THROW(g.add_edge(0, 1, 100));
    EXPECT_TRUE(g.has_edge(0, 1));
    EXPECT_TRUE(g.has_edge(1, 0));
    EXPECT_TRUE(g.has_vertex(0));
    EXPECT_TRUE(g.has_vertex(1));
}

TEST(TestGraphAdjacencyLLib, throw_when_try_add_edge_with_non_exist_vertices) {
    GraphAdjacencyL<int> g({ {0,1} }, false);
    ASSERT_ANY_THROW(g.add_edge(2, 3));
}

TEST(TestGraphAdjacencyLLib, can_delete_edge_unoriented) {
    GraphAdjacencyL<int> g({ {0,1}, {1,0}, { 1,2 }, {0,3}, {3,4} }, false);
    ASSERT_NO_THROW(g.delete_edge(0, 1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 0));
}

TEST(TestGraphAdjacencyLLib, can_delete_edge_oriented) {
    GraphAdjacencyL<int> g({ {0,1}, {1,0}, {1,2}, {0,3}, {3,4} }, true);
    ASSERT_NO_THROW(g.delete_edge(0, 1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_TRUE(g.has_edge(1, 0));
}

TEST(TestGraphAdjacencyLLib, throw_when_try_delete_edge_with_non_exist_vertices) {
    GraphAdjacencyL<int> g({ {0,1}, {1,0}, { 1,2 }, {0,3}, {3,4} }, false);
    ASSERT_ANY_THROW(g.delete_edge(5, 3));
}

TEST(TestGraphAdjacencyLLib, throw_when_try_delete_edge_with_non_exist_edges) {
    GraphAdjacencyL<int> g({ {0,1}, { 1,2 }, {0,3}, {3,4} }, true);
    ASSERT_ANY_THROW(g.delete_edge(1, 0));
}

TEST(TestGraphAdjacencyLLib, can_delete_vertex) {
    GraphAdjacencyL<int> g({ {0,1}, {1,2}, {2,0} }, false);
    ASSERT_NO_THROW(g.delete_vertex(1));
    EXPECT_FALSE(g.has_vertex(1));
    EXPECT_FALSE(g.has_edge(0, 1));
    EXPECT_FALSE(g.has_edge(1, 2));

    EXPECT_TRUE(g.has_edge(0, 2));
    EXPECT_TRUE(g.has_edge(2, 0));
}

TEST(TestGraphAdjacencyLLib, throw_when_try_delete_non_exist_vertices_and_edges) {
    GraphAdjacencyL<int> g({ {0,1}, {1,0}, { 1,2 }, {0,3}, {3,4} }, false);
    g.delete_vertex(1);
    ASSERT_ANY_THROW(g.delete_vertex(1));
    ASSERT_ANY_THROW(g.delete_vertex(5));
    ASSERT_ANY_THROW(g.delete_edge(0, 1));
    ASSERT_ANY_THROW(g.delete_edge(1, 2));
}

TEST(TestGraphAdjacencyLLib, can_delete_and_add_same_vertex) {
    GraphAdjacencyL<int> g({ {0,1}, {1,2}, {2,3} }, false);
    g.delete_vertex(1);
    ASSERT_NO_THROW(g.add_edge(1, 3));
    EXPECT_TRUE(g.has_vertex(1));
    EXPECT_TRUE(g.has_edge(1, 3));
    EXPECT_TRUE(g.has_edge(3, 1));
    EXPECT_FALSE(g.has_edge(0, 1));
}
