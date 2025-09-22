#include <iostream>
#include <string>
using namespace std;

class StudentCounter
{
    static int totalStudents;

public:
    static void increment() { totalStudents++; }
    static int getTotalStudents() { return totalStudents; }
};
int StudentCounter::totalStudents = 0;

class Task
{
    string title;
    int priority;

public:
    Task(string t = "Default Task", int p = 5)
    {
        title = t;
        priority = p;
    }
    void inputTask()
    {
        cout << "Enter Task Title: ";
        getline(cin, title);
        cout << "Enter Priority (1-10, default 5 if invalid): ";
        cin >> priority;
        if (priority < 1 || priority > 10)
            priority = 5;
        cin.ignore();
    }
    void displayTask() { cout << "Task: " << title << " (Priority: " << priority << ")\n"; }
    void operator++()
    {
        if (priority < 10)
            priority++;
    }
    friend void showTaskTitle(Task &t);
};
void showTaskTitle(Task &t) { cout << "[Friend] Task title: " << t.title << "\n"; }

class Subject
{
    string name;

public:
    Subject(string n = "Default Subject") { name = n; }
    void inputSubject()
    {
        cout << "Enter Subject Name: ";
        getline(cin, name);
    }
    void displaySubject() { cout << "Subject: " << name << "\n"; }
};

class Reminder
{
    string note;

public:
    void inputReminder()
    {
        cout << "Enter Reminder Note: ";
        getline(cin, note);
    }
    void displayReminder() { cout << "Reminder: " << note << "\n"; }
};

class Achievement
{
    string title;

public:
    Achievement(string t = "Default Achievement") { title = t; }
    void inputAchievement()
    {
        cout << "Enter Achievement Title: ";
        getline(cin, title);
    }
    void displayAchievement() { cout << "Achievement: " << title << "\n"; }
    Achievement operator+(Achievement &a) { return Achievement(title + " & " + a.title); }
};

class Progress
{
    int totalTasks;
    int doneTasks;
    float percent;

public:
    Progress(int t = 0, int d = 0)
    {
        totalTasks = t;
        doneTasks = d;
        percent = 0;
    }
    void inputProgress()
    {
        do
        {
            cout << "Enter Total Tasks: ";
            cin >> totalTasks;
            if (cin.fail() || totalTasks < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                totalTasks = -1;
            }
        } while (totalTasks < 0);

        do
        {
            cout << "Enter Completed Tasks (cannot exceed Total Tasks): ";
            cin >> doneTasks;
            if (cin.fail() || doneTasks < 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                doneTasks = -1;
            }
        } while (doneTasks < 0 || doneTasks > totalTasks);

        cin.ignore();
        percent = (totalTasks > 0) ? (doneTasks * 100.0f) / totalTasks : 0;
    }
    void displayProgress() { cout << "Progress: " << doneTasks << "/" << totalTasks << " (" << percent << "%)\n"; }
};

class User
{
protected:
    string name;
    int age;

public:
    void inputUser()
    {
        cout << "Enter Name: ";
        getline(cin, name);
        do
        {
            cout << "Enter Age (3-120): ";
            cin >> age;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                age = 0;
            }
        } while (age < 3 || age > 120);
        cin.ignore();
    }
    void displayUser() { cout << "Name: " << name << ", Age: " << age << "\n"; }
};

class StudentBase : public User
{
};
class StudentFinal : public StudentBase
{
protected:
    Task tasks[20];
    int taskCount;
    Subject subjects[10];
    int subjectCount;
    Reminder reminders[10];
    int reminderCount;
    Achievement achievements[10];
    int achievementCount;
    Progress progress;

public:
    StudentFinal()
    {
        taskCount = subjectCount = reminderCount = achievementCount = 0;
    }
    string getName() { return name; }
    void addTask()
    {
        if (taskCount < 20)
        {
            tasks[taskCount].inputTask();
            taskCount++;
        }
        else
            cout << "Task list full!\n";
    }
    void addSubject()
    {
        if (subjectCount < 10)
        {
            subjects[subjectCount].inputSubject();
            subjectCount++;
        }
        else
            cout << "Subject list full!\n";
    }
    void addReminder()
    {
        if (reminderCount < 10)
        {
            reminders[reminderCount].inputReminder();
            reminderCount++;
        }
        else
            cout << "Reminder list full!\n";
    }
    void addAchievement()
    {
        if (achievementCount < 10)
        {
            achievements[achievementCount].inputAchievement();
            achievementCount++;
        }
        else
            cout << "Achievement list full!\n";
    }
    void updateProgress() { progress.inputProgress(); }
    void showProfile()
    {
        displayUser();
        cout << "\n--- Subjects ---\n";
        for (int i = 0; i < subjectCount; i++)
            subjects[i].displaySubject();
        cout << "\n--- Tasks ---\n";
        for (int i = 0; i < taskCount; i++)
            tasks[i].displayTask();
        cout << "\n--- Reminders ---\n";
        for (int i = 0; i < reminderCount; i++)
            reminders[i].displayReminder();
        cout << "\n--- Achievements ---\n";
        for (int i = 0; i < achievementCount; i++)
            achievements[i].displayAchievement();
        cout << "\n--- Progress ---\n";
        progress.displayProgress();
    }
    void showTask(int i)
    {
        if (i >= 0 && i < taskCount)
            tasks[i].displayTask();
        else
            cout << "Invalid task index\n";
    }
    void showTask()
    {
        for (int i = 0; i < taskCount; i++)
            tasks[i].displayTask();
    }
    void incrementAllTasks()
    {
        for (int i = 0; i < taskCount; i++)
            ++tasks[i];
    }
    void combineAchievements(StudentFinal &s)
    {
        if (achievementCount > 0 && s.achievementCount > 0)
        {
            Achievement combined = achievements[0] + s.achievements[0];
            cout << "Combined Achievement: ";
            combined.displayAchievement();
        }
        else
            cout << "Not enough achievements to combine\n";
    }
};

