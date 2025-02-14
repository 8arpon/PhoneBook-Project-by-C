#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct phoneBook{
    char name[50];
    char email[50];
    char number[15];
};

FILE *contacts;
FILE *aRegFile;
FILE regFile;

struct phoneBook Contact[1000];
void panelFunc(FILE *contacts);
void choiceOpt(FILE *contacts);
void panelFunc(FILE *contacts);
void regFuncA();
void regFuncU();

int tUser = 0;

void infoFunc(){
    printf("\n-------------------------------------------------------\n");
    printf("Which one do you want? (Write the number only):\n");
    printf("1. Add Contacts\n");
    printf("2. Search Contacts\n");
    printf("3. See all Contacts\n");
    printf("4. Update Contacts\n");
    printf("5. Delete the contact file\n");
    printf("6. Total contacts\n");
    printf("7. Exit\n");
    printf("-------------------------------------------------------\n");
}

void infoFuncA(){
    printf("\n-------------------------------------------------------\n");
    printf("1. See total users.\n");
    printf("2. See User details\n");
    printf("3. Delete the user file\n");
    printf("4. Exit\n");
    printf("-------------------------------------------------------\n");
}


void aboutFunc(){
    FILE *us;
    FILE *contacts;
    us = fopen("about.txt", "r");
    
    char aboutS[500];
    while(fgets(aboutS, 500, us) != NULL){
        printf("%s", aboutS);
    }

    fclose(us);
    panelFunc(contacts);

}

void addCont(){
    for(int i = 0; i < 1; i++){
        printf("Write details of Person %d\n", i + 1);
        getchar();
        printf("Name: ");
        Contact[i].name[strcspn(Contact[i].name, "\n")] = 0;
        fgets(Contact[i].name, sizeof(Contact[i].name), stdin);
        printf("Email: ");
        fgets(Contact[i].email, sizeof(Contact[i].email), stdin);
        printf("Contact Number: ");
        fgets(Contact[i].number, sizeof(Contact[i].number), stdin);
    }
    printf("Your contacts added successfully\n");
}

void saveCont(FILE *contacts){
    contacts = fopen("contact.txt", "a");

    for(int i = 0; i < 1; i++){
        fprintf(contacts, "Contact Details of %s", Contact[i].name);
        fprintf(contacts, "Name: %s", Contact[i].name);
        fprintf(contacts, "Email: %s", Contact[i].email);
        fprintf(contacts, "Contact Number: %s", Contact[i].number);
    }
    fclose(contacts);
}

void showCont(FILE *contacts){
    contacts = fopen("contact.txt", "r");
    char string[500];
    while(fgets(string, 500, contacts) != NULL){
        printf("%s", string);
    }
    fclose(contacts);
}

void updateCont(FILE *contacts){
    int check = 0;
    contacts = fopen("contact.txt", "r");
    FILE *upCont;
    upCont = fopen("stored.txt", "w");
    struct phoneBook sNameD;
    printf("Enter the name you want to update: ");
    char sName[50];
    getchar();
    fgets(sName, sizeof(sName), stdin);
    sName[strcspn(sName, "\n")] = 0;

    
    while(fscanf(contacts, "Contact Details of %s\nName: %s\nEmail: %s\nContact Number: %s\n", sNameD.name, sNameD.name, sNameD.email, sNameD.number) != EOF){
        if(strcmp(sName, sNameD.name) == 0){
            check = 1;
            printf("Enter the new contact Name: ");
            fgets(sNameD.name, sizeof(sNameD.name), stdin);
            sNameD.name[strcspn(sNameD.name, "\n")] = 0;
            printf("Enter the new contact Email: ");
            fgets(sNameD.email, sizeof(sNameD.email), stdin);
            sNameD.email[strcspn(sNameD.email, "\n")] = 0;
            printf("Enter the new contact Number: ");
            fgets(sNameD.number, sizeof(sNameD.number), stdin);
            sNameD.number[strcspn(sNameD.number, "\n")] = 0;
        }
        fprintf(upCont, "Contact Details of %s\nName: %s\nEmail: %s\nContact Number: %s\n", sNameD.name, sNameD.name, sNameD.email, sNameD.number);
    }

    fclose(contacts);
    fclose(upCont);
    
    if(check == 1){
        remove("contact.txt");
        rename("stored.txt", "contact.txt");
        printf("Your contact updated successfully!!!");
        choiceOpt(contacts);
    }
    else{
        printf("No contact found...");
        choiceOpt(contacts);
    }

}

