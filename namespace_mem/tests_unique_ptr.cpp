// Author: Alek Frohlich, Date: 05/24/2019

#include "unique_ptr.h"
#include <gtest/gtest.h>
#include <type_traits>

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class foo {
public:
	int baz() { return 5; }
};

class UniquePointerTest : public testing::Test {
protected:
	int* ptr = new int(5);
	int* ptr2 = new int(7);
	int* ptr3 = nullptr;
	foo* barptr = new foo();
	mem::unique_ptr<int> uptr{ptr};
	mem::unique_ptr<int> uptr2{ptr2};
	mem::unique_ptr<int> uptr3{ptr3};
	mem::unique_ptr<foo> uptr4{barptr};
};

TEST_F(UniquePointerTest, NotCopyConstructible) {
	ASSERT_FALSE(std::is_copy_constructible<mem::unique_ptr<int>>::value);
}

TEST_F(UniquePointerTest, NotCopyAssignable) {
	ASSERT_FALSE(std::is_copy_assignable<mem::unique_ptr<int>>::value);
}

TEST_F(UniquePointerTest, MoveConstructible) {
	ASSERT_TRUE(std::is_move_constructible<mem::unique_ptr<int>>::value);
}

TEST_F(UniquePointerTest, MoveAssignable) {
	ASSERT_TRUE(std::is_move_assignable<mem::unique_ptr<int>>::value);
}

TEST_F(UniquePointerTest, ArrowAccessable) {
	ASSERT_EQ(barptr->baz(), uptr4->baz());
}

TEST_F(UniquePointerTest, ExplicitBoolean) {
	ASSERT_TRUE(uptr);
	ASSERT_FALSE(uptr3);
}

TEST_F(UniquePointerTest, Dereferenceable) {
	ASSERT_EQ(*ptr, *uptr);
}

TEST_F(UniquePointerTest, GetterAccessable) {
	ASSERT_EQ(ptr, uptr.get());
}

TEST_F(UniquePointerTest, Releasable) {
	ASSERT_EQ(ptr, uptr.release());
	ASSERT_EQ(nullptr, uptr.get());
}

TEST_F(UniquePointerTest, Swappable) {
	uptr.swap(uptr2);
	ASSERT_EQ(ptr, uptr2.get());
	ASSERT_EQ(ptr2, uptr.get());
}
