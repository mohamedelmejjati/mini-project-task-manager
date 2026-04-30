// Todo List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <format>

enum class Priority {
    Low,
    Medium,
    High
};

enum class Status {
    Afaire,
    EnCours,
    Terminee
};

enum class Field {
    title,
    priority,
    status,
    category
};

enum class Category {
    Travail,
    Personnel,
    Urgent,
    Autre
};

class Task {
    private:
        static int nextId;
        int id;
        std::string title;
        std::string time;
        Priority priority;
        Status status;
        Category category;

    public:
        // constructor
        Task(std::string t, Priority p, Category c) : id(nextId++), title(t), priority(p), category(c) {
            auto now = std::chrono::system_clock::now();
            time = std::format("{:%Y-%m-%d %H:%M:%S}", now);
            status = Status::EnCours;
        }

        // setters
        void SetTitle(std::string t) {
            title = t;
        }

        void SetPriority(Priority p) {
            priority = p;
        }

        void SetStatus(Status s) {
            status = s;
        }

        void SetCategory(Category c) {
            category = c;
        }

        // getters
        int getId() {
            return id;
        }

        Category getCategory() {
            return category;
        }

        // methodes
        void printTask() {
            std::cout << "id: " << id
                << " | [" << CategoryToString(category) << "]" 
                << " | Task: " << title
                << " | Status: " << StatusToString(status)
                << " | Priority: " << PriorityToString(priority) << std::endl;
        }

        std::string StatusToString(Status s) {
            switch (s) {
                case Status::Afaire:   return "A faire";
                case Status::EnCours:  return "En cours";
                case Status::Terminee: return "Terminee";
                default:               return "A faire";
            }
        }

        std::string PriorityToString(Priority p) {
            switch (p) {
            case Priority::Low:   return "Low";
            case Priority::Medium:   return "Medium";
            case Priority::High:   return "High";
            default:               return "Medium";
            }
        }

        std::string CategoryToString(Category c) {
            switch (c) {
            case Category::Travail:   return "Travail";
            case Category::Personnel: return "Personnel";
            case Category::Urgent:    return "Urgent";
            default:                  return "Autre";
            }
        }
        
};

int Task::nextId = 1;

int check_id(int id, std::vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].getId() == id) {
            return 0;
        }
    }
    return 1;
}

void show_tasks(std::vector<Task>& tasks) {
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
               
void delete_task(int id, std::vector<Task>& tasks) {
    if (id > tasks.size() || id < 0) {
        std::cout << "id pas disponible\n";
    }
    else {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getId() == id) {
                tasks.erase(tasks.begin() + i);
                std::cout << "task deleted succesfully\n";
                return;
            }
        }
    }
}

void tasks_by_category(std::vector<Task>& tasks) {
    int c;
    std::cout << "enter category: \n";
    std::cout << "1. Travail\n";
    std::cout << "2. Personnel\n";
    std::cout << "3. Urgent\n";
    std::cout << "4. Autre\n";
    std::cout << "votre choix: ";
    std::cin >> c;

    Category cat;
    if (c == 1) cat = Category::Travail;
    else if (c == 2) cat = Category::Personnel;
    else if (c == 3) cat = Category::Urgent;
    else cat = Category::Autre;

    bool found = false;
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].getCategory() == cat) {
            tasks[i].printTask();
            found = true;
        }
    }
    if (!found) {
        std::cout << "|----------------------|\n";
        std::cout << "|   No tasks to show   |\n";
        std::cout << "|----------------------|\n";
    }
}

