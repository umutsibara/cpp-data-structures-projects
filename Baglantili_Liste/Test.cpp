#include <iostream>

using namespace std;

// Tek Yönlü Bağlantılı Listede Kullanılacak düğüm yapısı
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Tek Yönlü Bağlantılı Listede Ekleme İşlemi Yapan Fonksiyon
void insertAtIndex(Node*& head, int index, int value) {
    if (index < 0) {
        cout << "Geçersiz indeks." << endl;
        return;
    }

    Node* newNode = new Node(value);

    if (index == 0) {
        // Başa ekleme
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    int currentIndex = 0;

    // Ekleme konumuna git
    while (current != nullptr && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current == nullptr) {
        cout << "Geçersiz indeks." << endl;
        return;
    }

    // Yeni düğümü ekleyin
    newNode->next = current->next;
    current->next = newNode;
}

// Tek Yönlü Bağlantılı Listeyi Yazdıran Fonksiyon
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Tek Yönlü Bağlantılı Listeyi Temizleyen Fonksiyon
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;

    // Liste başına eleman ekleme
    insertAtIndex(head, 0, 10);
    insertAtIndex(head, 0, 20);

    // Liste arasına eleman ekleme
    insertAtIndex(head, 1, 30);

    // Listenin sonuna eleman ekleme
    insertAtIndex(head, 3, 40);

    // Listeyi yazdır
    printList(head);

    // Belleği temizle
    deleteList(head);

    return 0;
}
