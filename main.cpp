#include <iostream>

#include "typelist.hpp"
#include "yzipper.hpp"
#include "brainfuck_machine.hpp"

template <typename T> class debug_t;

void print(const tl::null_t&) {}

template <typename T, char c>
void print(const tl::tl<char_t<c>, T>&)
{
    std::cout << c;
    print(T{});
}

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

    // Print output or state in a compiler error message
    //debug_t<bfm::run_tm_t<BFM, prog>::output> t;

    print(bfm::run_tm_t<BFM, prog>::output{});

    return 0;
};
