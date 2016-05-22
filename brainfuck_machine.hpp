#pragma once

#include "traits.hpp"
#include "typelist.hpp"
#include "tape.hpp"
#include "charlist.hpp"

namespace bfm {

template <class Tape> using tt_move_left_t  = ::tt::move_left_t<Tape>;
template <class Tape> using tt_move_right_t =::tt::move_right_t<Tape>;
template <class Tape> using tt_get_t = ::tt::get_t<Tape>;
template <class Tape, class T> using tt_set_t = ::tt::set_t<Tape, T>;
template <class T> using tt_make_t  = ::tt::make_t<T>;

template <class Tape>
struct null_to_0;
template <class LList, class RList>
struct null_to_0<::tt::tape<LList, ::tl::null_t, RList>> {
    using type = tt::tape<LList, ::char_t<0>, RList>;
};
template <class Tape> struct null_to_0 { using type = Tape; };
template <class Tape> using null_to_0_t = typename null_to_0<Tape>::type;

template <typename Tape>
struct machine {
    using move_left  = machine<null_to_0_t<tt_move_left_t<Tape>>>;
    using move_right = machine<null_to_0_t<tt_move_right_t<Tape>>>;

    using get = tt_get_t<Tape>;
    template <char value>
    using set = machine<tt_set_t<Tape, ::char_t<value>>>;

    static const constexpr char value {get::value};

    using increment = set<value + 1>;
    using decrement = set<value - 1>;
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

using make_t = machine<tt_make_t<::char_t<0>>>;

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
struct interpret_step;

template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, '.'> {
    using type = io_bfm<BFM, InList, ::tl::append_t<OutList, get_t<BFM>>>;
};
template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, ','> {
    using type = io_bfm<set_t<BFM, tl::head_t<InList>::value>, tl::tail_t<InList>, OutList>;
};
template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, '+'> {
    using type = io_bfm<increment_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, '-'> {
    using type = io_bfm<decrement_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, '<'> {
    using type = io_bfm<move_left_t<BFM>, InList, OutList>;
};
template <class BFM, class InList, class OutList>
struct interpret_step<io_bfm<BFM, InList, OutList>, '>'> {
    using type = io_bfm<move_right_t<BFM>, InList, OutList>;
};

template <class IOBFM, char InputChar>
using interpret_step_t = typename interpret_step<IOBFM, InputChar>::type;

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
    using type = typename run_tm<interpret_step_t<IOBFM, Command>, RestProg>::type;
};
template <class IOBFM>
struct run_tm<IOBFM, ::tl::null_t> {
    using type = IOBFM;
};

template <class IOBFM, class ProgList>
using run_tm_t = typename run_tm<IOBFM, ProgList>::type;

};
