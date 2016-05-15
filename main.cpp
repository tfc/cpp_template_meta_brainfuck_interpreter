#include <iostream>

#include "charlist.hpp"
#include "brainfuck_machine.hpp"

template <typename T> class debug_t;

#ifndef INPUT_STR
#define INPUT_STR ""
#endif

#ifndef PROGRAM_STR
// "Hello World" Program
#define PROGRAM_STR "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++." \
                    ".+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.+++."
#endif

struct input_str   { static constexpr const char * str() { return INPUT_STR;   } };
struct program_str { static constexpr const char * str() { return PROGRAM_STR; } };

int main()
{
    using input_list = string_list_t<input_str>;
    using prog       = string_list_t<program_str>;

    using BFM = bfm::io_bfm<bfm::make_t, input_list, tl::null_t>;

    using output = bfm::run_tm_t<BFM, prog>::output;

    // Print output or state in a compiler error message
    //debug_t<output> t;

    puts(tl_to_varlist<output>::str());

    return 0;
};
