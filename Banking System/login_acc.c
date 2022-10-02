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

void acc_not_exists() /*signal handler*/
{
    printf("\n\n\n\t\t\t\t\t\tThis Account doesn't exist! \n");
}
void wrong_pass() /*signal handler*/
{
    printf("\n\n\n\t\t\t\t\t\tYou have entered wrong Password\n");
}
void time_limit() /*signal handler*/
{
    printf("\n\n\n\t\t\t\t\t\t You reached time limit! \n");
}
void multiple_pass() /*signal handler*/
{
    printf("\n\n\n\t\t\t\t\t\tYou have entered wrong password multiple time! \n");
    printf("\n\n\n\t\t\t\t\t\t Wait for 10 seconds \n");
    sleep(10);
}

int getch_login(void)
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

void money_transfer(struct Node *curr_user, struct Node *head)
{
    // long long source_balance =
    int acc;
    long long amount;
    printf("\n\n\t\t\t\t\t\tEnter account number to transfer money: ");
    scanf("%d", &acc);
    printf("\n\t\t\t\t\t\tEnter the amount to transfer money: ");
    scanf("%lld", &amount);
    struct Node *temp = head;
    while (temp)
    {
        if (temp->account_Number == acc)
            break;
        else
            temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\n\n\t\t\t\t\t\tWrong Account Number\n");
    }
    else
    {
        if (curr_user->Balance < amount)
        {
            printf("\n\n\t\t\t\t\t\tYou don't have Enough Money\n");
        }
        else
        {
            curr_user->Balance -= amount;
            temp->Balance += amount;
            printf("\n\n\t\t\t\t\t\tMoney Transfered Succesfully\n\t\t\t\t\t\tYour Current Balance: %lld\n", curr_user->Balance);
        }
    }
}

int login(struct Node *head, int wrong_iterator)
{
    int Acc_no, flag = 0;
    char *key, *temp_pass;
    key = (char *)malloc(50 * sizeof(char));
    temp_pass = (char *)malloc(50 * sizeof(char));

    system("clear");
    printf("\n\t\t*********************************************************************************************************************\n\n");
    printf("\n\t\t\t\t\t\t\t\t\tUser Console\n");
    // signal(SIGALRM, time_limit);
    // alarm(15);

    printf("\n\t\t\t\t\t\tEnter Account no: ");
    scanf("%d", &Acc_no);
    printf("\n\t\t\t\t\t\tEnter Password: ");
    // scanf("%s", key);
    while ((getch_login()) != '\n')
        ;
    int p = 0;
    do
    {
        key[p] = getch_login();
        if (key[p] != '\n' && key[p] != 8)
        {
            printf("*");
        }
        p++;
    } while (key[p - 1] != '\n');
    key[p - 1] = '\0';
    getch_login();
    struct Node *temp = head;
    while (temp != NULL)
    {
        int x = temp->account_Number;
        if (x == Acc_no)
        {
            // signal(SIGUSR1,signal_handler)
            flag = 1;
            if (strcmp(temp->Password, key) == 0)
            {
                 printf("\n\n\t\t\t\t\t\tLogged in Successfully\n");
                int choice;
                long long balance = temp->Balance, amount = 0;

                while (1)
                {
                    printf("\n\t\t*********************************************************************************************************************\n\n");
                    wrong_iterator = 0;
                    printf("\n\t\t\t\t\t\t\t\t\tSelect Action : \n\n\t\t\t\t\t\t1.Money Withdraw\n\t\t\t\t\t\t2.Deposite\n\t\t\t\t\t\t3.Money Transfer\n\t\t\t\t\t\t4.Account Detail\n\t\t\t\t\t\t5.Exit\n\t\t\t\t\t\t");
                    scanf("%d", &choice);
                    amount = 0;

                    if (choice == 5)
                    {
                        system("clear");
                            break;
                    }
                    switch (choice)
                    {
                    case 1:
                        printf("\n\n\t\t\t\t\t\tHow much amount you want to Withdraw? : ");
                        scanf("%lld", &amount);

                        if (balance < amount)
                            printf("\n\n\t\t\t\t\t\tYou Don't have enough Balance\n");
                        else
                        {
                            balance -= amount;
                            printf("\n\n\t\t\t\t\t\tMoney Transffered Successfully");
                            printf("\n\n\t\t\t\t\t\tYour Balance : %lld\n", balance);
                            temp->Balance = balance;
                        }
                        break;
                    case 2:
                        printf("\n\n\t\t\t\t\t\tHow much amount you want to Deposite? : ");
                        scanf("%lld", &amount);

                        if (amount > 0)
                        {
                            balance += amount;
                            printf("\n\n\t\t\t\t\t\tBalance : %lld\n", balance);
                            temp->Balance = balance;
                        }
                        break;
                    case 3:
                        money_transfer(temp, head);
                        balance = temp->Balance;
                        break;
                    case 4:
                        printf("\n\n\t\t\t\t\t\tAccount No. : %d\n\t\t\t\t\t\tAccount holder : %s\n\t\t\t\t\t\tBalance : %lld\n\t\t\t\t\t\t", temp->account_Number, temp->Name, balance);
                        break;
                    default:
                        printf("\n\n\t\t\t\t\t\tEnter proper action");
                        break;
                    }
                }
            }
            else
            {
                wrong_iterator++;
                signal(SIGUSR1, wrong_pass);
                kill(getpid(), SIGUSR1);
                // alarm(1);
            }
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        signal(SIGUSR1, acc_not_exists);
        kill(getpid(), SIGUSR1);
        // alarm(1);
    }
    if (wrong_iterator == 3)
    {
        signal(SIGUSR1, multiple_pass);
        kill(getpid(), SIGUSR1);
        wrong_iterator = 0;
    }

    return wrong_iterator;
}