class Academic
{
protected:
    string schoolName;

public:
    void inputAcademic()
    {
        cout << "Enter School/College Name: ";
        getline(cin, schoolName);
    }
    void displayAcademic() { cout << "School/College: " << schoolName << "\n"; }
};
class PersonalInfo
{
protected:
    string email;

public:
    void inputPersonal()
    {
        cout << "Enter Email: ";
        getline(cin, email);
    }
    void displayPersonal() { cout << "Email: " << email << "\n"; }
};
class MultiStudent : public Academic, public PersonalInfo, public StudentFinal
{
public:
    void inputMultiStudent()
    {
        inputUser();
        inputAcademic();
        inputPersonal();
    }
    void showMultiProfile()
    {
        displayAcademic();
        displayPersonal();
        showProfile();
    }
};

int main()
{
    MultiStudent students[20];
    int studentCount = 0, choice;

    do
    {
        cout << "\n===== StudyPhile Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Task to Student\n";
        cout << "3. Add Subject to Student\n";
        cout << "4. Add Reminder to Student\n";
        cout << "5. Add Achievement to Student\n";
        cout << "6. Update Progress of Student\n";
        cout << "7. Show One Student Profile\n";
        cout << "8. Show All Students\n";
        cout << "9. Increment all Task Priorities of a Student (++ operator)\n";
        cout << "10. Combine first achievements of two students (+ operator)\n";
        cout << "11. Show total students (static function)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            if (studentCount < 20)
            {
                students[studentCount].inputMultiStudent();
                studentCount++;
                StudentCounter::increment();
            }
            else
                cout << "Student list full!\n";
        }
        else if (choice >= 2 && choice <= 6)
        {
            if (studentCount == 0)
            {
                cout << "No students available!\n";
                continue;
            }
            cout << "Select student (0 to " << studentCount - 1 << "): ";
            int idx;
            cin >> idx;
            cin.ignore();
            if (idx < 0 || idx >= studentCount)
            {
                cout << "Invalid index\n";
                continue;
            }
            switch (choice)
            {
            case 2:
                students[idx].addTask();
                break;
            case 3:
                students[idx].addSubject();
                break;
            case 4:
                students[idx].addReminder();
                break;
            case 5:
                students[idx].addAchievement();
                break;
            case 6:
                students[idx].updateProgress();
                break;
            }
        }
        else if (choice == 7)
        {
            if (studentCount == 0)
            {
                cout << "No students available!\n";
                continue;
            }
            cout << "Select student (0 to " << studentCount - 1 << "): ";
            int idx;
            cin >> idx;
            cin.ignore();
            if (idx >= 0 && idx < studentCount)
                students[idx].showMultiProfile();
            else
                cout << "Invalid index\n";
        }
        else if (choice == 8)
        {
            for (int i = 0; i < studentCount; i++)
            {
                cout << "\nStudent " << i << ":\n";
                students[i].showMultiProfile();
            }
        }
        else if (choice == 9)
        {
            if (studentCount == 0)
            {
                cout << "No students available!\n";
                continue;
            }
            cout << "Select student: ";
            int idx;
            cin >> idx;
            cin.ignore();
            students[idx].incrementAllTasks();
            cout << "All task priorities incremented!\n";
        }
        else if (choice == 10)
        {
            if (studentCount < 2)
            {
                cout << "Need at least 2 students!\n";
                continue;
            }
            cout << "Select first student: ";
            int i1, i2;
            cin >> i1;
            cout << "Select second student: ";
            cin >> i2;
            cin.ignore();
            if (i1 >= 0 && i1 < studentCount && i2 >= 0 && i2 < studentCount)
                students[i1].combineAchievements(students[i2]);
            else
                cout << "Invalid indices\n";
        }
        else if (choice == 11)
        {
            cout << "Total Students: " << StudentCounter::getTotalStudents() << "\n";
        }
        else if (choice == 0)
            cout << "Exiting...\n";
        else
            cout << "Invalid choice!\n";
    } while (choice != 0);

    return 0;
}
