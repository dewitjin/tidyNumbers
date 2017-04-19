#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/**
	Dewi Tjin
	Problem B. Tidy Numbers

	Problem

	Tatiana likes to keep things tidy. Her toys are sorted from smallest to largest,
	her pencils are sorted from shortest to longest and her computers from oldest to newest.
	One day, when practicing her counting skills, she noticed that some integers,
	when written in base 10 with no leading zeroes, have their digits sorted in non-decreasing order.
	Some examples of this are 8, 123, 555, and 224488. She decided to call these numbers tidy.
	Numbers that do not have this property, like 20, 321, 495 and 999990, are not tidy.

	She just finished counting all positive integers in ascending order from 1 to N. What was the last tidy number she counted?

	Input

	The first line of the input gives the number of test cases, T. T lines follow.
	Each line describes a test case with a single integer N, the last number counted by Tatiana.

	Output

	For each test case, output one line containing Case #x: y, where x is the test case number
	(starting from 1) and y is the last tidy number counted by Tatiana.

	Note: had problems uploading to Google drive because of non-ASCII characters below (<-)
	TODO: figure out how to configure editor to save this file properly

	Limits

	1 ≤ T ≤ 100.
	Small dataset

	1 ≤ N ≤ 1000.
	Large dataset

	1 ≤ N ≤ 1018.


**/

int main(int argc, char *argv[]) {

	//open file
	FILE *fp, *fpOut;
	char numberOfCases[10];//read first line, store as number of test cases, first line in B-small-practice.in is 100, so the next 100 lines will be test cases

	fp = fopen("B-small-practice.in", "r");//opening file for reading 
	fpOut = fopen("output.txt", "w");//writing the results to a output.txt, need this to upload for Google review

	if (fp == NULL)
	{
		perror("Error opening file");
		return(-1);
	}

	if (fgets(numberOfCases, 10, fp) != NULL)
	{
		printf("DEBUG number of cases %s", numberOfCases);//don't write this to output.txt, this is just for debugging
	}

	char *pNumberOfCases = numberOfCases; //if you store in char numberOfCases[] it would be numberOfCases not &numberOfCases (use &numberOfCases if we started with an int numberOfCases[] (int array)

	while (*pNumberOfCases != '\0')
	{
		pNumberOfCases++;
	}

	*(pNumberOfCases - 1) = '\0'; //using fgets automatically insert a new line charactter, this code replaces the new line with a null, better for strings

	//T lines follow. Each line describes a test case with a single integer N, 
	//the last number counted by Tatiana.

	char inputNumber[10];
	int convertNumber;
	int currentNumber; //Small dataset 1 ≤ N ≤ 1000.
	int countDigits = 0;//the number of digits in a the current number
	int limitCount = 0;
	int biggestTinyNumber = 0;
	int caseCount = 1;

	if (1 <= numberOfCases && numberOfCases >= 100) {
		//call fgets numberofCase times
		while (!feof(fp)) {
			//get input and check for limits
			if (fgets(inputNumber, 10, fp) != NULL)
			{
				//find number of digits in inputNumber Array
				char *pInputNumber = inputNumber;
				while (*pInputNumber != '\n') { //not \0 because fgets insert \n
					pInputNumber++; //move the pointer
					countDigits++;
				}

				convertNumber = atoi(inputNumber); //changed into a number
				if ((1 <= convertNumber) && (convertNumber <= 1000)) {
					currentNumber = convertNumber;
				}

				int firstDigit = 0, secondDigit = 0, thirdDigit = 0;

				switch (countDigits) {

				case 1:
					//numbers 1 to 9
					printf("Case #%d: %d\n", caseCount, currentNumber);
					fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", currentNumber);
					caseCount++;
					break;

				case 2:
					//Note: represents case when input as 2 digits and the right most digit is the second digit
					//MH said: Instead of counting from the lowest number to the max, start with the max number and keep decreasing it.  
					//That way, the "first" tidy number is the max "tidy" number.

					limitCount = 10;
					while (limitCount <= currentNumber) {

						//break the digits apart and compare them
						secondDigit = currentNumber % 10; // just the remainder
						firstDigit = currentNumber / 10;

						//Note: Just because the max number has two digits doesn't mean the 
						//max "tidy" number has two digits as well i.e. 10

						if (firstDigit == 1 && secondDigit == 0) {
							biggestTinyNumber = 9; //if convert number is 10 then the max tidy number is 9
							printf("Case #%d: %d\n", caseCount, biggestTinyNumber);
							fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", biggestTinyNumber);
							caseCount++;
							break;

						}
						else if (firstDigit < secondDigit) {
							biggestTinyNumber = currentNumber;
							printf("Case #%d: %d\n", caseCount, biggestTinyNumber);
							fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", biggestTinyNumber);
							caseCount++;
							break;
						}

						currentNumber--;//counting till we hit limit, more efficient then looping from limitCount and incrementing to convert number
					}

					break;//need the break or else case 3 will get executed

				case 3:

					limitCount = 100;

					while (limitCount <= currentNumber) {

						//given a number 123
						firstDigit = currentNumber / 100;//1
						secondDigit = (currentNumber % 100) / 10;//mod = 23, divide by 10 = 2
						thirdDigit = currentNumber % 10; //23 mod 10 = 3

						//deal with  the number 100
						if (firstDigit == 1 && secondDigit == 0 && thirdDigit == 0) {
							biggestTinyNumber = 99; //if convert number is 10 then the max tidy number is 9
							printf("Case #%d: %d\n", caseCount, biggestTinyNumber);
							fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", biggestTinyNumber);
							caseCount++;
							break;

						}
						else if (firstDigit <= secondDigit) { //don't forget the equal

							if (secondDigit <= thirdDigit) {
								biggestTinyNumber = currentNumber;
								printf("Case #%d: %d\n", caseCount, biggestTinyNumber);
								fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", biggestTinyNumber);
								caseCount++;
								break;
							}
						}

						currentNumber--;
					}

					break;//need the break

				case 4:

					//limit for small dataset (B-samll-practice.in) is 1000, so 999 is the biggest tidy number in this dataset
					printf("Case #%d: %d\n", caseCount, 999);
					fprintf(fpOut, "%s%d%s%d\n", "Case #", caseCount, ": ", 999);

					caseCount++;
					break;

				default:
					break;
				}

				countDigits = 0;//resets count, important
			}//end of if
		}
	}//end of if

	printf("\n");

	fclose(fp);//remember to close files

	return(0);

}

