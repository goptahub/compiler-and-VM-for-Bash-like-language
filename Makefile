EXE=bvmc

BISON_FLAGS=-Wno-conflicts-sr -Wno-conflicts-rr -Wno-other 
# BISON_FLAGS=-Wconflicts-rr
# BISON_FLAGS=-Wcounterexamples

.PHONY: sh_parser sh_pars


all: bvmc_exe sh_parser

dbg: DBG_FLAG=-DDEBUG
dbg: all


map.o: map.h map.c
	gcc -c map.c -o map.o

bytecode.o: bytecode.c bytecode.h
	gcc -c bytecode.c -o bytecode.o

# sh parser interface

string_module.o: string_module.c string_module.h
	gcc -c string_module.c -o string_module.o

list.o: list.c list.h
	gcc -c list.c -o list.o

basm_wizard.o: basm_wizard.h basm_wizard.c
	gcc -c basm_wizard.c -o basm_wizard.o

sh_parser.tab.o: sh_parser.y basm_wizard.h basm_wizard.o list.o string_module.o map.h
	bison -d sh_parser.y $(BISON_FLAGS) 
	gcc -r sh_parser.tab.c basm_wizard.o list.o string_module.o -o sh_parser.tab.o -DITSELF  $(DBG_FLAG)

sh_lexer.yy.o: sh_lexer.lx sh_parser.tab.h
	flex -o sh_lexer.yy.c sh_lexer.lx
	gcc -c sh_lexer.yy.c -o sh_lexer.yy.o  $(DBG_FLAG)

sh_parser_if.o: sh_parser.tab.o sh_lexer.yy.o
	gcc -r sh_parser.tab.o sh_lexer.yy.o -o sh_parser_if.o

# basm parser interface

basm_parser.tab.o: basm_parser.y bytecode.h map.h
	bison -d basm_parser.y $(BISON_FLAGS)
	gcc -c basm_parser.tab.c -o basm_parser.tab.o $(DBG_FLAG)

basm_lexer.yy.o: basm_lexer.lx basm_parser.tab.h bytecode.h map.h
	flex -o basm_lexer.yy.c basm_lexer.lx
	gcc -c basm_lexer.yy.c -o basm_lexer.yy.o $(DBG_FLAG)

basm_parser_if.o: basm_parser.tab.o basm_lexer.yy.o
	gcc -r basm_parser.tab.o basm_lexer.yy.o -o basm_parser_if.o

# bvm interface

stack.o: stack.c stack.h
	gcc -c stack.c -o stack.o

processor.o: processor.c processor.h stack.h bytecode.h
	gcc -c processor.c -o processor.o

bvm_if.o: bvm.c bvm.h processor.h
	gcc -c bvm.c -o bvm_if.o

bvm.o: bvm_if.o processor.o stack.o
	gcc -r bvm_if.o processor.o stack.o -o bvm.o

# bvmc interface

bvmc_if.o:
	gcc -c bvmc.c -o bvmc_if.o

# EXE

bvmc_exe: bvmc_if.o bvm.o basm_parser_if.o map.o bytecode.o
	gcc bvmc_if.o bvm.o basm_parser_if.o map.o bytecode.o -o $(EXE)

sh_parser: sh_parser_if.o map.o
	gcc sh_parser_if.o map.o -o sh_parser

clean:
	rm -f *.o *.tab.c *.tab.h *.yy.c

clean_exe:
	rm -f *.o *.tab.c *.tab.h *.yy.c basm_parser bvm $(EXE)

# separate build

sh_pars:
	bison -d sh_parser.y 
	flex -o sh_lexer.yy.c sh_lexer.lx
	gcc sh_parser.tab.c sh_lexer.yy.c basm_wizard.c map.c list.c -o sh_pars -DITSELF -DDEBUG


basmpars:
	bison -d basm_parser.y $(BISON_FLAGS)
	flex -o basm_lexer.yy.c basm_lexer.lx
	gcc basm_parser.tab.c basm_lexer.yy.c map.c -o basm_parser -DITSELF -DDEBUG

bvmexe:
	gcc bvm.c processor.c stack.c bytecode.c -o bvm -DITSELF


copy:
	rm -rf copy_dir
	mkdir copy_dir
	cp *.c *.h *.y *.lx Makefile copy_dir/.

zip:
	rm -f bvmc.zip
	zip -r bvmc.zip . -i *.c *.h *.y *.lx Makefile
