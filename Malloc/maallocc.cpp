
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void* mem; // memory pointer which is global.


struct header  // header containing the size of the memory block, and a pointer to the next memory block
{
	int size;
	header* next;
};

header* bestFitStrategy(int size) { // this method is for finding the smallest memory block that fits the size.

	struct header** localMem = (header**)&mem;
	struct header* bestFit = NULL;
	int  tempSize = 0, i = 0, checkUniqueCase = 0;
	printf("Starting best fit algorithm...\n");

	while (checkUniqueCase==0) { // we are looping through the memory until we end up at the beginning.
		if ((*localMem)->next == (header*)mem) {  checkUniqueCase = 1; } // if the main header is equal to the current one
		if (-((*localMem)->size) >= size) {
			if (-((*localMem)->size) == size) { bestFit = (*localMem); break; }
			if (i == 0)
			{   //we take the first header that can contain the memory, and we keep it in that block until we find a more suitable one.
				tempSize= -((*localMem)->size);
				bestFit = (*localMem);
			}
			if (-((*localMem)->size) < tempSize ) 
			{
				bestFit = (*localMem);
				tempSize = -((*localMem)->size);
			}
			
			i++;
		}

		localMem = &(*localMem)->next;   
	}
	if (bestFit != NULL) {  // if we found one we negate before returning so it will be positive, since its allocated from now on.
		bestFit->size = -(bestFit->size);
		printf("The algorithm found a free memory with the size of: %d \n", (bestFit->size));
	}
	return bestFit;
}
void* memory_alloc( int size)
{
	if (size <= 0) return NULL;
	int moreSpace;
	header* memAlloc;
	header* newHeader;
	printf("\n\n\nMemory allocation starting...\n");
	printf("Trying to allocate %d byte of memory\n",size);

	memAlloc = bestFitStrategy(size);// returns null if no available space

	if (memAlloc == NULL)
	{
		printf("Memory is full.\n\n");
		return memAlloc;
	}


	moreSpace = memAlloc->size - size ;
 
	if (moreSpace > sizeof(header)) { //
		printf("Memory allocated\n");
		if(moreSpace>0) { printf("Fragmentation occured\n"); } else { printf("No fragmentation occured\n"); }
		printf("Remaining unallocated memory within the block : %d byte\n", moreSpace);
		printf("Creating new block of memory from the remaining %d byte of space\n",moreSpace);
		newHeader = (header*)((char*)memAlloc + size + sizeof(header)); //create a new header and unallocated memory block. 
		newHeader->next = memAlloc->next;
		newHeader->size = ((-moreSpace) + sizeof(header));
		memAlloc->size -= moreSpace;
		memAlloc->next = newHeader; 
		printf("New header created:\n size : %d byte \n size of new unallocated memory block: %d  byte\n", sizeof(header), -(newHeader->size));
	}

		 if (moreSpace <= 0) { printf("The memory has been fully allocated.\nNo fragmentation occured.\n"); }
	if(moreSpace > 0 && moreSpace <= sizeof(header)) { printf("The memory has been fragmented. \n There is %d byte of space left that cannot be allocated\n", moreSpace); }
	
	
	
	return memAlloc + 1  ;  // pointer to the memory block coming after the header.
}
int coalesce(header** memFree) { //  defragmentation
	int size, nextCounter = 0;
	
	size = -((*memFree)->size);
	
	printf("Memory defragmantation in process...  \n");
	printf("Checking the surrounding blocks of memory for coalescing...\n");
	if ((*memFree)->next != (header*)mem && (*memFree) != (header*)mem) { // we check whether the memory we want to free is the header memory, or whether the next is the header memory, if yes then we wont look at next and previous.

	if ((*memFree)->next->size < 0) {// if the next block of memory is free
	
		printf("Found free memory in next block. Size of memory: %d\n", -((*memFree)->next->size) + sizeof(header));

		size = (size + ((*memFree)->next->size - sizeof(header)));   // add the next blocks memory size and its header size into our current freed memory.
		(*memFree)->next = (*memFree)->next->next;                   // change its next to the next one's next
		
		printf("Overall freed memory size : %d \n", -size);
		
	}
	
	header* tempPointer = (*memFree)->next;
	
	int sizeOFThePrev = 0;
	
	while (tempPointer->next != (*memFree))  // here I go through the circular linked list until I get the memory block that comes before the current one
	{
		tempPointer = tempPointer->next;
		
		sizeOFThePrev = (tempPointer)->size;
	}
	
	if (sizeOFThePrev < 0 )
	{
		
		printf("Found free memory in previous block. Size of memory: %d\n", -(sizeOFThePrev) + sizeof(header));
		size = (size + (sizeOFThePrev - sizeof(header)) );
		
		tempPointer->next = (*memFree)->next;
		tempPointer->size = size;
		printf("Overall freed memory size : %d \n", -size);
	}
	}
	else 	printf("Overall freed memory size : %d \n", -size);

	return (size); // here we convert it to negative , since negative numbers mean unallocated memory.
}
// check if the pointer is valid
int memory_check(void* ptr)
{
	header** localMem = (header**)&mem;
	if (ptr == NULL) {  return 0; }

	int checkUniqueCase = 0; // this is for the situation when a header actually points to the main header, which means we went through all the headers and we came back to the first one, the checkUniqueCase makes sure  that we check the last header before it would break the loop. 
	while ( checkUniqueCase == 0) { 
		if ((*localMem)->next == (header*)mem) { checkUniqueCase = 1; }
		
		if (((char*)ptr - sizeof(header)) == (char*)(*localMem) && (*localMem)->size > 0)// checking if we can find that pointer in our memory and whether it has allocated memory in it, if yes then returns a 1 so we can free that memory.
		{
			printf("Memory authentication...\n");
			printf("Valid memory address\n");
			return 1;
		}
		localMem = &(*localMem)->next;
	}
	
	
	printf("Invalid memory address\n ");

	return 0;
}
 int memory_free(void* valid_ptr)
 {
	 int check;
	 printf("Starting memory free process\n");
	 check = memory_check(valid_ptr);
	
	 if (check == 1) {
		
		 int size;
		 header* memory;
		 memory= (header*)((char*)valid_ptr - sizeof(header));
		 size = coalesce(&memory);

		 printf("Memory freeing process done.\nAmount of memory freed: %d\n", -size);
		 memory->size = size;
		 return 0;
	 }

	 return 1;
 }
 

 void memory_init(void* ptr, unsigned int size)
 {
	 mem = ptr;
	 header* headermem;
	 
	 unsigned int actualSize = size - sizeof(struct header);
	 if (actualSize > 0 && mem != NULL)
	 {
		 headermem = (struct header*)mem;    // structure pointer to the memory.
		 headermem->size = -((int)actualSize);     // unallocated or free memory is going to be negative, and allocated is gonna be positive
		 headermem->next = headermem;
		 printf("Memory initialization ... \n Memory initialized. \n Free memory: %d\n Header size: %d\n", -(headermem->size), sizeof(header));
	 }
 }
 
 // test 1 - specific test 
