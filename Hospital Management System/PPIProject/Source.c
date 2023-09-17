#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE* v(FILE* fr)
{
	
	if ((fr = fopen("patients.txt", "r")) == NULL)  // check if i can open the file
	{
		printf("Error!Could not open file.\n");     // error if not and exit the program
		exit(0);
		
	}
	else
	{ 
		int itemTypeCounter = 1;      // counter for counting the number of rows, where the row of name is equal to 1, and date is equal to 6  
		int i = 0;            // i for counting in the if statements.
		char stringsFromFile[1000]; // contains the strings from the file
		do {
			int yearOfBirth = 0;      // contains when the person was born, for value checking purposes.
			fgets(stringsFromFile, 1000, fr);  // here I go through all the item types, with the use of the itemTypeCounter, and check the values for
											  // for each item type. When the itemTypeCounter gets to row 7, which is an empty row, it resets to 0.
			if (itemTypeCounter == 1) {
				
				 i = 0;
				while (1) // here I check the char is the name, so that they only contain letters and spaces. and it doesn't contain more then 50 chars.
				{
					if ((stringsFromFile[i] < 'A' && stringsFromFile[i] != ' ') || (stringsFromFile[i] > 'Z' && stringsFromFile[i] < 'a') || (stringsFromFile[i] > 'z'))
					{
						printf("Wrong input for name. Closing the program."); fclose(fr); return NULL; break;
					};
					i++;
					if (i == 52) { printf("Wrong input for name. Closing the program."); fclose(fr); return NULL; break; }
					if (stringsFromFile[i] == '\n') { break; };
				}
				printf("name: ");
			}
				else if (itemTypeCounter == 2)  // here i check the personal numbers, i convert the strings  into long long int, so i don't get overflow
				                              // then i check if its divisible by 11 or whether the personal number is equal to 10, if not the close the program, and i get the birth year of the    
			{									// person and put it into the yearOfBirth variable which I will use in the date later on.
				long long int personalNumber = atoll(stringsFromFile);
				i = 0;
				
				while (1)
				{
					if (stringsFromFile[i] == '\n') { break; };
					i++;
					
				}
				
				
				if (personalNumber % 11 != 0  || i!=10) { printf("Wrong input for personal number. Closing the program."); fclose(fr); return NULL; }
				if (i == 10) {	
					int yearz = 0; if ((((stringsFromFile[0] - 0) * 10) + (stringsFromFile[1] - 0)) > 20) { yearz = 1900; }
					else { yearz = 2000; }
					yearOfBirth = yearz + ((stringsFromFile[0] - 0) * 10) + (stringsFromFile[1] - 0); 
				}
				
				
				printf("personal number: "); 
			}
				else if(itemTypeCounter==3) { // here i check the diagnosis if it contains only 1 capital letter on the first place and ints on the second and third
				i = 0;
				if(stringsFromFile[0]< 'A' || stringsFromFile[0]>'Z' || (stringsFromFile[1]<'0' || stringsFromFile[1] > '9') || (stringsFromFile[2]<'0' || stringsFromFile[2] > '9')){ printf("Wrong input for diagnosis. Closing the program."); fclose(fr); return NULL; }
				if(stringsFromFile[3]!='\n'){ printf("Wrong input for diagnosis. Closing the program."); fclose(fr); return NULL; }
				printf("diagnosis: "); 
				
				while (1) {

			if (stringsFromFile[i] == '\n') { break; };
					if (i == 4) { printf("Wrong input for diagnosis. Closing the program."); fclose(fr); return NULL; break; }
		 i++;
				}
				
			}
				else if (itemTypeCounter == 4) {  // checking whether the row only contains 50 or below 50 chars.
				i = 0;                                
				while (1) {


					if (i == 51) { printf("Wrong input for examination. Closing the program."); fclose(fr); return NULL; break; }
					if (stringsFromFile[i] == '\n') { break; }; i++;
				}
				printf("examination: "); }
				else if(itemTypeCounter==5) { // here i check whether the values are between 1000 and 0 and have on 4 decimal numbers
				i = 0;
				int decimalCounter = 0;
				int decimaboolean = 0;
				double examNumbers = strtod(stringsFromFile, 0); // i convert the string to double
				
				if (examNumbers > 1000 || examNumbers < 0) { printf("Wrong input for examination. Closing the program."); fclose(fr); return NULL; }
				while (1)
				{
					if (stringsFromFile[i] == '\n') { break; };
					if (decimaboolean == 1) { decimalCounter++; }   
					if (stringsFromFile[i] == '.') { decimaboolean = 1; } //if a decimal point has been found, the value of decimalboolean becames 1
																		 // which means in the next loop it will decimalcounter will start couting 
																		//	the number of numbers after the decimal point.
					if (decimalCounter > 4) { printf("Wrong input for examination. Closing the program."); fclose(fr); return NULL; break; };
					
					 i++;
				}

				printf("result: "); }
				else if (itemTypeCounter == 6) {
					i = 0;
					
					while (1) {   // i check if the number of chars equals to 8, 8 is the date format, and +1 is the \n or \0 at the end of the row. 
						int eachNumberOfTheDate; 
						eachNumberOfTheDate = stringsFromFile[i];
						  i++;
						
						 if (eachNumberOfTheDate == '\n' || eachNumberOfTheDate == '\0') { if (i != 9) { printf("Wrong input in \"date: \". Closing the program. "); fclose(fr); return NULL; }break; };
					}
					printf("date: "); // here i check the month(only check if months is bigger than 31), day and year, with a lots of if statements.
					for (int j = 6; j < 8; j++) { printf("%c",stringsFromFile[j]); }
					if ((stringsFromFile[6] >= '3' && stringsFromFile[7]>'1')  || stringsFromFile[6]>'3') { printf("Wrong input in \"date: day\". Closing the program. "); fclose(fr); return NULL; }
					printf("."); 
					for (int j = 4; j < 6; j++) { printf("%c", stringsFromFile[j]); }
					if ((stringsFromFile[4] >= '1' && stringsFromFile[5] > '2') || stringsFromFile[4] >'2') { printf("Wrong input in \"date: month\". Closing the program. "); fclose(fr); return NULL; }
					printf(".");
					int yearOfTheData = 0; // for getting the year when the data was written, i need it to compare it to the birth of the patient
					for (int j = 0; j < 4; j++) { printf("%c", stringsFromFile[j]); yearOfTheData = (atoi(stringsFromFile))/10000; }
					
					if (yearOfBirth>yearOfTheData) { printf("Error ! Wrong input in \"date: year \". Closing the program. "); fclose(fr); return NULL; }
				
					printf("\n");
					
					
					
				}
				else { itemTypeCounter = 0; } // reset the counter at the empty line.
				if (itemTypeCounter != 6) { printf("%s", stringsFromFile); } // i print out the row from the txt file, unless if it is the date, 
																// then I don't because i have that in the itemtyepcounter if statement.
				itemTypeCounter++;
				if (feof(fr)) {       // end of the line, I break out from the loop, 
					
					fseek(fr, 0, SEEK_SET);
					break;
				}



				
			} while (1);
			
	}
	fflush(fr);
	return fr;

}
FILE* o(FILE* fr)
{
	int m;
	scanf(" %d", &m);
	char** arrayD = NULL;        // array for storing the diagnoses
	int* counterArray = NULL;         // array for storing which diagnose has been found more than once
	int countTheStrings = 0;               // int for counting how many patients are in the file.
	  char text[130];               
	  rewind(fr);
	int amountOfEmptyLines = 0;        
	while (1)          // loop which goes through the file, and takes out a row, after that i increase the counter by one, if the counter
						// can be divided by 7  that means, we found an empty line, so i increase the empty line counter by one.
	{						// if end of file, then i increase the counter one more time before break.
		fgets(text, 130, fr);
		countTheStrings++; 
		if (countTheStrings%7==0) { amountOfEmptyLines++; }
		if (feof(fr)) { countTheStrings++; break; }
		

	}
	countTheStrings = (countTheStrings-amountOfEmptyLines) / 6; // here i substract the number of empty lines, and divide by 6 , which is the amount of information
																// about the patients, so I get how many patients there are in the file.
	
	  
	rewind(fr);
 

	arrayD = (char**)malloc(countTheStrings * sizeof(char*));  //I allocate memory to both of the arrays, which will have a size of the amounts of patients we had in the list
	counterArray = (int*)malloc(countTheStrings * sizeof(int));
   int counter = 2;          // counter for every 6th row, which is where the date is.
   text[103];      
   int dateFromFile;  // long long int this is where i convert the date string which i scan from the file.
   int counter1 = 5;      // counter for every third row , which is where the diagnosis is.
   int counter2 = 0;      // counter for the counterArray.
  
  
	do {							// i go through the text file with a do while loop
		
		fgets(text,103,fr);  
		
	      if(counter1%7==0) {  // if its true that means i am in the row where the diagnosis is.
										// which means i allocate a space in the arrayD for this string, and put it in.
									
			  arrayD[counter2] = (char*)malloc(110 * sizeof(char*));
			  
			 strcpy(arrayD[counter2],text);
			 
			 
		  }
		 
		if (counter % 7 == 0) { // if its true that means i am in the row where the date is
				
				
				dateFromFile= atoi(text); // this turns the date string into a int. so i can compare it to the one given as a parameter
			if (dateFromFile < m) { // if it is smaller than m, that means its before the m date, which means i have to store it.
				
				if(counter2==0){ counterArray[counter2] = 0; } // this if statement,for the first time I put a diagnosis in the array, because the loop wouldn't go the first time.
				else{
					for (int i = 0; i < counter2; i++) // loop to check whether the other diagnoses in the array are identical,
					{													// if they are, i don't assign it to the array but make it null, and just increase the number in the integer array at that [i]'s place by one, 
						if (strcmp(arrayD[i],arrayD[counter2])==0) {  // I also decerement  the counter for the diagnosis array, since the one I got and matched with a previous one  shouldn't count as actually finding one
							arrayD[counter2] = NULL;
							counterArray[i]++; 
							counter2--;
							
						} else { counterArray[counter2] = 0; } // if they are not identical, then  I just give it 0 value in the array.
					}
				}
					
				
				counter2++; // at the end i incerement the counter for the diagnosis array, so when i get the next one, it will go to the next place in the array-


				 } else { arrayD[counter2]=NULL;  // here I delete the diagnosis , this should only happen, if the diagnosis I found at the third
				 }															// line , while reading the file, is later (at the 7th line) found out that the date above the given in the parameter.
		}																	// because I don't want store that diagnosis, since its irrelevant.
		if (feof(fr)) {
			
			break;
		}
		counter++;
		counter1++;   
		
	} while (1);
	
	 int v = 0; int max = 0;   // simple max value finder loop
	for (int i = 0; i < counter2;i++)
	{
		if (max < counterArray[i]) { max=counterArray[i]; v = i; }

	}
	 // and here i print out if i found a diagnosis, and if yes, then which one is it.
	if (arrayD[v] == NULL) { printf("The program has found no patients until the date of  %d\n",m); } 
	printf("Most examined diagnosis for date %d is : %s", m,arrayD[v]);
	
     // here i  free the arrays.
	for(int i=0; i<counter2;i++)
	{
		arrayD[i] = NULL;
		free(arrayD[i]);
	}
	arrayD = NULL;
	free(arrayD);
	counterArray = NULL;
	free(counterArray);
	
	return fr;
}
FILE* n(FILE* fr, char*** arrayName, int** arrayDate, double** arrayResult, long long int** arrayPN, char*** arrayDiag, char*** arrayExam,int* sizeOfArrays)
{
	int countTheStrings = 0;               // int for counting how many patients are in the file.
	char justStrings[130];
	rewind(fr);
	int amountOfEmptyLines = 0;
	while (1)          // loop which goes through the file, and takes out a row, after that i increase the counter by one, if the counter
						// can be divided by 7  that means, we found an empty line, so i increase the empty line counter by one.
	{						// if end of file, then i increase the counter one more time before break.
		fgets(justStrings, 130, fr);
		countTheStrings++;
		if (countTheStrings % 7 == 0) { amountOfEmptyLines++; }
		if (feof(fr)) { countTheStrings++; break; }


	}
	countTheStrings = (countTheStrings - amountOfEmptyLines) / 6;
	*sizeOfArrays =countTheStrings;  // here i return the size of the arrays by this pointer
	if ((*arrayName) != NULL) {
		// deallocatinG
		for (int i = 0; i < countTheStrings; i++)
		{
			(*arrayName)[i] = NULL;
			free((*arrayName)[i]);
		}
		(*arrayName) = NULL;
		for (int i = 0; i < countTheStrings; i++)
		{
			(*arrayDiag)[i] = NULL;
			free((*arrayDiag)[i]);
		}
		(*arrayDiag) = NULL;
		for (int i = 0; i < countTheStrings; i++)
		{
			(*arrayExam)[i] = NULL;
			free((*arrayExam)[i]);
		}
		(*arrayExam) = NULL;

		free((*arrayName));
		free((*arrayDiag));
		free((*arrayExam));

		(*arrayPN) = NULL;
		free((*arrayPN));

		(*arrayDate) = NULL;
		free((*arrayDate));

		(*arrayResult) = NULL;
		free((*arrayResult));


	}
	(*arrayName) = (char**)malloc(countTheStrings * sizeof(char*)); // char
	(*arrayDiag) = (char**)malloc(countTheStrings * sizeof(char*));
	(*arrayExam) = (char**)malloc(countTheStrings * sizeof(char*)); 


	(*arrayPN) = (long long int*)malloc(countTheStrings * sizeof(long long int));
	(*arrayResult) = (double *)malloc(countTheStrings * sizeof(double));
	(*arrayDate) = (int*)malloc(countTheStrings * sizeof(int));
	rewind(fr);


	int itemTypeCounter = 1;      // counter for counting the number of rows, where the row of name is equal to 1, and date is equal to 6  
	int iNa = 0;            // i counter for every array.
	int iDi= 0;
	int iEx = 0;
	int iPn = 0;
	int iRe= 0;
	int iDa = 0;
	char stringsFromFile[103]; // contains the strings from the file
	while(1) {
		
		fgets(stringsFromFile, 103, fr);  // here I go through all the item types, with the use of the itemTypeCounter, and check the values for
										  // for each item type. When the itemTypeCounter gets to row 7, which is an empty row, it resets to 0.
		if (itemTypeCounter == 1) //name
		{
			(*arrayName)[iNa] = (char*)malloc(103 * sizeof(char*));

			strcpy((*arrayName)[iNa], stringsFromFile);
			
			iNa++;
		}
		else if (itemTypeCounter == 2)  // here i check the personal numbers, i convert the strings  into long long int, so i don't get overflow
									  // then i check if its divisible by 11 or whether the personal number is equal to 10, if not the close the program, and i get the birth year of the    
		{									// person and put it into the yearOfBirth variable which I will use in the date later on.
			long long int personalNumber = atoll(stringsFromFile);
			

			(*arrayPN)[iPn] = personalNumber;
		
			iPn++;
			
			
		}
		else if (itemTypeCounter == 3) { // here i check the diagnosis if it contains only 1 capital letter on the first place and ints on the second and third
			(*arrayDiag)[iDi] = (char*)malloc(5 * sizeof(char*));

			strcpy((*arrayDiag)[iDi], stringsFromFile);
	
			iDi++;
			
		}
		else if (itemTypeCounter == 4) {  // checking whether the row only contains 50 or below 50 chars.
			
			(*arrayExam)[iEx] = (char*)malloc(52 * sizeof(char*));

			strcpy((*arrayExam)[iEx], stringsFromFile);
			
			iEx++; 
		}
		else if (itemTypeCounter == 5) { // here i check whether the values are between 1000 and 0 and have on 4 decimal numbers
			
			
			double resultDouble = strtod(stringsFromFile,NULL);
		
			
			(*arrayResult)[iRe] = resultDouble;
			
			iRe++;
			
		}
		else if (itemTypeCounter == 6) {
			

			
			int datetInt = atoi(stringsFromFile);



			(*arrayDate)[iDa] = datetInt;
			
			iDa++;

		



		}
		else { itemTypeCounter = 0; } // reset the counter at the empty line.
		
		itemTypeCounter++;

		
		
		if (feof(fr)) {       // end of the line, I break out from the loop, 


			break;
		}
	

	}
	return fr;

}