void sContName(FILE *contacts){
    contacts = fopen("contact.txt", "r");
    char sName[50];
    printf("Enter the name to search: ");
    getchar();
    fgets(sName, sizeof(sName), stdin);
    sName[strcspn(sName, "\n")] = 0;

    struct phoneBook sNameD;
    int test = 0;

    while(fscanf(contacts, "Contact Details of %s\nName: %s\nEmail: %s\nContact Number: %s\n", sNameD.name, sNameD.name, sNameD.email, sNameD.number) != EOF){

        if(strcmp(sName, sNameD.name) == 0){
            printf("Contacts Found...\n");
            printf("Name: %s\n", sNameD.name);
            printf("Email: %s\n", sNameD.email);
            printf("Number: %s\n", sNameD.number);
            test = 1;
        }
    }
    if(test == 0){
        printf("No contacts found according to your details.\n");
    }

    fclose(contacts);
}

void sContNumber(FILE *contacts){
    contacts = fopen("contact.txt", "r");
    printf("Please write the number you want to search: ");
    char sNumber[15];
    getchar();
    fgets(sNumber, sizeof(sNumber), stdin);
    sNumber[strcspn(sNumber, "\n")] = 0;

    struct phoneBook sNumberD;
    int test = 0;
    while(fscanf(contacts, "Contact Details of %s\nName: %s\nEmail: %s\nContact Number: %s\n", sNumberD.name, sNumberD.name, sNumberD.email, sNumberD.number) != EOF){
        if(strcmp(sNumber, sNumberD.number) == 0){
            printf("Contacts Found...\n");
            printf("Name: %s\n", sNumberD.name);
            printf("Email: %s\n", sNumberD.email);
            printf("Number: %s\n", sNumberD.number);
            test = 1;
        }
    }
    if(test == 0){
        printf("No contacts found according to your details.\n");
    }

    fclose(contacts);

}


void choiceOpt(FILE *contacts){
    int option;
    do{
        infoFunc();
        scanf("%d", &option);

        if(option == 7){
            printf("Thanks for using the PhoneBook App.\n");
            exit(0);
        }

        else if(option == 1){
            addCont();
            saveCont(contacts);
        }
        else if(option == 3){
            printf("\n-------------------------------------------------------\n");
            printf("Here is your Contacts:\n");
            printf(".......................................................\n");
            showCont(contacts);
            printf("\n-------------------------------------------------------\n");
        }
        else if(option == 2){
            int check;
            printf("Write how you want to search?(Choose 1 or 2)\n1. Name\n2. Number\n");
            scanf("%d", &check);

            if(check == 1){
                sContName(contacts);
                choiceOpt(contacts);
            }
            else if(check == 2){
                sContNumber(contacts);
                choiceOpt(contacts);;
            }

        }
        else if(option == 4){
            updateCont(contacts);
        }
        else if(option == 5){
            int danger;
            printf("Are you sure to delete the contact file?\n1. Yes\n2. No\n(1 or 2): ");
            scanf("%d", &danger);
            if(danger == 1){
                remove("contact.txt");
                choiceOpt(contacts);
            }
            else if(danger == 2){
                printf("Contact file is safe. Contact file is not being deleted.\n");
                choiceOpt(contacts);
            }
        }
        else if(option == 6){
            contacts = fopen("contact.txt", "r");
            char string[500];
            int tLine = 0;
            while(fgets(string, 500, contacts) != NULL){
                tLine++;
            }
            int numCont;
            numCont = tLine / 4;
            printf("Total number of contacts you have: %d", numCont);
        }
        else{
            printf("Invalid Choice!!\n");
            choiceOpt(contacts);
        }
 
        
    }while(1);
    
}

void aShowUsers(){
    FILE *regFile;
    char aString[500];
    char passU;
    regFile = fopen("users.txt", "r");
    while(fgets(aString, sizeof(aString), regFile) != NULL){
        printf("%s", aString);
    }

    fclose(regFile);
}

