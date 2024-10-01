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

void StartWorkShop(CompressorStation& station) {
    cout << "Работает " << station.active_workshops << " цехов из " << station.total_workshops << endl;
    int count;
    int delta;
    delta = station.total_workshops - station.active_workshops;

    if (delta == 0)
    {
        cout << "Все цеха уже работают" << endl;
        return;
    }

    do {
        cout << "Возможно запустить " << delta << " цехов. Введите число: ";
        count = GetNumInt();
    } while (count < 1 || count > delta);

    station.active_workshops += count;
    cout << count << " цехов начали работу. Теперь работают" << station.active_workshops << " цехов" << endl;
}

void StopWorkShop(CompressorStation & station) {
    cout << "Работает " << station.active_workshops << " цехов из " << station.total_workshops << endl;
    int count;

    if (station.active_workshops == 0) {
        cout << "Все цеха уже остановлены" << endl;
        return;
    }
    do {
        cout << "Возможно остановить " << station.active_workshops << " цехов. Введите число: ";
        count = GetNumInt();
    } while (count < 1 || count > station.active_workshops);

    station.active_workshops -= count;
    cout << count << " цехов остановлено" << endl;
}


void FileWritePipe(const Pipe& pipe, ofstream& out)
{
    out << "data Pipe:" << endl;
    out << pipe.label << endl;
    out << pipe.length << " " << pipe.diametr << " " << pipe.repair << endl;
}

void FileWriteStation(const CompressorStation& station, ofstream& out)
{
    out << "data Station:" << endl;
    out << station.name << endl;
    out << station.total_workshops << " " << station.active_workshops << " " << station.efficiency;
}

void FileLoadPipe(Pipe& pipe, ifstream& in) {
    if (in.is_open()) {
        getline(in >> ws, pipe.label);
        in >> pipe.length >> pipe.diametr >> pipe.repair;
        in.ignore();
        cout << "Данные из файла о трубе записаны" << endl;
    }
}

void FileLoadStation(CompressorStation& station, ifstream& in){
    if (in.is_open()) {
        getline(in >> ws, station.name);
        in >> station.total_workshops >> station.active_workshops >> station.efficiency;
        in.ignore();
        cout << "Данные из файла о КС записаны" << endl; 
    }
}


void FileWriteAll(const Pipe& pipe, const CompressorStation& station) {
    ofstream out;
    out.open("Data.txt");
    if (out.is_open())
    {
        if (pipe.label.empty() && station.name.empty()) {
            cout << "У вас нет данных для записи!" << endl;
        }
        else if (!pipe.label.empty() && !station.name.empty()) {
            FileWritePipe(pipe, out);
            FileWriteStation(station, out);
            cout << "Данные о КС и трубе записаны!" << endl;
        }
        if (!pipe.label.empty() && station.name.empty()) {
            FileWritePipe(pipe, out);
            cout << "Данные о трубе записаны!" << endl;
        }
        if (pipe.label.empty() && !station.name.empty()) {
            FileWriteStation(station, out);
            cout << "Данные о КС записаны!" << endl;
        }

    }
    out.close();
}

void FileLoadAll(Pipe& pipe, CompressorStation& station) {
    ifstream in("Data.txt");
    if (!in.is_open()) 
    {
        cout << "File not found" << endl;
        return;
    }

    string findle;
    while (getline(in >> ws, findle)) {
        if (findle == "data Pipe:") {
            FileLoadPipe(pipe, in);
        }
        if (findle == "data Station:") {
            FileLoadStation(station, in);
        }
       
    }
    in.close();
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
            //ОТРЕДАЧИТЬ НОРМАЛЬНО ЕСТЬ ИЛИ НЕТУ
                get_data(pipe);
                get_data(station);
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
            FileWriteAll(pipe, station);
            break;
        case 7:
            FileLoadAll(pipe, station);
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