/***************************************************************************************
**********
This is to certify that this project is my own work, based on my personal efforts in
studying and applying the concepts learned. I have constructed the functions and their
respective algorithms and corresponding code by myself. The program was run, tested,
and debugged by my own efforts. I further certify that I have not copied in part or
whole or otherwise plagiarized the work of other students and/or persons.
Joaquin Lorenzo Tiro Sitoy, DLSU ID# 12273449
****************************************************************************************
*********/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<dirent.h>

#define max 100



struct project{
	int projectID;
	char name[41];
	int status;
	float completion;
	char description[101];
	int assignID;
};

struct date{
	int day,month,year;
};

struct task{
	int taskID;
	char name[41];
	int sequence;
	char description[101];
    int projectID;
	char startdate[11];
	char enddate[11];
	float totalDuration;
	int status;
	int assignID;
};

struct personnel{
    int personnelID;
    char name[41];
    char username[41];
    char password[41];
    int active;
    int access;
};

/* showPersonnel displays all active personnel (ID and name)
	@param tempPers - list of personnel
	@param stopPers - number of personnel
*/
void showPersonnel(struct personnel tempPers[], int stopPers)
{
	int ctr;
	for(ctr = 0; ctr < stopPers; ctr++) //goes through every personnel in the list, and displays active ones
		{
			if(tempPers[ctr].active == 1) //if currently selected personnel has active 1 (active), that personnel is displayed
			printf("\n%d %s", tempPers[ctr].personnelID, tempPers[ctr].name);
		}
}

/* filenameProject lets the string fileProject be "project_YYYYMMDD.txt" where YYYYMMDD is the date of
  the text file being edited.
  @param fileProject - empty string to be made into the format "project_YYYYMMDD.txt"
  Precondition - fileProject is empty.
*/
void filenameProject(char fileProject[])
{
	time_t t = time(NULL); //gets the number of seconds since the Epoch
	struct tm date = *localtime(&t); //helps separate the time from the previous line into year, month, and day
	
	/*saves the format into the string fileProject. Since the time only takes into account the Epoch, the year and month have to be
	 adjusted by adding 1900 and 1 to the year and month respectively to get the current date.*/
	sprintf(fileProject,"project_%d%02d%02d.txt", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
}
/* filenamePersonnel lets the string filePersonnel be "personnel_YYYYMMDD.txt" where YYYYMMDD is the date of
  the text file being edited.
  @param filePersonnel - empty string to be made into the format "personnel_YYYYMMDD.txt"
  Precondition - filePersonnel is empty.
*/
void filenamePersonnel(char filePersonnel[])
{
	time_t t = time(NULL); //gets the number of seconds since the Epoch
	struct tm date = *localtime(&t); //helps separate the time from the previous line into year, month, and day

	/*saves the format into the string filePersonnel. Since the time only takes into account the Epoch, the year and month have to be
	 adjusted by adding 1900 and 1 to the year and month respectively to get the current date.*/	
	sprintf(filePersonnel,"personnel_%d%02d%02d.txt", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
}
/* filenameTask lets the string fileTask be "task_YYYYMMDD.txt" where YYYYMMDD is the date of
  the text file being edited.
  @param fileTask - empty string to be made into the format "task_YYYYMMDD.txt"
  Precondition - fileTask is empty.
*/
void filenameTask(char fileTask[])
{
	time_t t = time(NULL);//gets the number of seconds since the Epoch
	struct tm date = *localtime(&t);//helps separate the time from the previous line into year, month, and day
	
	/*saves the format into the string fileTask. Since the time only takes into account the Epoch, the year and month have to be
	 adjusted by adding 1900 and 1 to the year and month respectively to get the current date.*/
	sprintf(fileTask,"task_%d%02d%02d.txt", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
}

/* getDateToday lets the string "today" be MM/DD/YYYY which corresponds to the current date.
  @param today - empty string where the current date is to be stored
*/
void getDateToday(char today[])
{
	time_t t = time(NULL);//gets the number of seconds since the Epoch
	struct tm date = *localtime(&t);//helps separate the time from the previous line into year, month, and day
	
	/*saves the current date into the string "today". Since the time only takes into account the Epoch, 1900 and 1 are added to the
	year and month respectively to get the current date*/
	sprintf(today,"%02d/%02d/%d", date.tm_mon + 1, date.tm_mday, date.tm_year + 1900);
	
}

/* countLeap counts the number of leap years from 0 AD to the given parameters.
  @param years - number of years since 0 AD
  @param months - number of months from the start of the "years" parameter
  @return number of leap years from 0 AD to the given parameters
*/
int countLeap(int years, int months)
{
	if(months < 3) //If the year to be taken into account doesn't include February, that year isn't to be included in the calculations by subtracting 1.
	--years;
	
	return years/4 + years/400 - years/100; //A leap year is divisible by 4 unless it is divisible by 100 (unless it is also divisible by 400).
}

/* personnelArray saves the list of personnel details in the latest file into an array
  @param temp - array where the list of personnel details is to be saved in
  @return number of elements in the array containing all personnel details
  precondition - temp is empty
*/
int personnelArray(struct personnel temp [])
{
	DIR *filename; //holds a directory
	struct dirent *details; //contains details of the currently selected file in the directory
	char latest[max]; //string to contain the name of the latest personnel file to be edited
	
	FILE *personnel; //holds the latest personnel file (or preloaded file)
	struct personnel check; //holds the details of the currently selected personnel in the personnel file
	int ctr = 0; //counts how many elements there are in the array
	int preloaded = 0; //determines if the preloaded file is to be used
	
	filename = opendir("."); //opens the current directory
	
	while((details = readdir(filename)) != NULL) //reads details of each file in the directory until the end
	{
		if(strlen(details->d_name) == 22) //Only the file names of personnel files (personnel_YYYYMMDD.txt) will have a length of 22. This checks if the current file is a personnel file.
		{
			if(strcmp(details->d_name, latest) > 0) //checks if the currently selected file is later than the currently saved "latest" file name
			strcpy(latest, details->d_name); //If the currently selected file is later, that file's name will be the new "latest" string
			preloaded = 1; //A preloaded file becoming 1 shows that the preloaded file need not be used.
		}
	}
	
	closedir(filename); //closes the directory

	if(preloaded) //If the preloaded file need not be used, the latest personnel file is used.
	personnel = fopen(latest, "r");
	else //If the preloaded file is still 0, the preloaded file must be used.
	personnel = fopen("preloaded.txt", "r");

	//This loop stores every personnel detail in the personnel file being used into an array
	while(fscanf(personnel,"%d %s %s %s %d %d", &check.personnelID, check.name, check.username, check.password, &check.active, &check.access) != EOF)
		{
			temp[ctr] = check; 
			++ctr; //number of elements inreases by 1 every time there's a new personnel stored in the array.
		}
	
	fclose(personnel); //closes the file
	
	return ctr; 
}

/* checkDate checks if the date in the given parameter is a valid date
  @param date - string of the date to be validated
  @return 3 if date is valid, 0 if not
*/
int checkDate(char date[])
{
	int check; //representation of validity of date; if 0, then invalid date
	int month; //month section of date
	int day; //day section of date
	int year; //year section of date
	
	check = sscanf(date, "%d/%d/%d", &month, &day, &year); //checks how many numbers are in the parameter string for the date that follow the format
	
	if(day < 1 || month < 1 || year < 1 || month > 12 || day > 31) //All months/days are represented by a positive number. Number of months in a year don't go past 12, and days in a month never go past 31.
	check = 0;
	else if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) //April (4), June(6), September(9), November(11) only have 30 days.
	check = 0;
	else if(month == 2) //checks conditions in February
	{
		if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))//checks if it's a leap year
		{
			if(day > 29) //checks if the number of days in February in a leap year is past 29
			check = 0;
		}
		else if(day > 28) //If it's not a leap year, the number of days in February can't go past 28.
		check = 0;
	}
	
	if(check != 3) //displays an error message if the date is invalid.
	printf("\nInvalid date. Please try again.\n");
	
	if(check == 3)
	sprintf(date,"%d/%d/%d", month,day,year); //in the case that the user inputted extra letters or special characters at the end, this line removes the extras.
	
	return check; 
}

