#pragma once

#include "typelist.hpp"

template <char val> struct char_t { static const constexpr char value {val}; };

template <char c, char ... chars>
struct char_tl;

template <char c, char ... chars>
struct char_tl {
    using type = tl::tl<char_t<c>, typename char_tl<chars...>::type>;
};
template <char c>
struct char_tl<c> {
    using type = tl::tl<char_t<c>, tl::null_t>;
};

template <char ... chars>
using char_tl_t = typename char_tl<chars...>::type;

template <class Str, size_t Pos, char C>
struct string_list;

template <class Str, size_t Pos>
struct string_list<Str, Pos, '\0'> {
    using type = tl::null_t;
};

template <class Str, size_t Pos, char C>
struct string_list {
    using type = tl::tl<char_t<C>, typename string_list<Str, Pos + 1, Str::str()[Pos + 1]>::type>;
};

template <class Str>
using string_list_t = typename string_list<Str, 0, Str::str()[0]>::type;

