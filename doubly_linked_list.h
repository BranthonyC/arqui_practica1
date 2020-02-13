struct node
{
    byte message_sprite[16];
    struct node *next;
    struct node *prev;
};
struct node *nodo = NULL;
struct node *first = NULL;
struct node *last = NULL;
struct node *current = NULL;
bool isEmpty()
{
    return first == NULL;
}

void insertLast(byte message_sprite[16])
{

    //create a link
    struct node *link = (struct node *)malloc(sizeof(struct node));
    link->message_sprite[0] = message_sprite[0];
    link->message_sprite[1] = message_sprite[1];
    link->message_sprite[2] = message_sprite[2];
    link->message_sprite[3] = message_sprite[3];
    link->message_sprite[4] = message_sprite[4];
    link->message_sprite[5] = message_sprite[5];
    link->message_sprite[6] = message_sprite[6];
    link->message_sprite[7] = message_sprite[7];
    link->message_sprite[8] = message_sprite[8];
    link->message_sprite[9] = message_sprite[9];
    link->message_sprite[10] = message_sprite[10];
    link->message_sprite[11] = message_sprite[11];
    link->message_sprite[12] = message_sprite[12];
    link->message_sprite[13] = message_sprite[13];
    link->message_sprite[14] = message_sprite[14];
    link->message_sprite[15] = message_sprite[15];

    if (isEmpty())
    {
        first = link;
        last = link;
        first->prev = last;
        last->next = first;
    }
    else
    {
        last->next = link;
        link->prev = last;
        last = link;
        last->next = first;
        first->prev = last;
    }
}