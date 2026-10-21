#ifndef LLREC_H
#define LLREC_H
#ifndef NULL
#define NULL 0
#endif

struct Node
{
    int val;
    Node *next;

    Node(int v, Node* n) : val(v), next(n) {}
};

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

template <typename Comp>
Node* llfilter(Node* head, Comp pred);

template <typename Comp>
Node* llfilter(Node* head, Comp pred)
{
    if (head == NULL) {
        return NULL;
    }

    Node* rest = llfilter(head->next, pred);

    if (pred(head->val)) {
        delete head;
        return rest;
    }

    head->next = rest;
    return head;
}

#endif
