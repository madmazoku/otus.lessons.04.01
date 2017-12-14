#pragma once

struct xray
{
    std::string str;
    xray(const std::string &s) : str(s)
    {
        std::cout << "[" << str << "] " << "ctor: " << this << ' ' << __FUNCTION__ << " [" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
    }
    xray(const xray& x)
    {
        std::cout << "copy ctor: " << this << " from " << &x << ' ' << __FUNCTION__ << std::endl;
    }
#ifdef MOVE
    xray(xray&& x) noexcept
    {
        std::cout << "copy ctor: " << this << " from " << &x << ' ' << __FUNCTION__ << std::endl;
        x.destroy_by_move();
        std::cout << "xray dem " << demangle_type_name<decltype(x)>() << std::endl;
        std::cout << "xray " << type_name<decltype(x)>() << std::endl;
    }
#endif
    struct xray &operator=(const struct xray& t) {
        std::cout << "[" << str << "] <- [" << t.str << "] " << "copy: " << this << ' ' << __FUNCTION__ << std::endl;
        return *this;
    }
#ifdef MOVE
    struct xray &operator=(struct xray&& x) noexcept {
        std::cout << "[" << str << "] <- [" << x.str << "] " << "move: " << this << ' ' << __FUNCTION__ << std::endl;
        str.swap(x.str);
        std::cout << "\t swapped [" << str << "] <- [" << x.str << "] " << "move: " << this << ' ' << __FUNCTION__ << std::endl;
        std::cout << "\txray dem " << demangle_type_name<decltype(x)>() << std::endl;
        std::cout << "\txray " << demangle_type_name<decltype(x)>() << std::endl;
        // x.destroy_by_move();
        return *this;
    }
#endif
    ~xray()
    {
        std::cout << "[" << str << "] " << "dtor: " << this << ' ' << __FUNCTION__ << std::endl;
    }
    void operator()()
    {
        std::cout << "[" << str << "] " << "tick" << std::endl;
    }
    void destroy_by_move() {
        std::cout << "[" << str << "] " << "destroy_by_move" << std::endl;
    }
};
inline std::ostream& operator<<(std::ostream& os, const struct xray& x)
{
    return os << "{xray: '" << &x << ", " << x.str << "'}";
}