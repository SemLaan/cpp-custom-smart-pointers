#pragma once
#include "allocator.h"

template <typename T>
class Scope
{
private:
	T* m_ptr;
	Allocator* m_allocator;
public:
	// Default constructor
	Scope()
		: m_ptr(nullptr)
	{}

	// Constructor from pointer, this takes ownership over the pointer
	explicit Scope(Allocator* allocator, T* ptr)
		: m_ptr(ptr), m_allocator(allocator)
	{}

	~Scope()
	{
		// Separate object destruction from deallocation
		m_ptr->~T();
		m_allocator->Deallocate(m_ptr, sizeof(T));
	}

	// Dereference operator
	T& operator*() const
	{
		return *m_ptr;
	}

	// Arrow operator
	T* operator->() const
	{
		// This returns the pointer because I think you're not actually overloading the true arrow operator, so when you
		// call the arrow operator on the scope "scopeObj->SomeFunc()" the arrow operator first returns the pointer -- which is what this code does --
		// and then it applies the "global" arrow operator that dereferences the pointer
		// If you simply return the dereferenced pointer it gives a vague warning about possible recursion
		return m_ptr;
	}
};

// Function for creating a scope of object type T with parameters args of types Types
// This is so unreadable because we want to avoid copying the args, so we have to first take the args as rvalues,
// and then because we're passing them to another function we have to let the compiler(?) know that the constructor of T can take
// ownership of the arguments as if they are still rvalues by using std::forward
// We also don't know the type of scope nor the constructor arguments that takes so we have to use templates
// And finally the ... are for variadic arguments
template <typename T, typename... Types>
Scope<T> CreateScope(Allocator* allocator, Types&&... args)
{
	// Separate allocation from object initialization
	T* temp = (T*)allocator->Allocate(sizeof(T));
	return Scope<T>(allocator, new(temp) T(std::forward<Types>(args)...));
}