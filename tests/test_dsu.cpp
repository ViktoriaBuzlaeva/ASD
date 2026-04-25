// Copyright 2025 Viktoria Buzlaeva

#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

#define EPSILON 0.000001

TEST(TestDSULib, can_create) {
    EXPECT_NO_THROW(DSU dsu(5));
}

TEST(TestDSULib, can_find_elems_correctly) {
    DSU dsu(5);
    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_EQ(dsu.find(2), 2);
    EXPECT_EQ(dsu.find(3), 3);
    EXPECT_EQ(dsu.find(4), 4);
}

TEST(TestDSULib, throw_when_try_find_with_invalid_input) {
    DSU dsu(3);
    EXPECT_ANY_THROW(dsu.find(-1));
    EXPECT_ANY_THROW(dsu.find(5));
}

TEST(TestDSULib, can_unite_elems_correctly) {
    DSU dsu(10);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 4);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(2));
    EXPECT_EQ(dsu.find(3), dsu.find(4));
    EXPECT_EQ(dsu.find(3), dsu.find(5));
}

TEST(TestDSULib, can_unite_dif_elems_correctly) {
    DSU dsu(3);
    dsu.unite(0, 1);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_NE(dsu.find(0), dsu.find(2));
}

TEST(TestDSULib, can_unite_same_elems_correctly) {
    DSU dsu(3);
    dsu.unite(1, 1);
    EXPECT_EQ(dsu.find(1), 1);
    dsu.unite(0, 2);
    dsu.unite(2, 0);
    EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(TestDSULib, throw_when_try_unite_with_invalid_input) {
    DSU dsu(3);
    EXPECT_ANY_THROW(dsu.unite(-1, 2));
    EXPECT_ANY_THROW(dsu.unite(1, 5));
}

TEST(TestDSULib, can_find_after_unions_correctly) {
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(0, 4);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(0), dsu.find(4));
    EXPECT_EQ(dsu.find(2), dsu.find(3));
    EXPECT_NE(dsu.find(0), dsu.find(2));
}

TEST(TestDSULib, can_compress_path_correctly) {
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(3, 1);
    EXPECT_EQ(dsu.find(2), dsu.find(1));
    EXPECT_EQ(dsu.find(4), dsu.find(1));
}
