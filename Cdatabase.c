#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 256
#define ClearScreen() system("cls")       /*For Windows*/
/*#define ClearScreen() system("clear")*/ /*For other operating systems*/

/* define structure */
struct vehicles
{
    char *name;
    char *country;
    int release_year;
    int average_price;
    float mileage;
    float engine_displacement;
    int on_sale_since[3];
};

/* define structured type */
typedef struct vehicles cars;

struct LNode
{
    int id;             /* unique value */
    cars *onsale;       /* data area */
    struct LNode *prev; /* link to previous node */
    struct LNode *next; /* link to next node */
};

struct LHead
{
    int cnt;
    struct LNode *first;
    struct LNode *last;
};

typedef struct LHead Head;
typedef struct LNode Node; /* datatype for pointer to node */

/* Shows menu */
void ShowMenu();

void print_frontier();

void Output(Head *p0, Node *p);

void AddInfo(Head *p0, Node *p);

void EditInfo(Head *p0, Node *p);

void DeleteInfo(Head *p0, Node *p);

void Search(Head *p0, Node *p);

void Sort(Head *p0, Node *p);

void Help();

int CheckDate(int Date1[3], int Date2[3]);

Head *make_head();

Node *create_node2(cars *onsale); /* node initialization */

Node *select_by_id(Head *my_head, int n);

void insert_before2(Head *my_head, Node *new_node, Node *current_node);

void add_first2(Head *my_head, Node *new_node); /* link head to first node */

void add_first2(Head *my_head, Node *new_node); /* link head to first node */

void add_last2(Head *my_head, Node *new_node, Node *prev_node);

void insert_after2(Head *my_head, Node *new_node, Node *current_node);

void insert_before2(Head *my_head, Node *new_node, Node *current_node);

void delete_selected2(Head *my_head, Node *current_node);

void ListOut(Node *p, Head *p0);

/* function to clear array of string */
void clear_string_array(char **str, int n);

/* function to split string to array by separator */
char **simple_split(char *str, int length, char sep);

/* function to print header string without data */
void print_header();

/* function to output structure fields on console */
void struct_out(cars *onsale, int id);

/* function to create structure by array of strings*/
cars *struct_fill(char **str);

/* function to clear memory from structure */
void clear_structure(cars *onsale);

int main()
{
    cars *onsale = NULL;
    int slen, i, j, n, count;
    char **s2 = NULL;
    char s1[maxlen], choice[4];
    char sep;
    FILE *df;
    /* ----------------------------------------- */
    Head *p0, *NewListHead;
    Node *p, *my_node = NULL;
    /* ----------------------------------------- */
    ClearScreen();
    /* ----------------------------------------- */
    sep = ';';
    ClearScreen();
    p0 = make_head();
    df = fopen("Input.csv", "r");
    if (sep != '\n')
    {
        puts("The initial information:\n");
        print_frontier();
        print_header();
    }
    else
        puts("Please, reboot the programm and enter the separator correctly!");
    if (df != NULL)
    {
        n = 0;
        while ((fgets(s1, maxlen, df)) != NULL)
            n++;
        rewind(df);
        onsale = (cars *)malloc(n * sizeof(cars *));
        if (onsale != NULL)
        {
            fgets(s1, maxlen, df);
            slen = strlen(s1);
            s1[slen] = '\0';
            slen = strlen(s1);
            s2 = simple_split(s1, slen, sep);
            if (s2 != NULL)
            {
                onsale = struct_fill(s2);
            }
            p = create_node2(onsale);
            add_first2(p0, p);
            p = p0->first;
            struct_out(p->onsale, p->id);
            for (i = 0, count = 0; i < n - 1; i++, count++)
            {
                fgets(s1, maxlen, df);
                slen = strlen(s1);
                s1[slen] = '\0';
                slen = strlen(s1);
                s2 = simple_split(s1, slen, sep);
                if (s2 != NULL)
                {
                    onsale = struct_fill(s2);
                    my_node = create_node2(onsale);
                    add_last2(p0, my_node, p);
                    p = my_node;
                    if (onsale != NULL)
                        struct_out(p->onsale, p->id);
                    else
                    {
                        puts("Structure not allocated!");
                        i = n;
                    }
                }
                else
                    puts("Error at data reading!");
            }
            print_frontier();
            puts("\nPress ENTER to continue");
            getchar();
            ClearScreen();
            ShowMenu();
            while (atoi(choice) != 8)
            {
                fgets(choice, 4, stdin);
                ClearScreen();
                switch (atoi(choice))
                {
                case 1: /* Output info */
                    Output(p0, p);
                    break;
                case 2: /* Add info */
                    AddInfo(p0, p);
                    break;
                case 3: /* Edit info */
                    EditInfo(p0, p);
                    break;
                case 4: /* Delete info */
                    DeleteInfo(p0, p);
                    break;
                case 5: /* Search */
                    Search(p0, p);
                    break;
                case 6: /* Sort by */
                    Sort(p0, p);
                    break;
                case 7: /* Help */
                    Help();
                    break;
                case 8:
                    ClearScreen();
                    puts("Thanks for working!");
                    break;
                default:
                    puts("Wrong number! Try again!");
                    break;
                }
                if (atoi(choice) != 8)
                {
                    puts("Press ENTER to continue");
                    getchar();
                    ClearScreen();
                    ShowMenu();
                }
            }
        }
        else
            puts("No memory allocation!");
        fclose(df);
    }
    else
        puts("File not found!");
    return 0;
}
/* ----------------------------------------- */
void ShowMenu()
{
    puts("Menu:\n1 - Output full information\n2 - Add information\n3 - Edit information\n4 - Delete information\n5 - Search information\n6 - Show sorted information\n7 - Help\n8 - Exit");
}
void ListOut(Node *p, Head *p0)
{
    puts("                                                           FOR SALE\n");
    print_frontier();
    print_header();
    p = p0->first;
    while (p != NULL)
    {
        struct_out(p->onsale, p->id);
        p = p->next;
    }
    print_frontier();
}

