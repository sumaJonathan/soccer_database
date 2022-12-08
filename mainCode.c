#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Define data structure*/
typedef struct{
  char team[30];
  char league [20];
  int goals;
  float shots;
  int cards;
  float passes;
  float possession;
}soccer_t;

/*Function Prototypes*/
int readFile(soccer_t list[]);
void displayRecs(int items, soccer_t sortList[]);

void sortFunc(int items, soccer_t table[]);
void sortByName(int items, soccer_t sortList[]);
void sortByLeague(int items, soccer_t sortList[]);
void sortByGoals(int items, soccer_t sortList[]);
void searchFunc(int items, soccer_t sortList[]);
void searchTeams(int items, soccer_t sortList[]);
void searchLeague(int items, soccer_t sortList[]);
void searchGoals(int items, soccer_t sortList[]);
void newFileFunc(int items, soccer_t sortList[]);
void addRecord(int items, soccer_t sortList[]);
void deleteRec(int items, soccer_t sortList[]);
void mainMenu(int items, soccer_t standings[]);

int main(void) {
  int i, numRecords;
  char opt, junk; //to handle the junk key presses
  soccer_t *array = (soccer_t*)malloc(100 * sizeof(soccer_t)); //allocate the needed memory
  
  printf("Welcome to the Multi-League Soccer Database version 1.9! \n\n");
  printf("This database stores statistics for soccer teams in different European leagues season 2021-2022.\nIt contains 7 entries: the team's name, its league, number of goals scored, average shots made,\nnumber of cards received, percentage success of passes made, and average possession per game.\nYou can search, sort, and make any changes you'd like!\n");
  printf("But, first...\n\nDo you want to:\n");
  
  numRecords = readFile(array);  //Read file 
  printf("\n");
  mainMenu(numRecords, array);  //Call the main menu method
  
  return 0;
}

