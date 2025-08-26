#!/bin/bash

# Test 0: Check Environment and Compilation
echo "=== Test 0: Environment & Compilation ==="

# 1. Check for author file
echo "Checking for author file..."
if [ ! -f "author" ]; then
    echo "ERROR: No author file found."
    exit 1
fi

# 2. Check Makefile rules
echo "Checking for Makefile..."
if [ ! -f "Makefile" ]; then
    echo "ERROR: No Makefile found."
    exit 1
fi

echo "Testing 'make' rule..."
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "ERROR: 'make' rule failed."
    exit 1
fi

echo "Testing 'make clean' rule..."
make clean > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "ERROR: 'make clean' rule failed."
    exit 1
fi

echo "Testing 'make re'..."
make re > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "ERROR: 'make re' rule failed."
    exit 1
fi

# 3. Check library and symlink creation
echo "Checking library file naming convention..."
export HOSTYPE="Testing"
make re > /dev/null 2>&1

if [ ! -f "libft_malloc_Testing.so" ]; then
    echo "ERROR: Library not named correctly (libft_malloc_\$HOSTYPE.so)."
    exit 1
fi

if [ ! -L "libft_malloc.so" ]; then
    echo "ERROR: Symbolic link 'libft_malloc.so' not created."
    exit 1
fi

# Check what the symlink points to
LINK_TARGET=$(readlink -f libft_malloc.so)
if [ "$LINK_TARGET" != "$(pwd)/libft_malloc_Testing.so" ]; then
    echo "ERROR: Symlink points to wrong target."
    exit 1
fi

echo "✓ All preliminary checks passed."
echo ""
