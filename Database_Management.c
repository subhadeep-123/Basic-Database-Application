#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <unistd.h>
struct Data
{
    char name[30];
    char age[5];
    char city[30];
} d;
int main()
{
    FILE *fp, *ft;
    char fname[40];
    long int resize;
    char another, choice;
    chdir("C:\\Users\\SUBHADEEP\\Desktop");
    fp = fopen("Database.DAT", "rb+");
    if (fp == NULL)
    {
        fp = fopen("Database.DAT", "wb+");
        if (fp == NULL)
        {
            puts("Cannot open the file");
            fclose(fp);
            exit(1);
        }
    }

    resize = sizeof(d);
    system("cls");
start:
    while (1)
    {

        puts("\n1. Add Records");

        puts("2. List Records");

        puts("3. Modify Records");

        puts("4. Delete Records");

        puts("5. Clear Screen");

        puts("0. Exit");

        puts("Enter You Choice");
        fflush(stdin);
        choice = getche();
        switch (choice)
        {
        case '1':
            fseek(fp, 0, SEEK_END);
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                puts("\nEnter Name: ");
                gets(d.name);
                puts("Enter Age: ");
                gets(d.age);
                puts("Enter City");
                gets(d.city);
                fwrite(&d, resize, 1, fp);
                puts("\nAdd Another Record (Y/N)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '2':
            rewind(fp);
            while (fread(&d, resize, 1, fp) == 1)
                printf("\n %s %s %s", d.name, d.age, d.city);
            printf("\n");
            break;
        case '3':
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {

                puts("\nEnter The Name To Modify: ");
                gets(fname);
                rewind(fp);
                while (fread(&d, resize, 1, fp) == 1)
                {
                    if (strcmp(fname, d.name) == 0)
                    {
                        puts("Enter Name: ");
                        gets(d.name);
                        // fflush(stdin);
                        puts("Enter Age: ");
                        // scanf("%d", &d.age);
                        gets(d.age);
                        // fflush(stdin);
                        puts("Enter City");
                        gets(d.city);
                        fseek(fp, -resize, SEEK_CUR);
                        fwrite(&d, resize, 1, fp);
                        break;
                    }
                }
                puts("\nModify Another Record (Y/N): ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                puts("\nEnter The Name To Delete ");
                gets(fname);
                ft = fopen("TEMP.DAT", "wb");
                if (ft == NULL)
                    exit(1);
                rewind(fp);
                while (fread(&d, resize, 1, fp) == 1)
                {
                    if (strcmp(d.name, fname) != 0)
                        fwrite(&d, resize, 1, ft);
                }
                fclose(fp);
                fclose(ft);
                remove("Database.DAT");
                rename("TEMP.DAT", "Database.DAT");
                fp = fopen("Database.DAT", "rb+");
                if (ft == NULL)
                    exit(1);
                puts("\nDelete Another Record (Y/N)");
                fflush(stdin);
                another = getche();
            }
            break;
        case '5':
            system("cls");
            goto start;
        case '0':
            fclose(fp);
            exit(0);
        default:
            puts("\nERROR: OPTION NOT VALID");
        }
    }

    printf("\nEnter anything to exit..");
    getch();
    return 0;
}
