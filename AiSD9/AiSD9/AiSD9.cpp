#include <iostream>
#include <queue>
#include <iomanip>
#include <locale>
#include <cstdlib>
#include <ctime>
//7 вариант

struct Node { //узел дерева
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// --- Часть 1: Бинарное дерево и обходы ---
class BinaryTree {
private:
    Node* root;

    void preOrder(Node* node) { //прямой обход
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) { //симметричный обход
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) { //обратный обход
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->data << " ";
    }

    int sumNodes(Node* node) { //сумма элементов
        if (node == nullptr) return 0;
        return node->data + sumNodes(node->left) + sumNodes(node->right);
    }

    int countNodes(Node* node) { //количество элементов
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void destroy(Node* node) { //очистка памяти
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {} //конструктор
    ~BinaryTree() { destroy(root); } //деструктор

    void buildSample() { //построение дерева из примера
        root = new Node(10);
        root->left = new Node(5);
        root->right = new Node(15);
        root->left->left = new Node(3);
        root->left->right = new Node(7);
        root->right->right = new Node(20);
        root->left->right->left = new Node(6);
        root->right->right->left = new Node(18);
    }

    void preOrder() { preOrder(root); std::cout << std::endl; }
    void inOrder() { inOrder(root); std::cout << std::endl; }
    void postOrder() { postOrder(root); std::cout << std::endl; }

    void levelOrder() { //уровневый обход
        if (root == nullptr) return;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->data << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    double getMean() { //среднее арифметическое
        int count = countNodes(root);
        if (count == 0) return 0;
        return (double)sumNodes(root) / count;
    }
};

// --- Часть 2: Бинарное дерево поиска (BST) ---
class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) { //вставка
        if (node == nullptr) return new Node(key);
        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);
        return node;
    }

    Node* search(Node* node, int key) { //поиск
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

    Node* findMin(Node* node) { //поиск минимума
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* findMax(Node* node) { //поиск максимума
        while (node->right != nullptr) node = node->right;
        return node;
    }

    Node* remove(Node* node, int key) { //удаление
        if (node == nullptr) return nullptr;
        if (key < node->data) node->left = remove(node->left, key);
        else if (key > node->data) node->right = remove(node->right, key);
        else {
            if (node->left == nullptr && node->right == nullptr) { //лист
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) { //один потомок (справа)
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) { //один потомок (слева)
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else { //два потомка
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

    void inOrder(Node* node) { //симметричный обход
        if (node == nullptr) return;
        inOrder(node->left);
        std::cout << node->data << " ";
        inOrder(node->right);
    }

    int getHeight(Node* node) { //высота дерева
        if (node == nullptr) return 0;
        int leftH = getHeight(node->left);
        int rightH = getHeight(node->right);
        return 1 + std::max(leftH, rightH);
    }

    void printTree(Node* node, int space) { //визуализация в консоли
        if (node == nullptr) return;
        space += 5;
        printTree(node->right, space);
        std::cout << std::endl;
        for (int i = 5; i < space; i++) std::cout << " ";
        std::cout << node->data << "\n";
        printTree(node->left, space);
    }

    void destroy(Node* node) { //очистка памяти
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {} //конструктор
    ~BST() { destroy(root); } //деструктор

    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key) != nullptr; }
    void remove(int key) { root = remove(root, key); }
    void inOrder() { inOrder(root); std::cout << std::endl; }
    int getHeight() { return getHeight(root); }
    int findMin() { return findMin(root)->data; }
    int findMax() { return findMax(root)->data; }
    void printTree() { printTree(root, 0); }
};

using namespace std; //разрешаем std в main

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    // --- Часть 1 ---
    cout << "== Часть 1: Бинарное дерево ==" << endl;
    BinaryTree bt;
    bt.buildSample();
    cout << "Прямой обход: "; bt.preOrder();
    cout << "Симметричный: "; bt.inOrder();
    cout << "Обратный: "; bt.postOrder();
    cout << "Уровневый: "; bt.levelOrder();
    cout << "Среднее арифметическое: " << bt.getMean() << endl << endl;

    // --- Часть 2 и Часть 3 ---
    cout << "== Часть 2 и 3: BST ==" << endl;
    BST bst;

    cout << "Генерация 20 случайных чисел: ";
    for (int i = 0; i < 20; i++) {
        int num = rand() % 100;
        cout << num << " ";
        bst.insert(num);
    }
    cout << endl;

    cout << "Отсортированный массив (in-order): ";
    bst.inOrder();

    cout << "Минимальный: " << bst.findMin() << endl;
    cout << "Максимальный: " << bst.findMax() << endl;
    cout << "Высота дерева: " << bst.getHeight() << endl;

    cout << "Визуализация дерева:" << endl;
    bst.printTree();

    int target;
    cout << "\nВведите элемент для удаления: ";
    cin >> target;

    bst.remove(target);
    cout << "Дерево после удаления " << target << ":" << endl;
    bst.printTree();
    cout << "Отсортированный массив после удаления: ";
    bst.inOrder();

    return 0;
}