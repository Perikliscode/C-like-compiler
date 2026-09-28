Requirements: gcc, yacc, flex \n
Commands to compile the program:\n
cd <folder location>
flex lex1m
yacc -dv syd1m
gcc lex.yy.c y.tab.c syd1_3m.c zyywrap.c