void Output(Head *p0, Node *p)
{
    char choice[4], OutputString[maxlen], temp[maxlen];
    FILE *file;
    printf("Output information to:\n1 - Console\n2 - File\n\nEnter a number: ");
    fgets(choice, 4, stdin);
    ClearScreen();
    switch (atoi(choice))
    {
    case 1:
        ListOut(p, p0);
        break;
    case 2:
        if ((file = fopen("Output.csv", "w")) != NULL)
        {
            p = p0->first;
            while (p != NULL)
            {
                strcpy(OutputString, p->onsale->name);
                strcat(OutputString, ";");
                strcat(OutputString, p->onsale->country);
                strcat(OutputString, ";");
                sprintf(temp, "%d", p->onsale->release_year);
                strcat(OutputString, temp);
                strcat(OutputString, ";");
                sprintf(temp, "%d", p->onsale->average_price);
                strcat(OutputString, temp);
                strcat(OutputString, ";");
                sprintf(temp, "%f", p->onsale->mileage);
                strcat(OutputString, temp);
                strcat(OutputString, ";");
                sprintf(temp, "%f", p->onsale->engine_displacement);
                strcat(OutputString, temp);
                strcat(OutputString, ";");
                sprintf(temp, "%d", p->onsale->on_sale_since[0]);
                strcat(OutputString, temp);
                strcat(OutputString, ".");
                sprintf(temp, "%d", p->onsale->on_sale_since[1]);
                strcat(OutputString, temp);
                strcat(OutputString, ".");
                sprintf(temp, "%d", p->onsale->on_sale_since[2]);
                strcat(OutputString, temp);
                strcat(OutputString, "\n");
                fputs(OutputString, file);
                p = p->next;
            }
            puts("The result was written successfully!");
            if (fclose(file) == EOF)
                perror("Closing error");
        }
        else
            puts("Error occured while opening file!");
        break;
    default:
        puts("Wrong number! Try again!");
        break;
    }
}

