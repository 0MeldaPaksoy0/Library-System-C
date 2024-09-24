#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  typedef struct{
  
  int C_ID;
   char name[25];
   char surname[25];
   int age;
   float wallet; } Customer;



  typedef struct {
  
  int B_ID;
   char name[100];
   char author[100];
   int age_limit;
   float price_per_week;
   int rented; } Book;


  typedef struct {
  
  int R_ID;
   int C_ID;
   int B_ID;
   char rented_date[15];
   int week; } Rented;

 
void createNewCustomer ();
void depositMoney ();
void addNewBook ();

 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////main
  int main () {
  
int choice;
  
  do{
	  printf ("\nMenu:\n");
	  printf ("1. Create New Customer\n");
	  printf ("2. Deposit Money to the Customer\n");
	  printf ("3. Add New Book\n");
	  printf ("4. Rent A Book\n");
	  printf ("5. Delivery A Book\n");
	  printf ("6. Burn Book\n");
	  printf ("7. Update Customer Information\n");
	  printf ("8. Update Book Information\n");
	  printf ("9. List of Customers Who Rent a Book\n");
	  printf ("10. List of Customers\n");
	  printf ("11. List of Books\n");
	  printf ("0. Exit\n");
	  printf ("Enter your choice: ");
	  scanf ("%d", &choice);
	  
 
switch (choice)	{
		
case 1:
		  
    printf ("Create New Customer\n");
     createNewCustomer ();
    break;
		
case 2:
		  
    printf ("Deposit Money to the Customer\n");
    depositMoney ();
    break;
		
case 3:
		  
    printf ("Add New Book\n");
    addNewBook ();
    break;
		
case 4:
		  
    printf ("Rent A Book\n");
    rentABook ();
    break;
		
case 5:
		  
    printf ("Delivery A Book\n");
    deliveryABook ();
    break;
		
case 6:
		  
    printf ("Burn Book\n");
    burnBook ();
    break;
		
case 7:
		  
    printf ("Update Customer Information\n");
			 updateCustomerInformation();
			break;
		
case 8:
		  
    printf ("Update Book Information\n");
			 updateBookInformation();
			break;
		
case 9:
		  
    printf ("List of Customers Who Rent a Book\n");
			 listOfCustomersWhoRentABook();
			break;
		
case 10:
		  
    printf ("List of Customers\n");
			 listOfCustomers();
			break;
		
case 11:
		  
    printf ("List of Books\n");
			 listOfBooks();
			break;
		
case 0:
		  
    printf ("Exiting...\n");
		  
break;
		
default:
		  
printf ("Invalid choice. Please enter a number between 0 and 11.\n");
		
}
	
}

  while (choice != 0);
return 0;

}


 
 
///////////////////////////////////////////////////////////////////////////////////createNewCustomer
  
void createNewCustomer () {
  
FILE * file = fopen ("customers.txt", "a+");	
  
if (file == NULL)	{
	  
printf ("Error opening file!\n");
exit (1);
	
}
  
  int maxC_ID = 0;
  
Customer temp;
  
while (fscanf
		  (file, "%d %s %s %d %f", &temp.C_ID, temp.name, temp.surname,
		   &temp.age, &temp.wallet) == 5){
	  
if (temp.C_ID > maxC_ID) {maxC_ID = temp.C_ID;}
	
}
  
maxC_ID++;					
  
	
	Customer newCustomer;
  
  printf ("Enter name: ");
  scanf ("%s", newCustomer.name);
  printf ("Enter surname: ");
  scanf ("%s", newCustomer.surname);
  printf ("Enter age: ");
  scanf ("%d", &newCustomer.age);
  printf ("Enter initial wallet amount: ");
  scanf ("%f", &newCustomer.wallet);
  
 
	rewind (file);				
  while (fscanf
		 (file, "%d %s %s %d %f", &temp.C_ID, temp.name, temp.surname,
		  &temp.age, &temp.wallet) == 5) {
	  
if (strcmp (temp.name, newCustomer.name) == 0
		   && strcmp (temp.surname, newCustomer.surname) == 0) {
		  
printf ("Customer with the same name and surname already exists!\n");
fclose (file);

return;

}
	
}
  
 
	fprintf (file, "%d %s %s %d %.2f\n", maxC_ID, newCustomer.name,
			 newCustomer.surname, newCustomer.age, newCustomer.wallet);
  
fflush (file);
  
printf ("New customer added successfully \n");
  
fclose (file);

}


 
 