/* projectArray saves the list of project details in the latest file into an array
  @param temp - array where the list of project details is to be saved in
  @return number of elements in the array containing all project details
  precondition - temp is empty
*/
int projectArray(struct project temp[])
{
	DIR *filename;//holds a directory
	struct dirent *details;//contains details of the currently selected file in the directory
	char latest[max];//string to contain the name of the latest project file to be edited
	
	FILE *project;	//holds the latest project file
	struct project check;//holds the details of the currently selected project in the project file
	int ctr = 0;//counts how many elements there are in the array
	
	strcpy(latest,""); //makes sure the "latest" array is empty.
	
	filename = opendir(".");//opens the current directory
	
	while((details = readdir(filename)) != NULL) //reads details of each file in the directory until the end
	{
		if(strlen(details->d_name) == 20) //Only the file names of project files (project_YYYYMMDD.txt) in the directory will have a length of 20. This checks if the current file is a project file.
		{
			if(strcmp(details->d_name, latest) > 0)//checks if the currently selected file is later than the currently saved "latest" file name
			strcpy(latest, details->d_name);//If the currently selected file is later, that file's name will be the new "latest" string
		}
	}
	
	closedir(filename); //closes the directory
	
	project = fopen(latest, "r"); //reads the latest project file
	
	if(project == NULL) //if there are no project files, 0 is returned (no project details)
	return 0;
	
	//This loop stores every project detail in the project file being used into an array
	while(fscanf(project, "%d %s %d %f %s %d", &check.projectID, check.name, &check.status, &check.completion, check.description, &check.assignID) != EOF)
	{
		temp[ctr] = check;
		++ctr; //number of elements inreases by 1 every time there's a new project stored in the array.
	}
	
	fclose(project); //closes the latest project file, if any
	
	return ctr;
}

/* taskArray saves the list of task details in the latest file into an array
  @param temp - array where the list of task details is to be saved in
  @return number of elements in the array containing all task details
  precondition - temp is empty
*/
int taskArray(struct task temp[])
{
	DIR *filename;//holds a directory
	struct dirent *details; //contains details of the currently selected file in the directory
	char latest[max];	//string to contain the name of the latest task file to be edited
	strcpy(latest,""); //ensures the "latest" array is empty.
	FILE *task; //holds the latest task file
	struct task check; //holds the details of the currently selected task in the task file
	int ctr = 0;//counts how many elements there are in the array.

	filename = opendir(".");//opens the current directory
	
	while((details = readdir(filename)) != NULL) //reads details of each file in the directory until the end
	{
		if(strlen(details->d_name) == 17)//Only the file names of task files (task_YYYYMMDD.txt) in the directory will have a length of 17. This checks if the current file is a task file.
		{
			if(strcmp(details->d_name, latest) > 0)//checks if the currently selected file is later than the currently saved "latest" file name
			strcpy(latest, details->d_name);//If the currently selected file is later, that file's name will be the new "latest" string
		}
	}
	
	closedir(filename);//closes the directory
	task = fopen(latest, "r");//reads the latest task file
	
	if(task == NULL)//if there are no task files, 0 is returned (no task details)
	return 0;
	
	//This loop stores every task detail in the task file being used into an array
	while(fscanf(task, "%d %s %d %s %d %s %s %f %d %d", &check.taskID, check.name, &check.sequence, check.description, &check.projectID, check.startdate, check.enddate, &check.totalDuration, &check.status, &check.assignID) != EOF)
	{
		temp[ctr] = check;
		++ctr; //number of elements inreases by 1 every time there's a new project stored in the array.
	}
	
	fclose(task); //closes the directory
	
	return ctr;
}

/* scanInput makes sure the inputted is a number within a range (if a range is indicated)
	@param *input - input that should be a number within a range(if indicated)
	@param low - lowest number in the range
	@param high - highest number in the range
*/
void scanInput(int *input, int low, int high)
{
	int check; //determines if an input is valid
	do
	{
		printf("\nEnter Input: ");
		check = scanf("%d", input); //check becomes 1 if a number is inputted, 0 if not
		if(!check) //checks if the inputted number is not a number
		{
		printf("\nYou inputted a letter. Please try again.\n");
		fflush(stdin);	//The input buffer is flushed to make sure there is no infinite loop.
		}
		else if(low != -1) //If low is -1, the user is telling the system that a range isn't indicated.
		{
			if(*input < low || *input > high) //checks if the input is within the range
			{
				check = 0; //invalidates the input.
				printf("\nPlease pick a number from within the choices.\n");
			}	
		}
		
	} while(!check); //the process is repeated until the input is valid.
}

/* searchPersonnelID checks if the inputted personnel is present in the database.
	@param array - the list of personnel to be compared to
	@param key - the personnel (through ID) whose presence is to be confirmed
	@param stop - number of personnel to be checked
	@return 1 if personnel inputted isn't in the database, 0 if the personnel is in the database.
*/
int searchPersonnelID(struct personnel array[], int key, int stop)
{
	int ctr; //counter in the loop
	
	for(ctr = 0; ctr < stop; ctr++)//loop to look through every personnel in the database
	{
		if(array[ctr].personnelID == key) //checks if the currently selected personnel has the same ID as the inputted personnelID.
		{
			return 0;
		}
	}
	
	printf("\nID not found. Please try again\n");
	
	return 1;
}

/* searchProjectID checks if the inputted project is present in the database.
	@param array - the list of projects to be compared to
	@param key - the project (through ID) whose presence is to be confirmed
	@param stop - number of projects to be checked
	@return 1 if project inputted isn't in the database, 0 if the project is in the database.
*/
int searchProjectID(struct project array[], int key, int stop)
{
	int ctr;//counter in the loop
	
	for(ctr = 0; ctr < stop; ctr++)//loop to look through every project in the database
	{
		if(array[ctr].projectID == key)//checks if the currently selected project has the same ID as the inputted projectID.
		return 0;
	}
	
	printf("\nID not found. Please try again\n");
	
	return 1;
}

