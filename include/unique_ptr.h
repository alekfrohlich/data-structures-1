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
	// should be explicit to avoid Y-> X implicit conversion to rvalue
	explicit unique_ptr(T* ptr) noexcept : raw_ptr(ptr) {}

	// remove compiler generated copy semantics
	unique_ptr(const unique_ptr& other) = delete;
	unique_ptr& operator=(const unique_ptr& other) = delete;

	// move constructor
	unique_ptr(unique_ptr&& other) {
		swap(*this, other);
		other.raw_ptr = nullptr;
	}

	// move assignment: only bind to rvalues
	unique_ptr& operator=(unique_ptr&& other) {
		swap(*this, other);
		return other;
	}

	// destructor
	~unique_ptr() { delete raw_ptr; }

	// access operator overload interface
	T* operator->() const noexcept { return raw_ptr; }
	T& operator*() const { return *raw_ptr; }

	// only bind to explicit use of unique_ptr as a boolean
	explicit operator bool() const noexcept { return raw_ptr; }

	// access method interface
	T* get() const noexcept { return raw_ptr; }

	// release pointer from unique_ptr
	T* release() noexcept {
		T* ptr = raw_ptr;
		raw_ptr = nullptr;
		return ptr;
	}

	// overload std::swap for the move-and-swap idiom
	void swap(unique_ptr& uptr) noexcept {
        std::swap(raw_ptr, uptr.raw_ptr);
    }

private:
	T* raw_ptr;
};
/*
template<typename T>
inline unique_ptr<typename std::decay<T>::type>
make_unique(T&& ptr) {
    return unique_ptr<typename std::decay<T>::type>{ new std::decay<T>(std::forward
}
*/

}  // namespace mem

#endif

