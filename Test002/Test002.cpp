#include <iostream>
#include <memory>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>


/*
 * test_001
 */
//auto
//Range-based for loops
//nullptr
//Strongly-typed enums
//Lambdas
//non-member begin() and end()
//static_assert
//std::to_string
enum class Options {One=1, Two = 2};
enum class Options100 {One=100, Two = 200};
template <typename Tv>
void test_001(Tv myValue)
{
    //auto
    //Range-based for loops
    //nullptr
    //Strongly-typed enums
    int a[] = {1,2,3};
    a[1] = (int)Options::Two;
    a[2] = (int)Options100::Two;
    if(a !=nullptr)
    {
       for(auto i:a)
       {
         std::cout<<i<<std::endl;  
       }       
    }
    
    //Lambdas and non-member begin() and end()
    int arr[] = {4,5,6,7};
    auto sum = 0;
    std::for_each(std::begin(arr), std::end(arr), [&sum](int n) { sum += n;});
    std::cout << "sum: " << sum << std::endl;
    
    auto mul3 = [](int n) {return n%3==0;};
    auto pos = std::find_if(std::begin(arr), std::end(arr), mul3);
    if(pos != std::end(arr))
      std::cout << *pos << std::endl;
    
    //static_assert
    static_assert(std::is_integral<Tv>::value, "Type must be integral");
    //std::to_string
    std::cout << "myValue: " + std::to_string(myValue*1000) << std::endl;
}

/*
 * test_002
 */
//override and final
//unique_ptr
//ALSO: virtual destructor 
class Aooo
{
public:
    virtual ~Aooo()
    {
        std::cout << "Aooo::~T" << std::endl;
    }
   //virtual void f(int) const {std::cout << "Aooo::f" << std::endl;}
   virtual void f(int i) {std::cout << "Aooo::f" << std::endl;}
};

class Booo : public Aooo
{
public:
    virtual ~Booo()
    {
        std::cout << "Booo::~T" << std::endl;
    }
   virtual void f(int i) override final {std::cout << "Booo::f" << std::endl;}
};
class Cooo : public Booo
{
public:
    virtual ~Cooo()
    {
        std::cout << "Cooo::~T" << std::endl;
    }
   ///no override here
   void f(int i) const {std::cout << "Cooo::f" << std::endl;}
};
void foo(Aooo* p)
{
   std::cout <<"in foo"<< std::endl;
   p->f(1);//call Booo::f
}
void test_002()
{
  std::unique_ptr<Aooo> p1(new Cooo());  
  foo(p1.get());
  
  /*
   * call destructor if that's virtual or only call Aooo::~T
   * Cooo::~T
   * Booo::~T
   * Aooo::~T
   */
}

/*
 * test_003
 */
//shared_ptr
//weak_ptr,break circular reference
//why make_shared:
//pro:
//make_shared is Exception-Safety,
//make_shared make a single heap-allocation for both the control block and the managed object.
//con:
//instances of weak_ptrs keep the control block alive and with the managed object.
struct Child;
 
struct Parent
{
    std::shared_ptr<Child> child;
     
    ~Parent() { std::cout << "Bye Parent" << std::endl; }
     
    void hi() const { std::cout << "Hello" << std::endl; }
};
 
struct Child
{
    std::weak_ptr<Parent> parent;
     
    ~Child() { std::cout << "Bye Child" << std::endl; }
};
void test_003()
{
    auto parent = std::make_shared<Parent>();
    auto child = std::make_shared<Child>();
    parent->child = child;
    child->parent = parent;
    child->parent.lock()->hi();
}
/*
 * test_004
 * 
 */
//std::thread
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << p.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
void test_004()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    //std::thread t1(thr, p), t2(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    //t1.join(); 
    //t2.join(); 
    std::cout << "All threads completed, the last one deleted Derived\n";
}
/*
 * test_005
 */
//Disallow copying,delete
class DoNotCopyMe {
    // ...
    DoNotCopyMe& operator=(const DoNotCopyMe&) = delete;  // Disallow copying
    DoNotCopyMe(const DoNotCopyMe&) = delete;
};
void test_005()
{
    DoNotCopyMe a;
    DoNotCopyMe b;
    a = b;
    DoNotCopyMe c(b);
}
int main()
{
    std::cout<<"in main"<<std::endl;
    
    test_001<int>(12345); 
    test_002();
    test_003();
    test_004();
    
    return 0;
}