////////////////////////////////////////////////////////////////////////////////depositMoney
  

void depositMoney() {
    int customerId;
    float amount;

    printf("Enter Customer ID: ");
    scanf("%d", &customerId);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    FILE *file = fopen("customers.txt", "r+"); 
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    Customer temp;
    int found = 0;
    long pos;
    FILE *tempFile = fopen("temp_customers.txt", "w"); 
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(file);
        exit(1);
    }

    while (fscanf(file, "%d %s %s %d %f", &temp.C_ID, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
        if (temp.C_ID == customerId) {
            temp.wallet += amount;
            found = 1;
        }
        fprintf(tempFile, "%d %s %s %d %.2f\n", temp.C_ID, temp.name, temp.surname, temp.age, temp.wallet);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove("customers.txt") != 0) {
            printf("Error deleting original file!\n");
            exit(1);
        }
        if (rename("temp_customers.txt", "customers.txt") != 0) {
            printf("Error renaming temporary file!\n");
            exit(1);
        }
        printf("Amount deposited successfully. New balance: %.2f\n", temp.wallet);
    } else {
        printf("Customer with ID %d not found.\n", customerId);
        remove("temp_customers.txt"); 
    }
}

 
 
///////////////////////////////////////////////////////////////////////////////////addNewBook
  
 
void addNewBook () {
  
FILE * file = fopen ("books.txt", "a+");	// Open file for appending and reading
  
if (file == NULL) {
	  printf ("Error opening file!\n");
	  exit (1);
}
  
 
  int maxB_ID = 0;
  
Book temp;
  
while (fscanf(file, "%d %s %s %d %f %d", &temp.B_ID, temp.name, temp.author,&temp.age_limit, &temp.price_per_week, &temp.rented) == 6) {
	  
if (temp.B_ID > maxB_ID) { maxB_ID = temp.B_ID; }
	
}
  
maxB_ID++;					
  
	
	Book newBook;
  
printf ("Enter book name: ");
  
scanf (" %[^\n]%*c", newBook.name);
  
printf ("Enter author name: ");
  
scanf (" %[^\n]%*c", newBook.author);
  
printf ("Enter age limit: ");
  
scanf ("%d", &newBook.age_limit);
  
printf ("Enter price per week: ");
  
scanf ("%f", &newBook.price_per_week);
  
newBook.rented = 0;
  
 
	
	rewind (file);			
  while (fscanf
		 (file, "%d %s %s %d %f %d", &temp.B_ID, temp.name, temp.author,
		  &temp.age_limit, &temp.price_per_week, &temp.rented) == 6) {
	  
if (strcmp (temp.name, newBook.name) == 0 && strcmp (temp.author, newBook.author) == 0) {
		  
		  printf ("Book with the same name and author already exists!\n");
		  fclose (file);
	return;
	}

}
  
 
	
	fprintf (file, "%d %s %s %d %.2f %d\n", maxB_ID, newBook.name,
			 newBook.author, newBook.age_limit, newBook.price_per_week,
			 newBook.rented);
  
fflush (file);				
  printf ("New book added successfully\n");
  
 
fclose (file);

}

/////////////////////////////////////////////////////////////////////////////////// rentABook
  

