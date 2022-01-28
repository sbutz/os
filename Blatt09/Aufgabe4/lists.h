# ifndef __LISTS_H_
# include <stdlib.h>

struct link {
    void *element;
    struct link *next;
    struct link *previous;
};

typedef struct link node;

struct nodes {
    int size;
    node head;
    node tail;
    node *current;
};

typedef struct nodes list; 

extern list *createList(void);
extern void insertElement(list *, void *);
extern node *getFirstNode(list *);
extern node *traverse(node *);
extern node *getNode(list *, int);

# define __LISTS_H_
# endif