void s(long long int** arrayPN, char*** arrayExam, double** arrayResult,int arraySize)
{
	long long int pn = NULL;
	char string[11];
	scanf("%s", &string);
	pn = atoll(string);
	int pointInArray;
	for (int i = 0; i < arraySize; i++) // with for loop i go through the  array of personal numbers, if it is the same as the one given as parameter
	{									// then i 
		if ((*arrayPN)[i] == pn) {
			
			printf("For the personal number %s :\n The examination was: %s The result was: %.4lf ", string, (*arrayExam)[i], (*arrayResult)[i]);
			break;

		}

	}
	
	
}

	
void h(int arraySize,long long int** arrayPN, char*** arrayDiag)
{
	char diagnosis[5];

	scanf("%s", &diagnosis);
	strncat(diagnosis, "\n", 1);
	int arraylistMales[150] = { 0 };   // age groups from 0 to 150 
	int arraylistFemales[150] = { 0 };
	int actualAgeOfPatient = 0;            
	for (int i = 0; i < arraySize; i++)
	{                                                   
		if (strcmp((*arrayDiag)[i],diagnosis) == 0) {  // to check if the diagnosis matches with one in the array
			int age1 = (int)(((*arrayPN)[i]) / 1000000);            // if yes then i divide the personal number of that patient, by 1000 000 ,so i get the last 4 digits
			int maleOrFemaleIdentifier = age1 % 10;                            //i get the first digit with a modulo 10
				age1 = age1 / 10;                                // reassign the age1 variable with age1 minus the last digit, which is the one i took away with modulo 10
			maleOrFemaleIdentifier += (age1 % 10) * 10;						// here i again modulo the reassigned age ,multiply it by 10 and add it to the maleOrFemaleIdentifier variable, which now contains the the birth month of the individual	
			age1 = age1 / 10;            // here i divide the age1 again, which will now contain the last 2 digits of the year the individual was born
			if (age1 > 20) { actualAgeOfPatient = 2020 - (1900 + age1); }  // here if it is above 20 then it means we are talking about someone born before in the 19's
			else { actualAgeOfPatient = 2020 - (2000 + age1); }     // if it is below 20 then I assume it was born in the 20's
			
			if (maleOrFemaleIdentifier > 31) { arraylistFemales[actualAgeOfPatient]++; }  // females have +50 added to their month digits in the pn so if the variable is bigger then 31 that means that individual is a female
			else { arraylistMales[actualAgeOfPatient]++; }


		}
		


	}
	printf("list of male patients:\n");
	for (int i = 0; i < 150; i++)
	{
		if (arraylistMales[i] > 0) { printf("%d : %d\n", i, arraylistMales[i]); }
	}

	printf("list of female patients:\n");
	for (int i = 0; i < 150; i++)
	{
		if (arraylistFemales[i] > 0) { printf("%d : %d\n ", i, arraylistFemales[i]); }
	}
	

}
void p(FILE* fr, int arraySize, long long int** arrayPN, char*** arrayExam, int** arrayDate,char*** arrayDiag, char*** arrayName, double** arrayResult)
{
	char exam[52];
	int date;
	long long int personalNumba;
	double resu;
    char string[11];
	
	
	
	scanf("%s %s %d", &string, &exam, &date );
	strncat(exam, "\n", 1);
	personalNumba = atoll(string);
	scanf("%lf", &resu);
	double prevResult = 0;
	for (int i = 0; i < arraySize; i++)                // with the if statement i find the person with the examination, and change the result to the one given as parameter
	{
		if ((*arrayPN)[i] == personalNumba && strcmp((*arrayExam)[i], exam) == 0 && (*arrayDate)[i] == date)
		{
			
			prevResult = (*arrayResult)[i];
			(*arrayResult)[i]= resu;
			
			break;
		}
	}
	fclose(fr);               // here I close the filE, and open it again so I can write into it.
	fr = fopen("patients.txt", "w");
	for (int i = 0; i < arraySize; i++)
	{ // here check the personalnumber because it is possible for them to start with 000, 00 ,0 and the long long it ignores that when i change it from string.
		// so here i check these 3 options and fprintf a 0 before the personal number, depending on how much they are missing
		
		if((*arrayPN)[i]>1000000 && (*arrayPN)[i] < 10000000) { fprintf(fr, "%s%d%d%d%lld\n%s%s%g\n%d", (*arrayName)[i],0,0,0, (*arrayPN)[i], (*arrayDiag)[i], (*arrayExam)[i], (*arrayResult)[i], (*arrayDate)[i]); }
		else 		if ((*arrayPN)[i] > 10000000 && (*arrayPN)[i] < 100000000) { fprintf(fr, "%s%d%d%lld\n%s%s%g\n%d", (*arrayName)[i], 0, 0, (*arrayPN)[i], (*arrayDiag)[i], (*arrayExam)[i], (*arrayResult)[i], (*arrayDate)[i]); }
		else if ((*arrayPN)[i] > 100000000 && (*arrayPN)[i] < 1000000000) { fprintf(fr, "%s%d%lld\n%s%s%g\n%d", (*arrayName)[i], 0, (*arrayPN)[i], (*arrayDiag)[i], (*arrayExam)[i], (*arrayResult)[i], (*arrayDate)[i]); }
		else 
		fprintf(fr, "%s%lld\n%s%s%g\n%d", (*arrayName)[i], (*arrayPN)[i], (*arrayDiag)[i], (*arrayExam)[i],(*arrayResult)[i], (*arrayDate)[i]);

		if (i == arraySize - 1) { break; } // if i am the last iteration in the loop, i break it so that the last \n 's wont be written out.
		fprintf(fr, "\n");
		fprintf(fr, "\n");
	}
	printf("The patient's result with the personal number %s  for the diagnosis %s has been modified  from %g to %g \n", string, exam, prevResult, resu);
	fclose(fr);                           // i close the file and open it for reading only, so that the functions called next time wont show error.
	fr = fopen("patients.txt", "r");
	
}