/* searchTaskID checks if the inputted task is present in the database.
	@param array - the list of tasks to be compared to
	@param key - the task (through ID) whose presence is to be confirmed
	@param stop - number of tasks to be checked
	@return 1 if task inputted isn't in the database, 0 if the task is in the database.
*/
int searchTaskID(struct task array[], int key, int stop)
{
	int ctr;//counter in the loop
	
	for(ctr = 0; ctr < stop; ctr++)//loop to look through every task in the database
	{
		if(array[ctr].taskID == key)//checks if the currently selected task has the same ID as the inputted taskID.
		return 0;
	}
	
	printf("\nID not found. Please try again\n");
	
	return 1;
}

/*computeTotalDuration computes for the number of days between a start date and end date
	@param inputTask - structure that contains the start date and end date
	@return number of days between the start date and end date
	precondition - strings for start and end date are valid dates containing integers and slashes.
*/
float computeTotalDuration(struct task inputTask)
{
	int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//enumerates the number of days for each month in a year
	int startTotal;//number of days from 0 AD to the start date
	int endTotal;//number of days from 0 AD to the end date
	int ctr;//counter in the loops
	struct date start;//contains the month, day, and year of the start date
	struct date end;//contains the month, day, and year of the end date
	

				startTotal = 0;
				endTotal = 0;
	
				sscanf(inputTask.startdate, "%d/%d/%d", &start.month, &start.day, &start.year);//stores inputted start date details (string) into the structure start (integers)
				sscanf(inputTask.enddate, "%d/%d/%d", &end.month, &end.day, &end.year);//stores inputted end date details (string) into the structure end (integers)
				
				for(ctr = 0; ctr < start.month; ctr++) //loop that counts the number of days in the year of the inputted start date (not including the last month)
				startTotal += months[ctr]; //adds days depending on how many days there are in that month.
				
				for(ctr = 0; ctr < end.month; ctr++) //loop that counts the number of days in the year of the inputted end date (not including the last month)
				endTotal += months[ctr]; //adds days depending on how many days there are in that month.
				
				startTotal += start.year * 365 + start.day + countLeap(start.year, start.month); //adds the number of days of the start date from 0 AD (years in days, includes leap years, and the final month)
				endTotal += end.year * 365 + end.day + countLeap(end.year, end.month); //adds the number of days of the end date from 0 AD (years in days, includes leap years, and the final month)
				
				inputTask.totalDuration = endTotal - startTotal; //The difference between startTotal and endTotal is the number of days between the start date and end date.
				
				
			
	return inputTask.totalDuration;
}

