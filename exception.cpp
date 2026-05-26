#include <format>
#include <iostream>


constexpr inline auto ptr(auto* p) noexcept
{
   return static_cast<void const*>(p);
}


struct A
{
   int m_id;

   ~A()
   {
      std::cout << ptr(this) << ".A::~A()" << std::endl;
   }

   A(int id = 0)
      : m_id(id)
   {
      std::cout << ptr(this) << ".A::A(" << id << ")" << std::endl;
   }

   A(A const& o)
      : m_id(o.m_id)
   {
      std::cout << ptr(this) << ".A::A(A const&)" << std::endl;
   }

   A& operator=(A const& o)
   {
      m_id = o.m_id;
      std::cout << ptr(this) << ".A::operator=(A const&)" << std::endl;
      return *this;
   }

   A(A&& o)
      : m_id(o.m_id)
   {
      o.m_id = -1;
      std::cout << ptr(this) << ".A::A(A&&)" << std::endl;
   }

   A& operator=(A&& o)
   {
      m_id = o.m_id;
      o.m_id = -1;
      std::cout << ptr(this) << ".A::operator=(A&&)" << std::endl;
      return *this;
   }
};


static void throw_static()
{
   std::cout << "--- [throw_static] ---\n";

   static A sa(7);

   try
   {
      throw &sa;
   }
   catch (A& e)
   {
      std::cout << "caught A at " << ptr(&e) << "\n";
   }
   catch (A* e)
   {
      std::cout << "caught A* at " << ptr(e) << "\n";
   }

   std::cout << "----------------------\n";
}

int main()
{
   static int static_a = 7;
   std::cout << "static data at " << ptr(&static_a) << std::endl;

   int stack_a = 9;
   std::cout << "stack top at " << ptr(&stack_a) << std::endl;

   throw_static();

   return 0;
}
