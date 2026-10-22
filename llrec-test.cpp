#include <iostream>
#include <fstream>
#include <cstdlib>
#include "llrec.h"
using namespace std;

Node* readRest(ifstream& ifile)
{
    int v;
    if (!(ifile >> v)) {
        return NULL;
    }
    Node* n = new Node(v, NULL);
    n->next = readRest(ifile);
    return n;
}

Node* readList(const char* filename)
{
    ifstream ifile(filename);
    return readRest(ifile);
}

void printRest(Node* head)
{
    if (head == NULL) {
        cout << endl;
        return;
    }
    cout << head->val << " ";
    printRest(head->next);
}

void print(Node* head)
{
    printRest(head);
}

void dealloc(Node* head)
{
    if (head == NULL) {
        return;
    }
    dealloc(head->next);
    delete head;
}

struct IsOdd {
    bool operator()(int x) { return x % 2 != 0; }
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    Node* smaller;
    Node* larger;
    llpivot(head, smaller, larger, 10);
    print(smaller);
    print(larger);

    Node* filtered = llfilter(smaller, IsOdd());
    print(filtered);

    dealloc(filtered);
    dealloc(larger);
    return 0;
}
