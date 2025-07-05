#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using namespace std;

class User {
public:
    string _name;
    string _login;
    string _pass;

    void load(ifstream& in) {
        getline(in, _name);
        getline(in, _login);
        getline(in, _pass);
    }

    void save(ofstream& out) const {
        out << _name << "\n" << _login << "\n" << _pass << "\n";
    }
};

class Message {
public:
    string _text;
    string _sender;
    string _receiver;

    void load(ifstream& in) {
        getline(in, _text);
        getline(in, _sender);
        getline(in, _receiver);
    }

    void save(ofstream& out) const {
        out << _text << "\n" << _sender << "\n" << _receiver << "\n";
    }
};

// Функция для установки прав доступа файла только для текущего пользователя
void setFilePermissions(const string& filename) {
    // Устанавливаем права rw для владельца, без прав для группы и остальных
    chmod(filename.c_str(), S_IRUSR | S_IWUSR);
}

int main() {
    vector<User> users;
    vector<Message> messages;

    // Файлы для хранения данных
    const string userFile = "users.txt";
    const string messageFile = "messages.txt";

    // Установка прав доступа к файлам перед чтением (чтобы только текущий пользователь мог читать)
    // Если файлы не существуют, создадим их
    ifstream infile;

    // Чтение пользователей
    infile.open(userFile);
    if (infile.is_open()) {
        while (!infile.eof()) {
            User u;
            u.load(infile);
            if (infile.fail()) break; // чтобы избежать пустых записей
            users.push_back(u);
        }
        infile.close();
    }
    setFilePermissions(userFile);

    // Чтение сообщений
    infile.open(messageFile);
    if (infile.is_open()) {
        while (!infile.eof()) {
            Message m;
            m.load(infile);
            if (infile.fail()) break;
            messages.push_back(m);
        }
        infile.close();
    }
    setFilePermissions(messageFile);

    // Здесь можно работать с объектами (например, добавлять, изменять)

    // Для примера добавим нового пользователя и сообщение
    User newUser{"John Doe", "johnd", "pass123"};
    users.push_back(newUser);

    Message newMessage{"Hello, World!", "johnd", "alice"};
    messages.push_back(newMessage);

    // Запись пользователей
    ofstream outfile(userFile);
    for (const auto& u : users) {
        u.save(outfile);
    }
    outfile.close();
    setFilePermissions(userFile);

    // Запись сообщений
    outfile.open(messageFile);
    for (const auto& m : messages) {
        m.save(outfile);
    }
    outfile.close();
    setFilePermissions(messageFile);

    return 0;
}
