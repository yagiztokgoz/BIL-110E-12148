#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void list(); // func prototype of list function

void add_an_extra_line_to_file(){ // adding extra \n to end of file because we want a fresh start.

    FILE *fptr1; // creating pointer 
    fptr1 = fopen("todo.txt", "a"); //opening up file in " a " mode.
    fprintf(fptr1, "\n"); // adding "\n"
    fclose(fptr1); // closing file
}

void delete(){ // deletes specific line from the text file.

 FILE *fptr1, *fptr2;  //creating pointers

    char file1[] ="todo.txt"; //creating text files
    char file2[] ="temporary.txt"; // creating text files
    char curr; 
    int del, line_number = 0;
    printf("\n"); // blank line for esthatic.
    list(); //listing contents in order to delete operation
    printf("\n"); // blank line for esthatic
    printf("Please enter the line number you want to delete : "); //getting info of line number
    scanf("%d", &del); //assigning user info to variable del
    fptr1 = fopen(file1,"r"); //opening file1 in read only mode
    fptr2 = fopen(file2, "w"); //opening file2 in write mode
    curr = getc(fptr1); //getting chars of fptr1 (file1)
    if(curr!=EOF) {line_number =1;} //checking if line 1 is not eof and then assigning line number to 1
    while(1){ // an infinite loop
      if(del != line_number) //checking whether del = line number or not
        putc(curr, fptr2); //writing chars to file2
        curr = getc(fptr1); //getting chars of next line
        if(curr =='\n') line_number++; //adding up 1 to line number
        if(curr == EOF) break; // breaking loop if it reachs end of file
    }
    fclose(fptr1); //closing file1
    fclose(fptr2); //closing file2
    remove("todo.txt"); // removing todo.txt because we do not need it anymore
    rename("temporary.txt", "todo.txt"); //renaming temporary.txt to todo.txt because temporary.txt is now our new file.
}

void list(){ //list function to list all contents of todo.list

    FILE *file = fopen("todo.txt", "r"); //opening todo.txt in read only mode
    if(file == NULL){ //basic check if file is accesible or not
        perror("Unable to open this file");
        exit(1); //exiting program
    }
    int counter = 1; // a counter which will be helpful to order lines
    char line[100]; 
    printf("\n"); // for esthatic
    while(fgets(line, sizeof(line), file)){ // an while loop for getting all lines from file1
        if(line[0] != '\n'){ // sometimes when we delete line 1, blank line may be occur. this check is for preventing it to happen.
        printf("%d- ", counter); // ordering lines to make delete operation more easily.
        printf("%s", line); // printing line by line
        counter++;  } // adding up 1 to counter
    }
    fclose(file); // closing file,  because we are going to delete todo.txt later.
}

void add(){ //a function to add item to todo.list

    FILE *fPointer; //assigning pointer
    fPointer = fopen("todo.txt", "a"); // mode is 'a' because we want former informations.
    char str[100]; 
    printf("Type what you would like to add to your TODO List: ");
    scanf("%s",str); //assigning item to variable. usage of whitespaces lead to weird bugs, so use '_' between words.
    fprintf(fPointer, str); // adding user input no whitespaces!
    fprintf(fPointer, "\n"); // adding "\n" character
    fclose(fPointer); // closing file
}

int main(void){

    add_an_extra_line_to_file(); // calling function

    printf("Welcome to the TODO APP!\n");
    printf("You need to use '_' instead of whitesepace character..."); // as mentioned, still could not resolve issue about whitespace chars.
    while(1){ // main software loop

        printf("\n");
        printf("\nPress 1 if you would like to read contents of TODO List! \n"); // a simple ui
        printf("Press 2 if you would like to add things to TODO List! \n"); 
        printf("Press 3 if you would like to delete a row.\n");

        int choice; // this will be used as user's choice
        printf("Your choice: "); 
        scanf("%d", &choice); // assigning user input to our choice variable

        //basic checks
        if(choice == 1){
            list(); // calling list function
        }
        else if(choice == 2){
            add(); // calling add function
        }
        else if(choice == 3){
            delete(); // calling delete function
        }

        else if(choice == 4){
            return 0; // succesfully exited program.
        }
        else{
            printf("Invalid input please try again."); // user may type invalid inputs.
        }
    
        choice = 0; // reassing choice to 0.
    }

}
