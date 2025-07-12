#include <iostream>
#include <ctime>
#include <random>  

using namespace std;

template <typename T>
class List {
public:
    List();
    ~List();
    void push_back(T data);
    int Get_Size();
    void createCycle(int pos);  
    bool hasCycle();           
    void print();              

private:
    class Node {
    public:
        T data;
        Node* pNext;
        Node(T data = T(), Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node* head;
    int Size;
};

template <typename T>
List<T>::List() {
    head = nullptr;
    Size = 0;
}

template <typename T>
List<T>::~List() {
    if (hasCycle()) {
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->pNext != nullptr) {
            slow = slow->pNext;
            fast = fast->pNext->pNext;
            if (slow == fast) {  
                slow = head;
                while (slow->pNext != fast->pNext) {
                    slow = slow->pNext;
                    fast = fast->pNext;
                }
                fast->pNext = nullptr;  
                break;
            }
        }
    }
    while (head != nullptr) {
        Node* temp = head;
        head = head->pNext;
        delete temp;
    }
}

template <typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node(data);
    } else {
        Node* current = head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}

template <typename T>
int List<T>::Get_Size() {
    return Size;
}

template <typename T>
void List<T>::createCycle(int pos) {
    if (pos < 0 || pos >= Size) return;  
    Node* tail = head;
    while (tail->pNext != nullptr) {
        tail = tail->pNext;
    }
    Node* cycleNode = head;
    for (int i = 0; i < pos; ++i) {
        cycleNode = cycleNode->pNext;
    }
    tail->pNext = cycleNode;  
}

template <typename T>
bool List<T>::hasCycle() {
    if (head == nullptr || head->pNext == nullptr) {
        return false;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->pNext != nullptr) {
        slow = slow->pNext;
        fast = fast->pNext->pNext;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

template <typename T>
void List<T>::print() {
    if (hasCycle()) {
        cout << "Список содержит цикл, печать невозможна!" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->pNext;
    }
    cout << endl;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 99); 

    List<int> lst;
    int size;
    cout << "Введите размер списка: ";
    cin >> size;

    for (int i = 0; i < size; ++i) {
        lst.push_back(dist(gen));  
    }

    cout << "Список без цикла: ";
    lst.print();

    uniform_int_distribution<> cycle_dist(0, 1); 
    if (cycle_dist(gen)) {  
        uniform_int_distribution<> pos_dist(0, size - 1);  
        int cyclePos = pos_dist(gen);
        lst.createCycle(cyclePos);
        cout << "Добавлен цикл на позицию " << cyclePos << endl;
    }

    if (lst.hasCycle()) {
        cout << "Да, цикл есть!" << endl;
    } else {
        cout << "Нет, цикла нет." << endl;
    }

    return 0;
}