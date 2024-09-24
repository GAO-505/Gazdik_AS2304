#include <iostream>
#include <string>
#include <fstream>


using namespace std;

int GetNumInt() {
    int num;
    while (true) {
        cin >> num;
        cout << "\n";
        if (cin.fail() || num <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите положительное целое число: ";
        }
        else {
            return num;
        }
    }
}

float GetNumFloat() {
    float num;
    while (true) {
        cin >> num;
        cout << "\n";
        if (cin.fail() || num <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите положительное число: ";
        }
        else {
            return num;
        }
    }
}

struct Pipe {
    string label; // Кил отметка
    float length; // Длина трубы
    int diametr; // Диаметр трубы
    bool repair; // В ремонте или нет
};

void set_data(Pipe &pipe) { //Ввод данных
    cout << "Введите название трубы(Англ): ";
    cin >> pipe.label;
    cout << "Введите длину трубы: ";
    pipe.length = GetNumFloat();
    cout << "Введите диаметр трубы: ";
    pipe.diametr = GetNumInt();
    pipe.repair = true;
}

void get_data(Pipe& pipe) { // Вывод данных
    cout << "\nНазвание трубы: " << pipe.label << endl;
    cout << "Длина трубы: " << pipe.length << endl;
    cout << "Диаметр трубы: " << pipe.diametr << endl;
    if (pipe.repair) {
        cout << "Состояние трубы: Работает" << endl;
    }
    else {
        cout << "Состояние трубы: В ремонте" << endl;
    }

}

void switch_status(Pipe& pipe) { // Смена статуса ремонта
    pipe.repair = !pipe.repair;
    cout << "Состояние трубы изменено!" << endl;
}

struct CompressorStation {
    string name; // Название станции
    int total_workshops; // Общее кол-во цехов
    int active_workshops; // кол-во Активных цехов
    float efficiency; // Эффективность
};

void set_data(CompressorStation &station) { // Ввод данных
    cout << "Введите название КС (Англ): ";
    cin >> station.name;
    cout << "Введите кол-во цехов КС: ";
    station.total_workshops = GetNumInt();
    do {//проверка на реальность
        cout << "Введите кол-во активных цехов КС (<= общего кол-ва): ";
        station.active_workshops = GetNumInt();
    } while (station.active_workshops > station.total_workshops);
    cout << "Эффективность КС (число): ";
    station.efficiency = GetNumFloat();
}

void get_data(CompressorStation &station) { // Вывод данных
    cout << "\nНазвание КС: " << station.name << endl;
    cout << "Кол-во цехов КС: " << station.total_workshops << endl;
    cout << "Кол-во активных цехов КС: " << station.active_workshops << endl;
    cout << "Эффективность КС: " << station.efficiency << endl;
}

void StartWorkShop(CompressorStation & station) {
    int count;
    do {
        cout << "Сколько цехов запустить? (>0): ";
        count = GetNumInt();
    } while (count < 1);

    if (station.active_workshops == station.total_workshops) {
        cout << "Все цеха уже работают" << endl;
    }
    else if (station.active_workshops + count > station.total_workshops) {
        station.active_workshops = station.total_workshops;
        cout << "Запуск всех цехов" << endl;
    }
    else if (station.active_workshops + count < station.total_workshops) {
        station.active_workshops += count;
        cout << count << " цехов начали работу" << endl;
    }

}
void StopWorkShop(CompressorStation & station) {
    int count;
    do {
        cout << "Сколько цехов остановить? (>0): ";
        count = GetNumInt();
    } while (count < 1);

    if (station.active_workshops == 0) {
        cout << "Все цеха уже остановлены" << endl;
    }
    else if (station.active_workshops - count > 0) {
        station.active_workshops -= count;
        cout << count << " цехов остановлено" << endl;

    }
    else if (station.active_workshops - count <= 0) {
        station.active_workshops = 0;
        cout << "Остановка всех цехов" << endl;
    }
}

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
        cout << "8. Выход\n";

        int choice;
        cout << "Выберите действие (введите число): ";
        choice = GetNumInt();
        cout << "\n";

        switch (choice) {
        case 1:
            set_data(pipe);
            pipeExists = true;
            break;
        case 2:
            set_data(station);
            stationExists = true;
            break;
        case 3:
            if (pipeExists) 
                get_data(pipe);
            else
                cout << "Труба не добавлена.\n";
            if (stationExists) 
                get_data(station);
            else
                cout << "Станция не добавлена.\n";
            break;
        case 4:
            if (pipeExists) 
                switch_status(pipe);
            else 
                cout << "Труба не добавлена.\n";
            break;
        case 5:
            if (stationExists) {
                cout << "1. Запустить цех\n2. Остановить цех\n";
                int action;
                action = GetNumInt();
                switch (action){
                case 1:
                    StartWorkShop(station);
                    break;
                case 2:
                    StopWorkShop(station);
                    break;
                default:
                    cout << "Команды не существует";
                    break;
                }
            }
            else
                cout << "Станция не добавлена.\n";
            break;
        case 6:
            if (pipeExists && stationExists)
                FileWrite(pipe, station);
            else 
                cout << "Данные для сохранения неполные.\n";
            break;
        case 7:
            FileLoad(pipe, station);
            pipeExists = true;
            stationExists = true;
            break;
        case 8:
            cout << "Выход из программы.\n";
            return;
        default:
            cout << "Команды не существует. Попробуйте снова.\n";
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}