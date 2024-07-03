#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct User
{
    int id;
    string user_name;
    int password;
    string name;
    string email;
    bool is_AQ;

    User()
        : id(0)
        , password(0)
        , is_AQ(false)
    {}

    static map<int, User> read_users(const string& file_path)
    {
        map<int, User> users;
        ifstream file(file_path);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return users;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            User user;
            iss >> user.id >> user.user_name >> user.password >> user.name >>
                user.email >> user.is_AQ;
            users[user.id] = user;
        }
        file.close();
        return users;
    }

    static void write_user(const User& user, const string& file_path)
    {
        ofstream file(file_path, ios::app);
        if (file.is_open()) {
            file << user.id << " " << user.user_name << " " << user.password << " "
                << user.name << " " << user.email << " " << user.is_AQ << endl;
            file.close();
        }
        else {
            cerr << "Unable to open file: " << file_path << endl;
        }
    }
};

struct Question
{
    int from_id;
    int to_id;
    int id_question;
    string parent_question;
    string answer;
    bool is_parent;

    Question()
        : from_id(0)
        , to_id(0)
        , id_question(0)
        , is_parent(false)
    {}

    static vector<Question> read_questions(const string& file_path)
    {
        vector<Question> questions;
        ifstream file(file_path);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return questions;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            Question q;
            iss >> q.from_id >> q.to_id >> q.id_question >> q.is_parent;
            getline(iss, q.parent_question, '?');
            q.parent_question += '?';
            iss.ignore();
            getline(iss, q.answer);
            questions.push_back(q);
        }
        file.close();
        return questions;
    }

    static void write_question(const Question& question, const string& file_path)
    {
        ofstream file(file_path, ios::app);
        if (file.is_open()) {
            file << question.from_id << " " << question.to_id << " "
                << question.id_question << " " << question.is_parent << " "
                << question.parent_question << " " << question.answer << endl;
            file.close();
        }
        else {
            cerr << "Unable to open file: " << file_path << endl;
        }
    }

    static void delete_question(int question_id, const string& file_path)
    {
        vector<Question> questions = read_questions(file_path);
        ofstream file(file_path, ios::trunc);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return;
        }
        for (const auto& q : questions) {
            if (q.id_question != question_id) {
                file << q.from_id << " " << q.to_id << " " << q.id_question << " "
                    << q.is_parent << " " << q.parent_question << " " << q.answer
                    << endl;
            }
        }
        file.close();
    }

    static void delete_related_questions(int parent_question_id,
        const string& file_path)
    {
        vector<Question> questions = read_questions(file_path);
        ofstream file(file_path, ios::trunc);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return;
        }
        for (const auto& q : questions) {
            if (q.id_question != parent_question_id &&
                q.to_id != parent_question_id) {
                file << q.from_id << " " << q.to_id << " " << q.id_question << " "
                    << q.is_parent << " " << q.parent_question << " " << q.answer
                    << endl;
            }
        }
        file.close();
    }
};
struct ThreadQuestion
{
    int from_id;
    int to_id;
    int id_thread_question;
    string thread_question;
    string answer;

    ThreadQuestion()
        : from_id(0)
        , to_id(0)
        , id_thread_question(0)
    {}

    static vector<ThreadQuestion> read_thread_questions(const string& file_path)
    {
        vector<ThreadQuestion> thread_questions;
        ifstream file(file_path);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return thread_questions;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            ThreadQuestion tq;
            iss >> tq.from_id >> tq.to_id >> tq.id_thread_question;
            getline(iss, tq.thread_question, '?');
            tq.thread_question += '?';
            iss.ignore();
            getline(iss, tq.answer);
            thread_questions.push_back(tq);
        }
        file.close();
        return thread_questions;
    }

    static void write_thread_question(const ThreadQuestion& tq,
        const string& file_path)
    {
        ofstream file(file_path, ios::app);
        if (file.is_open()) {
            file << tq.from_id << " " << tq.to_id << " " << tq.id_thread_question
                << " " << tq.thread_question << " " << tq.answer << endl;
            file.close();
        }
        else {
            cerr << "Unable to open file: " << file_path << endl;
        }
    }

    static void delete_thread_questions(int parent_question_id,
        const string& file_path)
    {
        vector<ThreadQuestion> thread_questions = read_thread_questions(file_path);
        ofstream file(file_path, ios::trunc);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return;
        }
        for (const auto& tq : thread_questions) {
            if (tq.to_id != parent_question_id) {
                file << tq.from_id << " " << tq.to_id << " " << tq.id_thread_question
                    << " " << tq.thread_question << " " << tq.answer << endl;
            }
        }
        file.close();
    }

    static void delete_single_thread_question(int thread_question_id,
        const string& file_path)
    {
        vector<ThreadQuestion> thread_questions = read_thread_questions(file_path);
        ofstream file(file_path, ios::trunc);
        if (!file.is_open()) {
            cerr << "Unable to open file: " << file_path << endl;
            return;
        }
        for (const auto& tq : thread_questions) {
            if (tq.id_thread_question != thread_question_id) {
                file << tq.from_id << " " << tq.to_id << " " << tq.id_thread_question
                    << " " << tq.thread_question << " " << tq.answer << endl;
            }
        }
        file.close();
    }
};
struct System
{
    map<int, User> users;
    int current_user_id;

