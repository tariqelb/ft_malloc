#!/bin/bash

# 
echo "Max tiny zone size is 64 time 100 equal to 6400 and page zone size is 64 * 4096 equal 262144"
echo "Max small zone size is 131071 time 100 equal to 1310710 and page zone size is 1024 * 4096 equal 4194304"

echo "-------------------------------------------"
head -n 34 ./ft_malloc.h | tail -n 7
echo "-------------------------------------------"
head -n 70 ./ft_allocate_new_page.c | tail -n 28

echo "-------------------------------------------"
