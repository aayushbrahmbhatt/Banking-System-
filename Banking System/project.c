#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
char admin_name[] = {'A', 'd', 'm', 'i', 'n', '\0'};
char admin_password[] = {'A', 'D', 'M', 'I', 'N', '\0'};

struct Node
{
    int account_Number;
    char Password[50];
    char Adhar[12];
    int Age;
    char Mobile_Number[10];
    char PAN[15];
    long long int Balance;
    char Name[50];
    struct Node *next;
};

struct Node *head = NULL;
struct Node *last = NULL;
int Account_Number, wrong_iterator = 0;

void money_transfer(struct Node *, struct Node *);
void Initializer();
void Iterator();
int login(struct Node *, int);
void ending();
void signup();

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

void Initializer()
{

    FILE *fp = fopen("UserData.csv", "r");

    if (!fp)
        printf("\n");
    else
    {
        char buffer[1024];

        int row = 0;
        int column = 0;
        while (fgets(buffer, 1024, fp))
        {
            column = 0;
            row++;

            if (row == 1)
            {
                continue;
            }

            char *PAN, *Adhar_, *Mobile_Num, *Pass;
            char *value = strtok(buffer, ", "), *_Name;
            _Name = (char *)malloc(50 * sizeof(char));
            Pass = (char *)malloc(50 * sizeof(char));
            PAN = (char *)malloc(15 * sizeof(char));
            Mobile_Num = (char *)malloc(10 * sizeof(char));
            int num;
            long long Balance;
            for (int i = 1; value; value = strtok(NULL, ", "), ++i)
            {
                if (i == 1)
                    _Name = value;
                else if (i == 2)
                    num = atoi(value);
                else if (i == 3)
                    Mobile_Num = value;
                else if (i == 4)
                    Adhar_ = value;
                else if (i == 5)
                    PAN = value;
                else if (i == 7)
                    Balance = atoi(value);
                else if (i == 6)
                    Pass = value;
                else if (i == 8)
                    Account_Number = atoi(value);
            }

            struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
            if (head == NULL)
            {
                head = new_node;
                new_node->next = NULL;
                new_node->Age = num;
                strcat(new_node->PAN, PAN);
                strcat(new_node->Name, _Name);
                strcat(new_node->Adhar, Adhar_);
                strcat(new_node->Mobile_Number, Mobile_Num);
                strcpy(new_node->Password, Pass);
                new_node->Balance = Balance;
                new_node->account_Number = Account_Number;
                last = new_node;
            }
            else
            {
                new_node->next = NULL;
                new_node->Age = num;
                strcat(new_node->PAN, PAN);
                strcat(new_node->Name, _Name);
                strcat(new_node->Adhar, Adhar_);
                strcat(new_node->Mobile_Number, Mobile_Num);
                strcpy(new_node->Password, Pass);
                new_node->Balance = Balance;
                new_node->account_Number = Account_Number;
                last->next = new_node;
                last = new_node;
            }

            value = strtok(NULL, ", ");
            column++;

            printf("\n");
        }

        // Close the file
        fclose(fp);
    }
}

