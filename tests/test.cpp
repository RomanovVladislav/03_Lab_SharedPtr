//
// Created by vladislav on 01.02.2021.
//

#include <SharedPtr.hpp>
#include <gtest/gtest.h>

TEST(Example, EmptyTest)
{
    EXPECT_TRUE(true);
}

TEST(TestConstructor, PtrNullptr)
{
    SharedPtr <int> Ptr;

    int* Tmp = Ptr.get();

    EXPECT_EQ(Tmp, nullptr);
}

TEST(TestConstructor, PtrInt)
{
    int *_Ptr = new int (100);

    SharedPtr <int> Ptr(_Ptr);
    int* Tmp = Ptr.get();

    EXPECT_EQ(Tmp, _Ptr);
}

class TestClass
{
public:
    int Tmp;
};

TEST(TestOperator, arrow_test)
{
    auto _TestClass = new TestClass;
    _TestClass ->Tmp = 100;

    SharedPtr <TestClass> Ptr(_TestClass);

    EXPECT_EQ(Ptr->Tmp, _TestClass->Tmp);
}

TEST(TestConstructor, Lvalue)
{
    int *_Ptr = new int (227);

    SharedPtr <int> Ptr1(_Ptr);
    SharedPtr <int> Ptr2(Ptr1);
    SharedPtr <int> Ptr3 = Ptr2;

    EXPECT_EQ(Ptr3.get(), Ptr1.get());
}

TEST(TestConstructor, Rvalue)
{
    int *_Ptr = new int;

    SharedPtr <int> Ptr1(_Ptr);
    SharedPtr <int> Ptr2 = Ptr1;
    SharedPtr <int> Ptr3(std::move(Ptr1));

    EXPECT_EQ(Ptr3.use_count(), 2);
}

TEST(TestMethod, GetNullptr)
{
    int *_Ptr = nullptr;

    SharedPtr <int> Ptr(_Ptr);
    int* Tmp = Ptr.get();

    EXPECT_EQ(Tmp, nullptr);
}

TEST(TestMethod, GetInt)
{
    int *_Ptr = new int (100);

    SharedPtr <int> Ptr1(_Ptr);
    SharedPtr <int> Ptr2 = Ptr1;

    EXPECT_EQ(Ptr2.get(), _Ptr);
}

TEST(TestMethod, Reset1)
{
    int  *_Ptr = new int (100);

    SharedPtr <int> Ptr(_Ptr);
    Ptr.reset();

    EXPECT_EQ(Ptr.get(), nullptr);
}

TEST(TestMethod, Reset2)
{
    int *_Ptr1 = new int (100);
    int *_Ptr2 = new int (200);

    SharedPtr <int> Ptr(_Ptr1);
    Ptr.reset(_Ptr2);

    EXPECT_EQ(Ptr.get(), _Ptr2);
}

TEST(TestMethod, Swap)
{
    int *_Ptr1 = new int (100);
    int *_Ptr2 = new int (200);

    SharedPtr <int> Ptr1(_Ptr1);
    SharedPtr <int> Ptr2(_Ptr2);
    Ptr1.swap(Ptr2);

    EXPECT_EQ(Ptr1.get(), _Ptr2);
    EXPECT_EQ(Ptr2.get(), _Ptr1);
}

TEST(TestOperator, Bool)
{
    int *_Ptr = new int (100);

    SharedPtr <int> Ptr1(_Ptr);
    SharedPtr <int> Ptr2 = Ptr1;
    bool Tmp = Ptr2;

    EXPECT_EQ(Tmp, true);
}

TEST(TestIs_move, is_move_assignable)
{
    EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);

    EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);

    EXPECT_EQ(std::is_move_assignable<SharedPtr<TestClass>>::value, true);
}

TEST(TestIs_move, is_move_constructible)
{
    EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);

    EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value, true);

    EXPECT_EQ(std::is_move_constructible<SharedPtr<TestClass>>::value, true);
}