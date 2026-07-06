#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
int valid_name(char name[]){
	for(int i=0;name[i]!='\0';i++){
		if(!isalpha(name[i])&&name[i]!='\0'&&name[i]!=' '){
			printf("Given Name is Invalid,must contain alphatic\n");
			return 0;
		}
		//return 1;
	}
	return 1;
}
int valid_phone(char phone[]){
	if(strlen(phone)!=10||'6'>phone[0]||'9'<phone[0]){
		printf("Phone No must contain numbveric\n");
		return 0;
	}
	for(int i=0;phone[i]!='\0';i++){
		if(!isdigit(phone[i])){
			printf("Must contain numeric value\n");
			return 0;
		}
	}
	return 1;
}
int valid_mail(char mail[]){
	if(!isalpha(mail[0])){
		printf("Invalid mail:must start with alphatic\n");
		return 0;
	}
	char *a=strchr(mail,'@');
	if(!a||strchr(a+1,'@')){
		printf("Mail must contain only one '@'symbol\n");
		return 0;
	}
	if(a==mail){
		printf("username is missing before @\n");
	}
	if(*(a+1)=='\0'){
		printf("Domain missing after @\n");
	}
	if(!(strstr(mail,"@gmail.com")&&strcmp(strchr(mail,'@'),"@gmail.com")==0)
			&&!(strstr(mail,"@yahoo.com")&&strcmp(strchr(mail,'@'),"@yahoo.com")==0)){
		printf("Invalid format must contain '@dmain.com'\n");
		return 0;
	}
	return 1;
}
int search_name(char name[],AddressBook *addressBook){
	int flag=0,count=0,i=0;
	for(i=0;i<addressBook->contactCount;i++){
		if(strcmp(addressBook->contacts[i].name,name)==0){
			flag++;
			count=i;
		}
	}
	if(flag==1){
		return count;
	}
	else if(flag>1){
		return -2;
	}else{
		//printf("Contact not found\n");
		return -1;
	}
}
int search_mail(char mail[],AddressBook *addressBook){
	int i=0,count=0,flag=0;
	for(i=0;i<addressBook->contactCount;i++){
		if(strcmp(addressBook->contacts[i].email,mail)==0){
			count=i;
			flag++;
		}
	}
	if(flag==1){
		return count;
	}else if(flag>1){
		return -2;
	}else{
		//printf("Contact not found\n");
		return -1;
	}
}
int search_phone(char phone[],AddressBook *addressBook){
	int i=0,count=0,flag=0;
	for(i=0;i<addressBook->contactCount;i++){
		if(strcmp(addressBook->contacts[i].phone,phone)==0){
			count=i;
			flag++;
		}
	}
	if(flag==1){
		return count;
	}else if(flag>1){
		return -2;
	}else{
		//printf("Contact not found\n");
		return -1;
	}
}
int duplicatemail(AddressBook *addressBook, char email[], int currentIndex){
	for(int i = 0; i < addressBook->contactCount; i++){
		if(i != currentIndex && strcmp(addressBook->contacts[i].email, email) == 0){
			return 1;
		}
	}
	return 0;
}
int duplicatephone(AddressBook *addressBook, char phone[], int currentIndex){
	for(int i = 0; i < addressBook->contactCount; i++){
		if(i != currentIndex && strcmp(addressBook->contacts[i].phone,phone) == 0){
			return 1;
		}
	}
	return 0;
}
void listContacts(AddressBook *addressBook) 
{

	// Sort contacts based on the chosen criteria
	int count=addressBook->contactCount;
	if(count==0){
		printf("No Contact is Available\n");
		return;
	}
	printf("\n%-20s %-30s %-15s\n", "Name", "Mail_Id", "Phone_no");
	printf("---------------------------------------------------------------------\n");
	for(int i=0;i<count;i++){
		printf("%-20s",addressBook->contacts[i].name);
		printf("%-30s",addressBook->contacts[i].email);
		printf("%-15s\n",addressBook->contacts[i].phone);
	}

}

