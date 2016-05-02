# A C++ Template Meta Brainfuck Interpreter

For practise reasons, i implemented this Brainfuck Interpreter on a long train ride.
It works completely at compile time, as it is implemented in a purely functional way, expressed in C++ Template Language.

The program and user input is provided via type lists, and the output is a type list again.
The output string, as well as the Brainfuck Machine state can be printed as a compiler error message.
Of course, it would also be possible to write code which prints the output on the terminal, when the compiled program is being run.

## Usage

The program is encoded like this in the source code:
``` c++
    using input_list = char_tl_t<'a', 'b', 'c'>;
    using prog       = char_tl_t<'+', '+', '+', '[', '.', '-', ']'>;

    using BFM = bfm::io_bfm<bfm::make_t, input_list, tl::null_t>;

    debug_t<bfm::run_tm_t<BFM, prog>::output> t;
```

The following is the (barely readable, but correct) output:

``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14
main.cpp:17:47: error: implicit instantiation of undefined template 'debug_t<tl::tl<char_t<'\x03'>, tl::tl<char_t<'\x02'>, tl::tl<char_t<'\x01'>, tl::null_t> > > >'
    debug_t<bfm::run_tm_t<BFM, prog>::output> t;
                                              ^
main.cpp:8:29: note: template is declared here
template <typename T> class debug_t;
                            ^
1 error generated.
``` 

The "Hello World" output looks like this:

``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14
main.cpp:25:47: error: implicit instantiation of undefined template 'debug_t<tl::tl<char_t<'H'>, tl::tl<char_t<'e'>, tl::tl<char_t<'l'>, tl::tl<char_t<'l'>, tl::tl<char_t<'o'>, tl::tl<char_t<' '>, tl::tl<char_t<'W'>, tl::tl<char_t<'o'>, tl::tl<char_t<'r'>,
      tl::tl<char_t<'l'>, tl::tl<char_t<'d'>, tl::tl<char_t<'!'>, tl::tl<char_t<'\n'>, tl::null_t> > > > > > > > > > > > > >'
    debug_t<bfm::run_tm_t<BFM, prog>::output> t;
                                              ^
main.cpp:8:29: note: template is declared here
template <typename T> class debug_t;
                            ^
1 error generated.
```
