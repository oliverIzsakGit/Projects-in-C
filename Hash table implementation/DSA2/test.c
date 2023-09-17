
#define _CRT_SECURE_NO_WARNINGS
#include  "rbt.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define amount 10000

int value[amount];


void  RBTTest1() {
	

	printf("	RED-BLACK TREE INSERT\n\n");

	int n, value;
	printf("Number of Values: ");
	scanf("%d", &n);
	while (n!=0) {
		printf("Enter value: ");
		scanf("%d", &value);
		red_black_insert(value);
		n--;
	}

	printf("Printing RBT:\n\n");
	tree_print(ROOT, 0);
	printf("\n");

	printf("Search for a value in the tree\n\n");
	printf("Enter value: ");
	scanf("%d", &value);


	if (value == tree_search(value)->key)
	{
		printf("Found it : %d\n", tree_search(value)->key);
	}
	else { printf("Not found\n"); }

	printf("\n");


}
void HashTest1() {


	//init array of list to NULL
	init();

	insert(10);
	insert(1);
	insert(3);
	insert(5);
	insert(8);
	insert(2);
	insert(20);
	insert(36);
	insert(48);
	insert(22);
	insert(17);
    print();
	// searching for 2
	printf("Searching element 22:\n");
	if (search(22)) { 
		printf("Search Found\n"); }
	else
	{
		printf("Search Not Found\n");
	}
	

	return 0;


}

void MyHashTest1() {

	// this is a specific test done with 10 hash table size, also changedSize set to 10.
	initialize();
	insertHT(1);
	insertHT(2);
	insertHT(4);
	insertHT(5);
	insertHT(6);
	insertHT(16);
	insertHT(8); 
	insertHT(18);
	insertHT(20);
	insertHT(30);  // the 10 sized table is full
    searchHT(28);  // we search for a data with a value 28, it says its not found.
    searchHT(18);  // 18 is found
	printHT();
    insertHT(15);  // here we add only values ending with 5, so the modulo is always 5
	insertHT(25);  // we can see that when adding value 15, it increases the table size  from 10 to 20. And then add the value of 15 into the 14th slot in the array.
	insertHT(45);  // we start adding other values that end with 5, and because of closed hashing the values will go into the following slot in the array. 
	insertHT(55); // at one point we reach the end of the list, in this case we start from the 10th, which is val  mod size = 0 slot, and then we start putting them there
	insertHT(65);  // and it continues like this until we are full again, then increase table size again and etc...
	insertHT(75);
	insertHT(85);
	insertHT(95);
	insertHT(215);
	insertHT(245);
	insertHT(1215);
	insertHT(505);
	insertHT(405);
    printHT();
	searchHT(55);
	searchHT(505);
	insertHT(505);
}


void InsertTimeEfficiency() {

	  // dont forget to change the size global variable and changedSize variable in "MyHash.c" file to be the  same as the value in the variable "amount" 
	LARGE_INTEGER freq;
	LARGE_INTEGER sta;
	LARGE_INTEGER end;
	double interval=0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);
	
	for (int i = 0; i < amount; i++) {

		red_black_insert(value[i]);
	}
	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;
	printf("Red Black Tree Insert time efficiency: %fs\n", interval);
	interval = 0;
QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);
for (int i = 0; i < amount; i++) {
		insert(value[i]);
		
	}

QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;


	printf("Open hashing Hash table Insert time efficiency: %fs\n", interval);


	interval = 0;
	
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);
	for (int i = 0; i < amount; i++) {
		insertHT(value[i]);
		
	}

	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;


	printf("Closed hashing Hash table Insert time efficiency: %fs\n", interval);
}



void SearchTimeEfficiency() {
	// dont forget to change the size global variable and changedSize variable in "MyHash.c" file to be the  same as the value in the variable "amount" 
	LARGE_INTEGER freq;
	LARGE_INTEGER sta;
	LARGE_INTEGER end;
	double interval = 0;
	int HashFound = 0;
	int RBTfound = 0;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);
	for (int i = 0; i < amount; i++) {
		if (tree_search(value[i]) != NILL) {
			RBTfound++;
		}
		

	}

QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;
	printf("Red Black Tree search time efficiency: %fs \nAmount of values found: %d\n", interval, RBTfound);
	interval = 0;
QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);

	for (int i = 0; i < amount; i++) {
		if (search(value[i]) == 1)
		{
			HashFound++;
		}

	}
QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;
	printf("Open hashing Hash table search time efficiency: %fs \nAmount of values found: %d\n", interval, HashFound);


	interval = 0;
	HashFound = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&sta);

	for (int i = 0; i < amount; i++) {
		if (searchHT(value[i]) !=NULL)
		{
			HashFound++;
		}

	}
	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - sta.QuadPart) / freq.QuadPart;
	printf("My closed hashing Hash table search time efficiency: %fs \nAmount of values found: %d\n", interval, HashFound);

}
void rotationTest()
{
	red_black_insert(10);// first we add 10, 3, 2 this would form a line, so the red_black_insert_fixup method should fix this imbalance with rotating right
	red_black_insert(3);
	red_black_insert(2);
	tree_print(ROOT, 0); // and we can see it shows that te root is not 10 , but the 3, since it rotated right.
	printf("-----------------------------------\n\n\n");
	red_black_insert(16); // now we want to check rotate left. by adding 2 right values, so it will create a line, which creates imbalance in the tree.
	red_black_insert(19); 
	tree_print(ROOT, 0); // it works since we can see it rotated left, and the 16 replaced 10 and became the parent child of 10 and 19.
	printf("----------------------------------\n\n");

}
void preOrderandInOrderTraversalTest()
{   
	red_black_insert(5);
	red_black_insert(10);
	red_black_insert(16);
	red_black_insert(11);
	red_black_insert(8);
	red_black_insert(1);
	red_black_insert(45);
	tree_print(ROOT, 0); 
	printf("\n\n");
	printf("Inorder: "); // inorder going from smallest to biggest, or from left to right.
	inorder();
	printf("\n");
	printf("preorder: "); // preorder going from the root, then from smallest to biggest, or from left to right
	preorder();
	printf("\n\n");


	printf("-------------------------------------------------\n");

	red_black_insert(87);

	red_black_insert(100);

	red_black_insert(99);
	tree_print(ROOT, 0);
	printf("inorder: ");
	inorder();
	printf("\n");
	printf("preorder: ");
	preorder();
	printf("\n\n");

	printf("------------------------------------------------------\n\n");
}
void collisionTest()
{
	init(); // first scenario
	             // here we can see that the collision is resolved by open hashing, which uses linked list
	insert(0);   // in this scenario we can see that data that has the same hash code will be put into the next available free slot.
	insert(1);   
	insert(3);
	insert(5);
	insert(2);
	insert(4);
	insert(7);
	insert(10);
	insert(11);
	print();

	                
}
void MyCollisionTest()
{   // again this test should be run while the value of the global variable "size" in the MyHash c file is set to 10. and changedSize also set to 10.
	initialize();
	// here we can see that the collision is resolved by closed hashing, which searchers through the hash table to find alternative locations for the data.
	insertHT(6);   // in this scenario we can see that data that has the same hash code will be put into the same array number but it will  be chained to the first
	insertHT(1);   // value that was added there  by a linked list.
	insertHT(3);
	insertHT(5);
	insertHT(2);
	insertHT(4);
	insertHT(7);
	insertHT(9);
	insertHT(10);
	insertHT(11);
	printHT();

	printf("INSERT INTO FULL TABLE \n\n");
	insertHT(16);
	printHT();
	// now the hash table is full, but we want to add another data into it, this will trigger the increaseSize method
					// which means the array size is increased by the same amount of slots as the initial hash table size. eg: Initial HT size 10, after size increase it will be 20.
					// and it will be increasing by 10 every time the increaseSize method is called.
					// Now we again have slots, and we want to add the data with the value of 16.
		// now, we still  want the array to have a good search time, this means we dont just want to add the value 16 to the 11th place in the new array.
			// So this time, we will look at the new added 10 slots as an entirely new Hash Table, so we put the 16 to the 6th slot, which in  initial array will be in the
					// 15th place. (0-9, 10-19)
}
void balanceTest()
{
	
	red_black_insert(5); // first we add 5,10 and after we add 11, the tree becomes imbalanced by 5 and 10 both being red.
	red_black_insert(10);  // it gets fixed up by rotating left, and by changin 5 and 11 to red.
	printf("\n\n1.\n");
	tree_print(ROOT, 0);
	red_black_insert(11);  
	printf("\n\n3.\n");
	tree_print(ROOT, 0);
	red_black_insert(12); // same thing happens after inserting 11. but this time it gets fixed up by only changing the color of 5 and 11 to black, and 5 to also black
	printf("\n\n4.\n");
	tree_print(ROOT, 0);
	printf("\n\n");
}

void main()
{
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;

	ROOT = NILL; 
	
    //RBTTest1();
	//rotationTest();
	//preOrderandInOrderTraversalTest();
	//balanceTest();

	
	//HashTest1();
	//collisionTest();

	//my implementation
	//MyHashTest1();
	//MyCollisionTest();


	// randomized tests
	srand(time(NULL));

	initialize();
	for (int i = 0; i < amount; i++)
	{
		value[i] = (rand() % 999999)+1;
	}
	// have to change the the global variable "size" in the hash.c file and MyHash.c file, to your desired value, so you can change the size of the hash table.
	InsertTimeEfficiency();
		
	//print();
//printHT();
	//tree_print(ROOT,0);
	SearchTimeEfficiency();
	
	
	return 0;
}