void z(int arraySize, char*** arrayExam, int** arrayDate, char*** arrayName, double** arrayResult)
{
	char exam[52];
	int date;
	int date2;

	scanf("%d %d %s", &date, &date2, &exam);  // i scan the values,
	strncat(exam, "\n", 1);
	if (date > date2) { printf("Error. The end date is smaller than the starting date.\n"); return; }            // check whether the date is smaller then date2,if no then i return.
	double max1 = -1;        // create 3 double variables, to later store the max values.
	double max2 = -1;
	double max3 = -1;
	for (int i = 0; i < arraySize; i++) // loop, check whether the dates and exams match, if yes then i take the value of that result, and put it in the
	{									// max1 variable, if not then max2 , if its smaller than that too, then into max 3.
		if ((*arrayDate)[i] > date && (*arrayDate)[i] < date2 && strcmp((*arrayExam)[i], exam) == 0) {
			if ((*arrayResult)[i] > max1) { max3 = max2; max2 = max1; max1 = (*arrayResult)[i]; }
			else {
				if ((*arrayResult)[i] > max2) {
					max3 = max2;
					max2 = (*arrayResult)[i];
				}
				else {
					if ((*arrayResult)[i] > max3)
					{
						max3 = (*arrayResult)[i];
					}
				}

			}
		}

	}
	int placeOfTheMaxInTheArray1 = -1;         // storing the place in the array in these variables, where the max values happened, so i can find their corresponding patient name
	int placeOfTheMaxInTheArray2 = -1;
	int placeOfTheMaxInTheArray3 = -1;
	for (int i = 0; i < arraySize; i++)
	{
		if ((*arrayResult)[i] == max1) { placeOfTheMaxInTheArray1 = i; }
		if ((*arrayResult)[i] == max2) { placeOfTheMaxInTheArray2 = i; }
		if ((*arrayResult)[i] == max3) { placeOfTheMaxInTheArray3 = i; }
	}
	if (max1 > -1) { printf("%s (%g)\n ", (*arrayName)[placeOfTheMaxInTheArray1], max1); }
	if (max2 > -1) { printf("%s (%g)\n ", (*arrayName)[placeOfTheMaxInTheArray2], max2); }
	if (max3 > -1) { printf("%s (%g)\n ", (*arrayName)[placeOfTheMaxInTheArray3], max3); }

}


