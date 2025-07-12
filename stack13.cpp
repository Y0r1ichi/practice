#include <iostream>
#include <vector>
using namespace std;

const int N = 8;

struct Cell {
    int x, y;
    int moves;
    Cell(int x = 0, int y = 0, int moves = 0) : x(x), y(y), moves(moves) {}
};

class Queue {
private:
    struct Node {
        Cell data;
        Node* next;
        Node(Cell data) : data(data), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    
public:
    Queue() : front(nullptr), rear(nullptr) {}
    
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    void enqueue(Cell data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    Cell dequeue() {
        if (isEmpty()) {
            return Cell(-1, -1, -1);
        }
        Node* temp = front;
        Cell data = temp->data;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        return data;
    }
};

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

int knightMoves(int startX, int startY, int targetX, int targetY) {
    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    
    Queue q;
    
    q.enqueue(Cell(startX, startY, 0));
    visited[startX][startY] = true;
    
    while (!q.isEmpty()) {
        Cell current = q.dequeue();
        
        if (current.x == targetX && current.y == targetY) {
            return current.moves;
        }
        
        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            
            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                q.enqueue(Cell(newX, newY, current.moves + 1));
            }
        }
    }
    
    return -1;
}

int main() {
    int startX, startY, targetX, targetY;
    
    cout << "Введите начальную позицию коня (x y от 0 до 7): ";
    cin >> startX >> startY;
    
    cout << "Введите позицию цели (x y от 0 до 7): ";
    cin >> targetX >> targetY;
    
    if (!isValid(startX, startY) || !isValid(targetX, targetY)) {
        cout << "Некорректные координаты!" << endl;
        return 1;
    }
    
    int moves = knightMoves(startX, startY, targetX, targetY);
    
    if (moves != -1) {
        cout << "Минимальное количество ходов: " << moves << endl;
    } else {
        cout << "Путь не найден!" << endl;
    }
    
    return 0;
}