void signup()
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    int acc;
    if (last == NULL)
        acc = 1001;
    else
        acc = last->account_Number + 1;
    int AC;
    char Pass[50];
    int age;
    char MN[11];
    char pan[15];
    long long int Bal;
    char Adr[12];
    char name[50];
    printf("\n\n\t\t\t\t\t\tEnter Name: ");
    scanf("%s", name);

    printf("\t\t\t\t\t\tEnter Age: ");
    scanf("%d", &age);

    printf("\t\t\t\t\t\tEnter Mobile Number: ");
    scanf("%s", MN);

    printf("\t\t\t\t\t\tEnter Aadhar Number: ");
    scanf("%s", Adr);

    printf("\t\t\t\t\t\tEnter PAN: ");
    scanf("%s", pan);

    printf("\t\t\t\t\t\tAmount you want to deposit: ");
    scanf("%lld", &Bal);

    printf("\t\t\t\t\t\tEnter your password: ");
    while ((getch()) != '\n')
        ;
    int p = 0;
    do
    {
        Pass[p] = getch();
        if (Pass[p] != '\n' && Pass[p] != 8)
        {
            printf("*");
        }
        p++;
    } while (Pass[p - 1] != '\n');
    Pass[p - 1] = '\0';
    getch();

    if (head == NULL)
    {
        head = new_node;
        new_node->next = NULL;
        strcpy(new_node->Name, name);
        new_node->Age = age;
        new_node->account_Number = acc;
        strcpy(new_node->Mobile_Number, MN);
        strcpy(new_node->Adhar, Adr);
        strcpy(new_node->PAN, pan);
        strcpy(new_node->Password, Pass);
        new_node->Balance = Bal;
        last = new_node;
    }
    else
    {
        new_node->next = NULL;
        strcpy(new_node->Name, name);
        new_node->Age = age;
        strcpy(new_node->Mobile_Number, MN);
        strcpy(new_node->Adhar, Adr);
        strcpy(new_node->PAN, pan);
        strcpy(new_node->Password, Pass);
        new_node->account_Number = acc;
        new_node->Balance = Bal;
        last->next = new_node;
        last = new_node;
    }

    printf("\n\n\n\t\t\t\t\t\tYour Account number is %d\n\n", new_node->account_Number);
}
void ending()
{
    FILE *fp = fopen("UserData.csv", "w");

    fprintf(fp, "%s , %s , %s , %s , %s , %s , %s, %s ", "Name", "Age", "MobileNumber", "Adhaar", "PAN", "Password", "Balance", "AccountNumber");

    if (!fp)
        printf("Can't open file\n");
    struct Node *cur = head;
    while (cur)
    {
        char str[10];
        sprintf(str, "%d", cur->account_Number);
        fprintf(fp, "\n%s , %d , %s , %s , %s , %s , %lld, %s ", cur->Name, cur->Age, cur->Mobile_Number, cur->Adhar, cur->PAN, cur->Password, cur->Balance, str);
        cur = cur->next;
    }
    fclose(fp);
}

void Iterator()
{
    struct Node *curr = head;
    if (curr == NULL)
        printf("\n\t\t\t\t\t\tNo Account in Bank\n\n");
    else
    {
        while (curr)
        {
            if (curr->account_Number != 0)
                printf("\n\t\t\t\t\t\tAccount Number: %d - Name: %s - Balance: %lld\n", curr->account_Number, curr->Name, curr->Balance);
            curr = curr->next;
        }
    }
}

void iterator(int acc_number)
{
    struct Node *curr = head;
    while (curr && curr->account_Number != acc_number)
    {
        curr = curr->next;
    }
    if (!curr)
    {
        printf("\n\t\t\t\t\t\tAccount Number doesn't Exist\n");
    }
    else
    {
        printf("\n\t\t\t\t\t\tAccount Number: %d - Name: %s - Balance: %lld\n", curr->account_Number, curr->Name, curr->Balance);
    }
}

void Delete(int key)
{
    struct Node *temp = head;
    struct Node *prev = NULL;
    if (temp != NULL && temp->account_Number == key)
    {
        head = temp->next;
        free(temp);
        printf("\n\t\t\t\t\t\tAccount Number %d deleted successfully\n", key);
        return;
    }

    else
    {
        while (temp != NULL && temp->account_Number != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            printf("\n\t\t\t\t\t\tAccount Number doesn't exist\n");
            return;
        }

        if (temp->next == NULL)
            last = prev;
        prev->next = temp->next;
        printf("\n\t\t\t\t\t\tAccount Number %d deleted successfully\n", key);

        free(temp);
    }
}