int main() {
	FILE* fr=NULL;
	int arraySize = 0;         // size of the array , which is the number of patients, gets reinitialized after n has been called.
	int* pointerToSize = &arraySize;
	char** arrayName = NULL;
	long long int* arrayPN = NULL;
	char** arrayDiag = NULL;
	char** arrayExam = NULL;
	double* arrayResult = NULL;
	int* arrayDate = NULL;
    char cc[1];
	while (1)
	{
		

		scanf("%s", &cc);   
		
		  
		if (strcmp(cc, "v") == 0)  // if the scanned char is v i run the v function which gives back a file and if that file is null then I exist the pogram
		{
			fr=v(fr);
			if (fr == NULL) { exit(EXIT_SUCCESS); }
			
	    }
		else 

		if (strcmp(cc, "o") == 0)   //if the scanned char is o I run the o function, wich takes in a file and a date. To call this function the V function 
		{											// has to be called before, to open the file.

		
			if (fr == NULL) { printf("The File is closed. Open it with \"v\""); }
			else
			fr=o(fr);
			
			
		}
		else 
		if (strcmp(cc, "n") == 0)   {
		

			if (fr == NULL) { printf("The File is closed. Open it with \"v\""); }
			else
				fr=n(fr,&arrayName,&arrayDate,&arrayResult, &arrayPN, &arrayDiag,&arrayExam,pointerToSize);
		
			
			



		}
		if (strcmp(cc, "s") == 0) {

			
			if (fr == NULL || arrayName == NULL) { printf("The fields are not created\n"); }
			
			else
				s(&arrayPN, &arrayExam, &arrayResult, arraySize);


		}
		if (strcmp(cc, "h") == 0) {

			
			
			if (fr == NULL || arrayName == NULL) { printf("The fields are not created\n"); }
			else
				h(arraySize,&arrayPN,&arrayDiag);


		}

		if (strcmp(cc, "p") == 0) {

		
			
			if (fr == NULL || arrayName == NULL) { printf("The fields are not created\n"); }
			else
				p(fr,arraySize,&arrayPN,&arrayExam, &arrayDate, &arrayDiag, &arrayName,&arrayResult);


		}

		if (strcmp(cc, "z") == 0) {



			if (fr == NULL || arrayName == NULL) { printf("The fields are not created\n"); }
			else
				z( arraySize, &arrayExam, &arrayDate, &arrayName, &arrayResult);


		}
		if (strcmp(cc, "k") == 0) {



			if (fr == NULL || arrayName == NULL) { printf("The fields are not created\n"); }
			else

			{
				for (int i = 0; i < arraySize; i++)
				{
					(arrayName)[i] = NULL;
					free((arrayName)[i]);
					(arrayDiag)[i] = NULL;
					free((arrayDiag)[i]);
					(arrayExam)[i] = NULL;
					free((arrayExam)[i]);

				}
				(arrayName) = NULL;
				(arrayDiag) = NULL;
				(arrayExam) = NULL;
				(arrayPN) = NULL;
				(arrayDate) = NULL;
				(arrayResult) = NULL;
				free(arrayName);
				free(arrayDiag);
				free(arrayExam);
				free(arrayPN);
				free(arrayDate);
				free(arrayResult);
			}


		}
	}
}