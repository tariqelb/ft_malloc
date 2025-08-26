#!/bin/bash

# Test 2: Basic Malloc Efficiency
echo "=== Test 2: Basic Malloc Efficiency ==="

# Compile the test
gcc -o test_basic_malloc test_basic_malloc.c

# Run without your malloc
echo "Running without your malloc:"
/usr/bin/time -l ./test_basic_malloc 2>&1 | grep "page reclaims"

# Run with your malloc
echo "Running with your malloc:"
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=libft_malloc_Testing.so
export DYLD_FORCE_FLAT_NAMESPACE=1
/usr/bin/time -l ./test_basic_malloc 2>&1 | grep "page reclaims"

# Unset variables
unset DYLD_LIBRARY_PATH
unset DYLD_INSERT_LIBRARIES
unset DYLD_FORCE_FLAT_NAMESPACE

echo ""
# Note: Compare the number of page reclaims. Refer to the marking sheet for grading.
