#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Function declarations
void input();
void writefile();
void search();
void output();

// Structure to represent date
struct date {
    int month;
    int day;
    int year;
};

// Structure to represent customer account
struct account {
    int number;
    char name[100];
    int acct_no;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
} customer;

// Global variables
int tl, sl, ts;

// Function to input customer details
void input() {
    FILE *fp = fopen("bills.txt", "rb");
    fseek(fp, 0, SEEK_END);
    tl = ftell(fp);
    sl = sizeof(customer);
    ts = tl / sl;
    fseek(fp, (ts - 1) * sl, SEEK_SET);
    fread(&customer, sizeof(customer), 1, fp);
    printf("\nCustomer no: %d\n", ++customer.number);
    fclose(fp);
    printf("Account number: ");
    scanf("%d", &customer.acct_no);
    printf("Name: ");
    scanf("%s", customer.name);
    printf("Mobile no: ");
    scanf("%f", &customer.mobile_no);
    printf("Street: ");
    scanf("%s", customer.street);
    printf("City: ");
    scanf("%s", customer.city);
    printf("Previous balance: ");
    scanf("%f", &customer.oldbalance);
    printf("Current payment: ");
    scanf("%f", &customer.payment);
    printf("Payment date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &customer.lastpayment.month, &customer.lastpayment.day, &customer.lastpayment.year);
    return;
}

// Function to write customer details to file
void writefile() {
    FILE *fp;
    fp = fopen("bills.txt", "ab");
    fwrite(&customer, sizeof(customer), 1, fp);
    fclose(fp);
    return;
}

// Function to search for customer accounts
void search() {
    char ch;
    char nam[100];
    int n, i, m = 1;
    FILE *fp;
    fp = fopen("bills.txt", "rb");
    do {
        printf("\nEnter your choice: ");
        ch = getche();
    } while (ch != '1' && ch != '2');
    switch (ch) {
        case '1':
            fseek(fp, 0, SEEK_END);
            tl = ftell(fp);
            sl = sizeof(customer);
            ts = tl / sl;
            do {
                printf("\nChoose customer number: ");
                scanf("%d", &n);
                if (n <= 0 || n > ts)
                    printf("\nEnter correct\n");
                else {
                    fseek(fp, (n - 1) * sl, SEEK_SET);
                    fread(&customer, sl, 1, fp);
                    output();
                }
                printf("\nAgain? (y/n): ");
                ch = getche();
            } while (ch == 'y');
            fclose(fp);
            break;
        case '2':
            fseek(fp, 0, SEEK_END);
            tl = ftell(fp);
            sl = sizeof(customer);
            ts = tl / sl;
            fseek(fp, (ts - 1) * sl, SEEK_SET);
            fread(&customer, sizeof(customer), 1, fp);
            n = customer.number;

            do {
                printf("\nEnter the name: ");
                scanf("%s", nam);
                fseek(fp, 0, SEEK_SET);
                for (i = 1; i <= n; i++) {
                    fread(&customer, sizeof(customer), 1, fp);
                    if (strcmp(customer.name, nam) == 0) {
                        output();
                        m = 0;
                        break;
                    }
                }
                if (m != 0)
                    printf("\nDoesn't exist\n");
                printf("\nAnother? (y/n): ");
                ch = getche();
            } while (ch == 'y');
            fclose(fp);
    }
    return;
}

// Function to output customer details
void output() {
    printf("\n\nCustomer no: %d\n", customer.number);
    printf("Name: %s\n", customer.name);
    printf("Mobile no: %.f\n", customer.mobile_no);
    printf("Account number: %d\n", customer.acct_no);
    printf("Street: %s\n", customer.street);
    printf("City: %s\n", customer.city);
    printf("Old balance: %.2f\n", customer.oldbalance);
    printf("Current payment: %.2f\n", customer.payment);
    printf("New balance: %.2f\n", customer.newbalance);
    printf("Payment date: %d/%d/%d\n\n", customer.lastpayment.month, customer.lastpayment.day, customer.lastpayment.year);
    printf("Account status: ");
    switch (customer.acct_type) {
        case 'C':
            printf("CURRENT\n\n");
            break;
        case 'O':
            printf("OVERDUE\n\n");
            break;
        case 'D':
            printf("DELINQUENT\n\n");
            break;
        default:
            printf("ERROR\n\n");
    }

    return;
}

// Main function
int main() {
    int i, n;
    char ch;

    // Display welcome message and menu
    printf("\nA PROJECT BY Team TRAILS");
    printf("\n\nWELCOME TO KTR SUPERMARKET\n");
    printf("The Ultimate shopping place\n");
    printf("\nCUSTOMER BILLING SYSTEM:\n\n");
    printf("==========================================================\n");
    printf("1: To Add Account on list\n");
    printf("2: To Search Customer's Account\n");
    printf("3: Exit\n");
    printf("=========================================================\n");

    // Get user choice
    do {
        printf("\nSelect what do you want to do?");
        ch = getche();
    } while (ch <= '0' || ch > '3');

    // Perform actions based on user choice
    switch (ch) {
        case '1':
            // Add customer accounts
            printf("\nHow many customer accounts?");
            scanf("%d", &n);
            for (i = 0; i < n; i++) {
                input();
                if (customer.payment > 0)
                    customer.acct_type = (customer.payment < 0.1 * customer.oldbalance) ? 'O' : 'D';
                else
                    customer.acct_type = (customer.oldbalance > 0) ? 'D' : 'C';
                customer.newbalance = customer.oldbalance - customer.payment;
                writefile();
            }
            main(); // Restart the main function
            break;
        case '2':
            // Search customer accounts
            printf("Search by what?\n");
            printf("1 --- Search by customer number\n");
            printf("2 --- Search by customer name\n");
            search();
            ch = getche();
            main(); // Restart the main function
            break;
        case '3':
            // Exit the program
            printf("\nThanks for visiting\nThis PROJECT is designed BY Team TRAILS");
            exit(1);
    }

    return 0;
}