void initialize(AddressBook *addressBook) {
	addressBook->contactCount = 0;    
	loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	char name[50];
	char phone[20];
	char mail[50];
	int len=0,i=0;
	int count=addressBook->contactCount;
	while(len<3){
		printf("Enter a name: ");
		scanf(" %[^\n]",name);
		if(valid_name(name))
			break;
		len++;
		if(len<3)
			printf("Please try again.Attempts left: %d\n",3-len);
	}
	if(len==3){
		printf("Try again Later\n");
		return;
	}
	len=0;
	while(len<3){
		printf("Enter a phone_no: ");
		scanf(" %[^\n]",phone);
		if(valid_phone(phone))
			break;
		len++;
		if(len<3)
			printf("Please try again.Attempts left: %d\n",3-len);
	}
	if(len==3){
		printf("Try again Later\n");
		return;
	}
	len=0;
	while(len<3){
		printf("Enter a mail_id: ");
		scanf(" %[^\n]",mail);	
		if(valid_mail(mail))
			break;
		len++;
		if(len<3)
			printf("Try Again,Attempts left %d\n",3-len);
	}
	if(len==3){
		printf("Try again later\n");
		return;
	}
	for(i=0;i<count;i++){
		if(strcmp(addressBook->contacts[i].phone,phone)==0){
			printf("Phone number is already exists\n");
			return;
		}
		if(strcmp(addressBook->contacts[i].email,mail)==0){
			printf("Email already exists\n");
			return;
		}
	}
	strcpy(addressBook->contacts[count].name,name);
	strcpy(addressBook->contacts[count].email,mail);
	strcpy(addressBook->contacts[count].phone,phone);
	addressBook->contactCount++;
	printf("Contact added successfully\n");
	//saveAndExit(addressBook);
	//saveAndExit(addressBook);
	return;
}

