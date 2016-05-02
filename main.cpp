#include <iostream>
#include <cassert>

#include "typelist.hpp"
#include "yzipper.hpp"
#include "brainfuck_machine.hpp"

template <typename T> class debug_t;

int main()
{
    using input_list = char_tl_t<'a', 'b', 'c'>;
    using prog       = char_tl_t<
        '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '[', '>', '+', '+',
        '+', '+', '+', '+', '+', '>', '+', '+', '+', '+', '+', '+', '+', '+',
        '+', '+', '>', '+', '+', '+', '>', '+', '<', '<', '<', '<', '-', ']',
        '>', '+', '+', '.', '>', '+', '.', '+', '+', '+', '+', '+', '+', '+',
        '.', '.', '+', '+', '+', '.', '>', '+', '+', '.', '<', '<', '+', '+',
        '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '.',
        '>', '.', '+', '+', '+', '.', '-', '-', '-', '-', '-', '-', '.', '-',
        '-', '-', '-', '-', '-', '-', '-', '.', '>', '+', '.', '>', '.'>;

    using BFM = bfm::io_bfm<bfm::make_t, input_list, tl::null_t>;

    debug_t<bfm::run_tm_t<BFM, prog>::output> t;

    return 0;
};
