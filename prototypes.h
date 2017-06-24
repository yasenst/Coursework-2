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
