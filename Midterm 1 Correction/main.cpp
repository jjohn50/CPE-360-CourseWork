#include<iostream>
using namespace std;

/*
 * I pledge my honor that I have abided by the Stevens Honor System X Justin John
 */

class Chunkbox{
public:
  int value = 0;
  Chunkbox *next;

    Chunkbox()
  {
    value = 0;
    next = NULL;
  }
};

class LinkList {
public:
    Chunkbox *head;
    int count;

    LinkList() {
        count = 0;
        head = NULL;
    }

    void insertAtHead(int x) {
        if (head == NULL) {
            head = new Chunkbox;
            head->value = x;
        }
        else {
            Chunkbox *helper = new Chunkbox;
            helper->value = x;
            helper->next = head;
            head = helper;
        }
        count++;
    }

    void insertAtPosition(int position, int x) {
        if (position > 0 && position <= count + 1) {
            Chunkbox *helper = new Chunkbox;
            helper->value = x;

            if (position == 1) {
                helper->next = head;
                head = helper;
            }
            else if (position == count + 1) {
                Chunkbox *h = this->head;
                for (int i = 1; i < count; i++) {
                    h = h->next;
                }
                h->next = helper;
            }
            else {
                Chunkbox *h = head;
                for (int i = 1; i < position - 1; i++) {
                    h = h->next;
                }
                helper->next = h->next;
                h->next = helper;
            }
            count++;
        }
        else {
            cout << "Invalid Position: Can Not Insert" << endl;
        }
    }

    void removeFromPosition(int position) {
        if (position > 0 && position <= count) {
            if (position == 1) {
                Chunkbox *r;
                r = head;
                head = head->next;
                cout << "Deleting: " << r->value << endl;
                cout << "Value Deleted" << endl;
                delete r;
            }
            else if (position == count) {
                Chunkbox *rep, *r;
                rep = r = head;
                while (r->next != NULL) {
                    rep = r;
                    r = r->next;
                }
                rep->next = NULL;
                cout << "Deleting: " << r->value << endl;
                cout << "Value Deleted" << endl;
                delete r;
            }
            else {
                Chunkbox *before, *after;
                before = after = head;
                for (int i = 1; i < position; i++) {
                    before = after;
                    after = after->next;
                }
                before->next = after->next;
                cout << "Deleting: " << after->value << endl;
                cout << "Value Deleted" << endl;
                delete after;
            }
            count--;
        }
        else {
            cout << "Invalid Position: Can Not Delete" << endl;
        }
    }

    void Display() {
        if (head == NULL) {
            cout << "No Content In Link List" << endl;
        }
        else {
            Chunkbox *print;
            print = head;
            while (print != NULL) {
                cout << print->value << endl;
                print = print->next;
            }
        }
    }

    void reverseLinkedList() { //star problem 5 (works)
        Chunkbox *middle = head;
        Chunkbox *slow, *fast = NULL;
        while (middle != NULL) {
            fast = middle->next;
            middle->next = slow;
            slow = middle;
            middle = fast;
        }
        head = slow;
    }

    void removeEveryOtherNode() { //star problem 7 (works)
        if (head == NULL) {
            return;
        }
        else {
            Chunkbox *rep = head;
            Chunkbox *mov = head->next;
            while (rep != NULL && mov != NULL) {
                rep->next = mov->next;
                free(mov);
                rep = rep->next;
                if (rep != NULL) {
                    mov = rep->next;
                }
            }
        }
        Display();
    }

    void dectectandRemoveLoops() { //star problem 6 (works)
        Chunkbox *repl = head;
        Chunkbox *movr = head->next;
        while (movr && movr->next) {
            if (repl == movr) {
                break;
            } else {
                repl = repl->next;
                movr = movr->next->next;
            }
        }
        if (repl == movr) {
            repl = head;
            while (repl != movr->next) {
                repl = repl->next;
                movr = movr->next;
            }
            movr->next = NULL;
        }
    }
};

int main() {
    LinkList List;
    int c, p, v;
    while (1) {
        cout << "Press 1 to Add to Linked List" << endl;
        cout << "Press 2 to Add at Specific Position" << endl;
        cout << "Press 3 to Delete from Linked List" << endl;
        cout << "Press 4 to Print Contents" << endl;
        cout << "Press 5 to Print Number of Counts" << endl;
        cout << "Press 6 to Reverse the Link List" << endl;
        cout << "Press 7 to Remove Every Other Node " << endl;
        cout << "Press 8 to Detect a Loop and Delete it" << endl;
        cin >> c;

        switch (c) {
            case 1 :
                cout << '\n';
                cout << "Input a Value" << '\n';
                cin >> v;
                cout << '\n';
                List.insertAtHead(v);
                cout << '\n';
                break;

            case 2 :
                cout << '\n';
                cout << "Input a Position" << '\n';
                cin >> p;
                cout << '\n';
                cout << "Input a Value" << '\n';
                cin >> v;
                cout << '\n';
                List.insertAtPosition(p, v);
                cout << '\n';
                break;

            case 3 :
                cout << '\n';
                cout << "Input a Position" << '\n';
                cin >> p;
                cout << '\n';
                List.removeFromPosition(p);
                cout << '\n';
                break;

            case 4 :
                cout << '\n';
                cout << "Here are all the values in the Stack" << '\n';
                List.Display();
                cout << '\n';
                break;

            case 5 :
                cout << '\n';
                cout << "Here is the count of the Linkedlist (count)" << '\n';
                cout << List.count << '\n';
                cout << '\n';
                break;
            case 6:
                cout << '\n';
                cout << "Here is the original order of the list" << '\n';
                List.Display();
                cout << '\n';
                cout << "Here is the reverse order of the list " << '\n';
                List.reverseLinkedList();
                List.Display();
                break;
            case 7:
                cout << "Here is what it is like when every other Node is deleted" << '\n';
                List.removeEveryOtherNode();
                break;
            case 8:
                cout << "Loop destroyed" << endl;
                List.dectectandRemoveLoops();
                break;
        }
    }
    return 1;
}
