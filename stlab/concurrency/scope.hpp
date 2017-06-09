/*
    Copyright 2015 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/**************************************************************************************************/

#ifndef STLAB_SCOPE_HPP
#define STLAB_SCOPE_HPP

/**************************************************************************************************/

namespace stlab {

/**************************************************************************************************/

inline namespace v1 {

/**************************************************************************************************/

template <typename Lock>
class scope {
    using mutex_type = typename Lock::mutex_type;
    using lock_type = Lock;

    lock_type _l;

    template <typename Tuple, size_t...S>
    explicit scope(Tuple&& t, std::index_sequence<S...>) : _l(std::get<S>(std::forward<Tuple>(t))...) {
    }

public:
    template <typename... Args>
    explicit scope(Args&&... args) : scope(std::forward_as_tuple(std::forward<Args>(args)...), std::make_index_sequence<sizeof...(args)-1>()) {
        constexpr std::size_t sz{sizeof...(args)};

        auto&& f = std::get<sz-1>(std::forward_as_tuple(std::forward<Args>(args)...));

        f();
    }

    template <typename F>
    void operator()(F&& f) {
        std::forward<F>(f)();
    }
};

/**************************************************************************************************/

} // namespace v1

/**************************************************************************************************/

} // namespace stlab

/**************************************************************************************************/

#endif

/**************************************************************************************************/
