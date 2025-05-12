#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for book record

typedef struct {
    int bookID;
    char title[100];
    char author[100];
    struct Node* next;
} Book;

// Structure for linked list node

typedef struct Node {
    Book book;
    struct Node* next;
} Node;

Node* head = NULL;  // Global variable for the head of the linked list

// Function to create a new node
Node* createNode(Book book) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->book = book;
    newNode->next = NULL;
    return newNode;
}

// Function to add a book to the linked list
void addBook(Book book) {
    Node* newNode = createNode(book);
    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Book added successfully!\n");
}

// Function to remove a book from the linked list by book ID
void removeBook(int bookID) {
    if (head == NULL) {
        printf("No books found!\n");
        return;
    }
    if (head->book.bookID == bookID) {
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("Book removed successfully!\n");
        return;
    }
    Node* temp = head;
    while (temp->next != NULL && temp->next->book.bookID != bookID) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Book ID %d not found!\n", bookID);
        return;
    }
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
    printf("Book removed successfully!\n");
}

// Function to search for a book by title or author
void searchBook(const char* keyword) {
    Node* temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->book.title, keyword) == 0 || strcmp(temp->book.author, keyword) == 0) {
            printf("Book ID: %d\nTitle: %s\nAuthor: %s\n\n", temp->book.bookID, temp->book.title, temp->book.author);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found with the given keyword!\n");
    }
}

// Function to display the list of books
void displayBooks() {
    Node* temp = head;
    if (temp == NULL) {
        printf("No books found!\n");
        return;
    }
    printf("Book ID\tTitle\tAuthor\n");
    while (temp != NULL) {
        printf("%d\t%s\t%s\n", temp->book.bookID, temp->book.title, temp->book.author);
        temp = temp->next;
    }
}

// Main function
int main() {
    int choice, bookID;
    Book book;
    char keyword[100];

    do {
        printf("\n------ Library Management System ------\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Search Book\n");
        printf("4. Display Books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter book ID: ");
                scanf("%d", &book.bookID);
                printf("Enter book title: ");
                scanf(" %[^\n]s", book.title);
                printf("Enter book author: ");
                scanf(" %[^\n]s", book.author);
                addBook(book);
                break;
            case 2:
                printf("Enter book ID to remove: ");
                scanf("%d", &bookID);
                removeBook(bookID);
                break;
            case 3:
                printf("Enter a keyword to search: ");
                scanf(" %[^\n]s", keyword);
                searchBook(keyword);
                break;
            case 4:
                displayBooks();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    // Free memory
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
