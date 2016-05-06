# A C++ Template Meta Brainfuck Interpreter

For practise reasons, i implemented this Brainfuck Interpreter on a long train ride.
It works completely at compile time, as it is implemented in a purely functional way, expressed in C++ Template Language.

The program and user input is provided via type lists, and the output is a type list again.
The output string, as well as the Brainfuck Machine state can be printed as a compiler error message, or on the terminal when launching the program after compilation.

## Usage

Program and user input are provided via preprocessor macros on the command line:
``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14 -DINPUT_STR=\"z\" -DPROGRAM_STR=\",[.-]\"
Jacek.Galowicz ~/src/tmp_brainfuck $ ./main
zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!
```

The brainfuck program output can also be printed at compile time, by producing an error message with the helper type ```debug_t```:

``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14 -DINPUT_STR=\"z\" -DPROGRAM_STR=\",[.-]\"
main.cpp:39:47: error: implicit instantiation of undefined template 'debug_t<tl::tl<char_t<'z'>, tl::tl<char_t<'y'>, tl::tl<char_t<'x'>, tl::tl<char_t<'w'>, tl::tl<char_t<'v'>, tl::tl<char_t<'u'>,
      tl::tl<char_t<'t'>, tl::tl<char_t<'s'>, tl::tl<char_t<'r'>, tl::tl<char_t<'q'>, tl::tl<char_t<'p'>, tl::tl<char_t<'o'>, tl::tl<char_t<'n'>, tl::tl<char_t<'m'>, tl::tl<char_t<'l'>,
      tl::tl<char_t<'k'>, tl::tl<char_t<'j'>, tl::tl<char_t<'i'>, tl::tl<char_t<'h'>, tl::tl<char_t<'g'>, tl::tl<char_t<'f'>, tl::tl<char_t<'e'>, tl::tl<char_t<'d'>, tl::tl<char_t<'c'>,
      tl::tl<char_t<'b'>, tl::tl<char_t<'a'>, tl::tl<char_t<'`'>, tl::tl<char_t<'_'>, tl::tl<char_t<'^'>, tl::tl<char_t<']'>, tl::tl<char_t<'\\'>, tl::tl<char_t<'['>, tl::tl<char_t<'Z'>,
      tl::tl<char_t<'Y'>, tl::tl<char_t<'X'>, tl::tl<char_t<'W'>, tl::tl<char_t<'V'>, tl::tl<char_t<'U'>, tl::tl<char_t<'T'>, tl::tl<char_t<'S'>, tl::tl<char_t<'R'>, tl::tl<char_t<'Q'>,
      tl::tl<char_t<'P'>, tl::tl<char_t<'O'>, tl::tl<char_t<'N'>, tl::tl<char_t<'M'>, tl::tl<char_t<'L'>, tl::tl<char_t<'K'>, tl::tl<char_t<'J'>, tl::tl<char_t<'I'>, tl::tl<char_t<'H'>,
      tl::tl<char_t<'G'>, tl::tl<char_t<'F'>, tl::tl<char_t<'E'>, tl::tl<char_t<'D'>, tl::tl<char_t<'C'>, tl::tl<char_t<'B'>, tl::tl<char_t<'A'>, tl::tl<char_t<'@'>, tl::tl<char_t<'?'>,
      tl::tl<char_t<'>'>, tl::tl<char_t<'='>, tl::tl<char_t<'<'>, tl::tl<char_t<';'>, tl::tl<char_t<':'>, tl::tl<char_t<'9'>, tl::tl<char_t<'8'>, tl::tl<char_t<'7'>, tl::tl<char_t<'6'>,
      tl::tl<char_t<'5'>, tl::tl<char_t<'4'>, tl::tl<char_t<'3'>, tl::tl<char_t<'2'>, tl::tl<char_t<'1'>, tl::tl<char_t<'0'>, tl::tl<char_t<'/'>, tl::tl<char_t<'.'>, tl::tl<char_t<'-'>,
      tl::tl<char_t<','>, tl::tl<char_t<'+'>, tl::tl<char_t<'*'>, tl::tl<char_t<')'>, tl::tl<char_t<'('>, tl::tl<char_t<'\''>, tl::tl<char_t<'&'>, tl::tl<char_t<'%'>, tl::tl<char_t<'$'>,
      tl::tl<char_t<'#'>, tl::tl<char_t<'\"'>, tl::tl<char_t<'!'>, tl::tl<char_t<' '>, tl::tl<char_t<'\x1F'>, tl::tl<char_t<'\x1E'>, tl::tl<char_t<'\x1D'>, tl::tl<char_t<'\x1C'>,
      tl::tl<char_t<'\x1B'>, tl::tl<char_t<'\x1A'>, tl::tl<char_t<'\x19'>, tl::tl<char_t<'\x18'>, tl::tl<char_t<'\x17'>, tl::tl<char_t<'\x16'>, tl::tl<char_t<'\x15'>, tl::tl<char_t<'\x14'>,
      tl::tl<char_t<'\x13'>, tl::tl<char_t<'\x12'>, tl::tl<char_t<'\x11'>, tl::tl<char_t<'\x10'>, tl::tl<char_t<'\x0F'>, tl::tl<char_t<'\x0E'>, tl::tl<char_t<'\x0D'>, tl::tl<char_t<'\x0C'>,
      tl::tl<char_t<'\x0B'>, tl::tl<char_t<'\n'>, tl::tl<char_t<'\t'>, tl::tl<char_t<'\x08'>, tl::tl<char_t<'\x07'>, tl::tl<char_t<'\x06'>, tl::tl<char_t<'\x05'>, tl::tl<char_t<'\x04'>,
      tl::tl<char_t<'\x03'>, tl::tl<char_t<'\x02'>, tl::tl<char_t<'\x01'>, tl::null_t> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > >
      > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > >'
    debug_t<bfm::run_tm_t<BFM, prog>::output> t;
                                              ^
main.cpp:7:29: note: template is declared here
template <typename T> class debug_t;
                            ^
1 error generated.
``` 

The "Hello World" example looks like this:

``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14 -DPROGRAM_STR='"++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.+++."'
Jacek.Galowicz ~/src/tmp_brainfuck $ ./main
Hello World!
```
