#pragma once

#include <exception>
#include <stdexcept>
#include <iostream>
#include <chrono>

namespace Detail{

// https://en.cppreference.com/w/cpp/error/current_exception
void handle_eptr(std::exception_ptr eptr)
{
    try{
        if (eptr)
            std::rethrow_exception(eptr);
    }
    catch(const std::exception& e){
        std::cout << "[KO], caught exception [" <<
            e.what() << "]" << std::endl;
    }
    catch(...){
        std::cout << "[KO], caught a non-standard exception" << std::endl;
    }
}

}

namespace TestUtils {

template <typename R, typename F>
void check(const R& expected, const F& f)
{
    std::exception_ptr eptr;
    try{
        const auto t0 = std::chrono::steady_clock::now();
        const auto result = f();
        const auto d = static_cast<size_t>(std::chrono::duration_cast<std::chrono::nanoseconds>
                        (std::chrono::steady_clock::now() - t0).count());
        if (result == expected) std::cout << "[OK], ran for [" << std::to_string(d) <<
            "] nanoseconds" << std::endl;
        else std::cout << "[KO], got [" <<
                result << "], expected [" << expected << "]" << std::endl;
    }
    catch(...){
        eptr = std::current_exception();
    }
    Detail::handle_eptr(eptr);
}

}
