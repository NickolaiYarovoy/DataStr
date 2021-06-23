#include <iostream>
#include "Adam.h"
#include "DateTime.h"
#include "Matrix.h"
#include "VeryLong.h"
#include "List.h"

#include <gtest/gtest.h>

TEST(TestList, SimpleAddTest)
{
    List test = List();
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    test.Add(&a).Add(&b).Add(&c);

    EXPECT_EQ((ADT*)&a, test[0]);
    EXPECT_EQ((ADT*)&b, test[1]);
    EXPECT_EQ((ADT*)&c, test[2]);
}

TEST(TestList, IncreaseSizeTest)
{
    List test = List();
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    test.Add(&a).Add(&b).Add(&c);

    EXPECT_EQ((ADT*)&a, test[0]);
    EXPECT_EQ((ADT*)&b, test[1]);
    EXPECT_EQ((ADT*)&c, test[2]);
}

TEST(TestList, AddToPositionTest)
{
    List test = List();
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    VeryLong d = 15165131;
    test.Add(&a, 0).Add(&b, 0).Add(&c, 2).Add(&d, 0);

    EXPECT_EQ((ADT*)&a, test[2]);
    EXPECT_EQ((ADT*)&b, test[1]);
    EXPECT_EQ((ADT*)&c, test[3]);
    EXPECT_EQ((ADT*)&d, test[0]);
}

TEST(TestList, BadAddToPositionTest)
{
    List test = List();
    VeryLong a = 1565130;
    EXPECT_THROW(test.Add(&a, 2), std::out_of_range);
}

TEST(TestList, BadTakeFromPositionTest)
{
    List test = List();
    EXPECT_THROW(test[2], std::out_of_range);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
