// Copyright 2020 Your Name <your_email>

#include <SharedPtr.hpp>
#include <gtest/gtest.h>

TEST(Example, EmptyTest)
{
    EXPECT_TRUE(true);
}

TEST(test_constructor, point_nullptr)
{
    SharedPtr <int> ptr;
    int* tmp = ptr.get();
    EXPECT_EQ(tmp, nullptr);
}

TEST(test_constructor, point_int_nullptr)
{
    int *points = new int (24);
    SharedPtr <int> ptr(points);
    int* tmp = ptr.get();
    EXPECT_EQ(tmp, points);
}

TEST(test_method, test_get)
{
    int *points = nullptr;
    SharedPtr <int> ptr(points);
    int* tmp = ptr.get();
    EXPECT_EQ(tmp, nullptr);
}

TEST(test_method, test_get_int)
{
    int *points = new int (227);
    SharedPtr <int> ptr(points);
    SharedPtr <int> ptr2 = ptr;
    EXPECT_EQ(ptr.get(), points);
}

TEST(test_operator, bool_test)
{
    int *points = new int (227);
    SharedPtr <int> ptr(points);
    SharedPtr <int> ptr2 = ptr;
    bool is_pointer = ptr2;
    EXPECT_EQ(is_pointer, true);
}

class Test_class
{
public:
    int x;
};

TEST(test_operator, arrow_test)
{
    auto test_class_ptr = new Test_class;
    test_class_ptr ->x = 227;
    SharedPtr <Test_class> ptr(test_class_ptr);
    EXPECT_EQ(ptr->x, test_class_ptr->x);
}

TEST(test_operator, equality_lvalue_test)
{
    int *points = new int (227);
    SharedPtr <int> ptr(points);
    SharedPtr <int> ptr2;
    SharedPtr <int> ptr3 = ptr2 = ptr;
    EXPECT_EQ(ptr3.get(), ptr.get());
}

TEST(test_constructor, rvalue_test)
{
    int *points = new int (227);
    SharedPtr <int> ptr(points);
    SharedPtr <int> ptr2 = ptr;
    SharedPtr <int> ptr3(std::move(ptr));
    EXPECT_EQ(ptr3.use_count(), 2);
}

TEST(test_method, reset_test)
{
    int  *points = new int (227);
    SharedPtr <int> ptr(points);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(test_method, reset_test_point)
{
    int *points = new int (227);
    int *points1 = new int (200);
    SharedPtr <int> ptr(points);
    ptr.reset(points1);
    EXPECT_EQ(ptr.get(), points1);
}

TEST(test_method, swap_test)
{
    int *points = new int (227);
    int *points1 = new int (200);
    SharedPtr <int> ptr(points);
    SharedPtr <int> ptr1(points1);
    ptr.swap(ptr1);
    EXPECT_EQ(ptr.get(), points1);
    EXPECT_EQ(ptr1.get(), points);
}

TEST(test_is_move, assign_construct_test)
{
    EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value,
              true);
    EXPECT_EQ(std::is_move_assignable<SharedPtr<Test_class>>::value,
              true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<Test_class>>::value,
              true);
}