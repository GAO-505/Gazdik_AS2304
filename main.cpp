#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Pipe {
    string label; // Кил отметка
    int length; // Длина трубы
    short diametr; // Диаметр трубы
    bool repair; // В ремонте или нет

    void set_data() { //Ввод данных
        cout << "Введите название трубы(Англ): ";
        cin >> label;
        cout << "Введите длину трубы: ";
        cin >> length;
        cout << "Введите диаметр трубы: ";
        cin >> diametr;
        cout << "Работает/Ремонтируется (Ввести 1 или 0): ";
        cin >> repair;
    }
    void get_data() { // Вывод данных
        cout << "\nНазвание трубы: " << label << endl;
        cout << "Длина трубы: " << length << endl;
        cout << "Диаметр трубы: " << diametr << endl;
        cout << "Состояние трубы: " << repair << endl;
    }
    void switch_status() { // Смена статуса ремонта
        repair = !repair;
        cout << "Состояние трубы изменено!" << endl;
    }
};

struct CompressorStation {
    string name; // Название станции
    int total_workshops; // Общее кол-во цехов
    int active_workshops; // кол-во Активных цехов
    float efficiency; // Эффективность

    void set_data() { // Ввод данных
        cout << "Введите название КС (Англ): ";
        cin >> name;
        cout << "Введите кол-во цехов КС: ";
        cin >> total_workshops;
        do {//проверка на реальность
            cout << "Введите кол-во активных цехов КС (<= общего кол-ва): ";
            cin >> active_workshops;
        } while (active_workshops > total_workshops);
        cout << "Эффективность КС (число): ";
        cin >> efficiency;
    }
    void get_data() { // Вывод данных
        cout << "\nНазвание КС: " << name << endl;
        cout << "Кол-во цехов КС: " << total_workshops << endl;
        cout << "Кол-во активных цехов КС: " << active_workshops << endl;
        cout << "Эффективность КС: " << efficiency << endl;
    }
    void StartWorkShop() {
        int count;
        do { 
            cout << "Сколько цехов запустить? (>0): ";
            cin >> count;
        } while (count < 1);

        if (active_workshops == total_workshops) {
            cout << "Все цеха уже работают" << endl;
        }
        else if (active_workshops + count > total_workshops) {
            active_workshops = total_workshops;
            cout << "Запуск всех цехов" << endl;
        }
        else if (active_workshops + count < total_workshops) {
            active_workshops += count;
            cout << count << " цехов начали работу" << endl;
        }
        
    }
    void StopWorkShop() {
        int count;
        do {
            cout << "Сколько цехов остановить? (>0): ";
            cin >> count;
        } while (count < 1);

        if (active_workshops == 0) {
            cout << "Все цеха уже остановлены" << endl;
        }
        else if (active_workshops - count > 0) {
            active_workshops -= count;
            cout << count << " цехов остановлено" << endl;
            
        }
        else if (active_workshops - count <= 0) {
            active_workshops = 0;
            cout << "Остановка всех цехов" << endl;
        }
    }
};

void FileWrite(Pipe & pipe, CompressorStation & station) {
    ofstream File("Data.txt", ios_base::out);
    if (File.is_open()) {
        File << pipe.label << " " << pipe.length << " " << pipe.diametr << " " << pipe.repair << "\n";
        File << station.name << " " << station.total_workshops << " " << station.active_workshops << " " << station.efficiency << "\n";
        File.close();
    }
    
    cout << "Data good";
}

void FileLoad(Pipe & pipe, CompressorStation & station) {
    ifstream File("Data.txt");
    if (File.is_open()) {
        File >> pipe.label >> pipe.length >> pipe.diametr >> pipe.repair;
        File >> station.name >> station.total_workshops >> station.active_workshops >> station.efficiency;
        File.close();
    }
}

// Главное меню программы
void menu() {
    Pipe pipe;
    CompressorStation station;
    bool pipeExists = false;
    bool stationExists = false;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить станцию\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Редактировать трубу (признак 'в ремонте')\n";
        cout << "5. Редактировать станцию (запуск/останов цеха)\n";
        cout << "6. Сохранить данные\n";
        cout << "7. Загрузить данные\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1:
            pipe.set_data();
            pipeExists = true;
            break;
        case 2:
            station.set_data();
            stationExists = true;
            break;
        case 3:
            if (pipeExists) pipe.get_data();
            else cout << "Труба не добавлена.\n";
            if (stationExists) station.get_data();
            else cout << "Станция не добавлена.\n";
            break;
        case 4:
            if (pipeExists) pipe.switch_status();
            else cout << "Труба не добавлена.\n";
            break;
        case 5:
            if (stationExists) {
                cout << "1. Запустить цех\n2. Остановить цех\n";
                int action;
                cin >> action;
                switch (action){
                case 1:
                    station.StartWorkShop();
                    break;
                case 2:
                    station.StopWorkShop();
                    break;
                default:
                    cout << "Команды не существует";
                    break;
                }
            }
            else cout << "Станция не добавлена.\n";
            break;
        case 6:
            if (pipeExists && stationExists) FileWrite(pipe, station);
            else cout << "Данные для сохранения неполные.\n";
            break;
        case 7:
            FileLoad(pipe, station);
            pipeExists = true;
            stationExists = true;
            break;
        case 0:
            cout << "Выход из программы.\n";
            return;
        default:
            cout << "Команды не существует. Попробуйте снова.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}