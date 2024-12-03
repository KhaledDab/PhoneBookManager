
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CapitalNa 65
typedef struct Contact {
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next
} Contact;

Contact* Names(Contact* phonebook[26],char *firstName,char * lastName){
    Contact* tempt;
    for (int i = 0; i < 26; ++i) {
        tempt = phonebook[i];
        while (tempt != NULL){
            if (strcmp(tempt->firstName,firstName)==0 && strcmp(tempt->lastName,lastName)==0){
                return tempt;
            }
            tempt = tempt->next;
        }
    }return NULL;
}

/******************************************************************************
 * Function name: CheckNumberContact .
 * Check if the number of the contact is already exist or not.
 ******************************************************************************/
Contact* CheckNumberContact(Contact* phonebook[26],char* Number){
    Contact *temp7 ;
    for (int i = 0; i < 26; ++i) {
        temp7 = phonebook[i];
        while (temp7 != NULL) {
            if (strcmp(temp7->phoneNum, Number) == 0) {
                return temp7;
            }
            temp7 = temp7->next;
        }
    }
        return NULL;
}

/************************************************************************
 * Function name : CheckNameContact.
 * Check if the first name and last name of the contact is already exist.
 ************************************************************************/
Contact* CheckNameContact(Contact* List,char* FirstName,char* LastName){
    Contact *basic = List;
    while (basic != NULL) {
        if (strcmp(basic->firstName, FirstName) == 0 &&
            strcmp(basic->lastName,LastName) == 0){
            return basic;
        }
        basic = basic->next;
    }
    return NULL;
}

/************************************************************************
 * Function name : createContact .
 * The function help us to a creat a new contact with his first name and
 * last name and his phone number .
 ************************************************************************/
Contact* createContact(char* FirstName,char* LastName,char* Number){
    Contact* NewCont= (Contact*) malloc(sizeof(Contact));
    NewCont->firstName=(char*) malloc(sizeof(char ) * strlen(FirstName));
    NewCont->lastName=(char*) malloc(sizeof(char ) * strlen(LastName));
    NewCont->phoneNum=(char*) malloc(sizeof(char ) * strlen(Number));
    strcpy(NewCont->firstName,FirstName);
    strcpy(NewCont->lastName,LastName);
    strcpy(NewCont->phoneNum,Number);
    NewCont->next=NULL;
    return NewCont;
}

/************************************************************************
 * Function name : AddToList
 * when we add a new contact in a function that help us to add a new contact ,
 * we add the contact to the List .
 * Function that help us to add a new contact in the true place .
 ************************************************************************/
void AddToList(int List, Contact* NewCont,Contact* phonebook[26]){

    Contact *basic= phonebook[List];
    if(phonebook[List] == NULL){
        phonebook[List]=NewCont;
        return;
    }else{
        while (basic->next != NULL){
            basic=basic->next;
        }
        basic->next=NewCont;

        return;
    }
}

/*************************************************************************
 * Function name : FreeToContact.
 * The function help us to do a free for The Contact his first name
 * and last name and a phone number .
 *************************************************************************/
void FreeToContact(Contact* phonebook[26]){
    Contact *temp9;
    for (int i = 0; i < 26; ++i) {
        temp9 = phonebook[i];
        while (temp9 != NULL) {
            Contact *temp10 = temp9;
            temp9 = temp9->next;
            free(temp10->firstName);
            free(temp10->lastName);
            free(temp10->phoneNum);
            free(temp10);
        }
    }
}

/******************************************************************************
 * Function name: NewContact.
 * input : FirstName , LastName , Number .
 * output : if the addition contact was failed or success .
 * The function help us to add a new contact
 * (his FirstName,Last Name ,Phone number)
 ******************************************************************************/