void choiceOptA(){
    FILE *contacts;
    FILE *regFile;
    FILE *aRegFile;
    int optionA;
    int danger;
    do{
        infoFuncA();
        scanf("%d", &optionA);
        if(optionA == 1){
            regFile = fopen("users.txt", "r");
            char string[500];
            while(fgets(string, sizeof(string), regFile) != NULL){
                tUser++;
            }
            printf("Total Users: %d", tUser / 4);
        }
        else if(optionA == 4){
            printf("Thanks for using our PhoneBook App.\n");
            exit(0);
        }
        else if(optionA == 2){
            printf("\nUsers Details: \n");
            aShowUsers();
        }
        else if(optionA == 3){
            printf("Are you sure to delete the file?\n(1. YES 2. NO)\n");
            scanf("%d", &danger);
            if(danger == 1){
                remove("users.txt");
                printf("Your file has been deleted successfully\n");
                choiceOptA();
            }
            else if(danger == 2){
                printf("Your user file is safe\n");
                choiceOptA();
            }
        }

        

    }while(1);

}


void loginFuncU(FILE *regFile, FILE *contacts){
    regFile = fopen("users.txt", "r");
    if(regFile == NULL){
        printf("\nNo data/file found.\nPlease Register first.\n\n");
        regFuncU();
    }

    printf("\nIf you have account then please login: \n");
    char test[500];
    char firstName[50];
    char lastName[50];
    char userName[50];
    char passWord[50];
    char iPass[50];
    char iUsrN[50];

    getchar();
    
    printf("Write your username: ");
    fgets(iUsrN, sizeof(iUsrN), stdin);
    iUsrN[strcspn(iUsrN, "\n")] = 0;
    
    printf("Write your password: ");
    fgets(iPass, sizeof(iPass), stdin);
    iPass[strcspn(iPass, "\n")] = 0;

    int loggedin = 0;
    while(fscanf(regFile, "First Name: %s\nLast Name: %s\nUserName: %s\nPassword: %s\n", firstName, lastName, userName, passWord) != EOF){
        if(strcmp(userName, iUsrN) == 0 && strcmp(passWord, iPass) == 0){
            printf("\nLogin Successful\n");
            choiceOpt(contacts);
            loggedin = 1;

        }
    }

    if(loggedin == 0){
        printf("Username or password is incorrect.\n");
        panelFunc(contacts);
    }
    fclose(regFile);

}