int main()
{

    Initializer(); /*all data will be stored in the linked list*/
    int choice, flag = 0, acc_num;
    int user_choice;
    int True = -1;
    char AdminName[50], AdminPassword[6];
    do
    {
        system("clear");
        printf("\n\t\t\t\t\t\t\t\tWelcome to Reserve Bank of DAIICT\n\n");
        printf("\n\t\t\t\t\t\t\t\tSelect an Option : \n\t\t\t\t\t\t1.Admin\n\t\t\t\t\t\t2.User\n\t\t\t\t\t\t3.Exit\n\n\t\t\t\t\t\t");
        scanf("%d", &user_choice);
        switch (user_choice)
        {
        case 2:
            system("clear");
            while (1)
            {
                // system("clear");

                printf("\n\t\t*********************************************************************************************************************\n\n");
                printf("\n\t\t\t\t\t\t\t\t\tUser Console\n\n");
                int PID = getpid();
                int child;
                printf("\n\t\t\t\t\t\t\t\tSelect Option : \n\t\t\t\t\t\t1.Login \n\t\t\t\t\t\t2.SignUp \n\t\t\t\t\t\t3.Query \n\t\t\t\t\t\t4.Complaint-Box \n\t\t\t\t\t\t5.exit \n\n\t\t\t\t\t\t");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    wrong_iterator = login(head, wrong_iterator);
                    break;
                case 2:
                    signup();
                    break;
                case 5:
                    flag = 1;
                    break;
                case 3:

                    if (fork() == 0)
                    {
                        child = getpid();
                        system("gnome-terminal -e ./query1.out");
                    }

                    else
                        system("gnome-terminal -e ./query2.out");

                    if (getpid() != PID)
                    {
                        kill(child, SIGKILL);
                    }
                    break;
                case 4:
                    system("clear");
                    printf("********************* CONNECTED TO BANK SERVER *********************\n\n");
                    printf("NOTE : press ctrl + c to end conversation\n\n");
                    system("./complain.out 192.168.127.199 15000");

                default:
                    printf("\n\t\t\t\t\t\tEnter proper action\n\n");
                    break;
                }
                if (flag == 1)
                    break;
            }
            break;
        case 1:
            system("clear");
            while (1)
            {
                True = -1;
                printf("\n\t\t\t\t\t\tEnter Your Name: ");
                scanf("%s", AdminName);
                printf("\n\t\t\t\t\t\tEnter Your Password: ");
                while ((getch()) != '\n')
                    ;
                int p = 0;
                do
                {
                    AdminPassword[p] = getch();
                    if (AdminPassword[p] != '\n' && AdminPassword[p] != 8)
                    {
                        printf("*");
                    }
                    p++;
                } while (AdminPassword[p - 1] != '\n');
                AdminPassword[p - 1] = '\0';
                getch();
                if (strcmp(AdminName, admin_name) != 0)
                {
                    printf("\n\n\t\t\t\t\t\tPlease Enter Valid Name\n");
                    continue;
                }
                else
                {
                    if (strcmp(AdminPassword, admin_password) != 0)
                    {
                        printf("\n\n\t\t\t\t\t\tIncorrect Password\n");
                        continue;
                    }
                    else
                    {
                        True = 1;
                    }
                }
                if (True == 1)
                {

                    printf("\n\n\t\t\t\t\t\tLogged in Successfully\n");
                    break;
                }
            }

            while (1)
            {
                printf("\n\t\t*********************************************************************************************************************\n\n");
                printf("\n\t\t\t\t\t\t\t\t\tAdmin Console\n\n");
                int curr_choice;
                printf("\n\t\t\t\t\t\tSelect Option : \n\n\t\t\t\t\t\t1.View All Account Detail\n\t\t\t\t\t\t2.View Single Account Detail\n\t\t\t\t\t\t3.Delete a Account\n\t\t\t\t\t\t4.Exit\n\n\t\t\t\t\t\t");
                scanf("%d", &curr_choice);
                if (curr_choice == 4)
                {
                    break;
                }
                switch (curr_choice)
                {
                case 1:
                    Iterator();
                    break;
                case 2:
                    printf("\n\n\t\t\t\t\t\tEnter Account Number: ");
                    scanf("%d", &acc_num);
                    iterator(acc_num);
                    break;
                case 3:
                    printf("\n\n\t\t\t\t\t\tEnter Account Number: ");
                    scanf("%d", &acc_num);
                    Delete(acc_num);
                    break;
                case 4:
                    break;
                default:
                    printf("\n\n\t\t\t\t\t\tPlease Enter Valid Choice\n");
                    break;
                }
            }

        case 3:
            break;
        default:
            printf("\n\n\t\t\t\t\t\tInvalid Input");
            break;
        }
    } while (user_choice != 3);

    ending();
    return 0;
}
