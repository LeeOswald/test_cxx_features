#include <generator>
#include <memory_resource>
#include <iostream>
#include <array>
#include <ranges>


std::pmr::generator<long> fibonacci(std::allocator_arg_t, 
                                    std::pmr::polymorphic_allocator<>,
                                    long base) //: pre (base == 0 || base == 1)
{
    long a = base;
    long b = 1;
    while (true) {
        co_yield a;
        a = std::exchange(b, a + b);
    }
}

int main()
{
    alignas(std::max_align_t) std::array<std::byte, 256> buf; 
    std::pmr::monotonic_buffer_resource arena(buf.data(), buf.size(),
                                    std::pmr::null_memory_resource());
    std::pmr::polymorphic_allocator<> alloc{&arena};

    long sum = 0;
    for (long x : fibonacci(std::allocator_arg, alloc, 0) 
                | std::views::take(20)) {
        sum += x;
    }

    std::cout << "Sum of first 20 (base 0): " << sum << '\n';
}
