P2.out : Project2.o SetLimits.o LexicalAnalyzer.o CodeGenerator.o SyntacticalAnalyzer.o
	g++ -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o CodeGenerator.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

CodeGenerator.o : CodeGenerator.cpp CodeGenerator.h LexicalAnalyzer.h
	g++ -g -c CodeGenerator.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm -f *.o P2.out *.gch *.lst *.dbg *.p* *~

submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp CodeGenerator.h CodeGenerator.cpp CodeGenerator.h SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf Team6P2
	mkdir Team6P2
	cp Project2.cpp Team6P2
	cp LexicalAnalyzer.h Team6P2
	cp LexicalAnalyzer.cpp Team6P2
	cp CodeGenerator.h Team6P2
	cp CodeGenerator.cpp Team6P2
	cp SyntacticalAnalyzer.h Team6P2
	cp SyntacticalAnalyzer.cpp Team6P2
	cp makefile Team6P2
	cp README.txt Team6P2
	tar cfvz Team6P2.tgz Team6P2
	cp Team6P2.tgz ~tiawatts/cs460drop