void AddInfo(Head *p0, Node *p)
{
    Node *my_node = NULL;
    cars *onsale = NULL;
    onsale = (cars *)malloc(sizeof(cars));
    int slen;
    char **s2 = NULL, **s3 = NULL;
    char s1[maxlen], temp[maxlen];
    p = p0->last;
    memset(s1, '\0', strlen(s1));
    puts("Enter the name and model: ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, temp);
    puts("Enter the producing country: ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, ";");
    strcat(s1, temp);
    puts("Enter year of issue: ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, ";");
    strcat(s1, temp);
    puts("Enter price ($): ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, ";");
    strcat(s1, temp);
    puts("Enter mileage ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, ";");
    strcat(s1, temp);
    puts("Enter engine displacement (L): ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    temp[strlen(temp) - 1] = '\0';
    strcat(s1, ";");
    strcat(s1, temp);
    puts("Enter the date of sale starts (separate with '.': dd.mm.yyyy): ");
    fgets(temp, maxlen, stdin);
    ClearScreen();
    strcat(s1, ";");
    if (strstr(temp, ".") == NULL)
    {
        ClearScreen();
        puts("Please, enter the date correctly!\nExample: 12.01.2012");
    }
    else
    {
        s3 = simple_split(temp, 11, '.');
        strcat(s1, s3[0]);
        strcat(s1, ";");
        strcat(s1, s3[1]);
        strcat(s1, ";");
        strcat(s1, s3[2]);
        slen = strlen(s1);
        s2 = simple_split(s1, slen, ';');
        if ((s2 != NULL) && (onsale != NULL))
        {
            onsale = struct_fill(s2);
        }
        else
            puts("Error at data reading!");
        my_node = create_node2(onsale);
        add_last2(p0, my_node, p);
        ClearScreen();
    }
}

void EditInfo(Head *p0, Node *p)
{
    char IdToBeEdited[4], FieldToBeEdited[4], temp[maxlen], **s2 = NULL;
    int i;
    ListOut(p, p0);
    printf("\nSelect the ID to edit: ");
    memset(IdToBeEdited, '\0', strlen(IdToBeEdited));
    fgets(IdToBeEdited, 4, stdin);
    if ((atoi(IdToBeEdited) <= p0->cnt) && (IdToBeEdited > 0))
    {
        ClearScreen();
        p = p0->first;
        while (p->id != atoi(IdToBeEdited))
        {
            p = p->next;
        }
        print_frontier();
        print_header();
        struct_out(p->onsale, p->id);
        print_frontier();
        printf("\nChoose what to edit:\n1 - Name and model\n2 - Country of issue\n3 - Year of issue\n4 - Price\n5 - Mileage\n6 - Engine displacement\n7 - On sale since\n\nEnter a number: ");
        memset(FieldToBeEdited, '\0', strlen(FieldToBeEdited));
        fgets(FieldToBeEdited, 4, stdin);
        ClearScreen();
        if ((atoi(FieldToBeEdited) <= 7) && (FieldToBeEdited > 0))
        {
            switch (atoi(FieldToBeEdited))
            {
            case 1:
                memset(temp, '\0', strlen(temp));
                memset(p->onsale->name, '\0', strlen(p->onsale->name));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                for (i = 0; i < strlen(temp) - 1; i++)
                {
                    p->onsale->name[i] = temp[i];
                }
                break;
            case 2:
                memset(temp, '\0', strlen(temp));
                memset(p->onsale->country, '\0', strlen(p->onsale->country));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                for (i = 0; i < strlen(temp) - 1; i++)
                {
                    p->onsale->country[i] = temp[i];
                }
                break;
            case 3:
                memset(temp, '\0', strlen(temp));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                p->onsale->release_year = atoi(temp);
                break;
            case 4:
                memset(temp, '\0', strlen(temp));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                p->onsale->average_price = atoi(temp);
                break;
            case 5:
                memset(temp, '\0', strlen(temp));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                p->onsale->mileage = atof(temp);
                break;
            case 6:
                memset(temp, '\0', strlen(temp));
                printf("Enter new data: ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                p->onsale->engine_displacement = atof(temp);
                break;
            case 7:
                memset(temp, '\0', strlen(temp));
                printf("Enter new data (dd.mm.yyyy): ");
                fgets(temp, maxlen, stdin);
                temp[strlen(temp)] = '\0';
                s2 = simple_split(temp, strlen(temp), '.');
                if ((atoi(s2[0]) != 0) && (atoi(s2[1]) != 0) && (atoi(s2[2]) != 0))
                {
                    p->onsale->on_sale_since[0] = atoi(s2[0]);
                    p->onsale->on_sale_since[1] = atoi(s2[1]);
                    p->onsale->on_sale_since[2] = atoi(s2[2]);
                }
                else
                {
                    ClearScreen();
                    puts("Please, enter the date correctly!\nExample: 12.01.2012");
                }
                break;
            default:
                break;
            }
        }
        else
        {
            ClearScreen();
            puts("Please, enter number correctly!");
        }
    }
    else
    {
        ClearScreen();
        puts("Please, enter ID correctly!");
    }
}

void DeleteInfo(Head *p0, Node *p)
{
    char IdToBeDeleted[4], FieldToBeDeleted[4];
    ListOut(p, p0);
    printf("Choose the ID to be deleted: ");
    memset(IdToBeDeleted, '\0', strlen(FieldToBeDeleted));
    fgets(IdToBeDeleted, 4, stdin);
    ClearScreen();
    if ((atoi(IdToBeDeleted) <= p0->cnt) && (atoi(IdToBeDeleted) > 0))
    {
        p = p0->first;
        while (p->id != atoi(IdToBeDeleted))
        {
            p = p->next;
        }
        delete_selected2(p0, p);
    }
    else
    {
        printf("Please, enter the ID correctly!");
    }
}

void Search(Head *p0, Node *p)
{
    char FieldToBeSearched[4], temp[maxlen], **LowerValueBorder = NULL, **UpperValueBorder = NULL;
    int SearchResulted, LowerDateBorder[3], UpperDateBorder[3], i;
    printf("Search by:\n1 - Name and model\n2 - Country of issue\n3 - Year of issue\n4 - Price\n5 - Mileage\n6 - Engine displacement\n7 - On sale since\n\nEnter a number: ");
    memset(FieldToBeSearched, '\0', strlen(FieldToBeSearched));
    fgets(FieldToBeSearched, 4, stdin);
    ClearScreen();
    SearchResulted = 0;
    if ((atoi(FieldToBeSearched) <= 7) && (atoi(FieldToBeSearched) > 0))
    {
        if (atoi(FieldToBeSearched) <= 2)
        {
            printf("Enter the value: ");
            memset(temp, '\0', strlen(temp));
            fgets(temp, maxlen, stdin);
            temp[strlen(temp) - 1] = '\0';
        }
        else
        {
            printf("The search will show results within [lower value border - upper value border] range.\nPlease, enter the range of values.\n\nEnter the lower value border: ");
            memset(temp, '\0', strlen(temp));
            fgets(temp, maxlen, stdin);
            if (atoi(FieldToBeSearched) <= 4)
            {
                LowerValueBorder = simple_split(temp, strlen(temp), '.');
                printf("Enter the upper value border: ");
                memset(temp, '\0', strlen(temp));
                fgets(temp, maxlen, stdin);
                if (strlen(temp) == 1)
                    strcat(temp, "100000000");
                UpperValueBorder = simple_split(temp, strlen(temp), '.');
            }
            else
            {
                if (atoi(FieldToBeSearched) < 7)
                {
                    LowerValueBorder = simple_split(temp, strlen(temp), '.');
                    printf("Enter the upper value border: ");
                    memset(temp, '\0', strlen(temp));
                    fgets(temp, maxlen, stdin);
                    if (strlen(temp) == 1)
                        strcat(temp, "100000000");
                    UpperValueBorder = simple_split(temp, strlen(temp), '.');
                }
                else
                {
                    LowerValueBorder = simple_split(temp, strlen(temp), '.');
                    printf("Enter the upper value border: ");
                    memset(temp, '\0', strlen(temp));
                    fgets(temp, maxlen, stdin);
                    if (strlen(temp) == 1)
                        strcat(temp, "31.31.2030");
                    UpperValueBorder = simple_split(temp, strlen(temp), '.');
                    for (i = 0; i < 3; i++)
                    {
                        LowerDateBorder[i] = atoi(LowerValueBorder[i]);
                        UpperDateBorder[i] = atoi(UpperValueBorder[i]);
                    }
                }
            }
        }
        p = p0->first;
        puts("                                                           FOR SALE\n");
        print_frontier();
        print_header();
        for (i = 0; i < p0->cnt; i++)
        {
            switch (atoi(FieldToBeSearched))
            {
            case 1:
                if (strstr(p->onsale->name, temp) != NULL)
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 2:
                if (strcmp(p->onsale->country, temp) == 0)
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 3:
                if ((p->onsale->release_year >= atoi(LowerValueBorder[0])) && (p->onsale->release_year <= atoi(UpperValueBorder[0])))
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 4:
                if ((p->onsale->average_price >= atoi(LowerValueBorder[0])) && (p->onsale->average_price <= atoi(UpperValueBorder[0])))
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 5:
                if ((p->onsale->mileage >= atof(LowerValueBorder[0])) && (p->onsale->mileage <= atof(UpperValueBorder[0])))
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 6:
                if ((p->onsale->engine_displacement >= atof(LowerValueBorder[0])) && (p->onsale->engine_displacement <= atof(UpperValueBorder[0])))
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            case 7:
                if ((CheckDate(p->onsale->on_sale_since, LowerDateBorder) == 1) && (CheckDate(UpperDateBorder, p->onsale->on_sale_since) == 1))
                {
                    struct_out(p->onsale, p->id);
                    SearchResulted = 1;
                }
                break;
            default:
                break;
            }
            p = p->next;
        }
        print_frontier();
        if (SearchResulted == 0)
        {
            ClearScreen();
            puts("The search didn't give any results!");
        }
    }
    else
    {
        puts("Please, enter the number correctly!");
    }
}

void Sort(Head *p0, Node *p)
{
    char SortBy[4], FieldToBeSearched[4], InputSortMode[4];
    cars *temp = NULL;
    int FirstListMemoryAllocation, i, j, SortMode;
    Head *NewListHead;
    Node *NewPointer, *NewPointer1, *Pointer1, *Pointer2, *my_node = NULL;
    printf("Sort information by:\n1 - Name and model\n2 - Country of issue\n3 - Year of issue\n4 - Price\n5 - Mileage\n6 - Engine displacement\n7 - On sale since\n\nEnter a number: ");
    memset(SortBy, '\0', strlen(FieldToBeSearched));
    fgets(SortBy, 4, stdin);
    ClearScreen();
    printf("\nSort information:\n1 - By ascending\n2 - By descending\n\nEnter a number: ");
    SortMode = atoi(fgets(InputSortMode, 4, stdin)) * 2 - 3;
    FirstListMemoryAllocation = 1;
    if (FirstListMemoryAllocation == 1)
        NewListHead = (Head *)malloc(sizeof(Head));
    NewListHead = make_head();
    p = p0->first;
    NewPointer = create_node2(p->onsale);
    add_first2(NewListHead, NewPointer);
    p = p->next;
    while (p != NULL)
    {
        my_node = create_node2(p->onsale);
        add_last2(NewListHead, my_node, NewPointer);
        NewPointer = my_node;
        p = p->next;
    }
    if (FirstListMemoryAllocation == 1)
    {
        NewPointer1 = (Node *)malloc(sizeof(Node));
        Pointer1 = (Node *)malloc(sizeof(Node));
        Pointer2 = (Node *)malloc(sizeof(Node));
    }
    NewPointer = NewListHead->first;
    p = p0->first;
    FirstListMemoryAllocation == 0;
    if ((atoi(SortBy) <= 7) && (atoi(SortBy) > 0) && ((SortMode >= -1) || (SortMode <= 1)))
    {
        switch (atoi(SortBy))
        {
        case 1:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (strcmp(Pointer1->onsale->name, Pointer2->onsale->name) * SortMode > 0)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        case 2:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (strcmp(Pointer1->onsale->country, Pointer2->onsale->country) * SortMode > 0)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        case 3:
        {
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (Pointer1->onsale->release_year * SortMode < Pointer2->onsale->release_year * SortMode)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        }
        case 4:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (Pointer1->onsale->average_price * SortMode < Pointer2->onsale->average_price * SortMode)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        case 5:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (Pointer1->onsale->mileage * SortMode < Pointer2->onsale->mileage * SortMode)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        case 6:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (Pointer1->onsale->engine_displacement * SortMode < Pointer2->onsale->engine_displacement * SortMode)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        case 7:
            for (i = 1; i <= p0->cnt - 1; i++)
            {
                for (j = i + 1; j <= p0->cnt; j++)
                {
                    Pointer1 = select_by_id(NewListHead, i);
                    Pointer2 = select_by_id(NewListHead, j);
                    if (CheckDate(Pointer2->onsale->on_sale_since, Pointer1->onsale->on_sale_since) * SortMode == 1)
                    {
                        temp = Pointer1->onsale;
                        Pointer1->onsale = Pointer2->onsale;
                        Pointer2->onsale = temp;
                    }
                }
            }
            break;
        }
        ListOut(NewPointer, NewListHead);
    }
    else
    {
        puts("Please, enter the number correctly!");
    }
}

void Help()
{
    puts("                                   HELP                                   ");
    puts("+-------------------------------------------------------------------------+");
    puts("| Basic information:                                                      |");
    puts("| This programm is writen for a car dealer company.                       |");
    puts("|                                                                         |");
    puts("| Please, pay attention to the documentation of the search function.      |");
    puts("| It has some additional opportunities.                                   |");
    puts("|                                                                         |");
    puts("| The programm will notify the user in case of most errors.               |");
    puts("|-------------------------------------------------------------------------|");
    puts("| Function description:                                                   |");
    puts("| 1 - 4: Output, edit, add, delete information                            |");
    puts("|        These functions work as stated in their names.                   |");
    puts("| 5 - Search                                                              |");
    puts("|        Please, notice that search engine has some additional features:  |");
    puts("|        Search in the 'Name and model' field can be done by typing       |");
    puts("|        name or model ONLY without a must to type a full name. For       |");
    puts("|        instance, the user can type '911' instead of 'Porsche 911        |");
    puts("|        Carrera 4S'                                                      |");
    puts("|                                                                         |");
    puts("|        Numeric fields search can be done by entering a range of values  |");
    puts("|        (for example, cars which price is in range [$60000-$100000])     |");
    puts("|        Nevertheless entering a full range isn't a must: the user        |");
    puts("|        can only enter one border of search, the other one will be set   |");
    puts("|        automatically (for instance, if the user only enters the upper   |");
    puts("|        border $100000, the search will be done in [$0-$100000 range.]). |");
    puts("|                                                                         |");
    puts("| 6 - Sorting                                                             |");
    puts("|        Sorting function shows the copy of initial information sorted.   |");
    puts("|        The function doesn't affect the initial list.                    |");
    puts("|        Sorting in 'Name and model' field is done in lexicographic       |");
    puts("|        order.                                                           |");
    puts("|        Ascending - low to high values, descending - high to             |");
    puts("|        low values.                                                      |");
    puts("+-------------------------------------------------------------------------+");
}

int CheckDate(int Date1[3], int Date2[3])
{
    int key, i;
    key = -1;
    if (Date1[2] > Date2[2])
        key = 1;
    if (Date1[2] == Date2[2])
    {
        if (Date1[1] > Date2[1])
            key = 1;
        if ((Date1[1] == Date2[1]) && (Date1[0] >= Date2[0]))
            key = 1;
    }
    return key;
}

void clear_string_array(char **str, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(str[i]);
        str[i] = NULL;
    }
    free(str);
    str = NULL;
}

char **simple_split(char *str, int length, char sep)
{
    char **str_array = NULL;
    int i, j, k, m;
    int key, count;
    for (j = 0, m = 0; j < length; j++)
    {
        if (str[j] == sep)
            m++;
    }
    key = 0;
    str_array = (char **)malloc((m + 1) * sizeof(char *));
    if (str_array != NULL)
    {
        for (i = 0, count = 0; i <= m; i++, count++)
        {
            str_array[i] = (char *)malloc(length * sizeof(char));
            if (str_array[i] != NULL)
                key = 1;
            else
            {
                key = 0;
                i = m;
            }
        }
        if (key)
        {
            k = 0;
            m = 0;
            for (j = 0; j < length; j++)
            {
                if (str[j] != sep)
                    str_array[m][j - k] = str[j];
                else
                {
                    str_array[m][j - k] = '\0';
                    k = j + 1;
                    m++;
                }
            }
        }
        else
        {
            clear_string_array(str_array, count);
        }
    }
    return str_array;
}

void print_header()
{
    printf("| %3s |%30s |%18s |%14s | %6s  |%8s |%13s |%14s |\n", "ID", "Name and model", "Country of issue", "Year of issue", "Price", "Mileage", "Displacement", "On sale since");
    printf("+-----+-------------------------------+-------------------+---------------+---------+---------+--------------+---------------+\n");
}
void print_frontier()
{
    printf("+-----+-------------------------------+-------------------+---------------+---------+---------+--------------+---------------+\n");
}

void struct_out(cars *onsale, int id)
{
    printf("|%3d  |%30s |%18s |%14d | $%6d |%8.1f |%13.1f |    %02d.%02d.%04d | \n", id,
           onsale->name, onsale->country, onsale->release_year, onsale->average_price, onsale->mileage, onsale->engine_displacement, onsale->on_sale_since[0], onsale->on_sale_since[1], onsale->on_sale_since[2]);
}

cars *struct_fill(char **str)
{
    cars *onsale = NULL;
    onsale = (cars *)malloc(sizeof(cars));
    if (onsale != NULL)
    {
        onsale->name = str[0];
        onsale->country = str[1];
        onsale->release_year = atoi(str[2]);
        onsale->average_price = atoi(str[3]);
        onsale->mileage = atof(str[4]);
        onsale->engine_displacement = atof(str[5]);
        onsale->on_sale_since[0] = atoi(str[6]);
        onsale->on_sale_since[1] = atoi(str[7]);
        onsale->on_sale_since[2] = atoi(str[8]);
    }
    return onsale;
}

void clear_structure(cars *onsale)
{
    free(onsale->name);
    free(onsale->country);
    onsale->name = NULL;
    onsale->country = NULL;
    free(onsale);
    onsale = NULL;
}

Head *make_head()
{
    Head *ph = NULL;

    ph = (Head *)malloc(sizeof(Head));
    if (ph)
    {
        ph->cnt = 0;
        ph->first = NULL;
        ph->last = NULL;
    }
    return ph;
}

Node *create_node2(cars *onsale) /* node initialization */
{
    Node *new_node = NULL; /* pointer to new node */
    cars *onsalecopy;

    new_node = (Node *)malloc(sizeof(Node));
    onsalecopy = (cars *)malloc(sizeof(cars));
    if (new_node && onsalecopy)
    {
        onsalecopy = onsale;
        new_node->id = 1; /* setting node ID to 1 */
        new_node->onsale = onsalecopy;
        new_node->prev = NULL; /* previous node is absent */
        new_node->next = NULL; /*     next node is absent */
    }
    return new_node; /* return of node address */
}

Node *select_by_id(Head *my_head, int n)
{
    Node *q;
    int k;
    q = my_head->first;
    k = my_head->cnt; /* last node id */
    if ((n > 0) && (n <= k))
    {
        while ((q->id) != n)
            q = q->next;
    }
    else
        q = NULL;
    return q;
}

void insert_before2(Head *my_head, Node *new_node, Node *current_node)
{
    Node *q = NULL;
    int n;

    if (my_head && new_node && current_node)
    {
        if (my_head->first == current_node)
        {
            new_node->next = current_node;
            current_node->prev = new_node;
            my_head->first = new_node;
        }
        else
        {
            q = current_node->prev;
            new_node->next = current_node;
            new_node->prev = q;
            q->next = new_node;
            current_node->prev = new_node;
        }
        n = my_head->cnt + 1;
        new_node->id = n;
        my_head->cnt = n;
    }
}

void add_first2(Head *my_head, Node *new_node) /* link head to first node */
{
    my_head->first = new_node;
    my_head->last = new_node;
    my_head->cnt++;
}

void add_last2(Head *my_head, Node *new_node, Node *prev_node)
{
    int n;
    if (my_head && new_node && prev_node)
    {
        n = my_head->cnt + 1;
        prev_node->next = new_node;
        new_node->prev = prev_node;
        my_head->last = new_node;
        new_node->id = n;
        my_head->cnt = n;
        new_node->next = NULL;
    }
}

void delete_selected2(Head *my_head, Node *current_node)
{
    Node *q, *q1;
    int k;
    q = my_head->first;
    q1 = my_head->last;
    if (current_node == q)
    {
        my_head->first = current_node->next;
        current_node->next = NULL;
        current_node->prev = NULL;
        free(current_node);
    }
    else
    {
        while (q != NULL)
        {
            if (q->next == current_node)
            {
                if (current_node == q1)
                    my_head->last = q;
                q->next = current_node->next;
                if (q->next != NULL)
                {
                    q = q->next;
                    q->prev = current_node->prev;
                }
                current_node->next = NULL;
                current_node->prev = NULL;
                free(current_node);
            }
            else
                q = q->next;
        }
    }
    q = my_head->first;
    k = 1;
    while (q != NULL)
    {
        q->id = k;
        q = q->next;
        k++;
    }
    my_head->cnt -= 1;
}