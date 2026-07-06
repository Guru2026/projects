#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
	FILE *f;
	f=fopen("contact.csv","w");
	if(f==NULL){
		printf("Contact is empty\n");
	}
	fprintf(f,"#%d\n",addressBook->contactCount);
	for(int i=0;i<addressBook->contactCount;i++){
		fprintf(f,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].email,addressBook->contacts[i].phone);
	}
	fclose(f);  
}

void loadContactsFromFile(AddressBook *addressBook) {
	FILE *f;
	f=fopen("contact.csv","r");
	if(f==NULL){
		printf("Contact is empty\n"); 
	}   
	if(fscanf(f,"#%d\n",&addressBook->contactCount)!=1){
		addressBook->contactCount=0;
	}
	for(int i=0;i<addressBook->contactCount;i++){
		fscanf(f,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].email,addressBook->contacts[i].phone);
	}
	fclose(f);
}

