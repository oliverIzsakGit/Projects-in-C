#include<stdio.h>
#include<stdlib.h>

#define size 10000 // if you change this value, change the changedSize's value to the same as the size value.
int changedSize =10000;


int* hashTable;
void initialize()
{
   
    hashTable = (int*)malloc(size*sizeof(int));
   for (int i = 0; i < size; i++)
   {
       hashTable[i] = 0;
         // the value 0 cannot be given as data, because everything is automatically set to 0.

   }
         
}
int createKey(int data) {
    if (data == NULL)
    {
        return -1;
    }
    int hashKey=0;  
 
    hashKey = data % size;  // creating the hash key with simple modulo.
    //printf("hash key created for %d  with the key : %d \n", data, hashKey);

    return hashKey;

}
void sizeIncrease()
{
    changedSize = changedSize + size;
    int* newHashTable=(int*)malloc(changedSize*sizeof(int));
    for (int i = 0; i <changedSize-size; i++)
    {
        newHashTable[i] = hashTable[i];
    }
    for (int i = changedSize-size; i < changedSize; i++)
    {
        newHashTable[i] = NULL;
    }

    hashTable = newHashTable;

       
    
    if (hashTable == NULL)
     {
         printf("erorr reallocating\n");
    }
}
int searchHT(int data)
{
    int key = createKey(data);
    int oriKey = key;
    int curr = -1;
    int actualData = NULL;
    int tempSize = 0;
    int currAr = size;
  

    for (int o = 0; o < changedSize / size; o++) // here first i check the most probable place for each section where i can find the key.
    {
        
        if (hashTable[key] == NULL || hashTable[key] == 0) {  break; }
        
        if (hashTable[key] == data)
        {
            //printf("Successfully found data : %d with the  %d key \n", data, key);
            actualData = hashTable[key];
            curr = 0;
            break;
        }
        tempSize += size;
        key = oriKey + tempSize;
        
    }

    if (actualData == NULL)           // here I will try to find them in each section by searching through the array starting from the key(if not found) then from the start until i reach they key
    {
        for(int t=0;t<changedSize/size;t++)
        {
        tempSize = 0;
        key = oriKey;

        for (int i = key + 1; i < currAr; i++)
        {

            if (hashTable[i] == NULL || hashTable[key] == 0) { break; }
            if (hashTable[i] == data)
            {
               // printf("Successfully found data : %d with the  %d key \n", data, i);
                actualData = hashTable[i];
                curr = 0; break;
            }
        }
        if (curr == -1)
        {
            for (int j = currAr - size; j < key; j++)
            {
                if (hashTable[j] == data)
                {
                 //   printf("Successfully found data : %d with the  %d key \n", data, j);
                    actualData = hashTable[j];
                    curr = 0; break;
                }
            }
        }

        currAr += size;
        tempSize += size;
        key = oriKey + tempSize;
    }
    }
    
    if (curr == -1)
    {
        
       // printf("The data %d cannot be found in the hash table\n", data); 
        return NULL;
    }

    return actualData;
}

void insertHT(int data)
{
   
    int key =  createKey(data);

    int originKey = key;
    if(key==-1)
    {
      //  printf("Null input\n");
        return;
    }
    int tempSize = 0;
    int curr = -1;
    

    if (changedSize > size)      // if the size of the hash table was increased atleast once before, then this if statement will run.
    {
            tempSize = changedSize - size;
            key = key + tempSize;
    }
       
  
    if (hashTable[key] == NULL)
    {
        hashTable[key] = data;
        curr = key;
    }
    else
    {
        for (int i = key; i < changedSize; i++)
        {
            if (hashTable[i] == NULL)
            {
                hashTable[i] = data;
                
                curr = i;
                break;
            }
        }
        if (curr == -1)
        {
            for (int j = changedSize-size; j < key; j++)
            {
                if (hashTable[j] == NULL)
                {
                    hashTable[j] = data;
                    curr =j;
                    break;
                }
            }
        }
    }
    if (curr == -1 )
    {
        //printf("The hash table is full\n"); 
        sizeIncrease();
        hashTable[(changedSize-size) + originKey] = data;
        curr = (changedSize - size) + originKey;
          //printf("The data : %d has been successfully stored with the %d key \n", data, curr);
    }
    else
    {
    
      //  printf("The data : %d has been successfully stored with the %d key \n", data, curr);
    }
    
}

void printHT()
{
    

  
        for (int i = 0; i < changedSize; i++)
        {
            printf("Key no. %d  data :  %d\n", i, hashTable[i]);
        }

   
}
/*
void main()
{
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
    insertHT(30);

 searchHT(28);
 
     searchHT(18);

    printHT();


    insertHT(15);
    insertHT(25);
    insertHT(45);
    insertHT(55);
    insertHT(65);
    insertHT(75);
    insertHT(85);
    insertHT(95);
    insertHT(215);
    insertHT(245);
    insertHT(1215);
    insertHT(505);
    insertHT(405);
   
   
    printHT();

    printf("size : %d", changedSize);
    searchHT(55);
    searchHT(505);
    insertHT(505);
  

}
*/
