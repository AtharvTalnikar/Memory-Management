# Memory-Management
Allocation and handling of memory
The allocation policy implemented by you
    - Best fit allocation

Basic logic used while implementing the policy
    - Consider each book keeping structure as a node of a linked list. Each structure holds the size it can allocate/allocated and a pointer to the next structure.
      Going through all the free memory blocks, a best-fit block is located and allocated. While freeing the program also makes sure that no consecutive free blocks of
      memory exist.If any such cases are found, those blocks will be merged.

Explanation of the book keeping structure
    - Each book keeping structure has three componenets
      a) int size - size available for that book structure
      b) struct book* next - Points to the next adjacent book structure in the global array.
      c) int flag - To check if the block of memory is free or allocated
                    0 - free
                    1 - allocated

Key takeaway from this assignment
    - I understood how memory management works and how to use memory efficiently. Helped me understand how malloc() works. Learnt how to allocate memory and how malloc() returns "void" pointer. 
      I also learnt about the working of free() and how to efficiently de-allocate memory space.
