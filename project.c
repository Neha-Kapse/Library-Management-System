#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book
{
    int id;
    char name[50];
    char author[50];
    int quantity;
};

void addBook()
{
    FILE *fp;
    struct book b;

    fp = fopen("library.txt", "ab");

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Name:")
    scanf(" %[^\n]", b.name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);

    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nBook Added Successfully!\n");
}

void displayBooks()
{
    FILE *fp;
    struct book b;

    fp = fopen("library.txt", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n--- Book List ---\n");

    while(fread(&b, sizeof(b), 1, fp))
    {
        printf("\nID: %d", b.id);
        printf("\nName: %s", b.name);
        printf("\nAuthor: %s", b.author);
        printf("\nQuantity: %d\n", b.quantity);
    }

    fclose(fp);
}

void searchBook()
{
    FILE *fp;
    struct book b;
    int id, found = 0;

    fp = fopen("library.txt", "rb");

    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(b), 1, fp))
    {
        if(b.id == id)
        {
            printf("\nBook Found!\n");
            printf("Name: %s\nAuthor: %s\nQuantity: %d\n",
                   b.name, b.author, b.quantity);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nBook Not Found!\n");

    fclose(fp);
}

void issueBook()
{
    FILE *fp;
    struct book b;
    int id, found = 0;

    fp = fopen("library.txt", "rb+");

    printf("\nEnter Book ID to Issue: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(b), 1, fp))
    {
        if(b.id == id)
        {
            if(b.quantity > 0)
            {
                b.quantity--;
                fseek(fp, -sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);

                printf("\nBook Issued Successfully!\n");
            }
            else
            {
                printf("\nBook Out of Stock!\n");
            }
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nBook Not Found!\n");

    fclose(fp);
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
