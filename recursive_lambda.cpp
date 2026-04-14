#include <iostream>

auto factorial = [](this auto&& self, int n) -> int {
    return (n <= 1) ? 1 : n * self(n - 1);
};

int main()
{
   auto n = factorial(3);

   std::cout << n << std::endl;

   return 0;
}
