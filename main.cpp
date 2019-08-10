#include "TestUtils.hpp"
#include "Compose.hpp"

#include <string>
#include <cmath>

namespace {

int addTwo(int a)
{
    return a + 2;
}

int powTwo(int a)
{
    return std::pow(a, 2);
}

int powN(int a, int n)
{
    return std::pow(a, n);
}

} // namespace anonymous

int main()
{
    TestUtils::check(12, []{
        const auto f = compose(addTwo);
        return f(10);
    });  
    TestUtils::check(14, []{
        const auto f = compose(addTwo, addTwo);
        return f(10);
    });
    TestUtils::check(16, []{
        const auto f = compose(addTwo, addTwo, addTwo);
        return f(10);
    });
        TestUtils::check(18, []{
        const auto f = compose(addTwo, addTwo, addTwo, addTwo);
        return f(10);
    });
        
        TestUtils::check(144, []{
        const auto f = compose(addTwo, powTwo);
        return f(10);
    });
    TestUtils::check(27, []{
        const auto f = compose(powN, addTwo);
        return f(5, 2);
    });
    TestUtils::check("012", []{
        const auto f = compose(
            [](const auto& s){return std::string(s);},
            [](const auto& s){return s.size();},
            [](const auto n){
                auto result = std::string();
                for (std::size_t i = 0; i < n; ++i)
                    result += std::to_string(i);
                return result;
            }
        );
        return f("abc");
    });
    TestUtils::check(std::size_t(3), []{
        const auto i = std::string("abc");
        const auto f = compose([](const auto& s){return s.size();});
        return f(i);
    });
}
