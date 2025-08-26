#!/bin/bash

# Test 6: show_alloc_mem
echo "=== Test 6: show_alloc_mem Output ==="

# Compile with explicit linking to your library
gcc -o test_show_mem test_show_mem.c -L. -lft_malloc_Testing

export DYLD_LIBRARY_PATH=.
echo "Expected: A formatted output with TINY, SMALL, LARGE zones and total bytes."
./test_show_mem

unset DYLD_LIBRARY_PATH

echo ""
