FILES :=                              \
    .travis.yml                       \
    Voting.c++                       \
    Voting.h                         \
    RunVoting.c++                    \
    RunVoting.in                     \
    RunVoting.out                    \
    TestVoting.c++                   \
    TestVoting.out	                  \
    TestVoting.out					  
	#collatz-tests/myk235-RunCollatz.in   
    #collatz-tests/myk235-RunCollatz.out  
    #collatz-tests/myk235-TestCollatz.c++ 
    #collatz-tests/myk235-TestCollatz.out 
    #Collatz.log                       
    #html     

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunVoting
	rm -f RunVoting.tmp
	rm -f TestVoting
	rm -f TestVoting.tmp

config:
	git config -l

scrub:
	make clean
	rm -f  Voting.log
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunVoting.tmp TestVoting.tmp

html: Doxyfile Voting.h Voting.c++ Voting.c++ TestVoting.c++
	doxygen Doxyfile

Voting.log:
	git log > Voting.log

voting-tests:
	git clone https://github.com/cs371p-fall-2015/voting-tests.git

Doxyfile:
	doxygen -g

RunVoting: Voting.h Voting.c++ RunVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ RunVoting.c++ -o RunVoting

RunVoting.tmp: RunVoting
	./RunVoting < RunVoting.in > RunVoting.tmp
	diff RunVoting.tmp RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ TestVoting.c++ -o TestVoting $(LDFLAGS)

TestVoting.tmp: TestVoting
	$(VALGRIND) ./TestVoting                                       >  TestVoting.tmp 2>&1
	$(GCOV) -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.tmp
	$(GCOV) -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.tmp
	cat TestVoting.tmp
