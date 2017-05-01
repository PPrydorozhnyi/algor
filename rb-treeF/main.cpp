#include <iostream>

//using namespace std;

int const RED = 1;
int const BLACK = 2;

template <typename KEY, typename VALUE>
class RedBlackTree {

public:
    struct Node {

        KEY key;
        VALUE value;
        Node *left, *right, *parent;
        int color;

        Node (KEY k, VALUE v) {

            key = k;
            value = v;
            left = right = parent = nullptr;
            color = RED;
        }

        Node () {

            left = right = parent = nullptr;
            color = BLACK;
        }

    } *root, *x, *y, *current;

// nothing
    Node *NIL;

    RedBlackTree () {

        NIL = new Node();
        root = NIL;
    }

    ~RedBlackTree() {

        clear();
        delete (NIL);

    }

    void insert (KEY key, VALUE value) {

        current = new Node (key, value);
        current->left = current->right = current->parent = NIL;

        x = root;
        y = NIL;

// iteration to paste new node to optimal position according to the depth
        while (x != NIL) {

            y = x;

            if (current->key < x->key) {

                x = x->left;

            }
            else if (current->key > x->key) {

                x = x->right;

            } else {
//replacement
                x->value = value;
                return ;

            }
        }

        if (y == NIL) {

            root = current;

        } else if (current->key <  y->key) {

            y->left = current;

        } else {

            y->right = current;

        }

        current->parent = y;

        insert_fix(current);
    }

    void print () {
        print (root);
        std::cout << std::endl;
    }

// print node from left to right
    void print (Node *n) {

        if (n == NIL)
            return;

        print (n->left);
        std::cout << n->key << " " << n->value << " " << n->color << std::endl;
        print (n->right);
    }

    void clear() {

        clear(root);
        root = NIL;

    }

  // free memory with recursion
    void clear (Node *n) {

        if (n == NIL)
        return;

        clear (n->left);
        clear (n->right);

        delete (n);
    }

    Node* search (KEY key, VALUE value) {

        x = root;

        while (x != NIL) {

            if (key < x->key) {

                x = x->left;

            } else if (key > x->key) {

                x = x->right;

            }
            else if (key == x->key) {

                break;

                } else {
                    insert(key, value);
                    x = search(key, value);
                    break;
                    }
        }

        return x;
    }

    void left_rotate(Node *x) {

        //make y
        y = x->right;

        //connect x->right to b
        x->right = y->left;

        if (x->right!= NIL) {
            x->right->parent = x;
        }

        //connect y to parent's x
        y->parent = x->parent;

        if (x->parent == NIL) {
            root = y;
        } else if (x->parent->left == x) {

            x->parent->left = y;

        } else {

            x->parent->right = y;

        }

        //connect y to x
        y->left = x;
        x->parent = y;
    }

    // copy from left_rotate but change x to y, left to right and vice versa
    void right_rotate(Node *y) {

        x = y->left;

        y->left = x->right;
        if (y->left!=NIL) {

            y->left->parent = y;
        }

        x->parent = y->parent;
        if (y->parent == NIL){
            root = x;
        }
        else if (y->parent->left == y) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    void insert_fix(Node *x){
        while (x->parent->color == RED){

        //Leftmost position(3 csae)
            if (x->parent->parent->left == x->parent) {

                y = x->parent->parent->right;

                if (y->color == RED) {

                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;

                } else {

                    if (x->parent->right == x) {

                        x = x->parent;
                        left_rotate(x);

                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    right_rotate(x->parent->parent);

                }
            } else {

                y = x->parent->parent->left;

                if (y->color == RED) {

                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;

                } else {

                    if (x->parent->left == x){
                        x = x->parent;
                        right_rotate(x);
                    }

                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    left_rotate(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // depth of the tree
    int depth() {

        return depth(root);

    }
    //depth with the recursion
    int depth (Node *n) {

        if (n == NIL)
            return 0;

        return 1 + std::max( depth(n->left), depth(n->right) );
    }
};

int main () {

    RedBlackTree <int,int > rbt;

    rbt.insert(1,2);
    rbt.insert(2,3);
    rbt.insert(3,6);
    rbt.insert(4,7);
    rbt.insert(5,5);
    rbt.insert(6,2);
    rbt.insert(7,8);

    rbt.print();

    std::cout << rbt.depth() << std::endl;
    std::cin.get();

	return 0;
}