void rentABook() {
    int customerId, bookId, rentWeeks;
    char rentedDate[15];

    printf("Enter Customer ID: ");
    scanf("%d", &customerId);

    printf("Enter Book ID: ");
    scanf("%d", &bookId);

    printf("Enter number of weeks to rent: ");
    scanf("%d", &rentWeeks);

    printf("Enter rental date (dd-mm-yyyy): ");
    scanf("%s", rentedDate);

    FILE *customerFile = fopen("customers.txt", "r+");
    if (customerFile == NULL) {
        printf("Error opening customers file!\n");
        exit(1);
    }

    Customer customer;
    int foundCustomer = 0;
    long customerPos;

    while ((customerPos = ftell(customerFile)) != -1 && fscanf(customerFile, "%d %s %s %d %f", &customer.C_ID,
           customer.name, customer.surname, &customer.age, &customer.wallet) == 5) {
        if (customer.C_ID == customerId) {
            foundCustomer = 1;
            break;
        }
    }

    if (!foundCustomer) {
        printf("Customer with ID %d not found.\n", customerId);
        fclose(customerFile);
        return;
    }

    // Open book file
    FILE *bookFile = fopen("books.txt", "r+");
    if (bookFile == NULL) {
        printf("Error opening books file!\n");
        fclose(customerFile);
        exit(1);
    }

    Book book;
    int foundBook = 0;
    long bookPos;

    while ((bookPos = ftell(bookFile)) != -1 && fscanf(bookFile, "%d %s %s %d %f %d", &book.B_ID, book.name,
           book.author, &book.age_limit, &book.price_per_week, &book.rented) == 6) {
        if (book.B_ID == bookId) {
            foundBook = 1;
            break;
        }
    }

    if (!foundBook) {
        printf("Book with ID %d not found.\n", bookId);
        fclose(customerFile);
        fclose(bookFile);
        return;
    }

    if (book.rented) {
        printf("Book is already rented.\n");
        fclose(customerFile);
        fclose(bookFile);
        return;
    }

    float totalCost = rentWeeks * book.price_per_week;
    if (customer.wallet < totalCost) {
        printf("Insufficient balance in customer's wallet.\n");
        fclose(customerFile);
        fclose(bookFile);
        return;
    }

    if (customer.age < book.age_limit) {
        printf("Customer does not meet the age requirement to rent this book.\n");
        fclose(customerFile);
        fclose(bookFile);
        return;
    }

    Book tempBook;
    book.rented = 1;

    FILE *tempBookFile = fopen("temp_books.txt", "w");
    if (tempBookFile == NULL) {
        printf("Error creating temporary file!\n");
        exit(1);
    }

    rewind(bookFile);
    while (fscanf(bookFile, "%d %s %s %d %f %d", &tempBook.B_ID, tempBook.name,
                  tempBook.author, &tempBook.age_limit, &tempBook.price_per_week,
                  &tempBook.rented) == 6) {
        if (tempBook.B_ID == bookId) {
            fprintf(tempBookFile, "%d %s %s %d %.2f %d\n", book.B_ID, book.name,
                    book.author, book.age_limit, book.price_per_week, book.rented);
        } else {
            fprintf(tempBookFile, "%d %s %s %d %.2f %d\n", tempBook.B_ID, tempBook.name,
                    tempBook.author, tempBook.age_limit, tempBook.price_per_week,
                    tempBook.rented);
        }
    }

    fclose(bookFile);
    fclose(tempBookFile);

    remove("books.txt");
    rename("temp_books.txt", "books.txt");

    Customer tempCustomer;
    customer.wallet -= totalCost;

    FILE *tempCustomerFile = fopen("temp_customers.txt", "w");
    if (tempCustomerFile == NULL) {
        printf("Error creating temporary file!\n");
        exit(1);
    }

    rewind(customerFile);
    while (fscanf(customerFile, "%d %s %s %d %f", &tempCustomer.C_ID, tempCustomer.name,
                  tempCustomer.surname, &tempCustomer.age, &tempCustomer.wallet) == 5) {
        if (tempCustomer.C_ID == customerId) {
            fprintf(tempCustomerFile, "%d %s %s %d %.2f\n", customer.C_ID, customer.name,
                    customer.surname, customer.age, customer.wallet);
        } else {
            fprintf(tempCustomerFile, "%d %s %s %d %.2f\n", tempCustomer.C_ID, tempCustomer.name,
                    tempCustomer.surname, tempCustomer.age, tempCustomer.wallet);
        }
    }

    fclose(customerFile);
    fclose(tempCustomerFile);

    remove("customers.txt");
    rename("temp_customers.txt", "customers.txt");

    FILE *rentedFile = fopen("rented.txt", "a");
    if (rentedFile == NULL) {
        printf("Error opening rented file!\n");
        exit(1);
    }

    int maxR_ID = 0;
    Rented tempRented;

    rewind(rentedFile);  
    while (fscanf(rentedFile, "%d %d %d %s %d", &tempRented.R_ID, &tempRented.C_ID,
                  &tempRented.B_ID, tempRented.rented_date, &tempRented.week) == 5) {
        if (tempRented.R_ID > maxR_ID) {
            maxR_ID = tempRented.R_ID;
        }
    }

    int newR_ID = maxR_ID + 1;

    fprintf(rentedFile, "%d %d %d %s %d\n", newR_ID, customerId, bookId,
            rentedDate, rentWeeks);
    fclose(rentedFile);

    printf("Book rented successfully \n");
}




