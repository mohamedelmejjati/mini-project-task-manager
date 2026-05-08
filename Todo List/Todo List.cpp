#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

// enum pour chaque propriété de classe

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

        // personnalisé pour l'importation de tâches
        Task(int existingId, std::string t, Priority p, Status s, Category c, std::string tm)
            : id(existingId), title(t), priority(p), status(s), category(c), time(tm) {
            if (existingId >= nextId) {
                nextId = existingId + 1;
            }
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

        std::string getTitle() {
            return title;
        }

        Category getCategory() {
            return category;
        }

        Priority getPriority() {
            return priority;
        }

        Status getStatus() {
            return status;
        }

        std::string getTime() const {
            return time;
        }

        // methodes
        void printTask() {
            std::cout << "id: " << id
                << " | [" << CategoryToString(category) << "]" 
                << " | Task: " << title
                << " | Status: " << StatusToString(status)
                << " | Priority: " << PriorityToString(priority) << std::endl;
        }

        // helpers

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

// initialisation de l'id
int Task::nextId = 1;


// vérification de la présence de l'id dans le tableau des tâches
int check_id(int id, std::vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].getId() == id) {
            return 0;
        }
    }
    return 1;
}


// helper methode pour afficher les tasks
void show_tasks(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "|----------------------|\n";
        std::cout << "|   No tasks to show   |\n";
        std::cout << "|----------------------|\n";
    }
    else {

        std::cout << "\n" << tasks.size() << " Tasks found\n";
        
        std::cout << "--------------------------------------------------------------------------------------\n";
        for (int i = 0; i < tasks.size(); i++) {                                                                    
            tasks[i].printTask();
        }
        std::cout << "--------------------------------------------------------------------------------------\n";
    }
}

   
// méthode pour supprimer une tâche avec son id
void delete_task(int id, std::vector<Task>& tasks) {
    if (check_id(id, tasks) == 1) {
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


// Méthodes d'assistance pour obtenir chaque élément (catégorie, priorité, champ, statut) sans duplication de code
Category c_input() {
    Category category;
    int c;

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

    return category;
}

Priority p_input() {
    Priority priority;
    int p;

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

    return priority;
}

Field f_input() {
    Field field = Field::title;
    int f;

    std::cout << "1. Title\n";
    std::cout << "2. Status\n";
    std::cout << "3. Priority\n";
    std::cout << "4. Category\n";
    std::cout << "votre choix: ";
    std::cin >> f;

    switch (f) {
    case 1: field = Field::title; break;
    case 2: field = Field::status; break;
    case 3: field = Field::priority; break;
    case 4: field = Field::category; break;
    default: field = Field::title; break;
    }

    return field;
}

Status s_input() {
    int choice;
    std::cout << "1. Afaire\n";
    std::cout << "2. EnCours\n";
    std::cout << "3. Terminee\n";
    std::cout << "votre choix: ";
    std::cin >> choice;

    switch (choice) {
        case 2:  return Status::EnCours;
        case 3:  return Status::Terminee;
        default: return Status::Afaire;
    }
}


// méthode de filtrage par (statut, priorité, catégorie)
void filter_by(Field field, std::vector<Task>& tasks) {
    bool found = false;
    switch (field) {
        case Field::category: {
            Category cat = c_input();

            for (int i = 0; i < tasks.size(); i++) {
                if (tasks[i].getCategory() == cat) {
                    tasks[i].printTask();
                    found = true;
                }
            }
            break;
        }
        case Field::priority: {

            Priority priority = p_input();

            for (int i = 0; i < tasks.size(); i++) {
                if (tasks[i].getPriority() == priority) {
                    tasks[i].printTask();
                    found = true;
                }
            }
            break;
        }
        case Field::status: {
            std::cout << "choisis la nouvelle status:\n";
            Status status = s_input();

            for (int i = 0; i < tasks.size(); i++) {
                if (tasks[i].getStatus() == status) {
                    tasks[i].printTask();
                    found = true;
                }
            }
            break;
        }
        
    }
    if (!found) {
        std::cout << "|----------------------|\n";
        std::cout << "|   No tasks to show   |\n";
        std::cout << "|----------------------|\n";
    }
}


// méthode pour modifier un champ de tâche (titre, statut, priorité, catégorie)
void modify_task(Field field, int id, std::vector<Task>& tasks) {
    int index = -1;
    if (check_id(id, tasks) == 1) {
        std::cout << "id pas disponible\n";
        return;
    }
    else {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].getId() == id) {
                index = i;
                break;
            }
        }
    }

    switch (field) {

        case Field::status: {
            Status s = s_input();

            tasks[index].SetStatus(s);

            std::cout << "Status changed Succesfully";
            break;

        }
        case Field::title: {
            std::string new_title;
            std::cout << "enter the new title: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, new_title);

            tasks[index].SetTitle(new_title);
            break;
        }
        case Field::priority: {
            std::cout << "choisis la nouvelle priority:\n";

            Priority p = p_input();

            tasks[index].SetPriority(p);

            std::cout << "Priority changed Succesfully";
            break;
        }
        case Field::category: {
            Category c = c_input();
            tasks[index].SetCategory(c);

            break;
        }
    }
        
}