//			 part 1- Testing allocation 
//			 part 2 - Testing  free.
 //          part 3- Testing defragmentation.

 /*
int main()
 { 
	//part1
	// This specific test only works if the regionsize is 100.
	int const regionSize = 100;
	
	 char region[regionSize];
	 memory_init(region, regionSize);
	 char* pointer[5];
	 int allocatedMem = 0;
	 int  headerMem = 0;

		 pointer[0] = (char*)memory_alloc(15);
		 if (pointer[0]) {
			 memset(pointer[0], 0, 15);
			 allocatedMem += 15;
			 headerMem += 8;
		 }
		 
		 pointer[1] = (char*)memory_alloc(10);
		 if (pointer[1]) {
			
			 memset(pointer[1], 0, 10);
			 allocatedMem += 10;
			 headerMem += 8;
		 }
		
		 pointer[2] = (char*)memory_alloc(1);
		 if (pointer[2]) {
			 memset(pointer[2], 0, 1);  
			allocatedMem += 1;
			headerMem += 8;
		 
		 }
		
		 pointer[3] = (char*)memory_alloc(22);
		 if (pointer[3]) {
			 memset(pointer[3], 0, 22);
			 allocatedMem += 22;
			 headerMem += 8;
		 }
		  //this wont work. memory full
		 pointer[4] = (char*)memory_alloc(300);
		 
		
		 
		 printf("Test for memory allocation : allocated: %d,headerspace: %d  =  %d\n\n", allocatedMem, headerMem, allocatedMem+headerMem);
		
				 pointer[4] = (char*)memory_alloc(8);
				 if (pointer[4]) {
					 memset(pointer[4], 0, 8); 
					 allocatedMem += 8;
					 headerMem += 8;
				 }
		// part3 coalesce testing and free
				 printf("\nTESTING COALESCE\n\n\n");
				 memory_free(pointer[2]);
				 allocatedMem -= 1;
				 
				 memory_free(pointer[3]);
				 allocatedMem -= 22;
				 headerMem -= 8;
				 memory_free(pointer[1]);
				 allocatedMem -= 10;
				 headerMem -= 8;
				
				 //with these 3 frees that are next to each other i was able to free up 33 bytes of space from the memory blocks
				 // + another a 16 bytes of space from 2 headers. So right now I have 49 bytes of free memory.
				 // and another 4 bytes of fragmented memory.
				 //Now  I will allocate 41 bytes of memory so I can get more fragmented memory.
				 pointer[1] = (char*)memory_alloc(41);
				 memset(pointer[1], 0, 41);
				 allocatedMem += 41;
				 // This way I get another 8 bytes of fragmented memory
				 // meaning I have 12 bytes of fragmented memory now.
				 //now i free the memory i just allocated
				 //If I try to allocate 6 bytes of memory. Even though in an ideal solution I have enough space for it.
				 // I cant do it here, because they are fragmented.
				 pointer[1] = (char*)memory_alloc(6);
				 // as you can see it says the memory is full.
				 
				 printf("\n\nAllocated blocks of memory:  %d \nallocated headers : %d\nAll memory used: %d \nAllocated blocks percentage compared to the ideal solution: %d / %d = %0.2f \nPercentage of actual memory space allocated(excluding headers): %d / %d = %0.2f\nPercentage of fragmented memory space %d / %d = %0.2f\nPercentage of header memory space %d / %d = %0.2f\n", 
					 allocatedMem, headerMem, allocatedMem+headerMem, allocatedMem + headerMem,regionSize, ((double)(allocatedMem + headerMem))/regionSize, regionSize,allocatedMem, ((double)(allocatedMem))/ ((double)(regionSize)), (regionSize - (allocatedMem + headerMem)), regionSize, ((double)(regionSize - (allocatedMem + headerMem)))/(double)regionSize,headerMem,regionSize,(double)headerMem/(double)regionSize );
				// 

	

	 return 0;
 
}


*/

