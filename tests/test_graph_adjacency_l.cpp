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

TEST(TestGraphAdjacencyLLib, can_find_min_way_unweighted) {
    GraphAdjacencyL<int> g1({ {0,2}, {2,1}, {1,4}, {3,0}, {3,4} }, false);
    std::vector<int> actual_path = g1.find_min_way(0, 4);

    std::vector<int> expected_path = { 0, 3, 4 };
    EXPECT_EQ(actual_path, expected_path);

    GraphAdjacencyL<int> g2({ {0,2}, {2,1}, {1,4}, {3,0}, {3,4} }, true);
    actual_path = g2.find_min_way(0, 4);

    expected_path = { 0, 2, 1, 4 };
    EXPECT_EQ(actual_path, expected_path);
}

TEST(TestGraphAdjacencyLLib, can_find_min_way_weighted) {
    GraphAdjacencyL<int> g1({ {{0,2}, 2}, {{2,1}, 7}, {{1,4}, 5},
        {{0,3}, 4}, {{3,4}, 30}, {{1,3}, 3} }, false);
    std::vector<int> actual_path = g1.find_min_way(0, 4);

    std::vector<int> expected_path = { 0, 3, 1, 4 };
    EXPECT_EQ(actual_path, expected_path);

    GraphAdjacencyL<int> g2({ {{0,2}, 2}, {{2,1}, 7}, {{1,4}, 5},
        {{0,3}, 4}, {{3,4}, 30}, {{1,3}, 3} }, true);
    actual_path = g2.find_min_way(0, 4);

    expected_path = { 0, 2, 1, 4 };
    EXPECT_EQ(actual_path, expected_path);
}

TEST(TestGraphAdjacencyLLib, can_find_min_way_to_itself) {
    GraphAdjacencyL<int> g({ {0,2} });
    std::vector<int> actual_path = g.find_min_way(0, 0);

    std::vector<int> expected_path = { 0 };
    EXPECT_EQ(actual_path, expected_path);
}

TEST(TestGraphAdjacencyLLib, can_find_min_way) {
    GraphAdjacencyL<int> g(
        { {{0,1}, 2}, {{0,2}, 5}, {{0,4}, 10},
        {{1,2}, 1}, {{1,3}, 4},
        {{2,3}, 2}, {{2,4}, 3},
        {{3,4}, 1}, {{3,5}, 6},
        {{4,5}, 2} }, true);

    auto actual_path = g.find_min_way(0, 5);
    std::vector<int> expected_path_1 = { 0, 1, 2, 3, 4, 5 };
    std::vector<int> expected_path_2 = { 0, 1, 2, 4, 5 };
    // Оба пути весом 8
    EXPECT_TRUE(actual_path == expected_path_2);
}

TEST(TestGraphAdjacencyLLib, throw_when_try_find_min_way_with_non_exist_vertex) {
    GraphAdjacencyL<int> g({ {0,2}, {2,1}, {1,4}, {3,0}, {3,4} }, false);
    ASSERT_ANY_THROW(g.find_min_way(0, 5));
}

TEST(TestGraphAdjacencyLLib, throw_when_try_find_min_way_with_non_exist_path) {
    GraphAdjacencyL<int> g({ {{0,2}, 2}, {{2,1}, 7}, {{1,4}, 5},
        {{0,3}, 4}, {{3,4}, 30}, {{1,3}, 3} }, true);
    ASSERT_ANY_THROW(g.find_min_way(4, 0));
}


