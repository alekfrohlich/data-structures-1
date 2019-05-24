// Author: Alek Frohlich, Date: 05/24/2019

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>

namespace mem {

/**
 * @brief Implements a unique pointer(smart pointer)
 *
 * @tparam T Data type of the elements
 */
template <typename T>
class unique_ptr {
public:
	explicit unique_ptr(T* ptr) noexcept : raw_ptr(ptr) {}

	// delete default constructor
	unique_ptr() = delete;

	// remove compiler generated copy semantics
	unique_ptr(const unique_ptr& other) = delete;
	unique_ptr& operator=(const unique_ptr& other) = delete;

	// move semantics
	unique_ptr(unique_ptr&& other) { swap(*this, other); }
	unique_ptr& operator=(unique_ptr&& other) {
		swap(*this, other);
		return other;
	}

	// destructor
	~unique_ptr() { delete raw_ptr; }

	// access operator overload interface
	T* operator->() const noexcept { return raw_ptr; }
	T& operator*() const { return *raw_ptr; }

	// avoids implicit conversion from unique_ptr to bools not in bool
	// expressions
	explicit operator bool() const noexcept { return raw_ptr; }

	// access method interface
	T* get() const noexcept { return raw_ptr; }

	// release pointer from unique_ptr
	T* release() noexcept {
		T* ptr = raw_ptr;
		raw_ptr = nullptr;
		return ptr;
	}

	// delete early
	void reset(T* ptr = nullptr) { delete release(); }

	// overload std::swap
	void swap(unique_ptr& uptr) { std::swap(raw_ptr, uptr.raw_ptr); }

private:
	T* raw_ptr;
};
}  // namespace mem

#endif