//TEST 2

 int main() //test with random values no frees.
 {
	 time_t t;
	 int allocatedMem = 0;
	 int headerMem = 0;
	 int const min = 500;   // here change minimum to 500 and max to 5000 or 8-50000 
	 int const max = 5000;
	 int const regionSize = 100000;  // here change regionsize to 50/100/200 or 50000+
	 int const n = (regionSize / (sizeof(header) + min)) + 1;  // amount of times to run the for loop
	 
	 char region[regionSize];
	 memory_init(region, regionSize);
	 char* pointer[n];
	 int count = 0;
	 srand((unsigned)time(&t));
	 for (int i = 0; i < n; i++) {
		 int mem = min + rand() % (max - min) + 1;


		 pointer[i] = (char*)memory_alloc(mem);

		 if (pointer[i] != NULL) {
			 memset(pointer[i], 0, mem);
			 headerMem += 8;
			 allocatedMem += mem;

			 count++;
		 }
		


	 }
	 printf("\n\nAllocated blocks of memory:  %d \nallocated headers : %d\nAll memory used: %d \nAllocated blocks percentage compared to the ideal solution: %d / %d = %0.6f \nPercentage of actual memory space allocated(excluding headers): %d / %d = %0.6f\nPercentage of fragmented memory space %d / %d = %0.6f\nPercentage of header memory space %d / %d = %0.6f\n",
		 allocatedMem, headerMem, allocatedMem + headerMem, allocatedMem + headerMem, regionSize, ((double)(allocatedMem + headerMem)) / regionSize, allocatedMem, regionSize, ((double)(allocatedMem)) / ((double)(regionSize)), (regionSize - (allocatedMem + headerMem)), regionSize, ((double)(regionSize - (allocatedMem + headerMem))) / (double)regionSize, headerMem, regionSize, (double)headerMem / (double)regionSize);
	 
	 printf("done\n");
 }
 
