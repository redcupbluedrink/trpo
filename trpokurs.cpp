#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <locale.h>
#include <iterator>
#include <algorithm>

using namespace std;

// Функция для генерации случайного пароля заданной длины
string generatePassword(int length) {

    setlocale(LC_ALL, "RU");

    string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*";  // Определяет набор символов для использования в пароле

    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Генерирование пароля
    string password = "";
    for (int i = 0; i < length; i++) {
        password += charset[rand() % charset.length()];
    }

    return password;
}

// Функция для проверки использовался ли пароль раньше
bool isPasswordUsed(string password, string file_name) {
    ifstream file(file_name);
    string line;
    while (getline(file, line)) {
        if (line == password) {
            return true;
        }
    }
    return false;
}

// Функция для добавления пароля в файл
void addUsedPassword(string username, string password, string file_name) {
    ofstream file(file_name, ios::app);
    file << "LOGIN : " << username << " " << "PASSWORD : " << password << endl;
}

void NewUsedPassword(string str, string password, string file_name) {
    ofstream file(file_name, ios::app);
    file << "LOGIN : " << str << " " << "NEWPASSWORD : " << password << endl;
}


void viewcontent() // Функция для просмотра файла
{
    string path = "used_passwords.txt";

    ifstream fin;
    fin.open(path);
    if (fin.is_open()) {
        cout << "\nUSED PASSWORDS : \n" << endl;
        char ch;
        while (fin.get(ch))
        {
            cout << ch;

        }
    }
    else {
        cout << "!!!Error!!!  File not open!" << endl;
    }
    fin.close();
}

int passchanger() { //Функция смены пароля
    string username;
    std::ifstream ifs("used_passwords.txt");
    cout << "Vvedite LOGIN: ";
    std::string str;
    std::cin >> str;
    using input_it = std::istream_iterator<std::string>;
    std::cout << std::boolalpha << (std::find(input_it(ifs), input_it(), str) != input_it());
    int length; // Длина пароля
    cout << "Vvedite dliny parolya: ";
    cin >> length;

    string password;  // Генерирует уникальный пароль
    do {
        password = generatePassword(length);
    } while (isPasswordUsed(password, "used_passwords.txt"));

    NewUsedPassword(str, password, "used_passwords.txt"); // Добавляет этот новый пароль в использованные

    return 0;
}

int deletepasswords() { //Функция удаления логина и пароля
   
        ifstream  in("used_passwords.txt", ios::in);
        ofstream out("passnews.txt", ios::out);
        char buff[256];
        int num, i;

        cout << "Nomer stroki: " << endl; cin >> num;
        i = 0;
        while (!in.eof()) {
            in.getline(buff, 255);
            if (i == num) break;
            out << buff << endl;
            i++;
        }
        while (!in.eof()) {
            in.getline(buff, 255);
            out << buff << endl;
        }
        out.close();
        in.close();
        cout << "\nDELETED!\n ";
        remove("used_passwords.txt");
        rename("passnews.txt", "used_passwords.txt");
        return 0;

}

int generator() {
    string username; // Название логина
    cout << "Vvedite USERNAME: ";
    cin >> username;
    int length; // Длина пароля
    cout << "Vvedite dliny parolya: ";
    cin >> length;

    string password;  // Генерирует уникальный пароль
    do {
        password = generatePassword(length);
    } while (isPasswordUsed(password, "used_passwords.txt"));

    addUsedPassword(username, password, "used_passwords.txt"); // Добавляет этот новый пароль в использованные

    return 0;
}

int main() {
    int x = 6;
    while (true) {
        if (x == 0) break;
        cout << "\n1 - Create login and generate password\n"
            "2 - View used logins and passwords\n"
            "3 - Change password for login\n"
            "4 - Delete login and password\n"
            "0 for exit\n\n";
        cin >> x;
        switch (x) {
        case 1:
            generator();
            break;
        case 2:
            viewcontent();
            break;
        case 3:
            passchanger();
            break;
        case 4:
            deletepasswords();
            break;
        case 0:
            break;
        default:
            cout << "x is undefined\n";
            break;
        }
    }
    return 0;
}