void regFuncU(){
    FILE *contacts;
    FILE *regFile;
    regFile = fopen("users.txt", "a+");
    char firstName[50];
    char lastName[50];
    char userName[50];
    char passWord[50];
  
    getchar();
    firstName[strcspn(firstName, "\n")] = 0;
    printf("Enter your First Name: ");
    fgets(firstName, sizeof(firstName), stdin);

    printf("Enter your Last Name: ");
    fgets(lastName, sizeof(lastName), stdin);

    printf("Enter your username: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = 0;

    printf("Enter a Password: ");
    fgets(passWord, sizeof(passWord), stdin);

    fprintf(regFile, "First Name: %s", firstName);
    fprintf(regFile, "Last Name: %s", lastName);
    fprintf(regFile, "UserName: %s\n", userName);
    fprintf(regFile, "Password: %s", passWord);

    printf("Congratulations! Your registration completed.\n");
    
    choiceOpt(contacts);
    fclose(regFile);
    
}

void loginFuncA(FILE *aRegFile, FILE *contacts){
    aRegFile = fopen("admins.txt", "r");
    if(aRegFile == NULL){
        printf("\nNo data/file found.\nPlease Register first.\n\n");
        regFuncA();

    }

    printf("\nIf you have account then please login: \n");
    char test[500];
    char firstName[50];
    char lastName[50];
    char userName[50];
    char passWord[50];
    char iPass[50];
    char iUsrN[50];

    getchar();
    
    printf("Write your username: ");
    fgets(iUsrN, sizeof(iUsrN), stdin);
    iUsrN[strcspn(iUsrN, "\n")] = 0;
    
    printf("Write your password: ");
    fgets(iPass, sizeof(iPass), stdin);
    iPass[strcspn(iPass, "\n")] = 0;

    int loggedin = 0;
    while(fscanf(aRegFile, "First Name: %s\nLast Name: %s\nUserName: %s\nPassword: %s\n", firstName, lastName, userName, passWord) != EOF){
        if(strcmp(userName, iUsrN) == 0 && strcmp(passWord, iPass) == 0){
            printf("\nLogin Successful\n");
            choiceOptA();
            loggedin = 1;

        }
    }

    if(loggedin == 0){
        printf("Username or password is incorrect.\n");
        panelFunc(contacts);
    }
    fclose(aRegFile);

}

void regFuncA(){
    FILE *aRegFile;
    FILE *contacts;
    aRegFile = fopen("admins.txt", "a+");
    char firstName[50];
    char lastName[50];
    char userName[50];
    char passWord[50];
  
    getchar();
    firstName[strcspn(firstName, "\n")] = 0;
    printf("Enter your First Name: ");
    fgets(firstName, sizeof(firstName), stdin);

    printf("Enter your Last Name: ");
    fgets(lastName, sizeof(lastName), stdin);

    printf("Enter your username: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = 0;

    printf("Enter a Password: ");
    fgets(passWord, sizeof(passWord), stdin);

    fprintf(aRegFile, "First Name: %s", firstName);
    fprintf(aRegFile, "Last Name: %s", lastName);
    fprintf(aRegFile, "UserName: %s\n", userName);
    fprintf(aRegFile, "Password: %s", passWord);

    printf("Congratulations! Your registration completed.\n");
    choiceOptA();
    
    fclose(aRegFile);
    
}

void adminFunc(FILE *contacts){
    FILE *aRegFile;
    printf("\n-------------------------------------------------------\n");
    printf("            Welcome to the Admin Panel.\n");
    printf("-------------------------------------------------------\n");

    char code[] = "arpon-sarker";
    char iCode[50];
    printf("Please write the 'Admin code' to access or be an Admin\n(or Contact with Arpon to get the 'Admin Code'): ");
    getchar();
    fgets(iCode, 50, stdin);
    iCode[strcspn(iCode, "\n")] = 0;

    if(strcmp(code, iCode) == 0){
        printf("\nPleae select Login or Registration?\n1. Login\n2. Registration\n");
        printf("-------------------------------------------------------\n");
        int logReg;
        scanf("%d", &logReg);

        if(logReg == 1){
            loginFuncA(aRegFile, contacts);
        }
        else if(logReg == 2){
            regFuncA();
        }

        else{
            printf("Invalid Input.\n");
            adminFunc(contacts);
        }
    }
    else{
        printf("You are not eligible for accessing the Admin Panel.\n");
        exit(0);
    }


}

void userFunc(FILE *contacts){
    FILE *regFile;
    printf("\n-------------------------------------------------------\n");
    printf("            Welcome to the User Panel.\n");
    printf("-------------------------------------------------------\n");
    printf("\nPleae select Login or Registration?\n1. Login\n2. Registration\n");
    printf("-------------------------------------------------------\n");
    int opt;
    scanf("%d", &opt);
    if(opt == 1){
        loginFuncU(regFile, contacts);
    }
    else if(opt == 2){
        regFuncU();
    }

}

void panelFunc(FILE *contacts){
    contacts = fopen("contact.txt", "r");
    printf("\n-------------------------------------------------------");
    printf("\nWelcome to the PhoneBook. Created by [Arpon Sarker]. \n");
    printf("-------------------------------------------------------\n");
    
    printf("\n-------------------------------------------------------\n");
    printf("Choose one option: \n1. Admin Panel\n2. User Panel\n3. About us\n4. Exit\n");
    printf("-------------------------------------------------------\n");

    int panel;
    scanf("%d", &panel);
    if(panel == 1){
        adminFunc(contacts);
    }
    else if(panel == 2){
        userFunc(contacts);
    }
    else if(panel == 3){
        aboutFunc();
    }
    else if(panel == 4){
        printf("Thank you\n");
        exit(0);
    }
    else{
        printf("Invalid Choice!!\n");
        panelFunc(contacts);
    }

}



int main()
{
    FILE *contacts;
    contacts = fopen("contact.txt", "a");
    if(contacts == NULL){
        printf("No file exists...");
    }

    panelFunc(contacts);

    return 0;
}