/*
TITLE: To illustrate the various Binary tree functions. For given expression eg. a-b*c-d/e+f
construct inorder sequence and traverse it using postorder traversal (non recursive).
*/

#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Tree {
private:
    struct Node {
        char data[10];
        Node* left;
        Node* right;
    };
    Node* root;
public:
    Tree() {
        root = NULL;
    }
    void create();
    void insert(Node* root, Node* New);
    void display();
    void recursive();
    void rec_postorder(Node* root);
    void nonrecursive();
    void nonrec_postorder(Node* root);
};

void Tree::create() {
    Node* New = new Node;
    cout << "\nEnter the data which you want: ";
    cin >> New->data;
    New->left = NULL;
    New->right = NULL;
    if (root == NULL) {
        root = New;
    }
    else {
        insert(root, New);
    }
}

void Tree::insert(Node* root, Node* New) {
    char ans;
    cout << "\nYou want to insert " << New->data << " at left or right child of " << root->data << ": ";
    cin >> ans;
    if (ans == 'l' || ans == 'L') {
        if (root->left == NULL) {
            root->left = New;
        }
        else {
            insert(root->left, New);
        }
    }
    else {
        if (root->right == NULL) {
            root->right = New;
        }
        else {
            insert(root->right, New);
        }
    }
}

void Tree::display() {
    if (root == NULL) {
        cout << "\nNULL Tree";
        return;
    }
    queue<Node*> q;
    q.push(root);
    cout << "\nLevelwise(BFS) Traversal\n";
    while (!q.empty()) {
        Node* node = q.front();
        cout << node->data << "\t";
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
}

void Tree::recursive() {
    rec_postorder(root);
}

void Tree::rec_postorder(Node* root) {
    if (root != NULL) {
        rec_postorder(root->left);
        rec_postorder(root->right);
        cout << "\t" << root->data;
    }
}

void Tree::nonrecursive() {
    nonrec_postorder(root);
}

void Tree::nonrec_postorder(Node* root) {
    if (!root) {
        cout << "\nTree empty";
        return;
    }
    stack<Node*> s;
    stack<Node*> op;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        op.push(curr);
        s.pop();
        if (curr->left)
            s.push(curr->left);
        if (curr->right)
            s.push(curr->right);
    }
    while (!op.empty()) {
        cout << op.top()->data << "\t";
        op.pop();
    }
}

int main() {
    Tree tr;
    int ch;
    char ans;
    do {
        cout << "\nExpression Tree";
        cout << "\n1. Create\n2. Display\n3. Exit\nEnter Your Choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            do {
                tr.create();
                cout << "\nDo You Want to Insert More Elements: ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
            tr.display();
            break;
        case 2:
            cout << "\nDisplay";
            cout << "\n1. Recursive\n2. Non Recursive\nEnter Your Choice: ";
            cin >> ch;
            switch (ch) {
            case 1:
                cout << "\nRecursive Postorder Traversal\n";
                tr.recursive();
                break;
            case 2:
                cout << "\nNon Recursive Postorder Traversal\n";
                tr.nonrecursive();
                break;
            }
            break;
        case 3:
            break;
        }
        cout << "\nDo You Want to Continue: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    return 0;
}
