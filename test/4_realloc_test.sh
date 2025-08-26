#!/bin/bash

# Test 4: Realloc Functionality
echo "=== Test 4: Realloc Functionality ==="

gcc -o test_realloc test_realloc.c

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_Testing.so
export DYLD_FORCE_FLAT_NAMESPACE=1

echo "Expected output: 'Bonjour' printed twice."
./test_realloc

unset DYLD_LIBRARY_PATH
unset DYLD_INSERT_LIBRARIES
unset DYLD_FORCE_FLAT_NAMESPACE

echo ""
