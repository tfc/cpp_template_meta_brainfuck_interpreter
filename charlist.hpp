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

template <class Str, size_t Pos, char C>
struct string_list {
    using next_piece = typename string_list<
                            Str,
                            Pos + 1,
                            Str::str()[Pos + 1]
                        >::type;
    using type = tl::tl<char_t<C>, next_piece>;
};

template <class Str, size_t Pos>
struct string_list<Str, Pos, '\0'> {
    using type = tl::null_t;
};

template <class Str>
using string_list_t = typename string_list<Str, 0, Str::str()[0]>::type;

template <typename typelist, char ... chars>
struct tl_to_varlist;

template <char c, typename restlist, char ... chars>
struct tl_to_varlist<tl::tl<char_t<c>, restlist>, chars...>
    : public tl_to_varlist<restlist, chars..., c>
{ };

template <char ... chars>
struct tl_to_varlist<tl::null_t, chars...> {
    static const char * const str() {
        static constexpr const char string[] = {chars..., '\0'};
        return string;
    }
};