//void modify_task(Field field, int id, std::vector<Task> tasks) {
void modify_task(Field field, int id, std::vector<Task>& tasks) {
    int index;
    if (check_id(id, tasks) == 1) {
        std::cout << "id pas disponible\n";
    }
    else {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getId() == id) {
                index = i;
            }
        }
    }

    switch (field) {

        case Field::status: {
            int choice;
            std::cout << "choisis la nouvelle status:\n";
            std::cout << "1. Afaire\n";
            std::cout << "2. EnCours\n";
            std::cout << "3. Terminee\n";
            std::cout << "votre choix: ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    tasks[index].SetStatus(Status::Afaire);
                    break;
                }
                case 2: {
                    tasks[index].SetStatus(Status::EnCours);
                    break;
                }
                case 3: {
                    tasks[index].SetStatus(Status::Terminee);
                    break;
                }
            }
            std::cout << "Status changed Succesfully";
            break;

        }
        case Field::title: {
            std::string new_title;
            std::cout << "enter the new title: ";
            std::cin >> new_title;
            tasks[index].SetTitle(new_title);
            break;
        }
        case Field::priority: {
            int choice;
            std::cout << "choisis la nouvelle priority:\n";
            std::cout << "1. Low\n";
            std::cout << "2. Medium\n";
            std::cout << "3. High\n";
            std::cout << "votre choix: ";
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    tasks[index].SetPriority(Priority::Low);
                    break;
                }
                case 2: {
                    tasks[index].SetPriority(Priority::Medium);
                    break;
                }
                case 3: {
                    tasks[index].SetPriority(Priority::High);
                    break;
                }
            }
            std::cout << "Priority changed Succesfully";
            break;
        }
        case Field::category: {
            int choice;
            std::cout << "choisis la nouvelle category:\n";
            std::cout << "1. Travail\n";
            std::cout << "2. Personnel\n";
            std::cout << "3. Urgent\n";
            std::cout << "4. Autre\n";
            std::cout << "votre choix: ";
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    tasks[index].SetCategory(Category::Travail);
                    break;
                }
                case 2: {
                    tasks[index].SetCategory(Category::Personnel);
                    break;
                }
                case 3: {
                    tasks[index].SetCategory(Category::Urgent);
                    break;
                }
                default: tasks[index].SetCategory(Category::Autre);
            }
            break;
        }
    }
        
}

int main()
{
    std::vector<Task> tasks;

    while (1) {
        std::cout << "----------------------------------|\n";
        std::cout << "|    GESTIONNAIRE DE TACHES       |\n";
        std::cout << "|1. Voir les taches               |\n";
        std::cout << "|2. Ajouter une tache             |\n";
        std::cout << "|3. Supprimer une tache           |\n";
        std::cout << "|4. Modifier une tache            |\n";
        std::cout << "|5. Sort By Category              |\n";
        std::cout << "|6. Quitter                       |\n";
        std::cout << "|---------------------------------|\n";

        int choice;
        std::cout << "choissisez: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                show_tasks(tasks);
                break;
            }
            case 2: {
                std::string title;
                int p;
                Priority priority;
                Category category;
                int c;

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

                std::cout << "enter category: \n";
                std::cout << "1. Travail\n";
                std::cout << "2. Personnel\n";
                std::cout << "3. Urgent\n";
                std::cout << "4. Autre\n";
                std::cout << "votre choix: ";
                std::cin >> c;

                switch (c) {
                    case 1: category = Category::Travail; break;
                    case 2: category = Category::Personnel; break;
                    case 3: category = Category::Urgent; break;
                    default: category = Category::Autre; break;
                }
                

                Task new_task = Task(title, priority, category);

                tasks.push_back(new_task);

                std::cout << "Task created successfully!\n";
                break;
            }
            case 3: {
                show_tasks(tasks);
                int id;
                std::cout << "entrez l'id de cette task: ";
                std::cin >> id;

                delete_task(id, tasks);
                
                break;
            }
            case 4: {
                show_tasks(tasks);
                int id;
                std::cout << "entrez l'id de cette task: ";
                std::cin >> id;
                if (check_id(id, tasks) == 1) {
                    std::cout << "id pas disponible\n";
                }else {
                    int choice;
                    std::cout << "Which field u wanna modifie:\n";
                    std::cout << "1. Title\n";
                    std::cout << "2. Status\n";
                    std::cout << "3. Priority\n";
                    std::cout << "4. Category\n";
                    std::cout << "votre choix: ";
                    std::cin >> choice;
                    switch (choice) {
                        case 1: {
                            modify_task(Field::title, id, tasks);
                            break;
                        }
                        case 2: {
                            modify_task(Field::status, id, tasks);
                            break;
                        }
                        case 3: {
                            modify_task(Field::priority, id, tasks);
                            break;
                        }
                        case 4: {
                            modify_task(Field::category, id, tasks);
                            break;
                        }
                    }
                }
                break;
            }
            case 5: {
                tasks_by_category(tasks);
                break;
            }
            case 6: {
                std::cout << "Bye!\n";
                std::exit(1);
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
