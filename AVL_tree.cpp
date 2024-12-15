#include <iostream>
#include <algorithm>

using namespace std;

// Definição da estrutura do nó da árvore
struct Node {
    int key;           // Valor armazenado no nó
    Node* left;        // Ponteiro para o nó filho à esquerda
    Node* right;       // Ponteiro para o nó filho à direita
    int height;        // Altura do nó

    // Construtor para inicializar o nó
    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// Retorna a altura de um nó
int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Retorna o maior valor entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Rotação simples à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna o novo nó raiz
    return x;
}

// Rotação simples à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna o novo nó raiz
    return y;
}

// Rotação dupla à esquerda (esquerda-direita)
Node* leftRightRotate(Node* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

// Rotação dupla à direita (direita-esquerda)
Node* rightLeftRotate(Node* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

// Função para inserir um valor na árvore AVL
Node* insert(Node* node, int key) {
    // 1. Realiza a inserção normal de uma árvore binária de busca
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas
        return node;

    // 2. Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtém o fator de balanceamento e balanceia a árvore
    int balance = getBalance(node);

    // Caso 1: Desbalanceamento à esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso 2: Desbalanceamento à direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso 3: Desbalanceamento à esquerda-direita
    if (balance > 1 && key > node->left->key)
        return leftRightRotate(node);

    // Caso 4: Desbalanceamento à direita-esquerda
    if (balance < -1 && key < node->right->key)
        return rightLeftRotate(node);

    // Retorna o ponteiro do nó (não houve desbalanceamento)
    return node;
}

// Função para buscar um valor na árvore AVL
Node* search(Node* node, int key) {
    // Caso base: árvore vazia ou valor encontrado
    if (node == nullptr || node->key == key)
        return node;

    // Se o valor é menor que a chave do nó atual, busque na subárvore esquerda
    if (key < node->key)
        return search(node->left, key);

    // Se o valor é maior que a chave do nó atual, busque na subárvore direita
    return search(node->right, key);
}

int main() {
    Node* root = nullptr;

    // Inserção de alguns valores
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);

    // Realizando busca binária
    int key = 15;
    Node* result = search(root, key);
    if (result != nullptr)
        cout << "Valor " << key << " encontrado na árvore!" << endl;
    else
        cout << "Valor " << key << " não encontrado na árvore!" << endl;

    return 0;
}