void searchContact(AddressBook *addressBook) 
{
	if(addressBook->contactCount==0){
		printf("contact is empty\n");
		return;
	}
	char name[100];
	char phone[20];
	char mail[50];
	int c;
	printf("Search the contact\n");
	printf("Enter a name to search: ");
	scanf("	%[^\n]",name);
	int res=search_name(name,addressBook);
	if(res==-1){
		printf("Contact not found\n");
		return;
	}
	if(res==-2){
		printf("Multiple contact found\n");
		printf("Choice:\n1.Mail\n2.Phone\n");
		scanf("%d",&c);
		switch(c){
			case 1:
				{
					printf("Enter a mail: ");
					scanf(" %[^\n]",mail);
					res=search_mail(mail,addressBook);
					break;
				}
			case 2:
				{
					printf("Enter a phone: ");
					scanf(" %[^\n]",phone);
					res=search_phone(phone,addressBook);
					break;
				}
			default:
				{
					printf("Invalid choice\n");
					return;
				}
		}			
	}
	if(res>=0){
		printf("\n%-20s %-30s %-15s\n", "Name", "Mail_Id", "Phone_no");
		printf("---------------------------------------------------------------------\n");	
		printf("%-20s",addressBook->contacts[res].name);
		printf("%-30s",addressBook->contacts[res].email);
		printf("%-15s\n",addressBook->contacts[res].phone);
	}
}
void editContact(AddressBook *addressBook)
{
	if(addressBook->contactCount == 0){
		printf("Contact is empty\n");
		return;
	}
	char name[50], mail[50], phone[20];
	int c, ch, len, res;
	printf("Enter a name to edit: ");
	scanf(" %[^\n]", name);
	res = search_name(name, addressBook);
	if(res == -1){
		printf("Contact not found\n");
		return;

	}
	if(res == -2){
		printf("Multiple contacts found\n");
		printf("1.Mail\n2.Phone\n");
		scanf("%d", &c);
		if(c == 1){
			printf("Enter mail: ");
			scanf(" %[^\n]", mail);
			res = search_mail(mail, addressBook);
		}
		else if(c == 2){
			printf("Enter phone: ");
			scanf(" %[^\n]", phone);
			res = search_phone(phone, addressBook);
		}
		else{
			printf("Invalid choice\n");
			return;
		}
		if(res < 0){
			printf("Contact not found\n");
			return;
		}
	}
	printf("\nOld Contact:\n");
	printf("%s\t%s\t%s\n",
			addressBook->contacts[res].name,
			addressBook->contacts[res].email,
			addressBook->contacts[res].phone);

	printf("\n1.Name\n2.Mail\n3.Phone\n4.All\n");
	printf("Enter choice: ");
	scanf("%d", &ch);
	switch(ch){
		case 1:
			{
				len = 0;
				while(1){
					printf("Enter new name: ");
					scanf(" %[^\n]", name);
					if(!valid_name(name)){
						//strcpy(addressBook->contacts[res].name, name);
						len++;
						if(len==3){
							printf("Too many invalid attempts.try again later\n");
							return;
						}
						printf("Invalid name. Attempts left: %d\n", 3-len);
					}
					else{
						strcpy(addressBook->contacts[res].name, name);
						break;
					}
				}
				break;
			}
		case 2:
			{	
lam:
				len = 0;
				while(1){
					printf("Enter new mail: ");
					scanf(" %[^\n]", mail);
					if(!valid_mail(mail)){
						//strcpy(addressBook->contacts[res].email, mail);
						//break;
						len++;
						if(len==3){
							printf("Too many invalid attempts.try again later\n");
							return;
						}
						printf("Invalid name. Attempts left: %d\n", 3-len);
					}
					else if(duplicatemail(addressBook,mail,res)){
						printf("Given mail already exists\n");
					}
					else{
						strcpy(addressBook->contacts[res].email,mail);
						break;
					}
				}
				break;
			}
		case 3:
			{
lam1:
				len = 0;
				while(1){
					printf("Enter new phone: ");
					scanf(" %[^\n]", phone);
					if(!valid_phone(phone)){
						//strcpy(addressBook->contacts[res].phone, phone);
						//break;
						len++;
						if(len==3){
							printf("Too many invalid attempts.try again later\n");
							return;
						}
						printf("Invalid name. Attempts left: %d\n", 3-len);
					}
					else if(duplicatephone(addressBook,phone,res)){
						printf("Given mail already exists\n");
					}
					else{	
						strcpy(addressBook->contacts[res].phone,phone);
						return;
					}
				}
				break;
			}
		case 4:
			{
				len = 0;
				while(len < 3){
					printf("Enter name: ");
					scanf(" %[^\n]", name);
					if(valid_name(name)){
						strcpy(addressBook->contacts[res].name, name);
						break;
					}
					len++;
				}
				goto lam;
				goto lam1;
			}

		default:
			{
				printf("Invalid choice\n");
				return;
			}
	}
	printf("\nUpdated Contact:\n");
	printf("\n%-20s %-30s %-15s\n", "Name", "Mail_Id", "Phone_no");
	printf("---------------------------------------------------------------------\n");
	printf("%-20s",addressBook->contacts[res].name);
	printf("%-30s",addressBook->contacts[res].email);
	printf("%-15s\n",addressBook->contacts[res].phone);
}
void deleteContact(AddressBook *addressBook)
{

	if(addressBook->contactCount == 0){
		printf("Contact is empty\n");
		return;
	}

	char name[50], mail[50], phone[20];
	int c,ch,res;
	printf("Enter a name to delete: ");
	scanf(" %[^\n]", name);
	res = search_name(name, addressBook);
	if(res== -1){
		printf("Contact not found\n");
		return;
	}
	if(res==-2){
		printf("Multiple contacts found. Refine search:\n");
		printf("1.Email\n2.Phone\nEnter choice: ");
		scanf("%d", &c);
		if(c == 1){
			printf("Enter email: ");
			scanf(" %[^\n]", mail);
			res = search_mail(mail, addressBook);
		}
		else if(c == 2){
			printf("Enter phone: ");
			scanf(" %[^\n]", phone);
			res = search_phone(phone, addressBook);
		}
		else{
			printf("Invalid choice\n");
			return;
		}
		if(res < 0){
			printf("Contact not found\n");
			return;
		}
	}
	printf("\nOld Contact Details:\n");
	printf("Name  : %s\n", addressBook->contacts[res].name);
	printf("Email : %s\n", addressBook->contacts[res].email);
	printf("Phone : %s\n", addressBook->contacts[res].phone);
	char conf;
	printf("Confirm to delete(y or n): ");
	scanf(" %c",&conf);
	if(conf!='y'&&conf!='Y'){
		printf("Delete cancelled\n");
		return;
	}
	for(int i=res;i<addressBook->contactCount-1;i++){
		addressBook->contacts[i]=addressBook->contacts[i+1];
	}
	addressBook->contactCount--;
	printf("Contact deleted\n");
}
