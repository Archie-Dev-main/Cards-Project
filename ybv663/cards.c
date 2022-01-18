#include<stdio.h>
#include<stdlib.h>

#include"cards.h"

/*
This function:
    Dynamically allocates a new Card struct object, assigns an action using the enum based on the probabilities in the description, and returns a pointer to that new Card.
*/
Card* createCard() {
    Card* head = (Card*)malloc(sizeof(Card));
    int random;
    random = rand() % 9 + 1;

    if (random <= 4) {
        head->type = ATTACK;
        head->value = rand() % 4 + 1;
    }
    else if (random > 4 && random <= 9) {
        head->type = DEFEND;
        head->value = rand() % 5 + 3;
    }
    else {
        head->type = RUN;
        head->value = rand() % 7 + 1;
    }
    head->next = NULL;
    return head;
}

/*
This function:
    Removes the first Card in the linked list, deallocates it, and returns the new head of the linked list.
*/
Card* removeCard(Card *head) {
    if(head == NULL)
      return head;
    
    Card* tmp;
    tmp = head->next;
    free(head);
    return tmp;
}

/*
This function:
    Adds a new Card to the linked list in descending order of values and returns the head.
*/
Card* addCard(Card *head, Card *c) {
    Card* t = head;
    int i;

    if(head == NULL){
        return c;
    }
    if (c->value > t->value) {
        c->next =t;
        return c;
    }
    else{
        while((t->next != NULL) && (t->next->value > c->value)) {
            t = t->next;
        }
        c->next = t->next;
        t->next = c;
    }
    t->next = c;
    return head;
}

/*
This funciton:
    Returns the length of the linked list by traversing it.
*/
int getLength(Card *head) {
    Card* t = head;
    int count = 0;
    while (t != NULL)
    {
        count++;
        t = t->next;
    }
    return count;
}

/*
This function:
    Prints out a single card’s action abbreviation and value.
*/
void printCard(Card *head) {
    if (head->type == ATTACK) {
        printf("A%d ", head->value);
    }
    else if (head->type == DEFEND) {
        printf("D%d ", head->value);
    }
    else {
        printf("R%d ", head->value);
    }
}
/*
This function:
    Traverses the linked list and prints out each card by internally calling the printCard() function.
*/
void printCards(Card *head) {
    Card* t = head;
    while (t != NULL)
    {
        printCard(t);
        t = t->next;
    }
}
/*
This funciton:
    Builds a new linked list based on the number of items passed into this function and returns the head of the linked list. This function internally uses calls to the createCard() and addCard() functions.
*/
Card* buildCards(int n) {
    Card* head = NULL;
    for (int i = 0; i < n; ++i) {
        head = addCard(head, createCard());
    }
    return head;
}
/*
This function:
    Deallocates the entire linked list without any memory leaks.
*/
}
Card* destroyCards(Card *head) {
    Card* t;
    if(head == NULL){
        return NULL;
    }
    t = head->next;
    free(head);
    return destroyCards(t);
}