// TEST 3
/*
int main() // test where we allocate random values then free and then allocate random values again.
{
time_t t;
int const regionSize = 50000;  // here change regionsize to 50/100/200 or 50000+
int const n = 100;  // here you can give how many times you want to allocate memory.
int const min = 8;   // here change minimum to 500 and max to 5000 or 8-50000 
int const max = 5000;
char region[regionSize];
memory_init(region, regionSize);
char* pointer[n];
int allocatedMem = 0;
int headerMem = 0;
int count = 0;
int memoryList[n] = {0};
srand((unsigned)time(&t));
for (int i = 0; i < n; i++) {
	int mem = min + rand() % (max - min) + 1;


	pointer[i] = (char*)memory_alloc(mem);

	if (pointer[i] != NULL) {
		memset(pointer[i], 0, mem);
		memoryList[count]=mem;
		allocatedMem += mem;
		headerMem += 8;
		
	
		count++;
	}

	

}
if ((regionSize - (allocatedMem + headerMem) > 8)) {
	int fragment = (regionSize - (allocatedMem + headerMem));
	memoryList[count] = -(fragment - 8);
	headerMem += 8;
	
printf("\n\nAllocated blocks of memory:  %d \nallocated headers : %d\nAll memory used: %d \nAllocated blocks percentage compared to the ideal solution: %d / %d = %0.2f \nPercentage of actual memory space allocated(excluding headers): %d / %d = %0.2f\nPercentage of fragmented memory space %d / %d = %0.2f\nPercentage of header memory space %d / %d = %0.2f\n",
	allocatedMem, headerMem, allocatedMem + headerMem, allocatedMem + headerMem, regionSize, ((double)(allocatedMem + headerMem)) / regionSize, allocatedMem, regionSize, ((double)(allocatedMem)) / ((double)(regionSize)), (regionSize - (allocatedMem + headerMem)), regionSize, ((double)(regionSize - (allocatedMem + headerMem))) / (double)regionSize, headerMem, regionSize, (double)headerMem / (double)regionSize);
// 
int freeMem = 0;
for (int z = 0; z < (n-10)/2; z++)
{
		
	if (count != freeMem) {
		int ptr = memory_free(pointer[freeMem]);
		memoryList[freeMem] = -memoryList[freeMem];
		allocatedMem += memoryList[freeMem];

	
		freeMem += 2;
	} 

	
}
printf("\n\nAllocated blocks of memory:  %d \nallocated headers : %d\nAll memory used: %d \nAllocated blocks percentage compared to the ideal solution: %d / %d = %0.2f \nPercentage of actual memory space allocated(excluding headers): %d / %d = %0.2f\nPercentage of fragmented memory space %d / %d = %0.2f\nPercentage of header memory space %d / %d = %0.2f\n",
	allocatedMem, headerMem, allocatedMem + headerMem, allocatedMem + headerMem, regionSize, (((double)(allocatedMem + headerMem))*100) / regionSize, allocatedMem, regionSize, (((double)(allocatedMem))*100) / ((double)(regionSize)), (regionSize - (allocatedMem + headerMem)), regionSize, (((double)(regionSize - (allocatedMem + headerMem)))*100) / (double)regionSize, headerMem, regionSize, (((double)headerMem)*100) / (double)regionSize);
// 
for (int i = 0; i < n; i++) {
	int mem = min + rand() % (max+1 - min) ;
	int count1 = 0; // how many different memory blocks i have allocated
	int countPoint = 0; // showing the exact memory block im in.
	int bestFit = 0;
	int c = 0;
	pointer[i] = (char*)memory_alloc(mem);
	
	if (pointer[i] != NULL) {
		memset(pointer[i], 0, mem);
		
		while (memoryList[count1] != 0) {
		
			if (-(memoryList[count1]) >= mem) {
				if (-(memoryList[count1]) == mem) { bestFit = -(memoryList[count1]);  break; }
				if (c == 0)
				{

					bestFit = -(memoryList[count1]);
					countPoint = count1;
				}
				if (-(memoryList[count1]) < -bestFit)
				{
					bestFit = -(memoryList[count1]);
					countPoint = count1;
				}

				c++;
			}
			count1++;

		}
		if (bestFit != 0) {
			
			if ((bestFit - mem) > 8) { memoryList[countPoint] = mem; allocatedMem += mem; headerMem += 8; memoryList[count++] = ((bestFit - mem) - 8);
			}
			else
			{
				memoryList[countPoint] = mem;
				allocatedMem += mem;
				
			}

			
		}
	}


}
printf("\n\nAllocated blocks of memory:  %d \nallocated headers : %d\nAll memory used: %d \nAllocated blocks percentage compared to the ideal solution: %d / %d = %0.2f \nPercentage of actual memory space allocated(excluding headers): %d / %d = %0.2f\nPercentage of fragmented memory space %d / %d = %0.2f\nPercentage of header memory space %d / %d = %0.2f\n",
	allocatedMem, headerMem, allocatedMem + headerMem, allocatedMem + headerMem, regionSize, ((double)(allocatedMem + headerMem)) / regionSize, allocatedMem, regionSize,  ((double)(allocatedMem)) / ((double)(regionSize)), (regionSize - (allocatedMem + headerMem)), regionSize, ((double)(regionSize - (allocatedMem + headerMem))) / (double)regionSize, headerMem, regionSize, (double)headerMem / (double)regionSize);
// 
printf("done\n");


 }
 */
