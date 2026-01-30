#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accNo;
    int pin;
    float balance;
};

void checkBalance(struct Account a) {
    printf("\nCurrent Balance: ₹%.2f\n", a.balance);
}

void deposit(struct Account *a) {
    float amt;
    printf("\nEnter amount to deposit: ");
    scanf("%f", &amt);

    if (amt > 0) {
        a->balance += amt;
        printf("Deposit successful!\n");
    } else {
        printf("Invalid amount!\n");
    }
}

void withdraw(struct Account *a) {
    float amt;
    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amt);

    if (amt > 0 && amt <= a->balance) {
        a->balance -= amt;
        printf("Please collect your cash.\n");
    } else {
        printf("Insufficient balance or invalid amount!\n");
    }
}

void saveAccount(struct Account a) {
    FILE *fp = fopen("account.txt", "w");
    fprintf(fp, "%d %d %.2f", a.accNo, a.pin, a.balance);
    fclose(fp);
}

void loadAccount(struct Account *a) {
    FILE *fp = fopen("account.txt", "r");
    if (fp == NULL) {
        a->accNo = 12345;
        a->pin = 1111;
        a->balance = 5000;
        saveAccount(*a);
    } else {
        fscanf(fp, "%d %d %f", &a->accNo, &a->pin, &a->balance);
        fclose(fp);
    }
}

int main() {
    struct Account acc;
    int enteredPin, choice;

    loadAccount(&acc);

    printf("====== ATM SYSTEM ======\n");
    printf("Enter PIN: ");
    scanf("%d", &enteredPin);

    if (enteredPin != acc.pin) {
        printf("Incorrect PIN! Access denied.\n");
        return 0;
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(acc);
                break;
            case 2:
                deposit(&acc);
                saveAccount(acc);
                break;
            case 3:
                withdraw(&acc);
                saveAccount(acc);
                break;
            case 4:
                printf("Thank you for using ATM!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
