#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
class User {
public:
    string name;
    string password;

    User() = default;
    User(string name, string password) : name(name), password(password) {}

    bool checkPassword(const string& inputPassword) const {
        return password == inputPassword;
    }
};

class Chat {
private:
    map<string, User> users; // логин -> пользователь
    map<string, vector<string>> messages; // логин -> сообщения
    
public:
    void registerUser(const string& login, const string& name, const string& password) {
        if (users.find(login) == users.end()) {
            users[login] = User(name, password);
            cout << "Пользователь " << name << " успешно зарегистрирован!\n";
        } else {
            cout << "Пользователь с таким логином уже существует.\n";
        }
    }

    bool login(const string& login, const string& password) {
        if (users.find(login) != users.end()) {
            if (users[login].checkPassword(password)) {
                cout << "Добро пожаловать, " << users[login].name << "!\n";
                return true;
            } else {
                cout << "Неверный пароль.\n";
            }
        } else {
            cout << "Пользователь не найден.\n";
        }
        return false;
    }

    void sendMessageToUser(const string& fromLogin, const string& toLogin, const string& message) {
        if (users.find(toLogin) != users.end()) {
            messages[toLogin].push_back(users[fromLogin].name + " (личное): " + message);
            cout << "Сообщение отправлено пользователю " << users[toLogin].name << ".\n";
        } else {
            cout << "Получатель не найден.\n";
        }
    }

    void sendMessageToAll(const string& fromLogin, const string& message) {
        for (auto& [login, user] : users) {
            messages[login].push_back(users[fromLogin].name + " (всем): " + message);
        }
        cout << "Сообщение отправлено всем пользователям.\n";
    }

    void showMessages(const string& login) {
        if (messages.find(login) != messages.end()) {
            cout << "Сообщения для " << users[login].name << ":\n";
            for (const auto& msg : messages[login]) {
                cout << msg << '\n';
            }
        } else {
            cout << "Сообщений нет.\n";
        }
    }
};

int main() {
    Chat chat;
    int choice;
    string login, password, name, message, toLogin;

    while (true) {
        cout << "1. Регистрация\n";
        cout << "2. Вход\n";
        cout << "3. Отправить сообщение пользователю\n";
        cout << "4. Отправить сообщение всем\n";
        cout << "5. Показать сообщения\n";
        cout << "6. Выход\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите логин: ";
                cin >> login;
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите пароль: ";
                cin >> password;
                chat.registerUser(login, name, password);
                break;
            case 2:
                cout << "Введите логин: ";
                cin >> login;
                cout << "Введите пароль: ";
                cin >> password;
                chat.login(login, password);
                break;
            case 3:
                cout << "Введите логин отправителя: ";
                cin >> login;
                cout << "Введите логин получателя: ";
                cin >> toLogin;
                cin.ignore();
                cout << "Введите сообщение: ";
                getline(cin, message);
                chat.sendMessageToUser(login, toLogin, message);
                break;
            case 4:
                cout << "Введите логин отправителя: ";
                cin >> login;
                cin.ignore();
                cout << "Введите сообщение: ";
                getline(cin, message);
                chat.sendMessageToAll(login, message);
                break;
            case 5:
                cout << "Введите логин для просмотра сообщений: ";
                cin >> login;
                chat.showMessages(login);
                break;
            case 6:
                return 0;
            default:
                cout << "Неверный выбор.\n";
                break;
        }
    }
}
