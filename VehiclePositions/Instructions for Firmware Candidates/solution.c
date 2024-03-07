#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


float coordinates[10][2] = {{34.544909f, -102.100843f}, {32.345544f, -99.123124f}, {33.234235f, -100.214124f}, {35.195739f, -95.348899f},{31.895839f, -97.789573f}, {32.895839f, -101.789573f},
 {34.115839f, -100.225732f}, {32.335839f, -99.992232f}, {33.535339f, -94.792232f}, {32.234235f, -100.222222f}};             //coordinates of the 10 positions

int closestCars[10][10] = {0};      //position IDs of the 10 closest cars to each coordinates...organised by rows meaning row 1 corresponds to coordinate 1, row 2 corresponds to coordinate 2...and so on

float cars[2000000][3] = {0};		//postionID and coordinates of each car is stored in this array

float applicableCars[10][3] = {0};				//the number of cars is dependent on the values chosen of x_threshold and y_threshold

float distance[10][2] = {{-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}, {-1.0, 1000000.0}};		//records the distance and the position id

float tempDistance = 0.0;			//the temp variable that is compared to determine whether the distance is small enough to be put into the array

int writtenFlag = 0;			//to ensure that a number isn't duplicated in the distance array

int counterForApplicableCars = 0;		//to ensure that there are no gaps in applicable cars

//values used to limit the amount of cars distance calculations need to be done on
int x_threshold = 325;
int y_threshold = 325;

//all used as temporary variables to enable distances to be ordered in ascending order
float temp = 0.0;
float temp1 = 0.0;
float tempID = 0;
float tempID1 = 0;

struct timeval start, end;		//used to determine time to execute code

int temporary = 0;					//variable to hold data from .dat file before being inserted into car array
int tempDataCounter = 0;			//used to keep track of what data values is recorded to cars array
int tempCarCounter = 0;				//variable to ensure correct input per row to car array


float square(float number) 			//function to get the square of a number passed to it
{
  return (number * number);
}

FILE *ptr_myfile;		//pointer variable for file

