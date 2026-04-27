// Todo List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

enum class Priority {
    Low,
    Medium,
    High
};



class Task {
    private:
        static int nextId;
        int id;
        std::string title;
        std::string time;
        Priority priority;

    public:
        // constructor
        Task(std::string t, Priority p) : id(nextId++), title(t), priority(p) {
            auto now = std::chrono::system_clock::now();
            time = std::format("{:%Y-%m-%d %H:%M:%S}", now);
        }

        // setters
        void SetTitle(std::string t) {
            title = t;
        }

        void SetPriority(Priority p) {
            priority = p;
        }

        // getters
        int getId() {
            return id;
        }

        // methodes
        void printTask(){
            std::cout << "id: " << id << " | Task: " << title << " | Created at: " << time << std::endl;
        }
        
};

int Task::nextId = 1;

void show_tasks(std::vector<Task> tasks) {
    if (tasks.empty()) {
        std::cout << "|----------------------|\n";
        std::cout << "|   No tasks to show   |\n";
        std::cout << "|----------------------|\n";
    }
    else {

        std::cout << "---------->" << tasks.size() << "Tasks found\n";
        
        std::cout << "****************************\n";
        for (int i = 0; i < tasks.size(); i++) {                                                                    
            tasks[i].printTask();
        }
        std::cout << "****************************\n";                                              
    }
}
                                                                     
int main()
{
    std::vector<Task> tasks;

    while (1) {
        std::cout << "-------------------------------|\n";
        std::cout << "|    GESTIONNAIRE DE TACHES    |\n";
        std::cout << "|1. Voir les taches            |\n";
        std::cout << "|2. Ajouter une tache          |\n";
        std::cout << "|3. Supprimer une tache        |\n";
        std::cout << "|4. Quitter                    |\n";
        std::cout << "|------------------------------|\n";

        int choice;
        std::cout << "choissisez: ";
        std::cin >> choice;

        std::cout << "your choice is: " << choice << "\n";

        switch (choice) {
            case 1: {
                show_tasks(tasks);
                break;
            }
            case 2: {
                std::string title;
                int p;
                Priority priority;
                std::cin.ignore();
                std::cout << "enter title: ";
                std::getline(std::cin, title);

                std::cout << "enter priority: \n";
                std::cout << "1. Low\n";
                std::cout << "2. Medium\n";
                std::cout << "3. High\n";
                std::cout << "votre choix: ";
                std::cin >> p;

                switch (p) {
                    case 1: priority = Priority::Low; break;
                    case 2: priority = Priority::Medium; break;
                    case 3: priority = Priority::High; break;
                    default: priority = Priority::Low; break;
                }
                Task new_task = Task(title, priority);

                tasks.push_back(new_task);

                std::cout << "Task created successfully!\n";
                break;
            }
            case 3: {
                show_tasks(tasks);
                int id;
                std::cout << "entrez l'id de cette task: ";
                std::cin >> id;

                if (id > tasks.size()) {
                    std::cout << "id pas disponible\n";
                }else {
                    for (int i = 0; i < tasks.size(); i++) {
                        if (tasks[i].getId() == id) {
                            tasks.erase(tasks.begin() + i);
                            std::cout << "task deleted succesfully\n";
                        }
                    }
                }
                
                break;
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files                                                                                                                                                                                             
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
