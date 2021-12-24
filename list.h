typedef struct node NodeType;
struct node
{
    int data;
    NodeType *next;
};
typedef struct
{
    int length;
    NodeType *head;
} List;

void init(List *L);
void add(List *L, int c);
void print(NodeType *head);
int length(List L);
int check(List L, int item);