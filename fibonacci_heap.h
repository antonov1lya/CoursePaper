#ifndef FIBONACCI_HEAP_FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_FIBONACCI_HEAP_H

#include <vector>
#include <cmath>

template<typename Type>
class FibonacciHeap {
private:
    struct Node {
        Type key;
        int degree = 0;
        Node *child = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    int size;
    Node *min;

    void mergeLists(Node *first, Node *second) {
        Node *l = first->left;
        Node *r = second->right;
        second->right = first;
        first->left = second;
        l->right = r;
        r->left = l;
    }

    void consolidate() {
        float lg = (log(size)) / (log(2));
        int D = lg;
        std::vector<Node *> A(D + 1, nullptr);
        Node *start = min;
        A[min->degree] = min;
        Node *current = min->right;
        while (current != start) {
            Node *x = current;
            Node *next = current->right;
            int d = x->degree;
            while (A[d] != nullptr) {
                Node *y = A[d];
                if (x->key > y->key) {
                    Node *tmp = x;
                    x = y;
                    y = tmp;
                }
                x->degree++;
                y->left = y;
                y->right = y;
                if (x->child != nullptr) {
                    mergeLists(x->child, y);
                } else {
                    x->child = y;
                }
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            current = next;
        }
        min = nullptr;
        for (int i = 0; i < D + 1; ++i) {
            if (A[i] != nullptr) {
                A[i]->left = A[i];
                A[i]->right = A[i];
                if (min == nullptr) {
                    min = A[i];
                } else {
                    mergeLists(min, A[i]);
                    if (A[i]->key < min->key) {
                        min = A[i];
                    }
                }
            }
        }
    }

public:
    FibonacciHeap() {
        size = 0;
        min = nullptr;
    }

    void insert(Type x) {
        Node *add = new(Node);
        add->key = x;
        add->left = add;
        add->right = add;
        if (!size) {
            min = add;
        } else {
            mergeLists(min, add);
            if (add->key < min->key) {
                min = add;
            }
        }
        ++size;
    }

    Type extractMin() {
        Node *removable = min;
        Type key = removable->key;
        if (removable->child != nullptr) {
            mergeLists(removable, removable->child);
        }
        Node *l = removable->left;
        Node *r = removable->right;
        l->right = r;
        r->left = l;
        min = removable->right;
        --size;
        if (removable->right == removable) {
            min = nullptr;
        } else {
            consolidate();
        }
        delete removable;
        return key;
    }

    bool empty() {
        return !size;
    }
};

#endif //FIBONACCI_HEAP_FIBONACCI_HEAP_H
