#include <iostream>
#include <string>
#include <map>
#include <vector>

class User {
public:
    std::string name;
    std::string password;

    User() = default;
    User(std::string name, std::string password) : name(name), password(password) {}

    bool checkPassword(const std::string& inputPassword) const {
        return password == inputPassword;
    }
};

class Chat {
private:
    std::map<std::string, User> users; // логин -> пользователь
    std::map<std::string, std::vector<std::string>> messages; // логин -> сообщения
    
public:
    void registerUser(const std::string& login, const std::string& name, const std::string& password) {
        if (users.find(login) == users.end()) {
            users[login] = User(name, password);
            std::cout << "Пользователь " << name << " успешно зарегистрирован!\n";
        } else {
            std::cout << "Пользователь с таким логином уже существует.\n";
        }
    }

    bool login(const std::string& login, const std::string& password) {
        if (users.find(login) != users.end()) {
            if (users[login].checkPassword(password)) {
                std::cout << "Добро пожаловать, " << users[login].name << "!\n";
                return true;
            } else {
                std::cout << "Неверный пароль.\n";
            }
        } else {
            std::cout << "Пользователь не найден.\n";
        }
        return false;
    }

    void sendMessageToUser(const std::string& fromLogin, const std::string& toLogin, const std::string& message) {
        if (users.find(toLogin) != users.end()) {
            messages[toLogin].push_back(users[fromLogin].name + " (личное): " + message);
            std::cout << "Сообщение отправлено пользователю " << users[toLogin].name << ".\n";
        } else {
            std::cout << "Получатель не найден.\n";
        }
    }

    void sendMessageToAll(const std::string& fromLogin, const std::string& message) {
        for (auto& [login, user] : users) {
            messages[login].push_back(users[fromLogin].name + " (всем): " + message);
        }
        std::cout << "Сообщение отправлено всем пользователям.\n";
    }

    void showMessages(const std::string& login) {
        if (messages.find(login) != messages.end()) {
            std::cout << "Сообщения для " << users[login].name << ":\n";
            for (const auto& msg : messages[login]) {
                std::cout << msg << '\n';
            }
        } else {
            std::cout << "Сообщений нет.\n";
        }
    }
};

int main() {
    Chat chat;
    int choice;
    std::string login, password, name, message, toLogin;

    while (true) {
        std::cout << "1. Регистрация\n";
        std::cout << "2. Вход\n";
        std::cout << "3. Отправить сообщение пользователю\n";
        std::cout << "4. Отправить сообщение всем\n";
        std::cout << "5. Показать сообщения\n";
        std::cout << "6. Выход\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите логин: ";
                std::cin >> login;
                std::cout << "Введите имя: ";
                std::cin >> name;
                std::cout << "Введите пароль: ";
                std::cin >> password;
                chat.registerUser(login, name, password);
                break;
            case 2:
                std::cout << "Введите логин: ";
                std::cin >> login;
                std::cout << "Введите пароль: ";
                std::cin >> password;
                chat.login(login, password);
                break;
            case 3:
                std::cout << "Введите логин отправителя: ";
                std::cin >> login;
                std::cout << "Введите логин получателя: ";
                std::cin >> toLogin;
                std::cin.ignore();
                std::cout << "Введите сообщение: ";
                std::getline(std::cin, message);
                chat.sendMessageToUser(login, toLogin, message);
                break;
            case 4:
                std::cout << "Введите логин отправителя: ";
                std::cin >> login;
                std::cin.ignore();
                std::cout << "Введите сообщение: ";
                std::getline(std::cin, message);
                chat.sendMessageToAll(login, message);
                break;
            case 5:
                std::cout << "Введите логин для просмотра сообщений: ";
                std::cin >> login;
                chat.showMessages(login);
                break;
            case 6:
                return 0;
            default:
                std::cout << "Неверный выбор.\n";
                break;
        }
    }
}
