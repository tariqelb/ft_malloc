#!/bin/bash

# Test 5: Error Handling
echo "=== Test 5: Error Handling ==="

gcc -o test_errors test_errors.c

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_Testing.so
export DYLD_FORCE_FLAT_NAMESPACE=1

echo "Expected output: 'Bonjour' with no errors or crashes."
./test_errors

unset DYLD_LIBRARY_PATH
unset DYLD_INSERT_LIBRARIES
unset DYLD_FORCE_FLAT_NAMESPACE

echo ""
