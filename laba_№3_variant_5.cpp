#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Task {
    string name;
    int priority;
    string dueDate;
};

void addTask() {
    ofstream file("tasks.txt", ios::app);
    if (!file) {
        cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    while (true) {
        string name;
        cout << "Введите название задачи (или пустую строку для выхода): ";
        getline(cin, name);

        if (name.empty()) break;

        int priority;
        string dueDate;

        cout << "Введите приоритет задачи (целое число): ";
        cin >> priority;
        cin.ignore();

        cout << "Введите срок выполнения задачи: ";
        getline(cin, dueDate);

        file << name << "|" << priority << "|" << dueDate << "\n";
    }

    file.close();
    cout << "Задачи успешно добавлены.\n";
}

vector<Task> readTasksFromFile() {
    ifstream file("tasks.txt");
    vector<Task> tasks;
    if (!file) {
        cerr << "Не удалось открыть файл для чтения.\n";
        return tasks;
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string name, priorityStr, dueDate;

        getline(stream, name, '|');
        getline(stream, priorityStr, '|');
        getline(stream, dueDate);

        if (!name.empty() && !priorityStr.empty() && !dueDate.empty()) {
            tasks.push_back({name, stoi(priorityStr), dueDate});
        }
    }

    file.close();
    return tasks;
}

void findTaskByName() {
    string nameToFind;
    cout << "Введите название задачи для поиска: ";
    getline(cin, nameToFind);

    vector<Task> tasks = readTasksFromFile();
    bool found = false;

    for (const auto& task : tasks) {
        if (task.name == nameToFind) {
            cout << "Задача найдена: " << task.name << ", Приоритет: " << task.priority << ", Срок выполнения: " << task.dueDate << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Задача с названием \"" << nameToFind << "\" не найдена.\n";
    }
}

void sortTasks() {
    vector<Task> tasks = readTasksFromFile();
    if (tasks.empty()) {
        cout << "Нет задач для сортировки.\n";
        return;
    }

    int choice;
    cout << "Выберите критерий сортировки (1 - по приоритету, 2 - по сроку выполнения): ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority < b.priority;
        });
    } else if (choice == 2) {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.dueDate < b.dueDate;
        });
    } else {
        cout << "Некорректный выбор.\n";
        return;
    }

    ofstream outFile("output.txt");
    for (const auto& task : tasks) {
        outFile << task.name << "|" << task.priority << "|" << task.dueDate << "\n";
        cout << "Задача: " << task.name << ", Приоритет: " << task.priority << ", Срок выполнения: " << task.dueDate << "\n";
    }

    cout << "Задачи успешно отсортированы и записаны в output.txt.\n";
}

void displayTasksByPriority() {
    int maxPriority;
    cout << "Введите максимальный приоритет для отображения задач: ";
    cin >> maxPriority;
    cin.ignore();

    vector<Task> tasks = readTasksFromFile();
    ofstream outFile("output.txt");
    bool found = false;

    for (const auto& task : tasks) {
        if (task.priority <= maxPriority) {
            cout << "Задача: " << task.name << ", Приоритет: " << task.priority << ", Срок выполнения: " << task.dueDate << "\n";
            outFile << task.name << "|" << task.priority << "|" << task.dueDate << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Нет задач с приоритетом меньше или равным " << maxPriority << ".\n";
    } else {
        cout << "Задачи успешно записаны в output.txt.\n";
    }
}

void displayMenu() {
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Найти задачу по названию\n";
        cout << "3. Сортировать задачи\n";
        cout << "4. Вывести задачи по приоритету\n";
        cout << "5. Выход\n";
        cout << "Выберите опцию: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                findTaskByName();
                break;
            case 3:
                sortTasks();
                break;
            case 4:
                displayTasksByPriority();
                break;
            case 5:
                cout << "Выход из программы.\n";
                return;
            default:
                cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";
                break;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