/*
Method open and read contents of the soccer listings file
*/
int readFile(soccer_t list[]){
  
  FILE *sFile; //open file
  
  int i, j; //loop counters
  char counter, junk[9], jnk;//junk array and jnk to cater for unwanted keys.
  char forName;
  int records = 0; 
  char fName[20];
  
  /*Give user option to choose new file or use default file*/
  printf("1. Enter new name file name\n[2. Use default file name (soccer.txt)]\n\nSelect (1, 2) [2]: ");
  scanf ("%c", &forName);
  
  //Error message if invalid entry
  
  while (forName != '1' && forName != '2' && forName != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry!\n1. Enter new name\n[2. Use default file name (soccer.txt)]\nSelect (1, 2) [2]: ");
    scanf ("%c", &forName);
  }
  //default '\n' to use default file
  if (forName == '\n') {
    forName = '2';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  printf("You entered: %c\n\n", forName);
  if (forName == '1'){
    printf("Enter your file name: ");//User's file name
    scanf("%[^\n]", fName);
    scanf("%c", &jnk);
  }
  else if (forName == '2'){
    strcpy(fName, "soccer.txt");//Use soccer.txt for file name
  }

  sFile = fopen(fName, "r");//open file for reading
  while (sFile == NULL){//Error message if file not found
    printf("Error! File not found.\nPlease upload a file.\n\n");
    printf("Enter your file name: ");
    scanf("%[^\n]", fName);
    scanf("%c", &jnk);
  
    sFile = fopen(fName, "r");
  }
  //Take count of number of elements in file
  if  (sFile != NULL){
    while (fscanf(sFile, "%c", &counter) != EOF){
      if (counter == '\n'){
        records++;
      }
    }
    fclose(sFile);//close file

    
    sFile = fopen(fName, "r");//re-open file to scan values into structure array

    for (i = 0; i < records; i++){
      fscanf(sFile,"%[^,],%[^,],%d,%f,%d,%f,%f%[^\n]%c", list[i].team, list[i].league,&list[i].goals, &list[i].shots, &list[i].cards, &list[i].passes, &list[i].possession, junk, &jnk);
    }

    fclose(sFile);//close file
  }

  return (records);//return count of elements in file
}
/*Main sort function*/
void sortFunc(int items, soccer_t table[]){
  int index[items];
  int j, i;
  char choice, bin[50], jnk;

  printf("Sort by:\n[n] Name\n[g] Goals\n[l] League\n");
  printf("Sort your display (n, l, g) [n].\nEntry: ");

  scanf("%c", &choice);
  
  while(choice !='n' && choice !='l'&& choice !='g' && choice != '\n'){
    scanf("%[^\n]", bin);
    scanf("%c", &jnk);
    printf("\nInvalid entry! Try again (n, l, g) [n]: ");
    scanf("%c", &choice);
  }
  if (choice == '\n'){
    choice = 'n';
    } else {
    scanf("%[^\n]", bin);
    scanf("%c", &jnk);
  }
  
  printf("You entered: %c\n\n", choice);
  switch (choice){
      case 'n':
      sortByName(items, table);
      break;
    
      case 'l':
      sortByLeague(items, table);
      break;
    
      case 'g':
      sortByGoals(items, table);
      break;
    } 
}
/*sorting by team name in alphabetical order*/
void sortByName(int items, soccer_t sortList[]){
  soccer_t fileSort[items];
  
  int index[items];
  int i, j, swap;
  char junks[30], jnk;
  
  for (j=0; j < items; j++){
    index[j] = j;
  }
  /*Bubble sort the array based on teams */
  for (i=0; i < items-1; i++){
    for (j = 0; j < items-1; j++){
      if (strcmp(sortList[index[j]].team, sortList[index[j+1]].team) > 0){
        swap = index[j];
        index[j] = index[j+1];
        index[j+1] = swap;
      }
    }
  }

  for (i=0; i < items;  i++){
    fileSort[i] = sortList[index[i]];//Copy the sorted array to a parallel array
  }
  
  for (i=0; i<items; i++){
    sortList[i] = fileSort[i];//Copy contents to original array
  }
  
  displayRecs(items, sortList);
  printf("Standings successfully sorted!\n\n");
  mainMenu(items, sortList);//Back to main menu
}
/*sorting by leagues in alphabetical order*/
void sortByLeague(int items, soccer_t sortList[]){
  soccer_t fileSort[items];
  int index[items];
  int i, j, swap;
  
  
  for (j = 0; j < items; j++){
    index[j] = j;
  }
/*Bubble sort the array */
  for (i=0; i<items-1; i++){
    for (j=0; j < items-1; j++){
      if (strcmp(sortList[index[j]].league, sortList[index[j+1]].league) > 0){
        swap = index[j];
        index[j] = index[j+1];
        index[j+1] = swap;
      }
    }
  }
  for (i=0; i<items;  i++){
    fileSort[i] = sortList[index[i]];//Copy the sorted array to a parallel array
  }
  for (i=0; i<items; i++){
    sortList[i] = fileSort[i];//Copy contents to original array
  }
  
  displayRecs(items, sortList);
  printf("Standings successfully sorted!\n\n");
  mainMenu(items, sortList);//Back to main menu
}
/*sorting data by goals in descending order*/
void sortByGoals(int items, soccer_t sortList[]){
  soccer_t fileSort[items];
  int index[items];
  int i, j, swap;

  for (j=0; j < items; j++){
    index[j] = j;
  }
/*Bubble sort the array */
  for (i=0; i < items-1; i++){
    for (j=0; j < items-1; j++){
      if (sortList[index[j]].goals < sortList[index[j+1]].goals){
        swap = index[j];
        index[j] = index[j+1];
        index[j+1] = swap;
      }
    }
  }
 
  for (i=0; i<items;  i++){ 
    fileSort[i] = sortList[index[i]];//Copy the sorted array to a parallel array
  }
  for (i=0; i<items; i++){
    sortList[i] = fileSort[i];//Copy contents to original array 
  }
  displayRecs(items, sortList);
  printf("Standings successfully sorted!\n\n");
  mainMenu(items, sortList);//Back to main menu
}
/*Display data in the current order*/
void displayRecs(int items, soccer_t standings[]){
  int i;
  for (i=0; i<50; i++){
    printf("__");
  }
  printf("\n");
  printf("Team\t\t\t\t\t\tLeague\t\t\t   Goals    Shots\t   Cards\tPasses\t\tPossession\n");
  
  for (i=0; i<50; i++){
    printf("––");
  }
  printf("\n");

  for (i=0; i < items; i++){
    printf("%-26s\t%-15s\t%5d\t%8.1f\t%5d\t%8.1f\t%8.1f\n", standings[i].team, standings[i].league, standings[i].goals, standings[i].shots, standings[i].cards, standings[i].passes, standings[i].possession);
  }
  
  for (i=0; i<50; i++){
    printf("==");
  }
  printf("\n\n");

}
/*main search function*/
void searchFunc(int items, soccer_t sortList[]){
  char select;
  char junk[50];
  char jnk;
  //Choose how to search
  printf("Search for teams by:\n");
  printf("\t\t[t] team name\n");
  printf("\t\t[l] league\n");
  printf("\t\t[g] total goals\nEntry(t, l, g) [t]: ");
  scanf("%c", &select);
 
  while (select != 't' && select != 'l' && select != 'g' && select != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry! Please try again: ");
    scanf("%c", &select);
  }
  //default '\n' to searching by team name
  if (select == '\n'){
    select = 't';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  
  printf("You entered: %c\n", select);
  switch (select){
    case 't':
    searchTeams(items, sortList);//search by league function
    break;
    
    case 'l':
    searchLeague(items, sortList);//search by league function
    break;
    
    case 'g':
    searchGoals(items, sortList);//search by goal function
    break;
  }
  
}
/*search by teams*/
void searchTeams(int items, soccer_t sortList[]){
  char findTeam[30];
  char option, junk[50], jnk;
  int j, found = 0;
  
  printf ("What team are you searching for?\nEnter exact full team name: ");
  scanf("%[^\n]", findTeam);
  scanf("%c", &jnk);
  
  printf("\n\n");
  //Search for similar record and print
  for (j=0; j<items;j++){
    if (strcmp(sortList[j].team, findTeam) == 0){
      printf("%d. ", (j+1));
      printf("%-26s\t%-15s\t%5d\t%8.1f\t%5d\t%8.1f\t%8.1f\n", sortList[j].team, sortList[j].league, sortList[j].goals, sortList[j].shots, sortList[j].cards, sortList[j].passes, sortList[j].possession);
      found++;
    }
  }
  //No record found
  if (found == 0){
      printf("No marching records in file.");
    }
  printf("\n\n");
  
  printf ("\n\nSelect:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
  scanf ("%c", &option);
  //Error message for invalid entries
  while (option != 's' && option != 'm' && option != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry! Select:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
    scanf ("%c", &option);
  }
  //set default to search menu
  if (option == '\n'){
    option = 's';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  
  if (option == 's'){
    searchFunc(items, sortList);
  } 
  else if(option == 'm') {
    mainMenu(items, sortList);//Back to main menu
  }
}
/*search by league*/
void searchLeague(int items, soccer_t sortList[]){
  char findLeague[30];
  char option, junk[50], jnk;
  int j, found = 0;
  
  printf ("What league are you searching for?\nEnter exact full league name: ");
  scanf("%[^\n]", findLeague);
  scanf("%c", &jnk);
  
  printf("\n\n");
  //Search for similar record and print
  for (j=0; j<items;j++){
    if (strcmp(sortList[j].league, findLeague) == 0){
      printf("%d. ", (j+1));
      printf("%-26s\t%-15s\t%5d\t%8.1f\t%5d\t%8.1f\t%8.1f\n", sortList[j].team, sortList[j].league, sortList[j].goals, sortList[j].shots, sortList[j].cards, sortList[j].passes, sortList[j].possession);
      found++;
    }
  }
  printf("\n\n");
  //No record found
  if(found == 0){
    printf("\nNo marching records found.\n\n");
  }
  
  printf ("Select:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
  scanf ("%c", &option);
//Error message for invalid entries
  while (option != 's' && option != 'm' && option != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry! Select:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
    scanf ("%c", &option);
  }
  
  if (option == '\n'){
    option = 's';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  //set default to search menu
  if (option == 's'){
    searchFunc(items, sortList);
  } 
  else if(option == 'm') {
    mainMenu(items, sortList);//Back to main menu
  }
}
/*search by goals*/
void searchGoals(int items, soccer_t sortList[]){
  int lower, upper;
  int i, found = 0;
  char option;
  char junk[20], jnk; //tak care of junks

  do{//Range of values being searched
    printf("Enter lower bound goals: ");
    scanf("%d", &lower);
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    
    printf("Enter upper bound for goals: ");
    scanf("%d", &upper);
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    
    }while (upper < lower);
  
  printf("\n\n");
  //print out teams with goals meeting user's preferences
  for (i = 0; i < items; i++){
    if (sortList[i].goals >= lower && sortList[i].goals <= upper){
      printf("%d. ", (i+1));
      printf("%-26s\t%-15s\t%5d\t%8.1f\t%5d\t%8.1f\t%8.1f\n", sortList[i].team, sortList[i].league, sortList[i].goals, sortList[i].shots, sortList[i].cards, sortList[i].passes, sortList[i].possession);
      found++;
    }
  }
  //No record found
  if (found == 0){
    printf("No matching records found!");
  }

  printf("\n\n");
  printf ("Select:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
  scanf ("%c", &option);
  //Error message for invalid entries
  while (option != 's' && option != 'm' && option != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry! Select:\n\t[s] for Search Menu\n\t[m] for Main Menu\nEntry: ");
    scanf ("%c", &option);
  }
  //set default to search menu
  if (option == '\n'){
    option = 's';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  
  if (option == 's'){
    searchFunc(items, sortList);
  } 
  else if(option == 'm') {
    mainMenu(items, sortList);//Back to main menu
  }
}

void mainMenu(int items, soccer_t *standings){
  char opt, junk[100], jnk;
  int end = 0;
  //Menu options
  printf("=====================\n\tMAIN MENU\n");
  printf("[v] Display listings\n");
  printf("[r] Search for data\n");
  printf("[t] Sort standings\n");
  printf("[d] Delete record\n");
  printf("[a] Add new record\n");
  printf("[s] Save records\n");
  printf("[q] Quit\n");
  printf("=====================\n");

  printf("\nEnter your option(v, r, t, d, a, s, q)[v]: ");
  scanf("%c", &opt);
  //Error message if invalid input
  while (opt != 'v' && opt != 'r' && opt != 't' && opt != 'd' && opt != 'a' && opt != 's' && opt != 'q'&& opt != '\n'){
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
    printf("Invalid entry!\nEnter your option (v, r, t, d, a, s, q) [v]: ");
    scanf("%c", &opt);
  }
  
  if (opt == '\n'){//'\n' to default view standings
    opt = 'v';
  } else {
    scanf("%[^\n]", junk);
    scanf("%c", &jnk);
  }
  
  printf("You entered: %c\n\n", opt);
  /*Call respective functions*/
  switch (opt){
    case 'v':
    displayRecs(items,standings);
    mainMenu(items, standings);//back to main menu
    break;

    case 'r':
    searchFunc(items, standings);
    break;
    
    case 't':
    sortFunc(items, standings);
    break;
    
    case 'd':
    deleteRec(items, standings);
    break;
    
    case 'a':
    addRecord(items, standings);
    break;

    case 's':
    newFileFunc(items, standings);
    break;
    
    case 'q':
    printf("Terminating program!\n");//Option to quit program
    end = 1;
    break;
  }
}

void newFileFunc(int items, soccer_t sortList[]){
  
  FILE *sFile;
  int i;
  char write, jnk, display;
  char fname[20], junks[40];
  
  printf("Enter your file name (with file format eg .txt or .csv): ");
  scanf("%[^\n]", fname);
  scanf("%c", &jnk);
  
  sFile = fopen(fname, "r"); // open file.

  if (sFile != NULL) {//Warn the user against overwrite
    printf("The file already exists!\nDo you wish to overwrite? (Results in permanent changes to file)\n\t[x] No, I don't want to overwrite\n\t[y] Yes, I want to overwrite existing file!\nEntry: ");
    scanf("%c", &write);
    //error message for invalid entry
    while (write != 'x' && write != 'y' && write != '\n'){
      scanf("%[^\n]", junks);
      scanf("%c", &jnk);
      printf("Invalid entry!\nDo you wish to overwrite existing file?\n\t[x] No\n\t[y] Yes\nEntry: ");
      scanf("%c", &write);
    }
    if (write == '\n'){
      write = 'x';
    }else{
      scanf("%[^\n]", junks);
      scanf("%c", &jnk);
    }
    
    if (write == 'x'){
      printf("Aborting overwrite! Creating new File instead...\n\n");
      newFileFunc(items, sortList);//Restart function to create new file instead
    }

    else if (write == 'y'){
      fclose (sFile); //close the filled file

      sFile = fopen(fname, "w"); //reopen and overwrite
      
      for (i = 0; i < items; i++){
        fprintf(sFile,"%s,%s,%d,%.1f,%d,%.1f,%.1f\n", sortList[i].team, sortList[i].league, sortList[i].goals, sortList[i].shots, sortList[i].cards, sortList[i].passes, sortList[i].possession);
      }
      fclose(sFile); //close file
      printf("Overwrite successful!\n\n");
    }
  }

  else if(sFile == NULL) {
    printf("Creating new file...");
    sFile = fopen(fname, "w"); //open new write and write to it
    
    for (i=0; i < items; i++){
      fprintf(sFile,"%s,%s,%d,%.1f,%d,%.1f,%.1f\n", sortList[i].team, sortList[i].league, sortList[i].goals, sortList[i].shots, sortList[i].cards, sortList[i].passes, sortList[i].possession);
    }
    fclose(sFile); //close file
    printf("Done!\n\n");
  }
  //Give user option to view or not
  printf("You can:\n\t[w] view new file\n\t[m] back to Main Menu\nEntry (w, m)[w]: ");
  scanf("%c", &display);
  
  while (display != 'w' && display != 'm' && display != '\n'){
    scanf("%[^\n]%c", junks, &jnk);
    printf("Invalid entry! Enter:\n\t[w] view new file\n\t[m] back to Main Menu\n Enter (w, m)[w]: \n");
    scanf("%c", &display);
  }
  if(display == '\n'){
    display = 'w';
  }else {
    scanf("%[^\n]", junks);
    scanf("%c", &jnk);
  }

  if (display == 'w'){
    displayRecs(items, sortList);//display file for view then back to main menu
    mainMenu(items, sortList);
  }
  
  else if (display == 'm'){
    mainMenu(items, sortList);//back to main menu
  }
}

void addRecord(int items, soccer_t sortList[]){
  char junks[50], jnk;
  char choice;
/*Ask user for inputs and add them to structure array*/
  printf("Enter team name: ");
  scanf("%[^\n]", sortList[items].team);
  scanf("%c", &jnk);
  
  printf("Enter league: ");
  scanf("%[^\n]", sortList[items].league);
  scanf("%c", &jnk);
  
  printf("Enter goals in latest season: ");
  scanf("%d", &sortList[items].goals);
  scanf("%[^\n]", junks);
  scanf("%c", &jnk);
    
  printf("Enter team's average shots per game: ");
  scanf("%f", &sortList[items].shots);
  scanf("%[^\n]", junks);
  scanf("%c", &jnk);
    
  printf("Enter cards received in latest season: ");
  scanf("%d", &sortList[items].cards);
  scanf("%[^\n]", junks);
  scanf("%c", &jnk);
  
  printf("Enter team's average passes per game: ");
  scanf("%f", &sortList[items].passes);
  scanf("%[^\n]", junks);
  scanf("%c", &jnk);
    
  printf("Enter team's average possesssion per game: ");
  scanf("%f", &sortList[items].possession);
  scanf("%[^\n]", junks);
  scanf("%c", &jnk);
  
  items++;//add 1 to element counter
  
  printf("\nRecord added successfully!\n\n");
  displayRecs(items, sortList);
  mainMenu(items, sortList);//back to main menu
  }

void deleteRec(int items, soccer_t sortList[]){
  char xteam[30], jnk, junk[50], choice;
  int j, index, found = 0;
  
  printf ("Which team's records would like to delete?\n Enter exact full team name: ");
  scanf("%[^\n]", xteam);
  scanf("%c", &jnk);
  //Compare user's entry to team names
  for (j=0; j<items;j++){
    if (strcmp(xteam, sortList[j].team) == 0){
      index = j; //initialize index variable with index of found record
      found++;//increase found elements by 1
    }
  }
  
  if (found == 0){ //No records found
    printf("Record not found!\n\n");
    mainMenu(items, sortList);
  }
  else{
    for (j = index; j<items; j++){
      sortList[j] = sortList[j+1]; //Switch indexes by 1 backward
    }
    --index;//delete record input by the user
    items--;//decrease count of items
    
    printf("Record deleted successfully!\n\n");
    displayRecs(items, sortList);
    mainMenu(items, sortList);//back to main menu
  }
}