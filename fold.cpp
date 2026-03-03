#include <cstddef>
#include <iomanip>
#include <iostream>


void for_each(auto&& fn, auto&&... args)
{
   (fn(std::forward<decltype(args)>(args)), ...);
}

static void test_for_each()
{
   std::clog << "---- [for_each] ----\n";
   for_each(
      [i = int{0}](auto&& val) mutable
      {
         if (i++ > 0)
            std::clog << ", ";
         std::clog << std::forward<decltype(val)>(val);
      },
      1,
      -2,
      4.56,
      "hey you"
   );

   std::clog << std::endl;
}


void reversed_for_each(auto&& fn, auto&&... args)
{
   [[maybe_unused]] int _;
   (_ = ... = (fn(std::forward<decltype(args)>(args)), 0));
}

static void test_reversed_for_each()
{
   std::clog << "---- [reversed_for_each] ----\n";
   reversed_for_each(
      [i = int{0}](auto&& val) mutable
      {
         if (i++ > 0)
            std::clog << ", ";
         std::clog << std::forward<decltype(val)>(val);
      },
      1,
      -2,
      4.56,
      "hey you"
   );

   std::clog << std::endl;
}


void for_each_until(
   auto&& pred,
   auto&& fn,
   auto&&... args
)
{
   [[maybe_unused]] auto _ =
   ((pred(std::forward<decltype(args)>(args)) ? false :
      (fn(std::forward<decltype(args)>(args)), true))
         &&...);
}


static void test_for_each_until()
{
   std::clog << "---- [for_each_until] ----\n";
   for_each_until(
      [](auto&& val)
      {
         return val < 0;
      },
      [i = int{0}](auto&& val) mutable
      {
         if (i++ > 0)
            std::clog << ", ";
         std::clog << "("
                   << std::forward<decltype(val)>(val)
                   << " >= 0)";
      },
      1,
      2,
      3,
      -2,
      4,
      5
   );

   std::clog << std::endl;
}


bool any_of(
   auto&& pred,
   auto&&... args
)
{
   return
      (pred(std::forward<decltype(args)>(args)) || ...);
}

static void test_any_of()
{
   std::clog << "---- [any_of] ----\n";
   auto b = any_of(
      [](auto&& val)
      {
         return val < 0;
      },
      1,
      2,
      -1,
      3
   );
   std::clog << std::boolalpha << b << std::endl;

   b = any_of(
      [](auto&& val)
      {
         return val == 0;
      },
      1,
      2,
      -1,
      3
   );
   std::clog << std::boolalpha << b << std::endl;
}



auto count_if(
   auto&& pred,
   auto&&... args
)
{
   auto n = (
      std::size_t(0) + ... +
      (pred(std::forward<decltype(args)>(args)) ? 1 : 0)
   );

   return n;
}

static void test_count_if()
{
   std::clog << "---- [count_if] ----\n";
   auto n = count_if(
      [](auto&& val)
      {
         return val < 0;
      },
      1,
      2,
      -1,
      3
   );
   std::clog << n << std::endl;
}


auto find_first_that(
   auto&& pred,
   auto&&... args
)
{
   std::common_type_t<decltype(args)...> result = {};

   [[maybe_unused]] bool found =
      ((pred(std::forward<decltype(args)>(args)) ?
         (result = args, true) : false) || ...);

   return result;
}


auto get_nth(
   std::size_t index,
   auto&&... arg
)
{
   std::common_type_t<decltype(arg)...> result = {};
   std::size_t i = 0;

   [[maybe_unused]] auto _ =
      ((i++ == index ?
         (result = arg, true) : false) || ...);

   return result;
}

static void test_get_nth()
{
   std::clog << "---- [get_nth] ----\n";
   auto x = get_nth(
      2,
      1,
      2,
      -1,
      3
   );
   std::clog << "args[2] = " << x << std::endl;
}


auto get_first(
   auto&&... arg
)
{
   std::common_type_t<decltype(arg)...> result = {};

   [[maybe_unused]] auto _ =
      ((result = arg, true) || ...);

   return result;
}

auto get_last(
   auto&&... arg
)
{
   return (arg, ...);
}

auto get_min(
   auto&&... arg
)
{
   auto min = (arg, ...);
   [[maybe_unused]] auto _ =
      (((arg < min) ? (min = arg, 0) : 0), ...);
   return min;
}

static void test_get_min()
{
   std::clog << "---- [get_min] ----\n";
   auto x = get_min(
      2,
      1,
      5,
      -7,
      3
   );
   std::clog << "min = " << x << std::endl;
}

int main()
{
   test_for_each();
   test_reversed_for_each();
   test_for_each_until();
   test_any_of();
   test_count_if();
   test_get_nth();
   test_get_min();
   return 0;
}