void NewContact(Contact* phonebook[26]){
    char FirstName[11];
    char LastName[11];
    char Number[11];
    scanf("%s",FirstName);
    scanf("%s",LastName);
    scanf("%s",Number);
    if (CheckNameContact(phonebook[LastName[0] - CapitalNa],
                         FirstName,LastName)!= NULL){
        printf(" The addition of the contact has failed,"
               " since the contact %s %s already exists!\n",
               FirstName,LastName);
        return;
    }
    if (CheckNumberContact(phonebook,Number) != NULL){
        printf(" The addition of the contact has failed,"
               " since the phone number %s already exists!\n",Number);
        return;
    }
    Contact* NewCont=createContact(FirstName,LastName,Number);
    int place = LastName[0]- 65;
     AddToList(place,NewCont,phonebook);
    printf(" The contact has been added successfully!\n");

}

/****************************************************************************
 * Function Name : RemoveContact .
 * The Function help to remove a contact.
 ****************************************************************************/
Contact* RemoveContact(Contact* List,char* FirstName,char* LastName){
    if (List == NULL){
        return 0;//return Error.
    }
    Contact* basic = List;
    if (strcmp(basic->firstName,FirstName)==0 && strcmp(basic->lastName,
                                                        LastName)==0){
        List = basic->next;
        free(basic);
        return List;
    }
    Contact *previous = basic;
    Contact *current = basic->next;
    while (current != NULL && strcmp(basic->firstName,FirstName)!=0 &&
           strcmp(basic->lastName,LastName)!=0){
        previous = previous->next;
        current = current->next;

    }
    if (current == NULL){
        //error
        return basic;
    }
    previous->next = current->next;
    free(current);
    return basic;
}

/*******************************************************************************
 * function name : RemoveCont
 * the function help us to remove a contact.
 *******************************************************************************/
void RemoveCont(Contact* phonebook[26], char* FirstName,char* LastName){

    phonebook[LastName[0]-CapitalNa] = RemoveContact(
            phonebook[LastName[0]-CapitalNa],
            FirstName,LastName);
}

/********************************************************************************
 * Function name : UpdatePhoneNumber.
 * The Function help us to update a phone number for a contact .
 ********************************************************************************/
void UpdatePhoneNumber(Contact *contact,char* Number){
    free(contact->phoneNum);
    contact->phoneNum = (char *) malloc(sizeof(char) * strlen(Number));
    strcpy(contact->phoneNum, Number);
}

/***********************************************************************************
 * Function name : findByPhone
 * The function help us to find a contact by his phone number.
 **********************************************************************************/
Contact* findByPhone(Contact* phonebook[26],char* number)
{
    Contact *temp;
    for (int i = 0; i < 26; ++i) {
        temp = phonebook[i];
        while (temp != NULL) {
            if (strcmp(temp->phoneNum, number) == 0) {
                return temp;
            }
            temp = temp->next;
        }
    }
    return NULL;
}

/*************************************************************************************
 * Function name : FindContactByName.
 * he return to us the basic that who is the first pointer.
 * Function help us To find a contact by his first name and last name .
 ************************************************************************************/
Contact* FindContactByName(Contact* List, char* FirstName,char* LastName){
    Contact *basic=List;
    while (basic != NULL){
        if(strcmp(basic->firstName,FirstName)== 0 && strcmp(basic->lastName,
                                                            LastName)==0){
            return basic;
        }
        basic = basic->next;
    }
    return NULL;
}
/**********************************************************
 * Function name : PrintList1
 * the function this print to us all the list of the phone book.
 *
 *********************************************************/
void PrintList(Contact *List){
    if (List == NULL){
        return;
    }else {
        PrintList(List->next);
        printf("%-11s",List->firstName);
        printf("%-11s",List->lastName);
        printf("%-11s\n",List->phoneNum);
    }
}

