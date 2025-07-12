#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>

using namespace std;

struct Employee {
    int id;
    int accessLevel;
    int importance;
    Employee* left;
    Employee* right;
    Employee(int id, int access, int imp) 
        : id(id), accessLevel(access), importance(imp), left(nullptr), right(nullptr) {}
};

class EmployeeTree {
    unordered_map<int, Employee*> employees;
    Employee* root;

    void clear(Employee* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    EmployeeTree() : root(nullptr) {}
    ~EmployeeTree() { clear(root); }

    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) return false;

        int id, access, imp, leftId, rightId;
        while (file >> id >> access >> imp >> leftId >> rightId) {
            employees[id] = new Employee(id, access, imp);
        }

        file.clear();
        file.seekg(0);

        while (file >> id >> access >> imp >> leftId >> rightId) {
            Employee* emp = employees[id];
            if (!root) root = emp;

            if (leftId != -1) {
                emp->left = employees[leftId];
                if (emp->left->accessLevel > emp->accessLevel) {
                    cerr << "Ошибка: уровень доступа подчиненного выше\n";
                    return false;
                }
            }
            if (rightId != -1) {
                emp->right = employees[rightId];
                if (emp->right->accessLevel > emp->accessLevel) {
                    cerr << "Ошибка: уровень доступа подчиненного выше\n";
                    return false;
                }
            }
        }

        return true;
    }

    int getTotalImportanceStack(int id) {
        if (employees.find(id) == employees.end()) return -1;

        int total = 0;
        stack<Employee*> st;
        st.push(employees[id]);

        while (!st.empty()) {
            Employee* current = st.top();
            st.pop();

            if (current->left) {
                total += current->left->importance;
                st.push(current->left);
            }
            if (current->right) {
                total += current->right->importance;
                st.push(current->right);
            }
        }

        return total;
    }

    int getTotalImportanceRecursive(int id) {
        if (employees.find(id) == employees.end()) return -1;
        return calculateImportance(employees[id]);
    }

private:
    int calculateImportance(Employee* emp) {
        if (!emp) return 0;
        int sum = 0;
        if (emp->left) sum += emp->left->importance + calculateImportance(emp->left);
        if (emp->right) sum += emp->right->importance + calculateImportance(emp->right);
        return sum;
    }
};

int main() {
    EmployeeTree tree;
    cout << "Введите имя файла с данными: ";
    string filename;
    cin >> filename;

    if (!tree.loadFromFile(filename)) {
        cerr << "Ошибка загрузки файла\n";
        return 1;
    }

    cout << "Введите ID сотрудника: ";
    int id;
    cin >> id;

    int stackImp = tree.getTotalImportanceStack(id);
    int recImp = tree.getTotalImportanceRecursive(id);

    if (stackImp == -1 || recImp == -1) {
        cout << "Сотрудник не найден!\n";
    } else {
        cout << "Совокупная важность (стек): " << stackImp << endl;
        cout << "Совокупная важность (рекурсия): " << recImp << endl;
    }

    return 0;
}