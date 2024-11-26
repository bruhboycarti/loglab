#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Определение структуры узла дерева
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания дерева
struct Node* CreateTree(struct Node* root, int data) {
    // Если дерево пустое, создаем новый узел
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    // Рекурсивно добавляем узел в левое или правое поддерево
    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    }
    else if (data > root->data) { // Добавляем проверку на равенство
        root->right = CreateTree(root->right, data);
    }

    return root;
}

// Функция для печати дерева
void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }

    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

// Функция для поиска значения в дереве
struct Node* search(struct Node* r, int data) {
    if (r->data == data) {
        return r;
    }
    if (data < r->data && r->left != NULL) {
        search(r->left, data);
    }
    else if (data > r->data && r->right != NULL) {
        search(r->right, data);
    }
    else
        return NULL;
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;
    struct Node* root = NULL; // Объявление корня дерева

    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    printf("Дерево:\n");
    print_tree(root, 0);

    // Поиск значения
    printf("Введите число для поиска: ");
    scanf("%d", &D);
    struct Node* result = search(root, D);

    if (result != NULL) {
        printf("Значение %d найдено в дереве.\n", D);
    }
    else {
        printf("Значение %d не найдено в дереве.\n", D);
    }

    // Освобождение памяти (необходимо реализовать)
    return 0;
}