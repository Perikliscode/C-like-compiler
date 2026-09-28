Requirements: gcc, yacc, flex
Commands to compile the program:
cd <folder location>
flex lex1m
yacc -dv syd1m
gcc lex.yy.c y.tab.c syd1_3m.c zyywrap.c
