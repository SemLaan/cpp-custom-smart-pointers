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

	void Deallocate(void* blk)
	{
		free(blk);
	}
};