int main() {
	
	gettimeofday(&start, NULL);		//start timing
	
	
	//The following scans the data file and inputs the relevant values into the cars array
	
	ptr_myfile=fopen("..\\VehiclePositions_DataFile\\VehiclePositions.dat","rb");          //specify path to datafile
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
	for ( int dataCounter=0; dataCounter < 10000000; dataCounter++)
	{
		fread(&temporary,sizeof(ptr_myfile),1,ptr_myfile);
		if(tempDataCounter==0)
		{
			cars[tempCarCounter][0]=(float)temporary;
			tempDataCounter++;
		}
		else if(tempDataCounter==1)
		{
			tempDataCounter++;
		}
		else if(tempDataCounter==2)
		{
			cars[tempCarCounter][1]=(float)temporary;
			tempDataCounter++;
		}
		else if(tempDataCounter==3)
		{
			cars[tempCarCounter][2]=(float)temporary;
			tempDataCounter++;
		}
		else if(tempDataCounter==4)
		{
			tempDataCounter=0;
			tempCarCounter++;
		}
		
	}
	fclose(ptr_myfile);
	
	
	for(int coordinateCounter=0; coordinateCounter<10; coordinateCounter++)			//used to loop between all the coordinates
	{
		//SQUARE algorithm to limit the amount of car distance calculations that need to be done
		
		for(int carsCounter=0; carsCounter<2000000; carsCounter++)				//carsCounter refers to the number of total cars that need to be analysed
		{
			if(((coordinates[coordinateCounter][0]-(float)x_threshold)<=cars[carsCounter][1]) && (cars[carsCounter][1]<=(coordinates[coordinateCounter][0]+(float)x_threshold)))		//vertical bounds set
			{
				if(((coordinates[coordinateCounter][1]-(float)y_threshold)<=cars[carsCounter][2]) && (cars[carsCounter][2]<=(coordinates[coordinateCounter][1]+(float)y_threshold)))		//horizontal bounds set
				{
					if(counterForApplicableCars<19)			//to ensure that the array index for the "applicableCars" array doesn't get exceeded
					{
						applicableCars[counterForApplicableCars][0] = cars[carsCounter][0];
						applicableCars[counterForApplicableCars][1] = cars[carsCounter][1];
						applicableCars[counterForApplicableCars][2] = cars[carsCounter][2];
						counterForApplicableCars= counterForApplicableCars + 1;
					}
				}
			}		
		}
		
		
		for(int counter=0; counter<counterForApplicableCars; counter++)			//counter refers to the number of applicable cars that need to be analysed
		{
			tempDistance = square(coordinates[coordinateCounter][0]-applicableCars[counter][1]) + square(coordinates[coordinateCounter][1]-applicableCars[counter][2]);
			
			for(int counter1=0; counter1<10; counter1++)					
			{
				if((counter1==0) && (tempDistance<distance[counter1][1]) && (writtenFlag!=1))																//deals with first entry
				{
					//the following is done to insert and shift the values within the array
					temp1 = distance[counter1][1];
					tempID1 = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp = distance[1][1];
					tempID = distance[1][0];
					distance[1][1] = temp1;
					distance[1][0] = tempID1;
					
					temp1 = distance[2][1];
					tempID1 = distance[2][0];
					distance[2][1] = temp;
					distance[2][0] = tempID;
					
					temp = distance[3][1];
					tempID = distance[3][0];
					distance[3][1] = temp1;
					distance[3][0] = tempID1;
					
					temp1 = distance[4][1];
					tempID1 = distance[4][0];
					distance[4][1] = temp;
					distance[4][0] = tempID;
					
					temp = distance[5][1];
					tempID = distance[5][0];
					distance[5][1] = temp1;
					distance[5][0] = tempID1;
					
					temp1 = distance[6][1];
					tempID1 = distance[6][0];
					distance[6][1] = temp;
					distance[6][0] = tempID;
					
					temp = distance[7][1];
					tempID = distance[7][0];
					distance[7][1] = temp1;
					distance[7][0] = tempID1;
					
					temp1 = distance[8][1];
					tempID1 = distance[8][0];
					distance[8][1] = temp;
					distance[8][0] = tempID;
					
					temp = distance[9][1];
					tempID = distance[9][0];
					distance[9][1] = temp1;
					distance[9][0] = tempID1;
					
					writtenFlag=1;
				}
				
				else if((counter1==1) && (distance[0][1]<tempDistance) && (tempDistance<distance[1][1]) && (writtenFlag!=1))																//deals with second entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[2][1];
					tempID1 = distance[2][0];
					distance[2][1] = temp;
					distance[2][0] = tempID;
					
					temp = distance[3][1];
					tempID = distance[3][0];
					distance[3][1] = temp1;
					distance[3][0] = tempID1;
					
					temp1 = distance[4][1];
					tempID1 = distance[4][0];
					distance[4][1] = temp;
					distance[4][0] = tempID;
					
					temp = distance[5][1];
					tempID = distance[5][0];
					distance[5][1] = temp1;
					distance[5][0] = tempID1;
					
					temp1 = distance[6][1];
					tempID1 = distance[6][0];
					distance[6][1] = temp;
					distance[6][0] = tempID;
					
					temp = distance[7][1];
					tempID = distance[7][0];
					distance[7][1] = temp1;
					distance[7][0] = tempID1;
					
					temp1 = distance[8][1];
					tempID1 = distance[8][0];
					distance[8][1] = temp;
					distance[8][0] = tempID;
					
					temp = distance[9][1];
					tempID = distance[9][0];
					distance[9][1] = temp1;
					distance[9][0] = tempID1;
					
					writtenFlag=1;
				}
				
				else if((counter1==2) && (distance[1][1]<tempDistance) && (tempDistance<distance[2][1]) && (writtenFlag!=1))																//deals with third entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					
					temp1 = distance[3][1];
					tempID1 = distance[3][0];
					distance[3][1] = temp;
					distance[3][0] = tempID;
					
					temp = distance[4][1];
					tempID = distance[4][0];
					distance[4][1] = temp1;
					distance[4][0] = tempID1;
					
					temp1 = distance[5][1];
					tempID1 = distance[5][0];
					distance[5][1] = temp;
					distance[5][0] = tempID;
					
					temp = distance[6][1];
					tempID = distance[6][0];
					distance[6][1] = temp1;
					distance[6][0] = tempID1;
					
					temp1 = distance[7][1];
					tempID1 = distance[7][0];
					distance[7][1] = temp;
					distance[7][0] = tempID;
					
					temp = distance[8][1];
					tempID = distance[8][0];
					distance[8][1] = temp1;
					distance[8][0] = tempID1;
					
					temp1 = distance[9][1];
					tempID1 = distance[9][0];
					distance[9][1] = temp;
					distance[9][0] = tempID;
					
					writtenFlag=1;
				}
				
				else if((counter1==3) && (distance[2][1]<tempDistance) && (tempDistance<distance[3][1]) && (writtenFlag!=1))																//deals with fourth entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[4][1];
					tempID1 = distance[4][0];
					distance[4][1] = temp;
					distance[4][0] = tempID;
					
					temp = distance[5][1];
					tempID = distance[5][0];
					distance[5][1] = temp1;
					distance[5][0] = tempID1;
					
					temp1 = distance[6][1];
					tempID1 = distance[6][0];
					distance[6][1] = temp;
					distance[6][0] = tempID;
					
					temp = distance[7][1];
					tempID = distance[7][0];
					distance[7][1] = temp1;
					distance[7][0] = tempID1;
					
					temp1 = distance[8][1];
					tempID1 = distance[8][0];
					distance[8][1] = temp;
					distance[8][0] = tempID;
					
					temp = distance[9][1];
					tempID = distance[9][0];
					distance[9][1] = temp1;
					distance[9][0] = tempID1;
					
					writtenFlag=1;
				}
				
				else if((counter1==4) && (distance[3][1]<tempDistance) && (tempDistance<distance[4][1]) && (writtenFlag!=1))																//deals with fifth entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[5][1];
					tempID1 = distance[5][0];
					distance[5][1] = temp;
					distance[5][0] = tempID;
					
					temp = distance[6][1];
					tempID = distance[6][0];
					distance[6][1] = temp1;
					distance[6][0] = tempID1;
					
					temp1 = distance[7][1];
					tempID1 = distance[7][0];
					distance[7][1] = temp;
					distance[7][0] = tempID;
					
					temp = distance[8][1];
					tempID = distance[8][0];
					distance[8][1] = temp1;
					distance[8][0] = tempID1;
					
					temp1 = distance[9][1];
					tempID1 = distance[9][0];
					distance[9][1] = temp;
					distance[9][0] = tempID;
					
					writtenFlag=1;
				}
				
				else if((counter1==5) && (distance[4][1]<tempDistance) && (tempDistance<distance[5][1]) && (writtenFlag!=1))																//deals with sixth entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[6][1];
					tempID1 = distance[6][0];
					distance[6][1] = temp;
					distance[6][0] = tempID;
					
					temp = distance[7][1];
					tempID = distance[7][0];
					distance[7][1] = temp1;
					distance[7][0] = tempID1;
					
					temp1 = distance[8][1];
					tempID1 = distance[8][0];
					distance[8][1] = temp;
					distance[8][0] = tempID;
					
					temp = distance[9][1];
					tempID = distance[9][0];
					distance[9][1] = temp1;
					distance[9][0] = tempID1;
					
					writtenFlag=1;
				}
				
				else if((counter1==6) && (distance[5][1]<tempDistance) && (tempDistance<distance[6][1]) && (writtenFlag!=1))																//deals with seventh entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[7][1];
					tempID1 = distance[7][0];
					distance[7][1] = temp;
					distance[7][0] = tempID;
					
					temp = distance[8][1];
					tempID = distance[8][0];
					distance[8][1] = temp1;
					distance[8][0] = tempID1;
					
					temp1 = distance[9][1];
					tempID1 = distance[9][0];
					distance[9][1] = temp;
					distance[9][0] = tempID;
					
					writtenFlag=1;
				}
				
				else if((counter1==7) && (distance[6][1]<tempDistance) && (tempDistance<distance[7][1]) && (writtenFlag!=1))																//deals with eighth entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					temp1 = distance[8][1];
					tempID1 = distance[8][0];
					distance[8][1] = temp;
					distance[8][0] = tempID;
					
					temp = distance[9][1];
					tempID = distance[9][0];
					distance[9][1] = temp1;
					distance[9][0] = tempID1;
					
					writtenFlag=1;
				}
				
				else if((counter1==8) && (distance[7][1]<tempDistance) && (tempDistance<distance[8][1]) && (writtenFlag!=1))																//deals with ninth entry
				{
					//the following is done to insert and shift the values within the array
					temp = distance[counter1][1];
					tempID = distance[counter1][0];
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					
					temp1 = distance[9][1];
					tempID1 = distance[9][0];
					distance[9][1] = temp;
					distance[9][0] = tempID;
					
					writtenFlag=1;
				}
				
				else if((counter1==9) && (distance[8][1]<tempDistance) && (tempDistance<distance[9][1]) && (writtenFlag!=1))																//deals with tenth entry
				{
					distance[counter1][1] = tempDistance;
					distance[counter1][0] = applicableCars[counter][0];
					
					writtenFlag=1;
				}
			}	
			writtenFlag=0;
		}
		
		
		for(int transferCounter=0; transferCounter<10; transferCounter++)			//used to place the contents of the distance array to the respective row in closest car array...as well as prepare distance array for next run
		{
			closestCars[coordinateCounter][transferCounter] = (int)distance[transferCounter][0];
			//resetting distance to original state
			distance[transferCounter][0] = -1.0;
			distance[transferCounter][1] = 1000000.0;
		}
		
		for(int counterS=0; counterS<counterForApplicableCars; counterS++)				//resetting applicable cars array for next run
		{
			applicableCars[counterS][0]=0.0;
			applicableCars[counterS][1]=0.0;
			applicableCars[counterS][2]=0.0;
		}
		
		counterForApplicableCars = 0;		//resetting the counter for applicable cars for next run
		
		
	}
	
	
	for(int printCounter3=0; printCounter3<10; printCounter3++)				//used to print the results of the 10 closest cars
	{
		printf("The position IDs for the 10 closest cars located to coordinate %d: ", printCounter3+1 );
		for(int printCounter4=0; printCounter4<10; printCounter4++)
		{
			printf("%d ",closestCars[printCounter3][printCounter4]);
		}
		printf("\n");
	}

	
	gettimeofday(&end, NULL);		//end timing
	
	//Calculate total time taken and displaying it
	double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	time_taken = time_taken * 1000.000;			//converts the time taken from seconds to milliseconds
	printf("Time taken by program is : %.2fms", time_taken);
    return 0;
}
