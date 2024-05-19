#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>  

int main()
{
    FILE *pf, *tf; 
    char other, option;

    struct emp
    {
        char name[50];
        int age; 
        float ds;  
    };

    struct emp e; 

    char emp_name[40]; 

    long int recsize; 

    pf = fopen("EMP.DAT","rb+");
    if(pf == NULL)
    {
        pf = fopen("EMP.DAT","wb+");
        if(pf == NULL)
        {
            printf("Cannot open the file");
            exit(1);
        }
    }


    recsize = sizeof(e);

    while(1)
    {
        system("cls"); 
        printf("\n1. Add Records\n"); 
        printf("\n2. List Records\n"); 
        printf("\n3. Modify Records\n"); 
        printf("\n4. Delete Records\n"); 
        printf("\n5. Exit\n");
        printf("\nPlease enter your choice: "); 
        fflush(stdin);
        option  = getche(); 
        switch(option)
        {
        case '1':  
            system("cls");
			fseek(pf,0,SEEK_END);
            other = 'y';
            while(other == 'y')  
            {
                printf("\nPlease enter the employee's name: ");
                scanf("%s",e.name);
                printf("\nPlease enter the employee's age: ");
                scanf("%d", &e.age);
                printf("\nPlease enter the basic salary: ");
                scanf("%f", &e.ds);

                fwrite(&e,recsize,1,pf);

                printf("\nWould you like to add another record ? (y/n)");
                fflush(stdin);
                other = getche();
            }
            break;
            
        case '2':
            system("cls");
            rewind(pf); 
            while(fread(&e,recsize,1,pf)==1) 
            {
                printf("\n%s %d %.2f",e.name,e.age,e.ds); 
            }
            getch();
            break;

        case '3':  
            system("cls");
            other = 'y';
            while(other == 'y')
            {
                printf("\nPlease enter the employee's name to modify it: ");
                scanf("%s", emp_name);
                rewind(pf);
                while(fread(&e,recsize,1,pf)==1)  
                {
                    if(strcmp(e.name,emp_name) == 0) 
                    {
                        printf("\nPlease enter new name, age and basic salary: ");
						scanf("%s%d%f",e.name,&e.age,&e.ds);
						fseek(pf,-recsize,SEEK_CUR);
                        fwrite(&e,recsize,1,pf); 
                        break;
                    }
                }
                printf("\nWould you like to modify another record ? (y/n)");
                fflush(stdin);
                other = getche();
            }
            break;
            
        case '4':
            system("cls");
            other = 'y';
            while(other == 'y')
            {
                printf("\nPlease enter the name of employee to delete it: ");
                scanf("%s",emp_name);
                tf = fopen("Temp.dat","wb"); 
                rewind(pf); 
                while(fread(&e,recsize,1,pf) == 1)  
                {
                    if(strcmp(e.name,emp_name) != 0)  
                    {
                        fwrite(&e,recsize,1,tf); 
                    }
                }
                fclose(pf);
                fclose(tf);
                remove("EMP.DAT"); 
                rename("Temp.dat","EMP.DAT"); 
                pf = fopen("EMP.DAT", "rb+");
                printf("\nWould you like to delete another record ? (y/n)");
                fflush(stdin);
                other = getche();
            }
            break;
            
        case '5':
            fclose(pf);
            exit(0); 
        }
    }
    return 0;
}
