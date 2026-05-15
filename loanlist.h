#ifndef LOANLIST_H
#define LOANLIST_H
#include "loan.h"
#include "transaction.h"
struct Node {
    loan data;
    Node* next;
    Node* previous;
};

struct List {
    Node* head;
    Node* tail;
    int size;
};
struct rNode {
    rloan data;
    rNode* next;
    rNode* previous;
};
struct rList {
    rNode* head;
    rNode* tail;
    int size;
};
struct node {
    loan data;
    node* next;
};

struct lista {
    node* head;
    int size;
};

struct tran{
    transaction t;
    QString username;
};

struct NODE {
    tran data;
    NODE* next;
};

struct LIST {
    NODE* head;
    int size;
};

#endif

