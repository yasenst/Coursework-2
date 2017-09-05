#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Gallery {
    char id[10];
    char author[50];
    char painting[50];
    double price;
    int year;
};

struct Node {
    struct Gallery info;
    struct Node* next;
};
typedef struct Node Node;

int Menu(void);
void Load(Node** head);
Node* Create_Node(Node** head);
void Add(Node** head);
void Delete(Node** head);
void Swap_Values(Node** a, Node** b);
void Sort_by_Price(Node* head);
void Sort_by_Name(Node* head);
void Show(Node* head);
void Update(Node* head);
void Save(Node* head);
void FreeList(Node*head);

int main()
{
    Node* head = NULL;
    int choice;

    Load(&head);

    do {
        system("cls");
        choice = Menu();

        switch (choice) {
		case 1: Add(&head);
            break;
		case 2: Delete(&head);
            break;
		case 3: Sort_by_Price(head);
                Sort_by_Name(head);
                Show(head);
            break;
		case 4: Update(head);
            break;
		case 5: Save(head);
                FreeList(head);
                printf("Data saved successfully! Exiting...\n\n");
		default:
			exit(0);
		}

        printf("\nPress ENTER to continue...\n");
        while(getchar() != '\n');

    } while(choice != 5);

    return 0;
}

int Menu(void)
{
    int i;
    char str[10];

    printf("What would you like to do?\n");
	printf("\n\t1. Add new painting\n");
	printf("\n\t2. Delete painting by given ID\n");
	printf("\n\t3. Show all paintings by author and descending price\n");
	printf("\n\t4. Update price of a painting by given ID\n");
	printf("\n\t5. Save and exit\n\n");

	do {
        printf("Enter number of choice: ");
        gets(str);
        i = atoi(str);
        printf("\n");
	} while(i<1 || i>5);

	return i;
}

// Reads the data already stored in data.bin and puts it in a linked list
void Load(Node** head)
{
    FILE* fp;
    Node* temp;

    if((fp = fopen("data.bin", "rb")) == NULL) {
        printf("No data to be loaded\n");
        return;
    }

    while(1) {
        temp = (Node*) malloc(sizeof(Node));
        if(fread(temp,sizeof(Node), 1, fp) != 1) break;
        temp->next = *head;
        *head = temp;
        }

    fclose(fp);
}

// allocates memory for a new node, asks user to input need information
Node* Create_Node(Node **head)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    Node* temp;

    int flag;

    do {
        flag = 0;
        temp = *head;
        printf("ID: ");
        fgets(newNode->info.id,10,stdin);
        while(temp != NULL) {
            if(strcmp(newNode->info.id, temp->info.id) == 0) {
                printf("Painting with this ID already exists.\n");
                flag = 1;
                break;
            }
            temp = temp->next;
        }

    }while(flag != 0);

    printf("Author: ");
    fgets(newNode->info.author,50,stdin);
    printf("Painting: ");
    fgets(newNode->info.painting,50,stdin);
    printf("Price: ");
    scanf("%lf", &newNode->info.price);
    getchar();
    printf("Year: ");
    scanf("%d", &newNode->info.year);
    getchar();

    newNode->next = NULL;

    return newNode;
}

// calls create_node function and puts the newly created node at the front of the linked list
void Add(Node** head)
{
    Node* newNode = Create_Node(head);
    newNode->next = *head;
    *head = newNode;
}

// deletes a node by give id from the user
void Delete(Node** head)
{
    Node *curr, *prev;
    curr = *head;
    prev = NULL;
    char id[10];
    printf("Enter id: ");
    fgets(id,10,stdin);

    if(strcmp((*head)->info.id,id) == 0) { // if first node has to be deleted
        *head = (*head)->next;
        free(curr);
        return;
    }


    while(strcmp(curr->info.id, id) != 0) {
        prev = curr;
        curr = curr->next;
    if(curr == NULL)
        break;
    }


    if(curr == NULL) {
        printf("ID not found\n");
        return;
    }

    prev->next = curr->next;
    free(curr);
}

// swaps values of two nodes
void Swap_Values(Node** a, Node** b)
{
    Node* temp = (Node*) malloc(sizeof(Node));

    strcpy(temp->info.id,(*a)->info.id);
    strcpy(temp->info.author,(*a)->info.author);
    strcpy(temp->info.painting,(*a)->info.painting);
    temp->info.price = (*a)->info.price;
    temp->info.year = (*a)->info.year;

    strcpy((*a)->info.id,(*b)->info.id);
    strcpy((*a)->info.author,(*b)->info.author);
    strcpy((*a)->info.painting,(*b)->info.painting);
    (*a)->info.price = (*b)->info.price;
    (*a)->info.year = (*b)->info.year;

    strcpy((*b)->info.id,temp->info.id);
    strcpy((*b)->info.author,temp->info.author);
    strcpy((*b)->info.painting,temp->info.painting);
    (*b)->info.price = temp->info.price;
    (*b)->info.year = temp->info.year;

    free(temp);
}

// sort by price using bubble sort
void Sort_by_Price(Node* head)
{
    if(head == NULL) {
        printf("There are no paintings in the gallery\n");
        return;
    }
    Node* temp=head;
    int flag;

    while(1) {
        flag = 0;
        temp = head;

        while(temp->next != NULL) {
            if(temp->info.price < temp->next->info.price) {
                Swap_Values(&temp, &temp->next);
                flag = 1;
            }
            temp=temp->next;
        }

        if(flag == 0)
            break;
    }
}

//sort by name using bubble sort
void Sort_by_Name(Node* head)
{
    if(head == NULL) {
        printf("There are no paintings in the gallery\n");
        return;
    }
    Node* temp=head;
    int flag;

    while(1) {
        flag = 0;
        temp = head;

        while(temp->next != NULL) {
            if(strcmp(temp->info.author,temp->next->info.author) > 0) {
                Swap_Values(&temp, &temp->next);
                flag = 1;
            }
            temp=temp->next;
        }

        if(flag == 0)
            break;
    }
}

//displays the list on the screen
void Show(Node* head)
{
    while(head != NULL) {
        printf("ID: %s", head->info.id);
        printf("Author: %s", head->info.author);
        printf("Painting: %s", head->info.painting);
        printf("Price: %.2f $\n", head->info.price);
        printf("Year: %d\n", head->info.year);
        printf("\n");
        head=head->next;
    }
    printf("\n");
}

//changes price of a picture by id given by the user
void Update(Node* head)
{
    char str[10];
    printf("Enter id: ");
    fgets(str,10,stdin);
    while(strcmp(head->info.id,str) != 0 && (head != NULL)) {
        head=head->next;
    }

    if(head == NULL) {
        printf("No such id\n");
        return;
    }

    printf("Enter new price: ");
    scanf("%lf",&head->info.price);
    getchar();
}

//writes the list to file data.bin
void Save(Node* head)
{
    FILE* fp;

    if((fp = fopen("data.bin", "wb")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    while(head != NULL) {
        fwrite(head, sizeof(struct Node), 1, fp);
        head=head->next;
    }

    fclose(fp);
}

//frees memory at the end of execution
void FreeList(Node*head)
{
    Node* curr = head;
    while(head != NULL) {
        head=head->next;
        free(curr);
        curr=head;
    }
}


