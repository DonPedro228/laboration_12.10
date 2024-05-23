#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int info;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->info = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }
    if (value < root->info) {
        root->left = insert(root->left, value);
    }
    else if (value > root->info) {
        root->right = insert(root->right, value);
    }
    return root;
}

void printInOrder(Node* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->info << " ";
        printInOrder(root->right);
    }
}

void deleteSubtree(Node* subtreeRoot) {
    if (subtreeRoot == nullptr) {
        return;
    }
    deleteSubtree(subtreeRoot->left);
    deleteSubtree(subtreeRoot->right);
    delete subtreeRoot;
}

Node* removeEvenNodes(Node*& root) {
    if (root == nullptr) {
        return nullptr;
    }
    root->left = removeEvenNodes(root->left);
    root->right = removeEvenNodes(root->right);
    if (root->info % 2 == 0) {
        Node* temp = root;
        if (root->left != nullptr) {
            root = root->left;
            delete temp;
            return root;
        }
        else if (root->right != nullptr) {
            root = root->right;
            delete temp;
            return root;
        }
        else {
            delete temp;
            return nullptr;
        }
    }
    return root;
}



Node* findMinimum(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* removeNode(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->info) {
        root->left = removeNode(root->left, key);
    }
    else if (key > root->info) {
        root->right = removeNode(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMinimum(root->right);
        root->info = temp->info;
        root->right = removeNode(root->right, temp->info);
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == nullptr || root->info == key) {
        return root;
    }
    if (root->info < key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Insert a node\n";
    cout << "2. Remove a node\n";
    cout << "3. Search for a node\n";
    cout << "4. Print the tree\n";
    cout << "5. Remove all even nodes\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Node* root = nullptr;
    ifstream file("1.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file.\n";
        return 1;
    }
    int value;
    while (file >> value) {
        root = insert(root, value);
    }
    file.close();

    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
        case 1: {
            int newValue;
            cout << "Enter the value to insert: ";
            cin >> newValue;
            root = insert(root, newValue);
            break;
        }
        case 2: {
            int removeValue;
            cout << "Enter the value to remove: ";
            cin >> removeValue;
            root = removeNode(root, removeValue);
            break;
        }
        case 3: {
            int searchValue;
            cout << "Enter the value to search: ";
            cin >> searchValue;
            Node* result = search(root, searchValue);
            if (result) {
                cout << "Value found in the tree.\n";
            }
            else {
                cout << "Value not found in the tree.\n";
            }
            break;
        }
        case 4: {
            cout << "Tree: ";
            printInOrder(root);
            cout << endl;
            break;
        }
        case 5: {
            root = removeEvenNodes(root);
            if (root == nullptr) {
                cout << "Tree is empty after removing even nodes.\n";
            }
            else {
                cout << "Tree after removing even nodes: ";
                printInOrder(root);
                cout << endl;
            }
        }
        case 6: {
            cout << "Exiting...\n";
            break;
        }
        default:
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}
