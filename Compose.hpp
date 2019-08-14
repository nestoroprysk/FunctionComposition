#pragma once

#include <utility>

#define INVOCABLE_ASSERTION_FAILED_ERROR_MESSAGE\
    "An object should be invokable with the provided arguments"

template <typename F>
auto compose(F&& f)
{
    return [a = std::forward<F>(f)](auto&&... args){
        static_assert(std::is_invocable_v<F, decltype(args)...>,
            INVOCABLE_ASSERTION_FAILED_ERROR_MESSAGE);
        return a(std::forward<decltype(args)>(args)...);
    };
}

template <typename F1, typename F2, typename... Fs>
auto compose(F1&& f1, F2&& f2, Fs&&... fs)
{
    return compose(
        [first = std::forward<F1>(f1), second = std::forward<F2>(f2)]
        (auto&&... args){
            static_assert(std::is_invocable_v<F1, decltype(args)...>,
                INVOCABLE_ASSERTION_FAILED_ERROR_MESSAGE
            );
            static_assert(
                std::is_invocable_v<F2,
                    std::result_of_t<F1(decltype(args)...)>
                >,
                INVOCABLE_ASSERTION_FAILED_ERROR_MESSAGE
            );
            return second(first(std::forward<decltype(args)>(args)...));
        },
        std::forward<Fs>(fs)...
    );
}
