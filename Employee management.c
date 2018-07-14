#include <stdio.h> //for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //for windows related functions
#include <string.h>  //string operations

/** structure that represent a employee */
  struct emp
    {
        char name[40], search[40]; //name of employee
        int age; // age of employee
        float bs;
		char date[12]; // basic salary of employee
    };
    
/* Main function */
int main()
{
    FILE *fp, *ft; // file pointers
    char another, choice,search[40];

    struct emp e; // structure variable creation
    char empname[40]; //string to store name of the employee
    long int recsize; //size of each record of employee

    /* open file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    // size of each record i.e. size of structure variable e
    recsize = sizeof(e);

    // infinite loop continues until the break statement encounter
    while(1)
    {
        system("cls"); //clear the console window
        
        printf("\t***** EMPLOYEE RECORD MANAGEMENT SYSTEM *****\n\n");
        
        printf("\t\t1. Add Record\n"); // option for add record
        
        printf("\t\t2. List Records\n"); // option for showing existing record
         
        printf("\t\t3. Search Records\n"); //option for searching employee record
       
        printf("\t\t4. Modify Records\n"); // option for editing record
        
        printf("\t\t5. Delete Records\n"); // option for deleting record
        
        printf("\t\t6. Exit\n"); // exit from the program
        
        printf("\t\t\nEnter Your Choice: "); // enter the choice
        fflush(stdin); /// flush the input buffer
        choice  = getche(); // get the input from keyboard
        
        switch(choice)
        {
        case '1':
            system("cls");
            fseek(fp,0,SEEK_END); // search the file and move cursor to end of the file
            // here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while(another == 'y'|| another == 'Y')  // if user want to add another record
            {
                printf("\n\nEnter Employee name: ");
                scanf("%s",e.name);
                printf("\nEnter Employee age: ");
                scanf("%d", &e.age);
                printf("\nEnter Employee basic salary: ");
                scanf("%f", &e.bs);
                printf ("\nEnter Date of Joining of Employee(dd/mm/yyyy): ");
                scanf("%s", &e.date);

                fwrite(&e,recsize,1,fp); /// write the record in the file

                printf("\nDo you want to add another employee record? Type y/n: ");
                fflush(stdin);
                another = getche();
            }
            break;
            
        case '2':
            system("cls");
            rewind(fp); // this moves file cursor to start of the file
            while(fread(&e,recsize,1,fp)==1)  // read the file and fetch the record one record per fetch
            {
                printf("\n%s %d %.2f %s",e.name,e.age,e.bs,e.date); /// print the name, age and basic salary
            }
            getch();
            break;
            
             case '3':
          system("cls");
          another='y';
          while(another == 'y'|| another == 'Y')
             {
               printf("\n\nEnter the search name: ");
               scanf("%s", search);
               rewind(fp);
               while(fread(&e,recsize,1,fp)==1)  // fetch all record from file
                {
                    if(strcmp(e.name,search) == 0)  //if entered name matches with that in file
                    {
                        printf("\n\nEmployee found.\n");
                        break;
                    }                  
                }
                if(strcmp(e.name,search)!=0)
                    printf("Employee not found.");
            printf("\nDo you want to search for another employee? Type y/n: ");
                fflush(stdin);
                another = getche();
            }
            break;

        case '4':  // if user press 3 then do editing existing record
            system("cls");
            another = 'y';
            while(another == 'y'|| another == 'Y')
            {
                printf("\n\nEnter employee name to modify record: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  // fetch all record from file
                {
                    if(strcmp(e.name,empname) == 0)  //if entered name matches with that in file
                    {
                        printf("\n\nEnter new details of %s: ",empname);
                        scanf("%s %d %f",e.name,&e.age,&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); // move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); // override the record
                        printf("\nModification successful.\n");
                        break;      
                    }
                }
                printf("\nDo you want to modify another employee record? Type y/n: ");
                fflush(stdin);
                another = getche();
            }
            break; 
            
        case '5':
            system("cls");
            another = 'y';
            while(another == 'y'|| another == 'Y')
            {
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(e.name,empname) != 0)  /// if the entered record match
                    {
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                printf("Do you want to delete another record? Type y/n: ");
                fflush(stdin);
                another = getche();
            }
            break;
            
        case '6':
            fclose(fp);  // close the file
            exit(0); // exit from the program
            break;

       
}
  
            
        }
        
    
    return 0;
}

