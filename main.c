#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 31

typedef struct p
{
    char *fileName;
    int a;
    int b;
} Parameters;

typedef struct node
{
    char val[MAX_STRING_SIZE];
    struct node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
} Queue;

void error(char *e);
Parameters readInput(int argc, char *argv[]);
Queue *createQueue();
void buildQueue(char *filename, Queue *q);
void enQueue(Queue *q, char *string);
char *deQueue(Queue *q);
bool isEmpty(Queue *q);
void elab(char *s, int a, int b);
void printQueue(Queue *q);
void printQueueHead(Queue *q, int a, int b);

int main(int argc, char *argv[])
{
    printf("=============A=============\n");
    Parameters p = readInput(argc, argv);
    printf("=============B=============\n");
    Queue *q = createQueue();
    buildQueue(p.fileName, q);
    // printQueue(q);
    printf("=============C=============\n");
    printQueueHead(q, p.a, p.b);
    printf("=============D=============\n");
}

void error(char *e)
{
    if (!e)
        return;

    fprintf(stderr, "[ERROR]: %s\n", e);
    exit(1);
}

Parameters readInput(int argc, char *argv[])
{
    if (argc != 4)
        error("Numero di parametri errati");

    char *fileName = strdup(argv[1]);

    if (fileName && strcmp(fileName + (strlen(fileName) - 4), ".txt"))
        error("Estensione del file non valida");

    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    if (a && b && a > b)
        error("il primo parametro inserito è maggiore del secondo parametro inserito");

    Parameters p = {fileName, a, b};

    return p;
}

bool isEmpty(Queue *q)
{
    return (q->head == NULL);
}

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
        error("Allocazione code non avvenuta correttamente!");

    q->head = q->tail = NULL;
    return q;
}

void enQueue(Queue *q, char *s)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        error("Problema nell'allocazione del nodo");

    strncpy(newNode->val, s, MAX_STRING_SIZE - 1);

    newNode->val[MAX_STRING_SIZE - 1] = '\0';
    newNode->next = NULL;

    if (q->head == NULL)
    {
        q->head = q->tail = newNode;
        return;
    }

    q->tail->next = newNode;
    q->tail = newNode;
}

char *deQueue(Queue *q)
{

    if (isEmpty(q))
        error("Coda vuota!");

    Node *to_delete = q->head;
    q->head = q->head->next;

    char *s = malloc(MAX_STRING_SIZE);
    if (s == NULL)
        error("Problema di allocazione stringa");

    strncpy(s, to_delete->val, MAX_STRING_SIZE - 1);
    s[MAX_STRING_SIZE - 1] = '\0';

    if (q->head == NULL)
        // Coda vuota
        q->tail = NULL;

    free(to_delete);

    return s;
}

void buildQueue(char *fileName, Queue *q)
{
    FILE *f = fopen(fileName, "r");

    if (!f)
        error("Errore nell'apertura del file");

    char line[MAX_STRING_SIZE];

    while (fgets(line, MAX_STRING_SIZE, f))
    {
        size_t len = strlen(line);
        line[len - 1] = '\0';
        enQueue(q, line);
    }

    printf("Building terminata\n");
}

void elab(char *s, int a, int b)
{
    // Nell'intervallo tra a e b dobbiamo sostituire i caratteri in c
    // consideriamo che a è minore di b per requisito
    while (a <= b)
    {
        s[a++] = 0;
    }

    printf("elab terminato!\n");
}

void printQueue(Queue *q)
{
    Node *to_print = q->head;
    printf("Coda: ");

    while (to_print)
    {
        if (to_print->next == NULL)
        {
            printf("%s\n", to_print->val);
            return;
        }

        printf("%s--->", to_print->val);
        to_print = to_print->next;
    }
}

void printQueueHead(Queue *q, int a, int b)
{
    while (!isEmpty(q))
    {
        char *string = deQueue(q);
        elab(string, a, b);
        printf("Stringa printata: %s\n", string);
        free(string);
    }
}