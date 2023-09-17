#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct ani             //structure containing all the informations about animals
{
	char name[50];
	char species[30];
	int height;
	double weight;
	int birthday;
	int lastfed;
	char zookeeper[50];
	struct ani* next;
}ANIMALZ;
FILE* n(FILE *fr,ANIMALZ** list, int *sizeOfArrays)  
{
	int counter = 0;
	if (list != NULL) {               
		ANIMALZ* act = NULL,*help;
	                                     
		act = (*list);
		while (act != NULL)
		{


			help = act;
			act = act->next;
			help->next = NULL;
			free(help);
		}
	}
	if ((fr = fopen("animals.txt", "r")) == NULL) 
	{
		printf("Records cannot be loaded!\n");     
		exit(0);

	}
	else
	{
		char stringsFromFile[100];
		
		int  i = 0;
		ANIMALZ*newNode= NULL;

		do {
			fgets(stringsFromFile, 100, fr);
			if (strcmp(stringsFromFile, "$$$\n") == 0 || strcmp(stringsFromFile, "$$\n")==0)  // if the read line contains $$ that means ,a new animal is coming in the list
			{  counter++;                                                             // so this is where i increment the animal countr
				fgets(stringsFromFile, 100, fr);
				
				if (i==-1){                               // if true, then that means there is another animal coming, so  new memory should be allocated to the node
				newNode->next= (ANIMALZ*)malloc(sizeof(ANIMALZ));		// and also make the old node so it points to the next one.
				newNode = newNode->next;
				} else newNode = (ANIMALZ*)malloc(sizeof(ANIMALZ));
				i = 0;  //reset the 0, for the new node.
				
				
				
			}	// with the if statements, i just scan each line from the txt file and copy them to the nodes.
			if (i == 0) { strcpy(newNode->name, stringsFromFile);  }  
			else if (i == 1) {
				strcpy(newNode->species, stringsFromFile);  
			}
			else if(i==2){ newNode->height = atoi(stringsFromFile);
			}
			else if(i==3){
				char* ptr=NULL;
				newNode->weight = strtod(stringsFromFile,ptr); 
			}
			else if(i==4){ newNode->birthday = atoi(stringsFromFile); 
			}
			else if(i==5){ newNode->lastfed = atoi(stringsFromFile);
			}
			else if(i==6){ strcpy(newNode->zookeeper, stringsFromFile); 
		 
			
			fgets(stringsFromFile, 2, fr);// check if the next line is empty, or there are more animals coming.
			if (stringsFromFile[0]== '$') {  i = -2; }   //if yes then i make i equal to -2
			else { newNode->next = NULL;  strncat(newNode->zookeeper, "\n", 1); } // if not, then i put the next node to be null, 
			
			}

			
			
			
			if ((counter == 1) && ((i == 6) || i==-2)) {  (*list) = newNode; }  // if true, that means we have the first animal from the list, and we scanned
																		// all the informations including the zookeeper, and we put this node to be the head node of the list.
			
			if (feof(fr)) {       // end of the line, I break out from the loop, 

				fseek(fr, 0, SEEK_SET);
				break;
			}
			i++;
		} while (1);
	}
	printf("loaded %d records", counter);
	*sizeOfArrays = counter;          // bring back the size of the list, through the pointer
	return fr;
}

