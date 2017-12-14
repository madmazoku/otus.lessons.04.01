#include <iostream>
#include <spdlog/spdlog.h>

#include "../bin/version.h"

#define MOVABLE
#include "xray.h"

#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <array>

int y = 10;
auto f = [x = y](auto... i){return std::make_tuple(x, i...);};

// ~~~~~~~~~~~~

std::string operator""_my(unsigned long long b) {
    return "ull";
}

std::string operator""_my(long double b) {
    return "double";
}

std::string operator""_my(const char *b, size_t s) {
    return "char";
}

using namespace std::string_literals;

// ~~~~~~~~~~~~

using v = std::vector<int>; // declare v as std::vector<int>;

template<typename T>
using vt = std::vector<T>; // std::vector<T> v<T>;

// ~~~~~~~~~~~~

enum Digit 
{
    ine,
    two,
    three
};

enum class DigitE
{
    ine,
    two,
    three,
    four
};

// ~~~~~~~~~~~~

constexpr int foo(int i) {
    return i * 2;
}

// ~~~~~~~~~~~~

class pFoo
{
public:
    pFoo() = default;
    pFoo(const pFoo& x) = delete;

    virtual void m() final { std::cout << "pFoo.m" << std::endl; };
    virtual void n() { std::cout << "pFoo.m" << std::endl; };
};

class pFooChild : pFoo
{
public:
    // void m() { std::cout << "pFooChild.m" << std::endl; } // compile error, parent.m is final
    void n() { std::cout << "pFooChild.m" << std::endl; }
    // void x() override { std::cout << "pFooChild.m" << std::endl; } // compile error, parent.x must be virtual
};

// ~~~~~~~~~~~~

struct sFoo 
{
    int a{-1};
    int b{-1};
    int c{-1};

    sFoo(int a_, int b_) : a(10*a_), b(10*b_) {}
    sFoo() = default;
    sFoo(std::initializer_list<int> l) : a(l.size()) {}
};

// ~~~~~~~~~~~~

int main(int argc, char** argv) {
    auto console = spdlog::stdout_logger_st("console");
    console->info("Welcome to spdlog!");

    {
        std::cout << "variadic lambda" << std::endl;

        y = 20;
        std::cout << "y: " << y << std::endl;

        auto z = f(1,2,3);
        std::cout << std::get<0>(z) << std::endl;
        std::cout << std::get<1>(z) << std::endl;
        std::cout << std::get<2>(z) << std::endl;
        std::cout << std::get<3>(z) << std::endl;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "custom suffix" << std::endl;
        auto z = 123_my; // operator "" my(123)
        auto y = 123.0_my; // operator "" my(123.0)
        auto x = "123"_my; // operator "" my(123.0)
        std::cout << z << std::endl;
        std::cout << y << std::endl;
        std::cout << x << std::endl;

        std::cout << "string with \\000" << "1\00023"s << std::endl;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "static assert" << std::endl;

        // static_assert(0, "comilation error");
        static_assert(1, "no compilation error");

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "using v" << std::endl;

        v i = {0};
        vt<int> it = {0};
        std::cout << i.size() << std::endl;
        std::cout << it.size() << std::endl;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "NULL / nullptr" << std::endl;
//        int i = nullptr; // compilation error
        int* p = nullptr;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "enumeration" << std::endl;

        int a = two;
        std::cout << "Digital two: " << two << std::endl;

        // int b = four; // compile error
        // int b = DigitE::four; // compile error
        // std::cout << "DigitalE four: " << DigitE::four << std::endl; // compile error
        std::cout << "DigitalE three: " << int(DigitE::three) << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "compile time initialization" << std::endl;

        int i = 10;
        // auto arr1 = std::array<int, i>(); // compile error

        constexpr int cei = 10;
        auto arr2 = std::array<int, cei>();
        std::cout << "arr2: " << arr2.size() << std::endl;
        
        auto arr3 = std::array<int, 2 *10>();
        std::cout << "arr3: " << arr3.size() << std::endl;

        auto arr4 = std::array<int, foo(10)>();
        std::cout << "arr4: " << arr4.size() << std::endl;

        // auto arr5 = std::array<int, foo(i)>(); // compile error
        
        auto arr6 = std::array<int, foo(cei)>();
        std::cout << "arr6: " << arr6.size() << std::endl;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "default constructor" << std::endl;

        pFoo pfoo;
        // pFoo pfoo2(pfoo); // compile error, constructor deleted

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    {
        std::cout << "initialization lists" << std::endl;

        auto a = {1, 2, 3, 4};
        // int a[4] = {1, 2, 3, 4}; // right 

        // std::cout << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", " << std::endl; // compile error

        // sFoo sf; // default constructor sFoo::sFoo()
        // sFoo sf{}; // same as above
        sFoo sf{1,2}; // init a and b with sFoo::sFoo() or call sFoo::sFoo(int,int) or sFoo(std::initializer_list<int> l)

        std::cout << "sFoo sf{1,2};" << std::endl;
        std::cout << sf.a << std::endl;
        std::cout << sf.b << std::endl;
        std::cout << sf.c << std::endl;

        sFoo sf2{}; // 

        std::cout << "sFoo sf2{};" << std::endl;
        std::cout << sf2.a << std::endl;
        std::cout << sf2.b << std::endl;
        std::cout << sf2.c << std::endl;

        std::cout << "end of scope" << std::endl;
    }
    std::cout << std::endl << std::endl;

    // {
    //     std::cout << "" << std::endl;
    //     std::cout << "end of scope" << std::endl;
    // }
    // std::cout << std::endl << std::endl;

    console->info("Goodbye!");

    return 0;
}