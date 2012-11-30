vfs_group21: FileOpns.o DirOpns.o Filesystem.o LinkedList.o Hashtable.o nAry.o Bst.o dsCreator.o Commons.o freelist.o vfsdriver.o Bst_test.o 
	gcc FileOpns.o DirOpns.o Filesystem.o LinkedList.o Hashtable.o nAry.o Bst.o dsCreator.o Commons.o freelist.o vfsdriver.o Bst_test.o -o vfs_group21
FileOpns.o: ../src/FileOpns.c ../include/FileOpns.h ../include/Filesystem.h ../include/LinkedList.h ../include/Hashtable.h ../include/Bst.h ../include/nAry.h ../include/freelist.h ../include/Commons.h ../include/dsCreator.h ../include/DirOpns.h ../include/vfs_errorcodes.h
	gcc -c ../src/FileOpns.c
DirOpns.o: ../src/DirOpns.c ../include/DirOpns.h ../include/Filesystem.h ../include/Bst.h ../include/nAry.h ../include/freelist.h ../include/Commons.h ../include/dsCreator.h ../include/vfs_errorcodes.h
	gcc -c ../src/DirOpns.c
Filesystem.o: ../src/Filesystem.c ../include/Filesystem.h ../include/LinkedList.h ../include/Hashtable.h ../include/Bst.h ../include/nAry.h ../include/dsCreator.h ../include/Commons.h ../include/freelist.h ../include/vfs_errorcodes.h
	gcc -c ../src/Filesystem.c
LinkedList.o: ../src/LinkedList.c ../include/LinkedList.h ../include/Filesystem.h ../include/Commons.h
	gcc -c ../src/LinkedList.c
Hashtable.o: ../src/Hashtable.c ../include/Hashtable.h ../include/Filesystem.h ../include/LinkedList.h ../include/Hashtable.h ../include/Commons.h
	gcc -c ../src/Hashtable.c
nAry.o: ../src/nAry.c ../include/nAry.h ../include/Filesystem.h ../include/Commons.h ../include/nAry.h ../include/Bst.h
	gcc -c ../src/nAry.c
Bst.o: ../src/Bst.c ../include/Bst.h ../include/Filesystem.h ../include/Commons.h ../include/nAry.h
	gcc -c ../src/Bst.c
dsCreator.o: ../src/dsCreator.c ../include/dsCreator.h ../include/Filesystem.h ../include/LinkedList.h ../include/Hashtable.h ../include/Bst.h ../include/nAry.h ../include/Commons.h
	gcc -c ../src/dsCreator.c
Commons.o: ../src/Commons.c ../include/Commons.h
	gcc -c ../src/Commons.c
freelist.o: ../src/freelist.c ../include/freelist.h ../include/Filesystem.h
	gcc -c ../src/freelist.c
Bst_test.o: ../src/Bst_test.c ../include/Filesystem.h ../include/Commons.h ../include/Bst.h ../include/Bst_test.h
	gcc -c ../src/Bst_test.c
vfsdriver.o: ../test/vfsdriver.c ../include/FileOpns.h ../include/DirOpns.h ../include/Filesystem.h ../include/vfs_errorcodes.h ../include/Bst_test.h 
	gcc -c ../test/vfsdriver.c
	make vfs_group21
	cp vfs_group21 ../bin/
	rm vfs_group21
	chmod 777 ../bin/vfs_group21
clean:
	rm -f FileOpns.o DirOpns.o Filesystem.o LinkedList.o Hashtable.o nAry.o Bst.o dsCreator.o Commons.o freelist.o vfsdriver.o Bst_test.o ../bin/vfs_group21
	rm -f ../bin/vfs_group21
