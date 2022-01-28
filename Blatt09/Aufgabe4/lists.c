# include "lists.h"

extern list *createList( )  {
    list *newList = (list *)malloc(sizeof(list));
    newList->head.next = &newList->tail;
    newList->head.previous = &newList->head;
    newList->tail.next = &newList->tail;
    newList->tail.previous = &newList->head;
    newList->current = &newList->head;
    return newList;
}

extern void insertElement(list *target, void *data)  {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->element = data; 
    newNode->next = target->current->next;
    newNode->previous = target->current;
    node *previous = target->current;
    previous->next  = newNode;
    target->current = newNode;
    newNode->next->previous = newNode;
}  

extern node *getFirstNode(list *source)  {
    return source->head.next;
}

extern node *traverse(node *position)  {
    return position->next;
}

extern node *getNode(list *source, int index)  {
    int position = 0;  node *current;
    for ( current = getFirstNode(source);  position++ < index; 
          current = traverse(current) );
    return current;
}