void v(ANIMALZ** list)
{
	if ((*list) != NULL) {
		ANIMALZ* act = NULL;
		int i = 1;
		act = (*list);
		while (act != NULL)
		{
			printf("%d. \nname: %sSpecies: %sHight: %d\nWeight: %.2lf\nBirthday: %d\nDate of the last feeding: %d\nZookeepers name: %s", i, act->name, act->species, act->height, act->weight, act->birthday, act->lastfed, act->zookeeper);
			act = act->next;
			i++;
		}
	}
}
int p(ANIMALZ** list,int listsize)
{
	int place;
	char name[52];
	char species[32];
	int height;
	double weight;
	int birthday;
	int lastfed;
	char zookeeper[52];

	
	// here is a compllicated scanf that makes it  possible to input spaces to the name, species and zookeeper strings.
	scanf("%d %50[0-9a-zA-Z ] %30[0-9a-zA-Z ]  %d %lf %d %d %50[0-9a-zA-Z ]", &place,name,species,&height,&weight,&birthday,&lastfed,zookeeper); 
	if (place <= 0) { printf("Wrong input for the place in the list\n"); return; } // here i check if the place  is 0, then i end the function

	ANIMALZ* newNode = (ANIMALZ*)malloc(sizeof(ANIMALZ));    //malloc
	ANIMALZ* lastNode = *list;                            // make a lastnode and make it euqal to the headnode;

	int k = 0;
	// here i add \n to the strings, so it looks nice.
	strncat(name, "\n",1);
	strncat(species, "\n", 1);
	strncat(zookeeper,"\n", 1);
	 // put the values into the node.
	strcpy(newNode->name, name);
	
	strcpy(newNode->species,species);
	newNode->height=height;
	newNode->weight=weight;
	newNode->birthday=birthday;
	newNode->lastfed=lastfed;
	strcpy(newNode->zookeeper,zookeeper);
	newNode->next = NULL;
	if (place > listsize )   // if the listsize is  bigger than the amount of nodes in the list, then it is added to the end
	{
		
		if (*list == NULL) { *list = newNode; return; }
		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
			
		}
		
		lastNode->next = newNode;
		
	}
	else if (place == 1) // if i want to add it to the first place,  i just switch the headnode with the new one
	{
		newNode->next = (*list);
		(*list) = newNode;

	}
	else // i go throught the list if it null and add the new node where it is needed.
	{
		ANIMALZ* current = NULL;
		ANIMALZ* prev= NULL;
		int i = 1;
		current = (*list);
		while (current != NULL)
		{
			
		 
		  if (i == place) {
			  newNode->next = current;
			  prev->next = newNode;
			  
			  break;
		  }
		  prev = current;
		  current = current->next;
			i++;
			
		}
		
	}
	listsize++;
	return listsize;
}
int z(ANIMALZ **list,int listSize)
{
	char name[52];
	scanf(" %50[0-9a-zA-Z ]", name);                 // this part is to make sure the function is not case-sensitive for the animal name.
	for (char* pointer = name; *pointer != '\0'; ++pointer) {
		*pointer = tolower(*pointer);
	}
	strcat(name, "\n", 1);
	
	ANIMALZ* temp = NULL;
	temp = (*list);
	ANIMALZ* prev = NULL;
	int i = 1;
	while (temp != NULL)
	{
		
		char toLower[52];
		
		strcpy(toLower, temp->name);                 // make the name of the animal also lower case, so i can compare them easily
			for (char* pointer = toLower; *pointer != '\0'; ++pointer) {
				*pointer = tolower(*pointer);
			}
			
			if (strcmp(toLower,name) == 0)
			{
				
				if(i==1)  
				{
					
					if (listSize == 1) { free((*list)); (*list) = NULL; }
					(*list) = temp->next;  // if listsize is bigger than 1 then I free the current head node,and just make the the second node the head node
				}
				else if (i==listSize)  
				{
					prev->next = NULL;
					free(temp);
				}
				else 
				{
					
					prev->next = temp->next;
						free(temp);
					
				}
				
				listSize--;
				
				break;
			}
			prev = temp;                // i go throught the nodes
			temp = temp->next;
			i++;
			
	}
	
	return listSize;
}
void a(ANIMALZ **list,int listSize)
{
	char name[52];
	int feedTime;
	scanf(" %50[0-9a-zA-Z ] %d", name,&feedTime);
	strncat(name, "\n", 1);
	ANIMALZ* temp = NULL;
	temp = (*list);
	int i = 0;
	
	while (temp != NULL)                  
	{
		if (strcmp(temp->name, name) == 0)  // compare the names, and if it matches the feedtime gets updated
		{
			
			temp->lastfed = feedTime;
			i = 1;
			break;
		}

		
		temp = temp->next;


	}
	if (i == 0) { printf("No animal with the name: %s exists in the list\n", name); }
	else { printf("%s was fed %d last time\n", name, feedTime); }
}
void otoc_zoznam(ANIMALZ** list,int n)
{
	ANIMALZ* curr = (*list);
	ANIMALZ* prev = NULL;
	ANIMALZ* next = NULL;
	if (n == 0 || n == 1) { return; }
	while (curr != NULL) {
		
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
(*list) = prev;
}
void m(ANIMALZ** list, int size)
{
	int max1 = -1;
	int max2 = -1;
	int max3 = -1;
	char* animal1[50];
	char* animal2[50];
	char* animal3[50];


	if ((*list) == NULL) { printf("Zaznamy neboli nacitane."); return; }

	ANIMALZ* checkList = NULL;
	checkList = (*list);
	for (int i = 0; i < size; i++)
	{
		int k = 0;
		int counter = 0;
		while (1)
		{
			if (checkList->name[k] == '\0' || checkList->name[k] == '\n') { break; }
			if (checkList->name[k] == 'a' || (checkList)->name[k] == 'A' || (checkList)->name[k] == 'e' || (checkList)->name[k] == 'E' || (checkList)->name[k] == 'i' || (checkList)->name[k] == 'I'
				|| (checkList)->name[k] == 'o' || (checkList)->name[k] == 'O' || (checkList)->name[k] == 'u' || (checkList)->name[k] == 'U' || (checkList)->name[k] == 'y' || (checkList)->name[k] == 'Y')
			{
				counter++;

			}
			k++;
		}
		if (max1 == -1) { max1 = counter; strcpy(animal1, (checkList)->name); }
		else if (max2 == -1 && max1 > counter) { max2 = counter; strcpy(animal2, (checkList)->name); }
		else if (max3 == -1 && max2 > counter) { max3 = counter; strcpy(animal3, (checkList)->name); }


		if (counter > max1) { strcpy(animal3, animal2), strcpy(animal2, animal1); strcpy(animal1, (checkList)->name); }
		else if (counter > max2) { strcpy(animal3, animal2); strcpy(animal2, (checkList)->name); }
		else if (counter > max3) { strcpy(animal3, (checkList)->name); }

		checkList = checkList->next;


	}
	printf("Top 3 animals with most vowels in their name: \n%s%s%s\n", animal1, animal2, animal3);
}
void h(ANIMALZ** list, int size)
{
	int dateOfFeeding;
	scanf("%d", &dateOfFeeding);



if ((*list) != NULL) {
		ANIMALZ* act = NULL;
		int i = 1;
		act = (*list);
		while (act != NULL)
		{
			if (act->lastfed < dateOfFeeding)
			{
				printf("%d. \nname: %sSpecies: %sHight: %d\nWeight: %.2lf\nBirthday: %d\nDate of the last feeding: %d\nZookeepers name: %s", i, act->name, act->species, act->height, act->weight, act->birthday, act->lastfed, act->zookeeper);
				i++;
			}act = act->next;
			
		}
	}
}

int main()
{
	FILE* fr = NULL;
	ANIMALZ *list = NULL;
	int listSize = 0;
	int* pointerToListSize = &listSize;

	char cc[1];
	while (1)
	{


		scanf("%s", &cc);


		if (strcmp(cc, "n") == 0)  // if the scanned char is v i run the v function which gives back a file and if that file is null then I exit the pogram
		{
			fr = n(fr,&list, pointerToListSize);
			if (fr == NULL) { exit(EXIT_SUCCESS); }
			
		}
		
		if (strcmp(cc, "v") == 0)
		{

			 v(&list);

		}
		if (strcmp(cc, "p") == 0)
		{
			listSize =p(&list,listSize);
		}
		if (strcmp(cc, "z") == 0)
		{
			listSize=z(&list, listSize);
		}
		if (strcmp(cc, "a") == 0)
		{
			a(&list, listSize);
		}
		if (strcmp(cc, "h") == 0)
		{
			h(&list, listSize);
		}

		if (strcmp(cc, "w") == 0)
		{
			m(&list, listSize);
		}

		if (strcmp(cc, "k") == 0)
		{

			
			ANIMALZ* next;

			while (list != NULL) // go throught the list and free each node.
			{
				next = list->next;
				free(list);
				list = next;
			}
			
		}
		

	}

}