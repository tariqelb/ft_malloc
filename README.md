# Project Overview

This project is about re-implementing the `malloc`, `realloc`, and `free` functions.  

## What I Learned from the Project

In this project, while implementing `malloc`, I understood several things about RAM, swap, paging, and page reclaim.  

### My Approach to Implementing malloc

When you call `malloc`, you reserve a block of memory in RAM. Internally, `malloc` often ends up calling `mmap` to reserve memory.  
To reduce the overhead caused by multiple calls to `mmap`, requested sizes are categorized into three types:  
- **Tiny** (less than `N` bytes)  
- **Small** (between `N` and `M` bytes)  
- **Large** (greater than `M` bytes)  

For tiny and small allocations, the first call reserves multiple pages at once (e.g., for tiny allocations we might reserve `16 * 4096` bytes, assuming a 4 KB page size). Subsequent calls of the same type reuse these pre-allocated pages until the zone is full. When it’s full, new pages are allocated.  

Large allocations are handled differently: because the requested size is big, we allocate directly with `mmap` for the exact number of bytes requested.  

### RAM and Swap

During my implementation, I discovered that the main role of **swap** is to store pages that are inactive or less frequently used. This frees space in RAM, which is much faster than disk. Inactive pages are moved to swap and recalled when needed.  

On a 64-bit architecture, even if the physical RAM is 64 GB, the kernel can let processes address much more — for example, up to 128 TiB.  
This is explained by **soft and hard memory limits**:  
- The **soft limit** is how much memory a process can use by default.  
- The **hard limit** is the maximum value to which the soft limit can be raised.  

This works because only **active pages** need to stay in RAM, while inactive ones are swapped out or discarded. That’s how the system can give the illusion of more memory than the actual physical RAM.  

### RAM and Programs
When writing a program, it’s important to minimize unnecessary memory access.  
An operating system runs many programs simultaneously, and they all compete for RAM. The more processes that need memory at the same time, the more overhead the OS has to manage, which can slow down performance.  

Since RAM is limited, efficient programs should carefully manage memory — especially when using functions like `malloc` (reserving memory, reading, and writing to it). Reducing unnecessary allocations and memory operations helps lower pressure on RAM and improves overall system performance.  

### Running the Main Test on Linux

#### 1. Compile the library  

```bash
make
```

#### 2. Compile `main` with the library  

```bash
gcc main.c -L. -lft_malloc -o main
```

#### 3. (Optional) Compile `main` without the library  

```bash
gcc main.c -o main
```

#### 4. Force preload of the library at runtime  

````bash

LD_LIBRARY_PATH=$PWD LD_PRELOAD=$PWD/libft_malloc.so ./main

````

#### 5. Described the entire sequence of events

Request: A block of memory is requested (e.g., via malloc).

Return: A virtual address (A) is returned to the program.

Access: A read/write operation is attempted on virtual address A.

Check: The CPU (its MMU) checks the page table for a mapping for the page containing address A.

Fault: The mapping does not exist, so the CPU triggers a page fault and transfers control to the OS kernel.

Kernel Action: The kernel handles the fault:
It finds a free physical page frame in RAM (let's say it starts at physical address N).
It updates its Virtual Memory Area (VMA) structures to note that this range of virtual addresses is now valid and backed by RAM. (This is the "new rule" you mentioned).

Map: The kernel adds an entry into the page table: "The virtual page containing address A is now mapped to the physical page frame starting at address N."

Resume: The kernel returns control to the program. The CPU restarts the instruction.

Success: The CPU checks the page table again, finds the new mapping, and the read/write operation finally completes, accessing the physical RAM at location N + offset.
