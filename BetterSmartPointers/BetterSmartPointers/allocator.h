#pragma once


class Allocator
{
public:
	Allocator()
	{

	}

	~Allocator()
	{

	}

	void* Allocate(size_t size)
	{
		return malloc(size);
	}

	void Deallocate(void* blk, size_t size)
	{
		// Now you can use size here to make a better deallocate function
		free(blk);
	}
};