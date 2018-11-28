P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm -f *.o P2.out *.gch *.lst *.dbg *.p* *~

submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamXP2
	mkdir TeamXP2
	cp Project2.cpp TeamXP2
	cp LexicalAnalyzer.h TeamXP2
	cp LexicalAnalyzer.cpp TeamXP2
	cp SyntacticalAnalyzer.h TeamXP2
	cp SyntacticalAnalyzer.cpp TeamXP2
	cp makefile TeamXP2
	cp README.txt TeamXP2
	tar cfvz TeamXP2.tgz TeamXP2
	cp TeamXP2.tgz ~tiawatts/cs460drop
