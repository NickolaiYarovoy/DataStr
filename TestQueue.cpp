#include <iostream>
#include "Adam.h"
#include "DateTime.h"
#include "Matrix.h"
#include "VeryLong.h"
#include "Queue.h"

#include <gtest/gtest.h>

TEST(TestQueue, SimpleAddTest)
{
    Queue test(3);
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    test.Add(&a).Add(&b).Add(&c);

    EXPECT_EQ((ADT*)&a, test[0]);
    EXPECT_EQ((ADT*)&b, test[1]);
    EXPECT_EQ((ADT*)&c, test[2]);
}

TEST(TestQueue, IncreaseSizeTest)
{
    Queue test(1);
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    EXPECT_THROW(test.Add(&a).Add(&b).Add(&c), std::out_of_range);
}

TEST(TestQueue, AddToPositionTest)
{
    Queue test(4);
    VeryLong a = 15165131;
    DateTime b = DateTime(2530, 10, 15, 12, 23, 33);
    Adam c = 7850;
    VeryLong d = 15165131;
    test.Add(&a, 0).Add(&b, 0).Add(&c, 1).Add(&d, 2);

    EXPECT_EQ((ADT*)&a, test[3]);
    EXPECT_EQ((ADT*)&b, test[0]);
    EXPECT_EQ((ADT*)&c, test[1]);
    EXPECT_EQ((ADT*)&d, test[2]);
}

TEST(TestQueue, BadAddToPositionTest)
{
    Queue test(4);
    VeryLong a = 1565130;
    EXPECT_THROW(test.Add(&a, 2), std::out_of_range);
}

TEST(TestQueue, BadTakeFromPositionTest)
{
    Queue test(4);
    EXPECT_THROW(test[2], std::out_of_range);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