    System()
        : current_user_id(0)
    {
        users = User::read_users("users_info.txt");
    }

    void sign_up()
    {
        User newUser;
        newUser.id = (int)users.size() + 1;

        cout << "\nEnter user_name: ";
        cin >> newUser.user_name;
        cout << "\nEnter password: ";
        cin >> newUser.password;
        cout << "\nEnter name: ";
        cin >> newUser.name;
        cout << "\nEnter email: ";
        cin >> newUser.email;
        cout << "\nAllow anonymous questions? (0, 1): ";
        cin >> newUser.is_AQ;

        users[newUser.id] = newUser;
        User::write_user(newUser, "users_info.txt");

        cout << "User signed up successfully with ID: " << newUser.id << endl;
    }

    bool log_in()
    {
        string user_name;
        int password;

        cout << "\nEnter user name: ";
        cin >> user_name;
        cout << "\nEnter password: ";
        cin >> password;

        for (const auto& pair : users) {
            if (pair.second.user_name == user_name &&
                pair.second.password == password) {
                current_user_id = pair.second.id;
                cout << "Login successful!" << endl;
                return true;
            }
        }
        cout << "Login failed! User name or password is incorrect." << endl;
        return false;
    }

    void list_system_users()
    {
        for (const auto& pair : users) {
            cout << "ID: " << pair.first << "\t\tName: " << pair.second.name << endl;
        }
    }
};

struct Questions
{
    vector<Question> questions;
    vector<ThreadQuestion> thread_questions;

    Questions()
    {
        questions = Question::read_questions("questions_info.txt");
        thread_questions =
            ThreadQuestion::read_thread_questions("thread_question_info.txt");
    }

    void ask_question(int from_id)
    {
        User user;
        Question newQuestion;
        newQuestion.from_id = from_id;

        int user_id;
        cout << "\nEnter user id or -1 to cancel: ";
        cin >> user_id;

        if (user_id == -1)
            return;

        newQuestion.to_id = user_id;

        ofstream question_file("questions_info.txt", ios::app);
        ofstream thread_question_file("thread_question_info.txt", ios::app);

        int question_id;
        cout << "\nFor thread question: Enter Question id or -1 for new question: ";
        cin >> question_id;

        if (question_id == -1) {
            cout << "\nEnter your question: ";
            cin.ignore();
            getline(cin, newQuestion.parent_question);
            newQuestion.id_question = (int)questions.size() + 1;
            newQuestion.is_parent = true;
            questions.push_back(newQuestion);
            Question::write_question(newQuestion, "questions_info.txt");
        }
        else {
            string thread_question;
            cout << "\nEnter your thread question: ";
            cin.ignore();
            getline(cin, thread_question);

            ThreadQuestion threadQuestion;
            threadQuestion.from_id = from_id;
            threadQuestion.to_id = question_id;
            threadQuestion.thread_question = thread_question;
            threadQuestion.id_thread_question = (int)thread_questions.size() + 1;
            thread_questions.push_back(threadQuestion);
            ThreadQuestion::write_thread_question(threadQuestion,
                "thread_question_info.txt");
        }

        question_file.close();
        thread_question_file.close();
    }

    void answer_question(int user_id)
    {
        int question_id;
        cout << "\nEnter the question id you want to answer: ";
        cin >> question_id;

        string answer;
        cout << "\nEnter your answer: ";
        cin.ignore();
        getline(cin, answer);

        for (auto& q : questions) {
            if (q.id_question == question_id) {
                q.answer = answer;
            }
        }

        Question::delete_question(question_id, "questions_info.txt");
        for (const auto& q : questions) {
            Question::write_question(q, "questions_info.txt");
        }

        for (auto& tq : thread_questions) {
            if (tq.to_id == question_id) {
                tq.answer = answer;
            }
        }

        ThreadQuestion::delete_thread_questions(question_id,
            "thread_question_info.txt");
        for (const auto& tq : thread_questions) {
            ThreadQuestion::write_thread_question(tq, "thread_question_info.txt");
        }

        cout << "Answer submitted successfully." << endl;
    }