int main() {
    int option; // the option is for the switch to do a list and cases.
    char FirsName[11];
    char LastName[11];
    char Number[11];
    char yesno; // yesno is for the question to delete contact.
    int menu = 1 ;//to the menu .
    Contact *phonebook[26];
    for (int i = 0; i < 26; ++i) {
        phonebook[i]=NULL;
    }
    while(1) {
        if (menu) {
            printf("Welcome to the phone book manager! \n"
                   "Choose an option:\n"
                   "1. Add a new contact to the phone book.\n"
                   "2. Delete a contact from the phone book.\n"
                   "3. Find a contact in the phone book by phone number.\n"
                   "4. Find a contact in the phone book by name.\n"
                   "5. Update phone number for a contact.\n"
                   "6. Print phone book.\n"
                   "7. Exit.\n");
        }
        scanf("%d", &option);
        menu = 1 ;
        switch (option) {
            case 1:
                printf("Enter a contact details (<first name> <last name>"
                       " <phone number>):");
                    NewContact(phonebook);

                break;

            case 2:
                printf("Enter a contact name (<first name> <last name>):");
                scanf("%s %s",FirsName,LastName);
                if (CheckNameContact(phonebook[LastName[0] - CapitalNa],
                                     FirsName, LastName) == NULL)
                {
                    printf(" The deletion of the contact has failed!\n");
                    break;
                }
                printf(" Are you sure? (y/n)");
                scanf(" %c",&yesno);
                if(yesno == 'y') {
                    RemoveCont(phonebook, FirsName, LastName);
                    printf(" The contact has been deleted successfully!\n");
                    break;
                }
                if(yesno != 'y') {
                    printf(" The deletion of the contact has been canceled.\n");
                    break;
                }
                break;

            case 3:
                printf("Enter a phone number:");
                scanf("%s",Number);
                Contact *Findit= findByPhone(phonebook,Number);
                if (Findit==NULL)
                {
                    printf(" No contact with a phone number %s"
                           " was found in the phone book\n",Number);
                    break;
                }
                else
                {
                    printf(" The following contact was found: %s %s %s\n",
                           Findit->firstName,Findit->lastName,Findit->phoneNum);
                    break;
                }

            case 4:
                printf("Enter a contact name (<first name> <last name>):");
                scanf("%s%s",FirsName,LastName);
                /*******************************************
                 * place is for the places in the phonebook.
                 ********************************************/
                int place = LastName[0] - CapitalNa;
                Contact *FindItByName = FindContactByName(phonebook[place]
                        ,FirsName,LastName);
                if (FindItByName == NULL){
                    printf(" No contact with a name %s %s "
                           "was found in the phone book\n",FirsName,LastName);
                }
                else {
                    printf(" The following contact was found: %s %s %s\n",
                           FindItByName->firstName,
                           FindItByName->lastName,FindItByName->phoneNum);
                    continue;
                }
                break;

            case 5:
                printf("Enter a contact name (<first name> <last name>):");
                scanf("%s %s",FirsName,LastName);
                if (CheckNameContact(phonebook[LastName[0] - CapitalNa],
                                     FirsName, LastName) == NULL)
                {
                    printf(" No contact with a name %s %s "
                           "was found in the phone book\n",FirsName,LastName);
                    break;
                }
                /*****************************************
                 * a is for the place in the phone book .
                 *****************************************/
                int a = LastName[0] - CapitalNa;
                Contact *FindByName = FindContactByName(phonebook[a],
                                                        FirsName,LastName);
                if (FindByName == NULL){
                    printf(" No contact with a name %s %s "
                           "was found in the phone book\n",FirsName,LastName);
                }else {
                    printf(" The following contact was found: %s %s %s\n",
                           FindByName->firstName,
                           FindByName->lastName, FindByName->phoneNum);
                    printf("Enter the new phone number: ");
                    scanf("%s", Number);
                    if (CheckNumberContact(phonebook, Number) != NULL) {
                        printf(" The update of the contact has failed,"
                               " since the phone number %s already exists!\n",
                               Number);
                        break;
                    }
                    UpdatePhoneNumber(CheckNameContact(
                            phonebook[LastName[0] - CapitalNa],
                            FirsName, LastName), Number);
                    printf(" The contact has been updated successfully!\n");
                }
                break;

            case 6:
                for (int i = 0; i < 26; ++i) {
                    PrintList(phonebook[i]);
                }
                break;

            case 7:
                printf("Bye!");
                FreeToContact(phonebook);
                return 0;
            default:
                printf("Wrong option, try again:\n");
                menu = 0;
                break;
        }
    }

}