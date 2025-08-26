#!/bin/bash

# Test 3: Free Functionality
echo "=== Test 3: Free Functionality ==="

gcc -o test_free test_free.c

export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_Testing.so
export DYLD_FORCE_FLAT_NAMESPACE=1

echo "Running free test:"
/usr/bin/time -l ./test_free 2>&1 | grep "page reclaims"

unset DYLD_LIBRARY_PATH
unset DYLD_INSERT_LIBRARIES
unset DYLD_FORCE_FLAT_NAMESPACE

echo ""
# The page reclaims should be significantly lower than the basic malloc test.