// method to show tasks sorted by priority and time
void tasks_sorted(std::vector<Task> tasks) { 
    if (tasks.empty()) {
        std::cout << "|----------------------|\n";
        std::cout << "|   No tasks to show   |\n";
        std::cout << "|----------------------|\n";
        return;
    }

    // Sort the local copy 'tasks' not the main one
    std::sort(tasks.begin(), tasks.end(), [](Task& a, Task& b) {
        if (a.getPriority() != b.getPriority()) {
            return a.getPriority() > b.getPriority();
        }

        return a.getTime() < b.getTime();
     });

    std::cout << "\n--- TASKS SORTED BY PRIORITY AND TIME ---\n";
    for (auto& t : tasks) {
        t.printTask();
    }
    std::cout << "---------------------------------------\n";
}

// Méthode permettant d'exporter les tâches vers deux fichiers : un pour la consultation et l'autre à utiliser lors de la prochaine importation.
void export_tasks(std::vector<Task> tasks) {

    if (tasks.empty()) {
        std::cout << "|----------------------|\n";
        std::cout << "|  No tasks to export  |\n";
        std::cout << "|----------------------|\n";
        return;
    }


    // for viewing
    std::ofstream TaskFile("tasks.txt");
    for (int i = 0; i < tasks.size(); i++) {
        TaskFile << "id: " << tasks[i].getId()
            << " | [" << tasks[i].CategoryToString(tasks[i].getCategory()) << "]"
            << " | Task: " << tasks[i].getTitle()
            << " | Status: " << tasks[i].StatusToString(tasks[i].getStatus())
            << " | Priority: " << tasks[i].PriorityToString(tasks[i].getPriority()) << std::endl;
    }
    TaskFile.close();


    // for importing
    std::ofstream FormattedTaskFile("formated_tasks.txt");
    
    for (Task task : tasks) {
        FormattedTaskFile << task.getId() << ","
                        << task.getTitle() << ","
                        << static_cast<int>(task.getPriority()) << ","
                        << static_cast<int>(task.getStatus()) << ","
                        << static_cast<int>(task.getCategory()) << ","
                        << task.getTime() << std::endl;
    }

    FormattedTaskFile.close();

    std::cout << "Tasks Exported Succesfully";
}


// méthode pour importer des tâches à partir d'un fichier texte
void import_tasks(std::vector<Task>& tasks, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Recheck file name\n";
        return;
    }

    tasks.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> data;

        while (std::getline(ss, segment, ',')) {
            data.push_back(segment);
        }

        if (data.size() == 6) {
            // using custom constructor
            Task new_task(
                std::stoi(data[0]), // ID
                data[1],            // Title
                static_cast<Priority>(std::stoi(data[2])),
                static_cast<Status>(std::stoi(data[3])),
                static_cast<Category>(std::stoi(data[4])),
                data[5]             // Time
            );
            tasks.push_back(new_task);
        }
    }
    file.close();
    std::cout << "Tasks imported successfully\n";
}


// fonction principale contenant le menu de l'application
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
        std::cout << "|6. Filter By Field               |\n";
        std::cout << "|7. Sort tasks                    |\n";
        std::cout << "|8. Export tasks                  |\n";
        std::cout << "|9. Import tasks                  |\n";
        std::cout << "|10. Quitter                      |\n";
        std::cout << "|---------------------------------|\n";

        int choice;
        std::cout << "choissisez: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input! Please enter a number (1..10)\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue; 
        }


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

                priority = p_input();

                category = c_input();

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

                    Field field = f_input();

                    modify_task(field, id, tasks);
                }
                break;
            }
            case 5: {
                filter_by(Field::category, tasks);
                break;
            }
            case 6: {
                int choice;
                std::cout << "Which field u wanna filter with:\n";

                Field field = f_input();

                filter_by(field, tasks);

                break;
            }
            case 7: {
                tasks_sorted(tasks);
                break;
            }
            case 8: {
                export_tasks(tasks);
                break;
            }
            case 9: {
                std::string filename;
                std::cout << "enter the filename.txt: ";

                std::cin >> filename;

                import_tasks(tasks, filename);

                break;
                
            }
            case 10: {
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
