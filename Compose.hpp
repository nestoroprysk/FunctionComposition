#pragma once

#include <utility>

template <typename F>
auto compose(F&& f)
{
    return [a = std::move(f)](auto&&... args){
        return a(std::move(args)...);
    };
}

template <typename F1, typename F2, typename... Fs>
auto compose(F1&& f1, F2&& f2, Fs&&... fs)
{
    return compose(
        [first = std::move(f1), second = std::move(f2)]
        (auto&&... args){
            return second(first(std::move(args)...));
        },
        std::move(fs)...
    );
}