    void delete_question(int user_id, int question_id)
    {
        for (auto it = questions.begin(); it != questions.end(); ++it) {
            if (it->id_question == question_id && it->from_id == user_id) {
                questions.erase(it);
                Question::delete_question(question_id, "questions_info.txt");
                ThreadQuestion::delete_thread_questions(question_id,
                    "thread_question_info.txt");
                cout << "Question and its thread deleted successfully!" << endl;
                return;
            }
        }

        cout << "No matching question found or you don't have permission to delete "
            "this question."
            << endl;
    }

    void print_question_to_me()
    {
        for (const auto& q : questions) {
            cout << "Question ID: " << q.id_question
                << "   From User ID: " << q.from_id
                << "\t\tQuestion: " << q.parent_question << endl;
            cout << "\t- Answer: " << q.answer << endl;
            for (const auto& tq : thread_questions) {
                if (tq.to_id == q.id_question) {
                    cout << "Thread:  Question ID: " << tq.from_id
                        << "  From User ID: " << q.from_id
                        << "\t\tQuestion: " << tq.thread_question << endl;
                    cout << "\t- Thread:  Answer: " << tq.answer << endl;
                }
            }
        }
    }

    void print_question_from_me()
    {
        for (const auto& q : questions) {
            cout << "Question ID: " << q.id_question << "   to User ID: " << q.to_id
                << "\t\tQuestion: " << q.parent_question;
            cout << "\t- Answer: " << q.answer << endl;
        }
    }

    void list_feed(int user_id)
    {
        cout << "\nFeed for User ID: " << user_id << endl;
        for (const auto& q : questions) {
            if (q.from_id == user_id || q.to_id == user_id) {
                cout << "Question ID: " << q.id_question << endl;
                cout << "From User ID: " << q.from_id << endl;
                cout << "To User ID: " << q.to_id << endl;
                cout << "Question: " << q.parent_question << endl;
                cout << "Answer: " << q.answer << endl;
                cout << "-----------------------------------" << endl;
            }
        }
        for (const auto& tq : thread_questions) {
            if (tq.from_id == user_id || tq.to_id == user_id) {
                cout << "Thread Question: " << tq.thread_question << endl;
                cout << "From User ID: " << tq.from_id << endl;
                cout << "To User ID: " << tq.to_id << endl;
                cout << "Answer: " << tq.answer << endl;
                cout << "-----------------------------------" << endl;
            }
        }
    }
};

static void print_menu()
{
    cout << "\nLogged In Menu:\n";
    cout << "1. Print Question to me.\n";
    cout << "2. Print Question from me.\n";
    cout << "3. Answer Question.\n";
    cout << "4. Ask Question.\n";
    cout << "5. Delete Question.\n";
    cout << "6. List System users.\n";
    cout << "7. Feed\n";
    cout << "8. Log Out\n";
    cout << "Enter your choice: ";
}

static void run()
{
    System system;
    Questions question_system;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.sign_up();

            int sub_choice;
            do {
                print_menu();
                cin >> sub_choice;

                switch (sub_choice) {
                case 1:
                    question_system.print_question_to_me();
                    break;
                case 2:
                    question_system.print_question_from_me();
                    break;
                case 3:
                    question_system.answer_question(system.current_user_id);
                    break;
                case 4:
                    question_system.ask_question(system.current_user_id);
                    break;
                case 5:
                    int question_id;
                    cout << "Enter the question ID you want to delete: ";
                    cin >> question_id;
                    question_system.delete_question(system.current_user_id,
                        question_id);
                    break;
                case 6:
                    system.list_system_users();
                    break;
                case 7:
                    question_system.list_feed(system.current_user_id);
                case 8:
                    cout << "Logged out." << endl;
                    break;
                default:
                    cout << "Invalid choice....Try again." << endl;
                    break;
                }
            } while (sub_choice != 8);

            break;

        case 2:
            system.log_in();

            do {
                print_menu();
                cin >> sub_choice;

                switch (sub_choice) {
                case 1:
                    question_system.print_question_to_me();
                    break;
                case 2:
                    question_system.print_question_from_me();
                    break;
                case 3:
                    question_system.answer_question(system.current_user_id);
                    break;
                case 4:
                    question_system.ask_question(system.current_user_id);
                    break;
                case 5:
                    int question_id;
                    cout << "Enter the question ID you want to delete: ";
                    cin >> question_id;
                    question_system.delete_question(system.current_user_id,
                        question_id);
                    break;
                case 6:
                    system.list_system_users();
                    break;
                case 7:
                    question_system.list_feed(system.current_user_id);
                case 8:
                    cout << "Logged out." << endl;
                    break;
                default:
                    cout << "Invalid choice....Try again." << endl;
                    break;
                }
            } while (sub_choice != 8);

        case 3:
            exit(0);
            break;

        default:
            cout << "Invalid choice....Try again." << endl;
            break;
        }
    } while (choice != 2);
}

int main()
{

    run();
    return 0;
}
