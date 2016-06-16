# A C++ Template Meta Brainfuck Interpreter

For exercise reasons, i implemented this Brainfuck Interpreter on a long train ride.
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

"*Hello World*" example, printed at compile time:
``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14 -DPROGRAM_STR='"++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.+++."'
main.cpp:31:51: error: implicit instantiation of undefined template 
'debug_t<char_tl<'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\n', '\x0D'> >'
    debug_t<typename tl_to_varlist<output>::list> t;
                                                  ^
main.cpp:6:29: note: template is declared here
template <typename T> class debug_t;
                            ^
1 error generated.
Makefile:3: recipe for target 'default' failed
make: *** [default] Error 1
``` 

The "Hello World" example, printed at runtime:

``` bash
Jacek.Galowicz ~/src/tmp_brainfuck $ g++ -o main main.cpp -std=c++14 -DPROGRAM_STR='"++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.+++."'
Jacek.Galowicz ~/src/tmp_brainfuck $ ./main
Hello World!
```
