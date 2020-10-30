//Linked list implementation

#include<stdlib.h>
#include<stdio.h>

char *p;
int size;
//Book keeping structure (12 bytes)
typedef struct book
{
    int size;
    struct book* next;
    int flag;
}book;

book *h; //Head
void allocate(int n) //Allocates size for global array p and creates first book keeping structure
{
    p = (char*)malloc(n);
    h = (book*)p;
    h->size = n - sizeof(book);
    h->next = NULL;
    h->flag = 0;
}

void* mymalloc(int size)
{
    book *h1 = h;
    book *temp = NULL; //Helps hold the allocated best-fit booking keeping structure
    book *prev = NULL;
    book *new_temp = NULL; //Next booking keeping structure
    while(h1 != NULL) //Finds the first free memory if it exists
    {
        if(!h1->flag && h1->size>=size)
        {
            temp = h1;
            break;
        }
        h1=h1->next;
    }

    if(temp == NULL)
        return NULL;
    
    while(h1 != NULL) //Finds best-fit memory block
    {
        if(!h1->flag && h1->size>=size && h1->size<temp->size)
        {
            temp = h1;
        }
        h1=h1->next;
    }

    if(temp->size == size) //If size available is equal to size to be allocated
    {
        temp->flag = 1;
    }
    else if(temp->size > size+sizeof(book))
    {
        temp->flag = 1;
        new_temp = (book*)(temp + sizeof(book) + size);
        new_temp->size = temp->size - sizeof(book) - size;
        new_temp->flag = 0;
        new_temp->next = temp->next;
        temp->next = new_temp;
        temp->size = size;
    }
    else
    {
        temp->flag = 1;
    }
    return (void*)temp;
}

void myfree(void *b)
{
    book* b1 = (book*)b;
    if(b1 == NULL)
        return;
    book *prev = h;
    if(b1 != h) //If given book structure is not the first book keeping structure
    {
        while(prev->next != b1)
            prev = prev->next;
    }
    book *next = b1->next;

    if(b1 == h) //Given book structure is the first book structure
    {
        if(next != NULL && next->flag == 0) //If the next book structure is free, merge the blocks
        {
            b1->size += next->size + sizeof(book);
            b1->flag = 0;
            b1->next = next->next;
        }
        else if(next != NULL && next->flag == 1) //If next book structure is not free
        {
            b1->flag = 0;
        }
    }
    else if(b1->next == NULL) //Given book structure is the last book structure
    {
        if(prev->flag == 0) //If the previous book structure is free, merge the blocks
        {
            prev->next = NULL;
            prev->size += sizeof(book) + b1->size; 
        }
        else if(prev->flag == 1) //If the previous book structure is not free
        {
            b1->flag = 0;
        }
    }
    else //Given book structure is the intermidiate book structure
    {
        if(prev->flag == 0 && next->flag == 0) //If both the previous and next book structure is free, merge the blocks
        {
            prev->next = next->next;
            prev->size += 2*sizeof(book) + b1->size + next->size;
        }
        else if(prev->flag == 1 && next->flag == 0) //If only the next book structure is free, merge the blocks
        {
            b1->size += next->size + sizeof(book);
            b1->flag = 0;
            b1->next = next->next;
        }
        else if(prev->flag == 0 && next->flag == 1) //If only the previous book structure is free, merge the blocks
        {
            prev->next = b1->next;
            prev->size += sizeof(book) + b1->size;
        }
        else //If no blocks are free around the given book structure
        {
            b1->flag = 0;
        }
    }
}
void print_book() //Prints size of book keeping structure
{
    printf("%d\n", sizeof(book));
}
void display_mem_map()
{
    int a=0;
    book* curr = h;
    printf("start_addr\tblock_in_bytes\tstatus\n");
    while(curr != NULL)
    {
        printf("%d\t%d\tBook\n",a,sizeof(book)); //Print book size
        a += sizeof(book);
        if(curr->flag == 1) //Check if allocated
        {
            printf("%d\t%d\tAllocated\n",a,curr->size);
        }
        else if(curr->flag == 0) //Check if free
        {
            printf("%d\t%d\tFree\n",a,curr->size);
        }
        a += curr->size;
        curr = curr->next;
    }
}