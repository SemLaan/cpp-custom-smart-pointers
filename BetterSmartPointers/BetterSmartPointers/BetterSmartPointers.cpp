#include <iostream>
#include "example_class.h"
#include "scope.h"
#include "allocator.h"

#define MEMORY_LEAK_TEST_COUNT 100000


int main()
{
    Allocator allocator = Allocator();

    // === Scope ptr ===
    {
        Scope<int> uniq = CreateScope<int>(&allocator, 3);
        *uniq = 5;

        Scope<Example> example = CreateScope<Example>(&allocator, 3);
        example->PrintVars();

        for (int i = 0; i < MEMORY_LEAK_TEST_COUNT; ++i)
        {
            // Example has a pointer in it so if the destructor doesn't get called properly this will create a leak
            // If you are in debug mode ofcourse because this will get optimized out in release because this for loop does nothing
            Scope<Example> temp = CreateScope<Example>(&allocator);
        }
    }

    // === Unique ptr ===
    {
        std::unique_ptr<int> uniq = std::make_unique<int>(3);
        *uniq = 5;

        std::unique_ptr<Example> example = std::make_unique<Example>(3);
        example->PrintVars();

        for (int i = 0; i < MEMORY_LEAK_TEST_COUNT; ++i)
        {
            // Example has a pointer in it so if the destructor doesn't get called properly this will create a leak
            // If you are in debug mode ofcourse because this will get optimized out in release because this for loop does nothing
            std::unique_ptr<Example> temp = std::make_unique<Example>();
        }
    }

    std::cin.get();
}