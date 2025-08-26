#!/bin/bash

# Test 1: Check if required symbols are exported
echo "=== Test 1: Symbol Exports ==="

# Use nm to list symbols
NM_OUTPUT=$(nm -D libft_malloc_Testing.so)

# Check for required functions
REQUIRED_SYMS="malloc free realloc show_alloc_mem"
MISSING_SYMS=""

for sym in $REQUIRED_SYMS; do
    if ! echo "$NM_OUTPUT" | grep -q " T $sym"; then
        MISSING_SYMS="$MISSING_SYMS $sym"
    fi
done

if [ -n "$MISSING_SYMS" ]; then
    echo "ERROR: Missing symbols:$MISSING_SYMS"
    exit 1
fi

echo "✓ All required symbols are exported."
echo ""
