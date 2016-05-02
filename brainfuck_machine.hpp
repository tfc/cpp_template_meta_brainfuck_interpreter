#pragma once

#include "traits.hpp"
#include "typelist.hpp"
#include "yzipper.hpp"
#include "charlist.hpp"

namespace bfm {

template <class YZ> using yz_move_left_t  = ::yz::move_left_t<YZ>;
template <class YZ> using yz_move_right_t =::yz::move_right_t<YZ>;
template <class YZ> using yz_get_t = ::yz::get_t<YZ>;
template <class YZ, class T> using yz_set_t = ::yz::set_t<YZ, T>;
template <class T> using yz_make_t  = ::yz::make_t<T>;

template <class YZipper>
struct null_to_0;
template <class LList, class RList>
struct null_to_0<::yz::yzipper<LList, ::tl::null_t, RList>> {
    using type = yz::yzipper<LList, ::char_t<0>, RList>;
};
template <class YZipper> struct null_to_0 { using type = YZipper; };
template <class YZ> using null_to_0_t = typename null_to_0<YZ>::type;

template <typename YZipper>
struct machine {
    using move_left  = machine<null_to_0_t<yz_move_left_t<YZipper>>>;
    using move_right = machine<null_to_0_t<yz_move_right_t<YZipper>>>;

    using get = yz_get_t<YZipper>;
    template <char value>
    using set = machine<yz_set_t<YZipper, ::char_t<value>>>;

    static const constexpr char value {get::value};

    using increment = machine<yz_set_t<YZipper, ::char_t<value + 1>>>;
    using decrement = machine<yz_set_t<YZipper, ::char_t<value - 1>>>;
};

template <typename Machine>
using move_left_t = typename Machine::move_left;
template <typename Machine>
using move_right_t = typename Machine::move_right;

template <typename Machine>
using get_t = typename Machine::get;
template <typename Machine, char val>
using set_t = typename Machine::template set<val>;

template <typename Machine>
using increment_t = typename Machine::increment;
template <typename Machine>
using decrement_t = typename Machine::decrement;

using make_t = machine<yz_make_t<::char_t<0>>>;

template <class BFM, class Inlist, class OutList>
struct io_bfm {
    using output = OutList;
    using state  = BFM;
};


template <class InList, class OutList, size_t Counter>
struct find_brace;

template <class InList, class OutList>
struct find_brace<::tl::tl<::char_t<']'>, InList>, OutList, 1> {
    using brace_block = OutList;
    using rest_prog   = InList;
};
template <class InList, class OutList, size_t N>
struct find_brace<::tl::tl<::char_t<']'>, InList>, OutList, N>
    : public find_brace<InList, ::tl::append_t<OutList, ::char_t<']'>>, N - 1>
{};
template <class InList, class OutList, size_t N>
struct find_brace<::tl::tl<::char_t<'['>, InList>, OutList, N>
    : public find_brace<InList, ::tl::append_t<OutList, ::char_t<'['>>, N + 1>
{};
template <char C, class InList, class OutList, size_t N>
struct find_brace<::tl::tl<::char_t<C>, InList>, OutList, N>
    : public find_brace<InList, ::tl::append_t<OutList, char_t<C>>, N>
{};


template <class IOBFM, char InputChar>
struct interprete_step;

template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, '.'> {
    using type = io_bfm<BFM, InList, ::tl::append_t<OutList, get_t<BFM>>>;
};
template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, ','> {
    using type = io_bfm<set_t<BFM, tl::head_t<InList>::value>, tl::tail_t<InList>, OutList>;
};
template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, '+'> {
    using type = io_bfm<increment_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, '-'> {
    using type = io_bfm<decrement_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, '<'> {
    using type = io_bfm<move_left_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interprete_step<io_bfm<BFM, InList, OutList>, '>'> {
    using type = io_bfm<move_right_t<BFM>, InList, OutList>;
};

template <class IOBFM, char InputChar>
using interprete_step_t = typename interprete_step<IOBFM, InputChar>::type;

template <class IOBFM, class ProgList>
struct run_tm;
template <class IOBFM, class RestProg>
struct run_tm<IOBFM, ::tl::tl<::char_t<'['>, RestProg>> {
    static const constexpr bool loop_terminated {get_t<typename IOBFM::state>::value == 0};
    using blocks = find_brace<RestProg, ::tl::null_t, 1>;
    using type = typename if_else_t<loop_terminated,
        run_tm<IOBFM, typename blocks::rest_prog>,
        run_tm<
            typename run_tm<IOBFM, typename blocks::brace_block>::type,
            ::tl::tl<::char_t<'['>, RestProg>>
    >::type;
};
template <class IOBFM, char Command, class RestProg>
struct run_tm<IOBFM, ::tl::tl<::char_t<Command>, RestProg>> {
    using type = typename run_tm<interprete_step_t<IOBFM, Command>, RestProg>::type;
};
template <class IOBFM>
struct run_tm<IOBFM, ::tl::null_t> {
    using type = IOBFM;
};

template <class IOBFM, class ProgList>
using run_tm_t = typename run_tm<IOBFM, ProgList>::type;

};
