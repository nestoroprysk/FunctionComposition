#pragma once

#include <utility>

template <typename F>
auto compose(F&& f)
{
    return [a = std::forward<F>(f)](auto&&... args){
        return a(std::forward<decltype(args)>(args)...);
    };
}

template <typename F1, typename F2, typename... Fs>
auto compose(F1&& f1, F2&& f2, Fs&&... fs)
{
    return compose(
        [first = std::forward<F1>(f1), second = std::forward<F2>(f2)]
        (auto&&... args){
            return second(first(std::forward<decltype(args)>(args)...));
        },
        std::forward<Fs>(fs)...
    );
}