//////////////////////////////////////////////////////////////////////////////////deliveryABook
  

void deliveryABook() {
    int R_ID, remainingWeeks;
    printf("Enter Rent ID (R_ID): ");
    scanf("%d", &R_ID);
    printf("Enter remaining weeks: ");
    scanf("%d", &remainingWeeks);
    
    FILE *rentedFile = fopen("rented.txt", "r+");
    if (rentedFile == NULL) {
        printf("Error opening rented file!\n");
        exit(1);
    }
   
    FILE *tempRentedFile = fopen("temp_rented.txt", "w");
    if (tempRentedFile == NULL) {
        printf("Error opening temporary rented file!\n");
        fclose(rentedFile);
        exit(1);
    }

    Rented rented;
    int foundRented = 0;
    while (fscanf(rentedFile, "%d %d %d %s %d", &rented.R_ID, &rented.C_ID, &rented.B_ID, rented.rented_date, &rented.week) == 5) {
        if (rented.R_ID == R_ID) {
            foundRented = 1;
            continue; 
        }
        fprintf(tempRentedFile, "%d %d %d %s %d\n", rented.R_ID, rented.C_ID, rented.B_ID, rented.rented_date, rented.week);
    }
    fclose(rentedFile);
    fclose(tempRentedFile);

    if (remove("rented.txt") != 0) {
        printf("Error deleting rented file!\n");
        exit(1);
    }
    if (rename("temp_rented.txt", "rented.txt") != 0) {
        printf("Error renaming temporary rented file!\n");
        exit(1);
    }

    if (foundRented) {
        FILE *booksFile = fopen("books.txt", "r+");
        if (booksFile == NULL) {
            printf("Error opening books file!\n");
            exit(1);
        }

        FILE *tempBooksFile = fopen("temp_books.txt", "w");
        if (tempBooksFile == NULL) {
            printf("Error opening temporary books file!\n");
            fclose(booksFile);
            exit(1);
        }

        int B_ID, field1, field2;
        char str1[50], str2[50];
        float price_per_week;
        int availability;
        while (fscanf(booksFile, "%d %s %s %d %f %d", &B_ID, str1, str2, &field1, &price_per_week, &availability) == 6) {
            if (B_ID == rented.B_ID)  fprintf(tempBooksFile, "%d %s %s %d %.2f 0\n", B_ID, str1, str2, field1, price_per_week);
             else fprintf(tempBooksFile, "%d %s %s %d %.2f %d\n", B_ID, str1, str2, field1, price_per_week, availability);
            
        }
        fclose(booksFile);
        fclose(tempBooksFile);

        if (remove("books.txt") != 0) {
            printf("Error deleting books file!\n");
            exit(1);
        }
        if (rename("temp_books.txt", "books.txt") != 0) {
            printf("Error renaming temporary books file!\n");
            exit(1);
        }

        float refundAmount = remainingWeeks * price_per_week;
        printf("Customer refunded %.2f TL for returning the book %d week(s) early.\n", refundAmount, remainingWeeks);


        FILE *customersFile = fopen("customers.txt", "r+");
        if (customersFile == NULL) {
            printf("Error opening customers file!\n");
            exit(1);
        }

        FILE *tempCustomersFile = fopen("temp_customers.txt", "w");
        if (tempCustomersFile == NULL) {
            printf("Error opening temporary customers file!\n");
            fclose(customersFile);
            exit(1);
        }

        Customer customer;
        while (fscanf(customersFile, "%d %s %s %d %f", &customer.C_ID, customer.name, customer.surname, &customer.age, &customer.wallet) == 5) {
            if (customer.C_ID == rented.C_ID) {
                customer.wallet += refundAmount;
            }
            fprintf(tempCustomersFile, "%d %s %s %d %.2f\n", customer.C_ID, customer.name, customer.surname, customer.age, customer.wallet);
        }
        fclose(customersFile);
        fclose(tempCustomersFile);

        if (remove("customers.txt") != 0) {
            printf("Error deleting customers file!\n");
            exit(1);
        }
        if (rename("temp_customers.txt", "customers.txt") != 0) {
            printf("Error renaming temporary customers file!\n");
            exit(1);
        }

    } else {
        printf("Rental record not found.\n");
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////burnBook

void burnBook() {
    int B_ID;
    printf("Enter Book ID to burn: ");
    scanf("%d", &B_ID);

    FILE *rentedFile = fopen("rented.txt", "r");
    if (rentedFile == NULL) {
        printf("Error opening rented file!\n");
        exit(1);
    }

    int rented = 0;

    int temp_R_ID, temp_C_ID, temp_B_ID, temp_weeks;
    char rented_date[15];
    while (fscanf(rentedFile, "%d %d %d %s %d\n", &temp_R_ID, &temp_C_ID, &temp_B_ID, rented_date, &temp_weeks) == 5) {
        if (temp_B_ID == B_ID) {
            rented = 1;
            break;
        }
    }

    fclose(rentedFile);

    if (rented) {
        printf("Book with ID %d is currently rented and cannot be burned.\n", B_ID);
        return;
    }


    FILE *bookFile = fopen("books.txt", "r");
    if (bookFile == NULL) {
        printf("Error opening books file!\n");
        exit(1);
    }

    Book book;
    FILE *tempBookFile = fopen("temp_books.txt", "w");
    if (tempBookFile == NULL) {
        printf("Error opening temporary books file!\n");
        fclose(bookFile);
        exit(1);
    }


    while (fscanf(bookFile, "%d %49s %49s %d %f %d\n", &book.B_ID, book.name, book.author, &book.age_limit, &book.price_per_week, &book.rented) == 6) {
        if (book.B_ID != B_ID) {
            fprintf(tempBookFile, "%d %s %s %d %.2f %d\n", book.B_ID, book.name, book.author, book.age_limit, book.price_per_week, book.rented);
        }
    }

    fclose(bookFile);
    fclose(tempBookFile);

    remove("books.txt");
    rename("temp_books.txt", "books.txt");
    printf("Book with ID %d burned successfully.\n", B_ID);
}

////////////////////////////////////////////////////////////////////////////////////////////// updateCustomerInformation



void updateCustomerInformation() {
    int C_ID;
    printf("Enter Customer ID to update: ");
    scanf("%d", &C_ID);

    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("Error opening customers file!\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        exit(1);
    }

    Customer customer;
    int found = 0;
    while (fscanf(file, "%d %24s %24s %d %f", &customer.C_ID, customer.name, customer.surname, &customer.age, &customer.wallet) == 5) {
        if (customer.C_ID == C_ID) {
            found = 1;

            char newName[25], newSurname[25];
            int newAge;
            printf("Enter new name: ");
            scanf("%s", newName);
            printf("Enter new surname: ");
            scanf("%s", newSurname);
            printf("Enter new age: ");
            scanf("%d", &newAge);

            // Update customer information
            strcpy(customer.name, newName);
            strcpy(customer.surname, newSurname);
            customer.age = newAge;
        }
        fprintf(tempFile, "%d %s %s %d %.2f\n", customer.C_ID, customer.name, customer.surname, customer.age, customer.wallet);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Customer with ID %d not found.\n", C_ID);
        remove("temp.txt");
        return;
    }

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    printf("Customer information updated successfully.\n");
}




/////////////////////////////////////////////////////////////////////////////////// updateBookInformation

void updateBookInformation() {
    int B_ID;
    printf("Enter Book ID to update: ");
    scanf("%d", &B_ID);

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening books file!\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        exit(1);
    }

    Book book;
    int found = 0;
    while (fscanf(file, "%d %99s %99s %d %f %d", &book.B_ID, book.name, book.author, &book.age_limit, &book.price_per_week, &book.rented) == 6) {
        if (book.B_ID == B_ID) {
            found = 1;

            char newName[100], newAuthor[100];
            int newAgeLimit;
            float newPricePerWeek;

            printf("Enter new name: ");
            scanf(" %[^\n]%*c", newName);
            printf("Enter new author: ");
            scanf(" %[^\n]%*c", newAuthor);
            printf("Enter new age limit: ");
            scanf("%d", &newAgeLimit);
            printf("Enter new price per week: ");
            scanf("%f", &newPricePerWeek);

            strcpy(book.name, newName);
            strcpy(book.author, newAuthor);
            book.age_limit = newAgeLimit;
            book.price_per_week = newPricePerWeek;
        }
        fprintf(tempFile, "%d %s %s %d %.2f %d\n", book.B_ID, book.name, book.author, book.age_limit, book.price_per_week, book.rented);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Book with ID %d not found.\n", B_ID);
        remove("temp.txt");
        return;
    }

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("Book information updated successfully.\n");
}




///////////////////////////////////////////////////////////////////////////////listCustomersWhoRentABook


void listOfCustomersWhoRentABook() {
    FILE *rentedFile = fopen("rented.txt", "r");
    if (rentedFile == NULL) {
        printf("Error opening rented file!\n");
        exit(1);
    }

    printf("\nList of Customers Who Rented a Book:\n");
    printf("Customer ID | Name       | Surname   | Age | Wallet\n");
    printf("-----------------------------------------------\n");


    int temp_R_ID, temp_C_ID, temp_B_ID, temp_weeks;
    char rented_date[15];
    while (fscanf(rentedFile, "%d %d %d %s %d\n", &temp_R_ID, &temp_C_ID, &temp_B_ID, rented_date, &temp_weeks) == 5) {
        FILE *customersFile = fopen("customers.txt", "r");
        if (customersFile == NULL) {
            printf("Error opening customers file!\n");
            fclose(rentedFile);
            exit(1);
        }


        Customer customer;
        int found = 0;
        while (fscanf(customersFile, "%d %24s %24s %d %f\n", &customer.C_ID, customer.name, customer.surname, &customer.age, &customer.wallet) == 5) {
            if (customer.C_ID == temp_C_ID) {
                printf("%-12d| %-10s | %-10s | %-3d | %.2f\n", customer.C_ID, customer.name, customer.surname, customer.age, customer.wallet);
                found = 1;
                break;
            }
        }
        fclose(customersFile);

        if (!found) {
            printf("Customer with ID %d not found.\n", temp_C_ID);
        }
    }

    fclose(rentedFile);
}


//////////////////////////////////////////////////////////////////////////////////////7  listOfCustomers

void listOfCustomers() {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("Error opening customers file!\n");
        return;
    }

    Customer customer;
    printf("\nList of Customers:\n");
    printf("C_ID | Name                 | Surname              | Age | Wallet\n");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%d %24s %24s %d %f", &customer.C_ID, customer.name, customer.surname, &customer.age, &customer.wallet) == 5) {
        printf("%-4d | %-20s | %-20s | %-3d | %.2f\n", customer.C_ID, customer.name, customer.surname, customer.age, customer.wallet);
    }

    fclose(file);
}



//////////////////////////////////////////////////////////////////////////listOfBooks

void listOfBooks() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening books file!\n");
        return;
    }

    Book book;
    char line[300];  
    int result;
    printf("\nList of Books:\n");
    printf("B_ID | Name                     | Author                   | Age Limit | Price per Week | Rented\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        
        result = sscanf(line, "%d %99s %99s %d %f %d",
                        &book.B_ID, book.name, book.author, &book.age_limit, &book.price_per_week, &book.rented);

        if (result == 6) {
            printf("%-4d | %-25s | %-25s | %-10d | %-14.2f | %d\n",
                   book.B_ID, book.name, book.author, book.age_limit, book.price_per_week, book.rented);
        } else {
            printf("Error parsing line: %s\n", line);
            printf("sscanf returned %d\n", result);
        }
    }

    fclose(file);
}
