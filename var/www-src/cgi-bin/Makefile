OUTFILE="ls"
CGIOUTFILE="public/cgi-bin/${OUTFILE}"
TESTFILE="run-tests"

all: directory.o entry.o formatter.o
	gcc main.c directory.o entry.o formatter.o -o ${OUTFILE}

cgi: directory.o entry.o formatter.o
	gcc cgi.c directory.o entry.o formatter.o -o ${CGIOUTFILE}

directory.o: directory.c directory.h
	gcc -c directory.c

entry.o: entry.c entry.h
	gcc -c entry.c

formatter.o: formatter.c formatter.h
	gcc -c formatter.c

test: directory.o entry.o formatter.o
	gcc test.c formatter.o directory.o entry.o -o ${TESTFILE}
	./${TESTFILE}

pkg: clean
	mkdir -p pkg
	tar cvfz "pkg/${OUTFILE}-v`cat public/VERSION`.tar.gz" public

clean:
	rm -rf *.o
	rm -f ${TESTFILE}
	rm -f ${OUTFILE}
	rm -f ${CGIOUTFILE}