/* adminMenu contains all the features for the administrator
	@param tempPers - list of personnel details from the latest personnel file or preloaded file.
	@param stopPers - number of personnel in the latest personnel file or preloaded file.
	@return 1 if the user wants to go back to the main menu, 0 otherwise
*/
int adminMenu(struct personnel tempPers[], int stopPers)
{
	FILE *preload, *project, *task; //preload holds the latest personnel/preloaded file, project holds the latest project file, task holds the latest task file
	char fileProject[max], filePersonnel[max], fileTask[max]; //These hold the file names for the newly edited project/personnel/task files
	int pick; //determines which admin feature is to be performed
	int ctr; //counter for the loops
	int stopProj; //number of projects from the latest project file
	int stopTask; //number of tasks from the latest task file
	int checkUsername = 0; //checks if a username has already been taken
	int projCtr = 0; //number of active projects in the project file
	int manCtr = 0; //number of managers in the personnel file
	int projectID; //inputted projectID to be assigned
	int managerID; //inputted manager to have inputted project assigned to
	struct personnel input; //inputted details for a personnel
	struct personnel managers[max];//list of managerse from the personnel file
	struct project tempProj[max];//list of projects from the project file
	struct project activeProj[max];	//list of active projects from the project file
	struct task tempTask[max];//list of tasks
	
	//These store the names for the newly edited files.
	filenameProject(fileProject);
	filenamePersonnel(filePersonnel);
	filenameTask(fileTask);

	//These both count the number projects/tasks and store projects/tasks from the latest files in arrays.
	stopProj = projectArray(tempProj);
	stopTask = taskArray(tempTask);	

	//displays options
	printf("\n(1) Add New User\n");
	printf("(2) Update User\n");
	printf("(3) Delete User\n");
	printf("(4) Archive User\n");
	printf("(5) Assign Project\n");
	printf("(6) Go Back to Main Menu\n\n");
		
		scanInput(&pick, 1, 6);//gets input and loops if invalid input
		

		switch(pick) //this switch determines which feature to use
		{
			case 1: //Add New User			
				printf("\nEnter new user's name (use _ instead of spaces): ");
				scanf("%s", input.name); 
				
				do //loop if inputted username is taken
				{
					checkUsername = 0;
					
					printf("\nEnter new user's username: ");
					scanf("%s", input.username);
					
					for(ctr = 0; ctr < stopPers; ctr++) //goes through list of personnel to check if username is taken
					{
						if(strcmp(input.username, tempPers[ctr].username) == 0) //check if currently selected username in list is the same as input
						{
							printf("\nThat username's already taken. Please try again.\n");
							checkUsername = 1;
						}
						
					}
				} while(checkUsername);
				
				
				strcpy(input.password,"temp"); //password for all newly added users is temp
				
				printf("\nNew user's password is 'temp'");
				printf("\n\nNew user access:\n(2) Manager\n(3) User\n");
				
				scanInput(&input.access, 2, 3);
				
				input.personnelID = tempPers[stopPers - 1].personnelID + 1; //new user's ID is the last personnel in the list's ID plus 1.
				
				preload = fopen(filePersonnel, "w"); //opens new file to be edited
				
				for(ctr = 0; ctr < stopPers; ctr++) //loop to rewrite all personnel from last file
				{
					fprintf(preload,"%d %s\n", tempPers[ctr].personnelID, tempPers[ctr].name);
					fprintf(preload,"%s",tempPers[ctr].username);
					fprintf(preload,"\n%s\n%d\n",tempPers[ctr].password, tempPers[ctr].active); 
					fprintf(preload,"%d\n\n", tempPers[ctr].access);	
				}
				
				//writes the details of new personnel at the end of new file.
				fprintf(preload,"%d %s\n", input.personnelID, input.name);
				fprintf(preload,"%s",input.username);
				fprintf(preload,"\n%s\n1\n",input.password); 
				fprintf(preload,"%d\n\n", input.access);
				
				fclose(preload); break;
				
			case 2: //Update User
				do //loop to make sure personnel inputted is actually present in list
				{
					printf("\n(personnel ID to be updated)");
					scanInput(&input.personnelID, -1, -1);
				} while(searchPersonnelID(tempPers, input.personnelID, stopPers));
				
	
				do //loop to make sure username isn't taken already
				{
					checkUsername = 0;
					
					printf("\nEnter new user's username: ");
					scanf("%s", input.username);
					for(ctr = 0; ctr < stopPers; ctr++)//goes through list of personnel to see if username is taken
					{
						if(strcmp(input.username, tempPers[ctr].username) == 0 && input.personnelID != tempPers[ctr].personnelID)//checks if the currently selected personnel's username matches input
						{
							printf("\nThat username's already taken. Please try again.\n");
							checkUsername = 1;
						}
						
					}
				} while(checkUsername);
				
				printf("\n\nEnter new password: ");
				scanf("%s", input.password);
				
				printf("\n\nEnter new user access (2 for Manager, 3 for User) ");
				scanInput(&input.access, 2, 3);
				
				preload = fopen(filePersonnel, "w");//opens new personnel file to write for updated details
				
				for(ctr = 0; ctr < stopPers; ctr++)//rewrites all previous personnel details with updated details if the selected personnelID matches the input.
				{
					if(tempPers[ctr].personnelID == input.personnelID) //updates personnel details if the currently selected personnelID matches the input.
					{
						fprintf(preload,"%d %s\n", input.personnelID, tempPers[ctr].name);
						fprintf(preload,"%s",input.username);
						fprintf(preload,"\n%s\n%d\n",input.password, tempPers[ctr].active); 
						fprintf(preload,"%d", input.access);
						fprintf(preload,"\n\n");
					}
					else //if the currently selected personnelID doesn't match input, original personnel details are rewritten.
					{
						fprintf(preload,"%d %s\n", tempPers[ctr].personnelID, tempPers[ctr].name);
						fprintf(preload,"%s",tempPers[ctr].username);
						fprintf(preload,"\n%s\n%d\n",tempPers[ctr].password, tempPers[ctr].active); 
						fprintf(preload,"%d", tempPers[ctr].access);
						fprintf(preload,"\n\n");
					}
						
				}
				
				break;
				
				case 3: //delete user
					do //loop to make sure inputted personnelID is actually in the list of personnel
					{
						printf("\n(personnel ID to be deleted)");
						scanInput(&input.personnelID, -1, -1);
					} while(searchPersonnelID(tempPers, input.personnelID, stopPers));
					
					preload = fopen(filePersonnel, "w");//opens new personnel file to write for updated details
					
					for(ctr = 0; ctr < stopPers; ctr++)//rewrites all original personnel details except the deleted user
					{
						if(input.personnelID != tempPers[ctr].personnelID)//only rewrites the currently selected personnel if it's not the personnel to be deleted.
						{
							fprintf(preload,"%d %s\n", tempPers[ctr].personnelID, tempPers[ctr].name);
							fprintf(preload,"%s",tempPers[ctr].username);
							fprintf(preload,"\n%s\n%d\n",tempPers[ctr].password, tempPers[ctr].active); 
							fprintf(preload,"%d", tempPers[ctr].access);
							fprintf(preload,"\n\n");
						}
					}
										
					fclose(preload); //closes newly edited file
					
					task = fopen(fileTask, "w"); //opens new task file to write for updated details
					
					for(ctr = 0; ctr < stopTask; ctr++)//rewrites all original task details, but reassigns deleted user's tasks to admin
					{
						fprintf(task, "%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
						fprintf(task, "\n%d", tempTask[ctr].sequence);
						fprintf(task, "\n%s", tempTask[ctr].description);
						fprintf(task, "\n%d", tempTask[ctr].projectID);
						fprintf(task, "\n%s", tempTask[ctr].startdate);
						fprintf(task, "\n%s", tempTask[ctr].enddate);
						fprintf(task, "\n%f", tempTask[ctr].totalDuration);
						fprintf(task, "\n%d", tempTask[ctr].status);
						if(input.personnelID == tempTask[ctr].assignID) //checks if the task was assigned to the deleted user
						fprintf(task, "\n0\n\n"); //assigns task to admin if deleted user was previously assigned.
						else
						fprintf(task, "\n%d\n\n", tempTask[ctr].assignID);	//if task wasn't assigned to deleted user, original detail is rewritten.				
					}
					
					fclose(task); //closes newly edited task file
					
					project = fopen(fileProject, "w"); //opens new project file to write for updated details
					
					for(ctr = 0; ctr < stopProj; ctr++) //rewrites all original project details, but reassigns deleted user's project/s to admin
					{
						fprintf(project, "%d %s", tempProj[ctr].projectID, tempProj[ctr].name);
						fprintf(project, "\n%d", tempProj[ctr].status);
						fprintf(project, "\n%.2f", tempProj[ctr].completion);
						fprintf(project, "\n%s", tempProj[ctr].description);
						if(tempProj[ctr].assignID == input.personnelID) //checks if the project was assigned to the deleted user.
						fprintf(project, "\n0\n\n"); //assigns project to admin if deleted user was previously assigned
						else
						fprintf(project, "\n%d\n\n", tempProj[ctr].assignID);	//otherwise, original detail is rewritten					
					}
					
					fclose(project); //closes newly edited project file
					
					break;
				
				case 4://archive user
					do//loop to ensure inputted ID is within the list of personnel
					{
						printf("\n(personnel ID to be archived)");
						scanInput(&input.personnelID, -1, -1);
					} while(searchPersonnelID(tempPers, input.personnelID, stopPers));
					
					preload = fopen(filePersonnel, "w"); //opens new personnel file for updated details
					
					for(ctr = 0; ctr < stopPers; ctr++) //rewrites all original details except for archived user
					{
						fprintf(preload,"%d %s\n", tempPers[ctr].personnelID, tempPers[ctr].name);
						fprintf(preload,"%s",tempPers[ctr].username);
						
						if(input.personnelID == tempPers[ctr].personnelID) //if currently selected personnel matches input, that user is archived
						fprintf(preload,"\n%s\n2\n",tempPers[ctr].password);
						else //otherwise, original detail is rewritten
						fprintf(preload,"\n%s\n%d\n",tempPers[ctr].password, tempPers[ctr].active);
						
						fprintf(preload,"%d", tempPers[ctr].access);
						fprintf(preload,"\n\n");
					}
					
					fclose(preload); //closes newly edited personnel file.
					break;
				
				case 5: //Assign project
					printf("\n\nList of Active Projects: \n");
					for(ctr = 0; ctr < stopProj; ctr++) //Goes through all projects and displays those that are active
					{
						if(tempProj[ctr].status != 3) //Projects that aren't done are considered active
						{
							activeProj[projCtr] = tempProj[ctr]; //Lists active projects in an array.
							++projCtr;//Increases number of active projects by 1 for every manager.
							printf("\n%d %s", tempProj[ctr].projectID, tempProj[ctr].name);//displays active project
						}
						
					}
					
					if(projCtr == 0) //scenario if there aren't any active projects
					{
						printf("\nThere are no active projects.");
						return 0;
					}
					
					printf("\n\nList of Managers: \n");
					for(ctr = 0; ctr < stopPers; ctr++) //goes through list of personnel and displays those with access of 2 (managers) and are active
					{
						if(tempPers[ctr].access == 2 && tempPers[ctr].active == 1)//if access is 2 then personnel is manager; if active is 1, then personnel is active
						{
							managers[manCtr] = tempPers[ctr]; //lists active managers in an array
							++manCtr;//increases number of managers by 1 for every manager.
							printf("\n%d %s", tempPers[ctr].personnelID, tempPers[ctr].name); //displays manager
						}				
					}
					
					if(manCtr == 0) //scenario if there are no managers
					{
						printf("\nThere are no managers.");
						return 0;
					}
					
					do //loop to ensure inputted project is found in the list of active projects
					{
						printf("\n\n(choose ID of project to be assigned)\n");
						scanInput(&projectID, -1, -1);
					}while(searchProjectID(activeProj, projectID, projCtr));
					
					do// loop to ensure inputted personnel is found in the list of managers
					{
						printf("\n\n(choose ID of manager to be assigned to)\n");
						scanInput(&managerID, -1, -1);
					}while(searchPersonnelID(managers, managerID, manCtr));
					
					project = fopen(fileProject, "w"); //opens new project file to write for updated details
					
					for(ctr = 0; ctr < stopProj; ctr++) //rewrites all original detais except for newly assigned project
					{
						
						fprintf(project, "%d %s\n", tempProj[ctr].projectID, tempProj[ctr].name);
						fprintf(project, "%d\n", tempProj[ctr].status);
						fprintf(project, "%.2f\n", tempProj[ctr].completion);
						fprintf(project, "%s\n", tempProj[ctr].description);
						if(projectID == tempProj[ctr].projectID) //if currently selected project matches input, updated detail is written
						fprintf(project, "%d\n\n", managerID);
						else//otherwise, original detail is rewritten
						fprintf(project, "%d\n\n", tempProj[ctr].assignID);
					}
					
					fclose(project); break;
					
				case 6: //back to main menu
					return 1; break; 
					
						
		}		
	
	return 0;
	
}

/* managerMenu provides all the features for a manager
	@param tempPers - list of personnel
	@param stopPers - number of personnel
	@return 1 if user wants to return to main menu, 0 otherwise
*/
int managerMenu(struct personnel tempPers[], int stopPers)
{
	FILE *project;//holds the latest project file
	FILE *task;//holds the latest task file
	int pick;//determines which feature to be performed
	int ctr;//counter for loops
	int stopProj;//number of projects in file
	int stopTask;//number of tasks in file
	int actProjCount = 0;//number of active projects
	int checkUser = 0; //checks if the currently selected personnel in the loop is a user
	float totalTask = 0;//total tasks under inputted project
	float doneTask = 0;//number of done tasks under inputted project
	float completion = 0;//percent of finished tasks in inputted project
	char fileProject[max];//file name for new project file
    char fileTask[max];// file name for new task file
	struct project inputProj;//details for inputted project
	struct project activeProj[max];//list of active projects
	struct task tempTask[max];//list of tasks
	struct task inputTask;//details for inputted task;
	char today[30];//date for today in the form MM/DD/YYYY
	struct project tempProj[max];//list of projects 
	
	
	//These generate the names for the new files with updated details for project/task
	filenameProject(fileProject);
	filenameTask(fileTask);
	
	
	//These both count the number of tasks/projects and store the list of tasks/projects in their respective arrays.
	stopProj = projectArray(tempProj);	
	
	stopTask = taskArray(tempTask);	
	
	//generates the date for today and stores the string in "today"
	getDateToday(today);

	//displays options
	printf("(1) Add New Project\n");
	printf("(2) Add New Task\n");
	printf("(3) Update Task\n");
	printf("(4) Show Personnel List\n");
	printf("(5) Assign Task\n");
	printf("(6) Show Project Details\n");
	printf("(7) Show Delayed Task\n");
	printf("(8) Run Project Completion\n");
	printf("(9) Back to Main Menu\n\n");
	scanInput(&pick, 1, 9);
	
	switch(pick)
	{
		case 1: //add new project
			
			printf("\n\nEnter project name (use _ instead of spaces): ");
			scanf("%s",inputProj.name);
			printf("\nEnter project description (use _ instead of spaces): ");
			scanf("%s",inputProj.description);
			
			project = fopen(fileProject, "w"); //opens new project file to write for updated details
			
			for(ctr = 0; ctr < stopProj; ctr++) //rewrites all original project details
			{
				fprintf(project, "%d %s", tempProj[ctr].projectID, tempProj[ctr].name);
				fprintf(project, "\n%d", tempProj[ctr].status);
				fprintf(project, "\n%.2f", tempProj[ctr].completion);
				fprintf(project, "\n%s", tempProj[ctr].description);
				fprintf(project, "\n%d\n\n", tempProj[ctr].assignID);
			}
			
			//writes details for new project at the end
			fprintf(project, "%d %s", tempProj[stopProj - 1].projectID + 1, inputProj.name);
			fprintf(project, "\n1");
			fprintf(project, "\n0.00");
			fprintf(project, "\n%s", inputProj.description);
			fprintf(project, "\n0\n\n");
			
			fclose(project); //closes newly updated project file
			break;	
				
		case 2: //add new task
			printf("\n\nEnter task name (use _ instead of spaces): "); 
			scanf("%s",inputTask.name);
			
			printf("\nEnter task description (use _ instead of spaces): ");
			scanf("%s",inputTask.description);
						
				do //loop to ensure inputted personnel is found in the list of personnel
				{
					checkUser = 0;
					printf("\n(Enter personnel ID to be assigned to)");
					scanInput(&inputTask.assignID, -1, -1);
					
					for(ctr = 0; ctr < stopPers; ctr++)
					{
						if(tempPers[ctr].personnelID == inputTask.assignID && tempPers[ctr].access != 3)
						checkUser = 1;
					}
					if(checkUser)
					printf("\nOnly users can be assigned tasks. Please try again.\n");
				}while(searchPersonnelID(tempPers, inputTask.assignID, stopPers) || checkUser);				
					
			do//loop to ensure inputted project is found in the list of projects
			{
				printf("\n(entering project ID to assign to)\n");
				scanInput(&inputTask.projectID, -1, -1);
			} while(searchProjectID(tempProj, inputTask.projectID, stopProj));
			
			
			inputTask.sequence = 1;
			for(ctr = 0; ctr < stopTask; ctr++) //counts how many tasks there are under the inputted project
			{
				if(inputTask.projectID == tempTask[ctr].projectID) //if the inputted assigned projectID matches the currently selected project, sequence for new task is incremented each time.
				++inputTask.sequence;
			}
			
			do //loop to ensure inputted start date is not later than end date
				{
					do //loop to ensure inputted start date is valid
					{
						printf("\nEnter start date (MM/DD/YYYY) for task: ");
						scanf("%s",inputTask.startdate);
					} while(checkDate(inputTask.startdate) != 3);
					
					do//loop to ensure inputted end date is valid
					{
						printf("\nEnter end date (MM/DD/YYYY) for task: ");
						scanf("%s",inputTask.enddate);
					} while(checkDate(inputTask.enddate) != 3);
					
					inputTask.totalDuration = computeTotalDuration(inputTask); //computation for totalDuration			
					
					if(inputTask.totalDuration < 0) //if totalDuration is negative, start date is later than end date.
					printf("\nEnd date is earlier than the start date. Please try again.\n");	
					
				} while(inputTask.totalDuration < 0);
			
			inputTask.taskID = tempTask[stopTask - 1].taskID + 1; //new task's ID is one more than the last task's ID.
			
			task = fopen(fileTask,"w"); //opens new task file to write updated details
			
			for(ctr = 0; ctr < stopTask; ctr++) //rewrites all original task details
			{
				fprintf(task, "%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
				fprintf(task, "\n%d", tempTask[ctr].sequence);
				fprintf(task, "\n%s", tempTask[ctr].description);
				fprintf(task, "\n%d", tempTask[ctr].projectID);
				fprintf(task, "\n%s", tempTask[ctr].startdate);
				fprintf(task, "\n%s", tempTask[ctr].enddate);
				fprintf(task, "\n%.2f", tempTask[ctr].totalDuration);
				fprintf(task, "\n%d", tempTask[ctr].status);
				fprintf(task, "\n%d\n\n", tempTask[ctr].assignID);
			}
			
			//writes new task's details at the end of the file
			fprintf(task, "%d %s", inputTask.taskID, inputTask.name);
			fprintf(task, "\n%d", inputTask.sequence);
			fprintf(task, "\n%s", inputTask.description);
			fprintf(task, "\n%d", inputTask.projectID);
			fprintf(task, "\n%s", inputTask.startdate);
			fprintf(task, "\n%s", inputTask.enddate);
			fprintf(task, "\n%.2f", inputTask.totalDuration);
			fprintf(task, "\n1");
			fprintf(task, "\n%d\n\n", inputTask.assignID);
			
			fclose(task);	//closes newly updated task file
			break;
			
			case 3: //update task
			
				if(stopTask == 0) //scenario if there aren't any tasks yet
				{
					printf("\nThere are no tasks to be updated.");
					return 0;
					
				}
				
				do //ensures inputted taskID is found in the list of tasks
				{
					printf("\n\n(Enter ID of task to be updated)\n");
					scanInput(&inputTask.taskID, -1, -1); 
				} while(searchTaskID(tempTask, inputTask.taskID, stopTask));
				
				printf("\nEnter new task name (use _ instead of spaces): ");
				scanf("%s",inputTask.name);
				printf("\nEnter new description (use _ instead of spaces): ");
				scanf("%s",inputTask.description);
				
				do //loop to ensure inputted start date is not later than inputted end date
				{
					do // loop to ensure start date is valid
					{
						printf("\nEnter new start date (MM/DD/YYYY) for task: ");
						scanf("%s",inputTask.startdate);
					} while(checkDate(inputTask.startdate) != 3);
					
					do //loop to ensure end date is valid
					{
						printf("\nEnter new end date (MM/DD/YYYY) for task: ");
						scanf("%s",inputTask.enddate);
					} while(checkDate(inputTask.enddate) != 3);
					
					inputTask.totalDuration = computeTotalDuration(inputTask);	//computes totalDuration in days		
					
					if(inputTask.totalDuration < 0) //displays error when end date is earlier than start date
					printf("\nEnd date is earlier than the start date. Please try again.\n");	
					
				} while(inputTask.totalDuration < 0);


				do //loop to ensure personnelID is found in the list of personnel
				{
					printf("\n(Enter personnel ID to be assigned to)");
					scanInput(&inputTask.assignID, -1, -1);
				}while(searchPersonnelID(tempPers, inputTask.assignID, stopPers));
					
				task = fopen(fileTask,"w"); //opens new task file to write for updated details.
				
				for(ctr = 0; ctr < stopTask; ctr++) //rewrites all original task details except task to be updated
				{
					if(tempTask[ctr].taskID == inputTask.taskID) //if currently selected task matches inputted task, updated details are written
					{
						fprintf(task,"%d %s", inputTask.taskID, inputTask.name);
						fprintf(task,"\n%d",tempTask[ctr].sequence);
						fprintf(task,"\n%s",inputTask.description);
						fprintf(task,"\n%d",inputTask.projectID);
						fprintf(task,"\n%s",inputTask.startdate);
						fprintf(task,"\n%s",inputTask.enddate);
						fprintf(task,"\n%.2f",inputTask.totalDuration);
						fprintf(task,"\n%d",tempTask[ctr].status);
						fprintf(task,"\n%d\n\n",inputTask.assignID);
					}
					else //if currently selected task doesn't match inputted task, original details are rewritten
					{
						fprintf(task,"%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
						fprintf(task,"\n%d",tempTask[ctr].sequence);
						fprintf(task,"\n%s",tempTask[ctr].description);
						fprintf(task,"\n%d",tempTask[ctr].projectID);
						fprintf(task,"\n%s",tempTask[ctr].startdate);
						fprintf(task,"\n%s",tempTask[ctr].enddate);
						fprintf(task,"\n%.2f",tempTask[ctr].totalDuration);
						fprintf(task,"\n%d",tempTask[ctr].status);
						fprintf(task,"\n%d\n\n",tempTask[ctr].assignID);
					}
				}
				
				fclose(task); //closes newly updated task file
				break;
			
			case 4: //show personnel list
				showPersonnel(tempPers, stopPers);
				break;
				
			case 5: //assign task
				if(stopTask == 0) //scenario if there are no tasks yet
				{
					printf("\nThere are no tasks");
					return 0;
				}
				
				do //loop to ensure inputted task ID is found in the list of tasks
				{
					printf("\n(Enter task ID for task details) \n");
					scanInput(&inputTask.taskID, -1, -1);	
				}while(searchTaskID(tempTask, inputTask.taskID, stopTask));
				
				printf("\n\n");
				
				for(ctr = 0; ctr < stopTask; ctr++) //goes through the list of tasks to display the inputted task
				{
					if(tempTask[ctr].taskID == inputTask.taskID) //displays details if currently selected task matches inputted task
					{
						printf("Task ID: %d", tempTask[ctr].taskID);
						printf("\nName: %s", tempTask[ctr].name);
						printf("\nSequence: %d", tempTask[ctr].sequence);
						printf("\nDescription: %s", tempTask[ctr].description);
						printf("\nUnder Project ID: %d", tempTask[ctr].projectID);
						printf("\nStart Date: %s", tempTask[ctr].startdate);
						printf("\nEnd Date: %s", tempTask[ctr].enddate);
						printf("\nTotal Duration: %.2f days", tempTask[ctr].totalDuration);
						printf("\nStatus: ");
						switch(tempTask[ctr].status)
						{
							case 1: printf("Not Started"); break;
							case 2: printf("In Progress"); break;
							case 3: printf("Done"); break;
						}
						printf("\nPersonnel ID assigned to: %d", tempTask[ctr].assignID);
					}					
				}

				do //loop to ensure the inputted task ID is found in the list of tasks
				{
					printf("\n\n(Enter task ID to assign)\n ");
					scanInput(&inputTask.taskID, -1, -1);					
				}while(searchTaskID(tempTask, inputTask.taskID, stopTask));

				do //loop to ensure the inputted personnel ID is found in the list of personnel and the inputted personnel has access 3 (user)
				{
					checkUser = 0;
					printf("\n(Enter personnel ID to be assigned)\n ");
					scanInput(&inputTask.assignID, -1, -1);				
					
					for(ctr = 0; ctr < stopPers; ctr++)
					{
						if(tempPers[ctr].personnelID == inputTask.assignID && tempPers[ctr].access != 3)
						checkUser = 1;
					}
					if(checkUser)
					printf("\nOnly users can be assigned tasks. Please try again.\n");
						
				}while(searchPersonnelID(tempPers, inputTask.assignID, stopPers) || checkUser);

				
				task = fopen(fileTask, "w"); //opens new task file to write for updated details
				
				for(ctr = 0; ctr < stopTask; ctr++) //rewrites all original details except for updated task
				{
					fprintf(task, "%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
					fprintf(task, "\n%d", tempTask[ctr].sequence);
					fprintf(task, "\n%s", tempTask[ctr].description);
					fprintf(task, "\n%d", tempTask[ctr].projectID);
					fprintf(task, "\n%s", tempTask[ctr].startdate);
					fprintf(task, "\n%s", tempTask[ctr].enddate);
					fprintf(task, "\n%.2f", tempTask[ctr].totalDuration);
					fprintf(task, "\n%d", tempTask[ctr].status);
					if(tempTask[ctr].taskID == inputTask.taskID) //if currently selected task matches inputted task, updated detail is written
					fprintf(task, "\n%d\n\n", inputTask.assignID);
					else //otherwise, original detail is rewritten
					fprintf(task, "\n%d\n\n", tempTask[ctr].assignID);			
				}
										
				fclose(task); //closes newly updated task file
				break;
				
			
			case 6: //show project details
				
				printf("\n\n");
				for(ctr = 0; ctr < stopProj; ctr++) //goes through list of projects to list/display active projects
				{
					if(tempProj[ctr].status != 3) //if currently selected project is not done (3), it is active
					{
						printf("%d %s\n", tempProj[ctr].projectID, tempProj[ctr].name);
						activeProj[actProjCount] = tempProj[ctr]; //lists active projects
						++actProjCount; //increases number of active projects by 1 each time an active project is found
					}
						
				}
				
				if(actProjCount == 0) //scenario if there are no active projects
				{
					printf("\nThere are no active projects.");
					return 0;
				}
				
				do //loop to ensure inputted projectID is found in the list of active projects
				{
					printf("\n(Enter ID of project to show details)\n ");
					scanInput(&inputProj.projectID, -1, -1);					
				}while(searchProjectID(activeProj, inputProj.projectID, actProjCount));

				
				for(ctr = 0; ctr < actProjCount; ctr++) //goes through the list of active projects and displays details of inputted project
				{
					if(inputProj.projectID == activeProj[ctr].projectID) //displays details if currently selected active project matches inputted project
					{
						printf("\n\nProject ID: %d", activeProj[ctr].projectID);
						printf("\nName: %s", activeProj[ctr].name);
						printf("\nStatus: ");
						switch(activeProj[ctr].status)
						{
							case 1: printf("Not Started"); break;
							case 2: printf("In Progress"); break;
							case 3: printf("Done"); break;//subject to change
						}
						printf("\nCompletion: %.2f%%", activeProj[ctr].completion);
						printf("\nDescription: %s", activeProj[ctr].description);
						printf("\nAssigned Personnel ID: %d", activeProj[ctr].assignID);
					}
				} 
				
				break;
			
			case 7: //show delayed task
				
				printf("\n\nList of delayed tasks:\n");
				
				for(ctr = 0; ctr < stopTask; ctr++) //goes through list of tasks to check/display delayed tasks
				{
					strcpy(tempTask[ctr].startdate, today);	//to fit the parameters of the computeTotalDuration function, the startdate is set to today
					
					if(tempTask[ctr].status != 3 && computeTotalDuration(tempTask[ctr]) < 0) //if the task isn't finished and today is later than its end date (negative computeTotalDuration) it is displayed
					printf("%d %s\n", tempTask[ctr].taskID, tempTask[ctr].name);
				}
				
				break;
				
			case 8: //run project completion
				if(stopProj == 0) //scenario if there are no projects
				{
					printf("\nThere are no projects.");
					return 0;
				}
				
				do //loop to ensure inputted project ID is found in the list projects
				{
					printf("\n\n(Enter project ID)\n ");
					scanInput(&inputTask.projectID, -1, -1);					
				}while(searchProjectID(tempProj, inputTask.projectID, stopProj));

				for(ctr = 0; ctr < stopTask; ctr++) //goes through each task to check if it's under the inputted project
				{
					if(inputTask.projectID == tempTask[ctr].projectID) //checks if the currently selected task's assigned project matches the inputted project
					{
						if(tempTask[ctr].status == 3) //if the task is done, the number of total tasks and done tasks under the inputted project is incremented
						{
							++totalTask;
							++doneTask;
						}
						else//otherwise the number of total tasks under the inputted project is incremented
						++totalTask;
					}
						
				}
				
				if(totalTask != 0)
				completion = (doneTask/totalTask) * 100; //computes for the percentage of the completion of the project 

				project = fopen(fileProject, "w"); //opens new project file to write for updated details
				
				for(ctr = 0; ctr < stopProj; ctr++) //rewrites all original project details except for project to be updated
				{
					fprintf(project, "%d %s", tempProj[ctr].projectID, tempProj[ctr].name);
					if(completion == 100 && tempProj[ctr].projectID == inputTask.projectID)
					fprintf(project, "\n3");
					else if(completion > 0 && tempProj[ctr].projectID == inputTask.projectID)
					fprintf(project, "\n2");
					else if(completion == 0 && tempProj[ctr].projectID == inputTask.projectID)
					fprintf(project,"\n1");				
					else
					fprintf(project,"\n%d",tempProj[ctr].status);		
					if(tempProj[ctr].projectID == inputTask.projectID)
					fprintf(project, "\n%.2f", completion);
					else
					fprintf(project, "\n%.2f", tempProj[ctr].completion);
					fprintf(project, "\n%s", tempProj[ctr].description);
					fprintf(project, "\n%d\n\n", tempProj[ctr].assignID);
				}
				
				fclose(project); //closes newly updated project file
				break;
				
				case 9: return 1; break; //return to main menu
				
	}
	
	return 0;
			
}

/* userMenu contains all features for user access
	@param personnelID - personnelID of the current user
	@return 1 to go back to main menu, 0 otherwise
*/
int userMenu(int personnelID)
{
	FILE* task; //holds task file
	int pick; //determines which feature is to be performed
	int ctr; //counter for loops
	int stopTask; //number of tasks
	int assignCtr = 0; //number of tasks assigned to current user
	int check = 1;//checks if current user has tasks assigned for the day
	char today[30];//string for the current date
	char fileTask[max];//name for new task file with updated details
	struct task tempTask[max], temp; //tempTask - list of tasks, temp - placeholder to check if today is within start date and end date 
	struct task assignTask[max];//number of tasks assigned to current user
	struct task inputTask;//details for inputted task
	
	filenameTask(fileTask); //generates name for new task file with updated details
	getDateToday(today); //generates current date as a string for "today"
	
	printf("(1) Show Today's Task\n");
	printf("(2) Show All Assigned Task\n");
	printf("(3) Update Task Status\n");
	printf("(4) Back to Main Menu\n\n");
	scanInput(&pick, 1, 4);
	
	stopTask = taskArray(tempTask); //lists the task details from the latest task file and counts the number of tasks in the list
	
	switch(pick)
	{
		case 1: //show todays' task
			printf("\n\n");
			
			for(ctr = 0; ctr < stopTask; ctr++) //goes through the list of tasks to see if today is within the start date and end date of each task assigned to the user
			{
				if(personnelID == tempTask[ctr].assignID) //checks if the currently selected task matches the current user's ID
					{
						//these two lines set the values of temp to fit the parameters of the computeTotalDuration function to check if today is earlier than the end date of the currently selected task
						strcpy(temp.startdate, today);
						strcpy(temp.enddate, tempTask[ctr].enddate);
						
						strcpy(tempTask[ctr].enddate, today); //fits the parameter of tempTask[ctr] to fit the parameters to compute totalDuration to check if today is later than the start date of the currently selected task
						
						if(computeTotalDuration(temp) >= 0 && computeTotalDuration(tempTask[ctr]) >= 0) //checks if today is between the currently selected task's start date and end date
						{
							printf("\nTask ID %d: %s\nDescription: %s", tempTask[ctr].taskID, tempTask[ctr].name, tempTask[ctr].description);
							check = 0; //represents that there are assigned tasks for today
						}
					}
			}
			
			if(check) //if check is still equal to 1, there are no assigned tasks for today
			printf("\n\nNo tasks for today.");
			
			break;
		
		case 2: //show all assigned task
			printf("\n\nList of Assigned Tasks:");
			
			for(ctr = 0; ctr < stopTask; ctr++)//goes through each task in the list of tasks to check if task's assignID matches the current user's ID
			{
				if(tempTask[ctr].assignID == personnelID) //displays the currently selected task if its assignID matches the current user's ID
				printf("\n%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
			} 
			
			break;
		
		case 3: //update task status
			printf("\n\nAssigned Tasks:");
			
			for(ctr = 0; ctr < stopTask; ctr++) //goes through each to see task in the list of tasks to check which ones are assigned to the current user
			{
				if(tempTask[ctr].assignID == personnelID) //checks if the currently selected task's assignID matches the current user's ID
				{
					printf("\n%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
					assignTask[assignCtr] = tempTask[ctr]; 
					++assignCtr; //for each task that is assigned to the current user the number of assigned tasks to the user increases by 1
				}
				
			} 
			
			if(assignCtr == 0) //scenario if the current user has no assigned tasks
			{
				printf("\nYou have no assigned tasks.");
				return 0;
			}
			
			do //loop to ensure the inputted task ID is found in the list of tasks
			{
				printf("\n\n(Enter task ID to update)\n ");
				scanInput(&inputTask.taskID, -1, -1);				
			}while(searchTaskID(assignTask, inputTask.taskID, assignCtr));

			printf("\nEnter task updated task status (1 - Not Started, 2 - In Progress, 3 - Done): ");
			scanInput(&inputTask.status, 1, 3);
			
			task = fopen(fileTask, "w"); //opens new task file to write for updated details
			
			for(ctr = 0; ctr < stopTask; ctr++) //rewrites all original task details except for the updated task's
			{
				fprintf(task, "%d %s", tempTask[ctr].taskID, tempTask[ctr].name);
				fprintf(task, "\n%d", tempTask[ctr].sequence);
				fprintf(task, "\n%s", tempTask[ctr].description);
				fprintf(task, "\n%d", tempTask[ctr].projectID);
				fprintf(task, "\n%s", tempTask[ctr].startdate);
				fprintf(task, "\n%s", tempTask[ctr].enddate);
				fprintf(task, "\n%f", tempTask[ctr].totalDuration);
				if(inputTask.taskID == tempTask[ctr].taskID) //updates the currently selected task if it matches the inputted task
				fprintf(task, "\n%d", inputTask.status);
				else //otherwise the original detail is rewritten
				fprintf(task, "\n%d", tempTask[ctr].status);
				fprintf(task, "\n%d\n\n", tempTask[ctr].assignID);
			}
			
			fclose(task); //closes the newly updated task file
			break; 
			
			
		case 4: return 1; break; //return to main menu
	}
	
	return 0;
	
}

int main()
{
	FILE *preload; //holds latest personnel file or preloaded file
	char username[40]; //inputted username
	char password[40]; //inputted password
	char filePersonnel[max]; //name for new personnel file to write updated details
	struct personnel tempPers[max]; //list of personnel
	
	int ctr; //counter for loops
	int log; //checks if the login was successful (username and password match)
	int stopPers; //number of personnel
	int access; //access for the current user if login was successful
	int checkMenu; //checks if user is to go back to login screen
	int personnelID; //personnel ID of current user
	int ID; //personnel ID of current user
	int temporary; //checks if personnel details are to be updated if new password is set
	
	filenamePersonnel(filePersonnel);//generates file name for the new file where updated personnel are to be written
	stopPers = personnelArray(tempPers);//lists the personnel in an array and counts the number of personnel
	
	do //loop if the user decides to go back to the main menu
	{
		log = 0;
		
		do //loop if login was unsuccessful
		{
			temporary = 0;
			printf("Enter username: ");
			scanf("%s",username);
			printf("\nEnter password: ");
			scanf("%s",password);
			
			for(ctr = 0; ctr < stopPers; ctr++) //goes through the list of personnel to check if the inputs match the details of a personnel
			{
				if(!strcmp(username, tempPers[ctr].username) && !strcmp(password, tempPers[ctr].password) && tempPers[ctr].active != 2) //checks if the username and password match and if the user is still active
				{
					log = 1;
					access = tempPers[ctr].access;
					ID = tempPers[ctr].personnelID;
					
					if(!strcmp(password, "temp")) //user has to change password after first login
					{
						temporary = 1; //tells the system that personnel details have to be updated with new password
						do //loop to ensure the password is still not temp
						{
							printf("\nEnter new password: ");
							scanf("%s", password);
							personnelID = tempPers[ctr].personnelID;
							if(!strcmp(password, "temp"))
							printf("\nNew password must not be 'temp'.Please try again.\n");				
						}while(!strcmp(password, "temp"));

					}
				}
			}
			

			if(temporary) //updates details if new password was set
			{
				preload = fopen(filePersonnel, "w"); //opens new personnel file to write updated details
				
				for(ctr = 0; ctr < stopPers; ctr++) //rewrites all original details except user with new password
				{
					fprintf(preload,"%d %s\n", tempPers[ctr].personnelID, tempPers[ctr].name);
					fprintf(preload,"%s",tempPers[ctr].username);
					if(personnelID == tempPers[ctr].personnelID) //checks if the currently selected personnel matches the current user's ID and updates new password
					fprintf(preload,"\n%s", password);
					else//otherwise, original detail is rewritten
					fprintf(preload,"\n%s",tempPers[ctr].password);
					fprintf(preload,"\n%d\n",tempPers[ctr].active);
					fprintf(preload,"%d\n\n", tempPers[ctr].access);				
				}
				
				printf("\nPlease restart the program and login again\n");
				fclose(preload); //closes newly updated personnel file
				
				return 0;
			}


			if(log)
			printf("\nSuccessful Login\n\n");
			else
			printf("\nError. Please try again.\n\n");		
			
		} while(!log);
	
		
		switch(access) //determines which menu to be shown depending on current user's access
		{
			case 1: checkMenu = adminMenu(tempPers, stopPers); break;
			case 2: checkMenu = managerMenu(tempPers, stopPers); break;
			case 3: checkMenu = userMenu(ID); break;
		}
		
		
	} while(checkMenu);
		
	
	
	return 0;
}
