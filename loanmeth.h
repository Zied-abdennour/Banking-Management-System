#ifndef LOANMETH_H
#define LOANMETH_H
#include <QtCore/QString>
#include "loanlist.h"
#include "customer.h"
#include <QLabel>
Node* createNode(loan value);
void destroyNode(Node* node);
bool isEmpty(const List& L);
bool isFull(const List& L);
int listSize(const List& L);
int addLoan(List* L, loan n);
QString removeAt(List* L, int pos);
loan getElement(const List& L, int pos);
List createloanlist();
void destroyList(List* L);
void inirloan(rloan& l);
int radd(rList* requestl, rloan n);
rNode* rcreateNode(rloan value);
int addl(lista* completed_loans, loan n);
node* createnode(loan value);
NODE* createNODE(tran value);
int ADD(LIST* t, transaction n ,QString username);
void declineReq(customer& c, QLabel *l);
rloan getReq(const customer& c);
void acceptReq(customer& c,QLabel *l);
bool hasReq(const customer& c);
void removeLoan(List& list, int index);
#endif
