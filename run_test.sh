#!/bin/bash
set -e

LIB=./libft_malloc.so
PAGE_SIZE=$(getconf PAGESIZE)

compile_tests() 
{
    echo "[*] Compiling tests..."
    gcc -o test0 ./test/test0.c
    gcc -o test1 ./test/test1.c
    gcc -o test2 ./test/test2.c
    gcc -o test3 ./test/test3.c
    gcc -o test3b ./test/test3b.c
    gcc -o test4 ./test/test4.c
    gcc -o test5 ./test/test5.c -L. -lft_malloc
}

run_time() 
{
    BIN=$1 #test0 or test1 ...
    MODE=$2 #is custom malloc or system malloc
    if [ "$MODE" = "system" ]; then
        /usr/bin/time -v ./$BIN 2>&1
    else
        LD_LIBRARY_PATH=$PWD LD_PRELOAD=$LIB /usr/bin/time -v ./$BIN 2>&1
    fi
}

grade_test1() 
{
	BASE=$1
	MALLOC_FAULTS=$2
	
	if ! [[ $MALLOC_FAULTS =~ ^[0-9]+$ ]]; then
	    echo "Error: MALLOC_FAULTS is not numeric: $MALLOC_FAULTS"
	    exit 1
	fi
	
	PAGES=$(($MALLOC_FAULTS - $BASE))
	echo "[*] Test1 grading: pages used = $PAGES"

	if [ $PAGES -lt 255 ]; then
		echo " -> Grade: 0 (insufficient memory allocated)"
	elif [ $PAGES -ge 1023 ]; then
		echo " -> Grade: 1 (one page per allocation, too much overhead)"
	elif [ $PAGES -ge 513 ]; then
		echo " -> Grade: 2 (overhead too big)"
	elif [ $PAGES -ge 313 ]; then
		echo " -> Grade: 3 (very big overhead)"
	elif [ $PAGES -ge 273 ]; then
		echo " -> Grade: 4 (big overhead)"
	else
		echo " -> Grade: 5 (good overhead)"
	fi
}

compile_tests

echo "================= TEST0 ================="
BASE_FAULTS=$(run_time test0 system | grep "Minor (reclaiming a frame) page faults" | awk '{print $6}')
echo "[system] test0 faults = $BASE_FAULTS"
run_time test0 preload | grep "Minor (reclaiming a frame) page faults"

echo "================= TEST1 ================="
SYS_FAULTS=$(run_time test1 system | grep "Minor (reclaiming a frame) page faults" | awk '{print $6}')
#MALLOC_FAULTS=$(run_time test1 preload | grep "Minor (reclaiming a frame) page faults" | awk '{print $6}')
MALLOC_FAULTS=$(run_time test1 preload | grep "Minor (reclaiming a frame) page faults" | awk '{print $6}' || echo 0)
echo "[system] test1 faults = $SYS_FAULTS"
echo "[malloc] test1 faults = $MALLOC_FAULTS"
grade_test1 $BASE_FAULTS $MALLOC_FAULTS

echo "================= TEST2 (free) ================="
run_time test2 preload | grep "Minor (reclaiming a frame) page faults"

echo "================= TEST3 (realloc) ================="
LD_LIBRARY_PATH=$PWD LD_PRELOAD=$LIB ./test3

echo "================= TEST3b (realloc++) ================="
LD_LIBRARY_PATH=$PWD LD_PRELOAD=$LIB ./test3b

echo "================= TEST4 (errors) ================="
LD_LIBRARY_PATH=$PWD LD_PRELOAD=$LIB ./test4

echo "================= TEST5 (show_alloc_mem) ================="
LD_LIBRARY_PATH=$PWD LD_PRELOAD=$LIB ./test5

rm test0 test1 test2 test3 test3b test4 test5


