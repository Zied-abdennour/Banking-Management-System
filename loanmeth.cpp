#include "loanmeth.h"
#include <iostream>
#include <QString>
#include <stdexcept>
#include <new>

using namespace std;

Node* createNode(loan value) {
    Node* node = new (nothrow) Node{ value, nullptr, nullptr };
    if (!node) {
        cerr << "\nMemoryallocation failed for node\n";
        exit(1);
    }
    return node;
}
void destroyNode(Node* node) {
    delete node;
}
bool isEmpty(const List& L) {
    return L.size == 0;
}
bool isFull(const List& L) {
    Node* test = new (nothrow) Node;
    if (!test) return true;
    delete test;
    return false;
}
int listSize(const List& L) {
    return L.size;
}
int addLoan(List* L, loan e) {
    if (!L) return 0;
    Node* n = createNode(e);
    if (!n) return 0;
    if (isEmpty(*L)) {
        L->head = n;
        L->tail = n;
    }
    else {
        L->tail->next = n;
        n->previous = L->tail;
        L->tail = n;
    }
    L->size++;
    return 1;
}
QString removeAt(List* L, int pos) {
    if (!L || isEmpty(*L)) {
        return "List is empty";
    }
    if (pos < 1 || pos > L->size) {
        return "Invalid position";
    }

    Node* current = nullptr;
    if (pos == 1) {
        current = L->head;
        L->head = current->next;

        if (L->head) {
            L->head->previous = nullptr;
        }
        else {
            L->tail = nullptr;
        }
    }
    else if (pos == L->size) {
        current = L->tail;
        L->tail = current->previous;

        if (L->tail) {
            L->tail->next = nullptr;
        }
        else {
            L->head = nullptr;
        }
    }

    else {
        if (pos < L->size / 2) {
            current = L->head;
            for (int i = 1; i < pos; i++)
                current = current->next;
        }
        else {
            current = L->tail;
            for (int i = L->size; i > pos; i--)
                current = current->previous;
        }

        current->previous->next = current->next;
        current->next->previous = current->previous;
    }

    destroyNode(current);
    L->size--;

    return "Loan removed successfully";
}
loan getElement(const List& L, int pos) {
    if (isEmpty(L)) {
        throw runtime_error("List is empty");
    }
    if (pos < 1 || pos > L.size) {
        throw runtime_error("Invalid position");
    }

    Node* current = L.head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    return current->data;
}
List createloanlist() {
    return List{ nullptr , nullptr , 0 };
}
void destroyList(List* L) {
    if (!L) return;
    Node* current = L->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        destroyNode(temp);
    }
    L->head = nullptr;
    L->size = 0;
}
void inirloan(rloan& l){
    l.LoanType="";
    l.PrincipalAmount=0;
    l.InterestRate=0;
    l.StartDate="";
    l.EndDate="";
    l.MonthlyPayment=0.0;
}
int radd(rList* requestl, rloan n){
    if (!requestl) return 0;
    rNode* t = rcreateNode(n);
    if (!t) return 0;
    if (requestl->size == 0) {
        requestl->head = t;
        requestl->tail = t;
    }
    else {
        requestl->tail->next = t;
        t->previous = requestl->tail;
        requestl->tail = t;
    }
    requestl->size++;
    return 1;
}
rNode* rcreateNode(rloan value) {
    rNode* node = new (nothrow) rNode{ value, nullptr, nullptr };
    if (!node) {
        cerr << "\nMemoryallocation failed for node\n";
        exit(1);
    }
    return node;
}
int addl(lista* completed_loans, loan n){
    if (!completed_loans) return 0;
    node* t = createnode(n);
    if (!t) return 0;
    if (completed_loans->size == 0) {
        completed_loans->head = t;
    }
    else {
        node* current = completed_loans->head;
        for (int i = 1; i < completed_loans->size; i++) {
            current = current->next;
        }
        current->next=t;
    }
    completed_loans->size++;
    return 1;
}
node* createnode(loan value) {
    node* nodE = new (nothrow) node{ value, nullptr };
    if (!nodE) {
        cerr << "\nMemoryallocation failed for node\n";
        exit(1);
    }
    return nodE;
}
int ADD(LIST* t, transaction n , QString username){
    if (!t) return 0;
    tran tr;
    tr.t=n;
    tr.username=username;
    NODE* tn = createNODE(tr);
    if (!tn) return 0;
    if (t->size == 0) {
        t->head = tn;
    }
    else {
        NODE* current = t->head;
        for (int i = 1; i < t->size; i++) {
            current = current->next;
        }
        current->next=tn;
    }
    t->size++;
    return 1;
}
NODE* createNODE(tran value) {
    NODE* nodE = new (nothrow) NODE{ value , nullptr };
    if (!nodE) {
        cerr << "\nMemoryallocation failed for node\n";
        exit(1);
    }
    return nodE;
}

bool hasReq(const customer& c) {
    return c.acc.requestl != nullptr;
}
rloan getReq(const customer& c) {
    if (c.acc.requestl != nullptr) {
        return (*c.acc.requestl);
    }
    rloan empty;
    inirloan(empty);
    return empty;
}
void acceptReq(customer& c, QLabel *l) {
    if (!hasReq(c)) {
        return;
    }
    rloan req =(*c.acc.requestl);
    loan newloan;
    newloan.LoanID = c.acc.AccountNumber+ "-L" +QString::number(c.acc.l.size);
    newloan.LoanType = req.LoanType;
    newloan.PrincipalAmount = req.PrincipalAmount;
    newloan.InterestRate = req.InterestRate;
    newloan.AmountPaid = 0.0;
    newloan.RemainingBalance = req.PrincipalAmount;
    newloan.StartDate = req.StartDate;
    newloan.EndDate = req.EndDate;
    newloan.LoanStatus = "Active";
    newloan.MonthlyPayment = req.MonthlyPayment;
    if (!addLoan(&(c.acc.l), newloan)){
        l->setText("Your Reached the Limit of Loans!");
    }
    else{
        l->setText("Your Request is accepted!");
        delete c.acc.requestl;
        c.acc.requestl = nullptr;
    }
}
void declineReq(customer& c,QLabel *l) {
    if (!hasReq(c)) {
        return;
    }
    delete c.acc.requestl;
    c.acc.requestl = nullptr;
    l->setText("Your Request is declined");
}
void removeLoan(List& list, int index)
{
    if (index < 0 || index >= list.size || list.head == nullptr) {
        return;
    }

    Node* current = list.head;

    if (index == 0) {
        list.head = current->next;
        if (list.head == nullptr) {
            list.tail = nullptr;
        }
        delete current;
        list.size--;
        return;
    }

    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    Node* toDelete = current->next;
    current->next = toDelete->next;

    if (toDelete == list.tail) {
        list.tail = current;
    }

    delete toDelete;
    list.size--;
}
