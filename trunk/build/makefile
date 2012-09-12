

bin/FinalBin: ../bin/test.o ../bin/linkedList.o ../bin/Hash.o ../bin/Nary.o ../bin/Bst.o
	gcc -o ../bin/FinalBin ../bin/linkedList.o ../bin/Hash.o ../bin/Nary.o ../bin/Bst.o

bin/test.o: ../src/test.c 
	gcc -c ../src/test.c -o ../bin/bin/test.o

bin/linkedList.o: ../src/LinkedList.c
	gcc -c ../src/LinkedList.c -o ../bin/LinkedList.o

bin/Hash.o: ../src/Hash.c
	gcc -c ../src/Hash.c -o ../bin/Hash.o

bin/Nary.o: ../src/Nary.c
	gcc -c ../src/Nary.c -o ../bin/Nary.o

bin/Bst.o: ../src/Bst.c
	gcc -c ../src/Bst.c -o ../bin/Bst.o

/*
bin/Bsth.o:../include/Bsth.h
	gcc -c ../include/Bsth.h -o../bin/Bsth.o

bin/Hashh.o:../include/Hashh.h
	gcc -c ../include/Hashh.h -o../bin/Hashh.o

bin/LinkedListh.o: ../include/LinkedListh.h
	gcc -c ../include/LinkedListh.h -o../bin/LinkedListh.o

bin/Naryh.o: ../include/Naryh.h
	gcc -c ../include/Naryh.h -o../bin/Naryh.o

bin/Structureh.o:../include/Structureh.h
	gcc -c ../include/Structureh.h -o../bin/Structureh.o
*/

bin/all.o:  Bsth.h Naryh.h Structureh.h LinkedListh.h Hashh.h
	gcc -c ../include/Structureh.h  ../include/Hashh.h ../include/LinkedListhh.h ../include/Bsth.h ../include/Naryh.h -o ../bin/all.o
