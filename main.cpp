#include <iostream>
#include <string>
#include <fstream>


using namespace std;

int GetNumInt() {
    int num;
    while (true) {
        cin >> num;
        cout << "\n";
        if (cin.fail() || num <= 0 || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������ �����. ������� ������������� ����� �����: ";
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
            cout << "������ �����. ������� ������������� �����: ";
        }
        else {
            return num;
        }
    }
}

struct Pipe {
    string label; // ��� �������
    float length; // ����� �����
    int diametr; // ������� �����
    bool repair; // � ������� ��� ���
};

void set_data(Pipe &pipe) { //���� ������
    cout << "������� �������� �����(����): ";
    getline(cin >> ws, pipe.label);
    cout << "������� ����� �����: ";
    pipe.length = GetNumFloat();
    cout << "������� ������� �����: ";
    pipe.diametr = GetNumInt();
    pipe.repair = true;
}

void get_data(Pipe& pipe) { // ����� ������//!!!!!!!!!!!!!!!!!!
    if (pipe.length <= 0) {
        cout << "����� ���\n";
        return;
    }
    cout << "\n�������� �����: " << pipe.label << endl;
    cout << "����� �����: " << pipe.length << endl;
    cout << "������� �����: " << pipe.diametr << endl;
    if (pipe.repair) {//!!!!!!!!!!!!!!
        cout << "��������� �����: ��������" << endl;
    }
    else {
        cout << "��������� �����: � �������" << endl;
    }

}

void switch_status(Pipe& pipe) { // ����� ������� �������
    pipe.repair = !pipe.repair;
    cout << "��������� ����� ��������!" << endl;
}

struct CompressorStation {
    string name; // �������� �������
    int total_workshops; // ����� ���-�� �����
    int active_workshops; // ���-�� �������� �����
    float efficiency; // �������������
};

void set_data(CompressorStation &station) { // ���� ������
    cout << "������� �������� �� (����): ";
    getline(cin >> ws, station.name);
    cout << "������� ���-�� ����� ��: ";
    station.total_workshops = GetNumInt();
    do {//�������� �� ����������
        cout << "������� ���-�� �������� ����� �� (<= ������ ���-��): ";
        station.active_workshops = GetNumInt();
    } while (station.active_workshops > station.total_workshops);
    cout << "������������� �� (�����): ";
    station.efficiency = GetNumFloat();
}

void get_data(CompressorStation &station) { // ����� ������//!!!!!!!!!!!
    if (station.total_workshops <= 0) {
        cout << "������� ���\n";
        return;
    }
    cout << "\n�������� ��: " << station.name << endl;
    cout << "���-�� ����� ��: " << station.total_workshops << endl;
    cout << "���-�� �������� ����� ��: " << station.active_workshops << endl;
    cout << "������������� ��: " << station.efficiency << endl;
}

void StartWorkShop(CompressorStation& station) {
    cout << "�������� " << station.active_workshops << " ����� �� " << station.total_workshops << endl;
    int count;
    int delta;
    delta = station.total_workshops - station.active_workshops;

    if (delta == 0)
    {
        cout << "��� ���� ��� ��������" << endl;
        return;
    }

    do {
        cout << "�������� ��������� " << delta << " �����. ������� �����: ";
        count = GetNumInt();
    } while (count < 1 || count > delta);

    station.active_workshops += count;
    cout << count << " ����� ������ ������. ������ ��������" << station.active_workshops << " �����" << endl;
}

void StopWorkShop(CompressorStation & station) {
    cout << "�������� " << station.active_workshops << " ����� �� " << station.total_workshops << endl;
    int count;

    if (station.active_workshops == 0) {
        cout << "��� ���� ��� �����������" << endl;
        return;
    }
    do {
        cout << "�������� ���������� " << station.active_workshops << " �����. ������� �����: ";
        count = GetNumInt();
    } while (count < 1 || count > station.active_workshops);

    station.active_workshops -= count;
    cout << count << " ����� �����������" << endl;
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
        cout << "������ �� ����� � ����� ��������" << endl;
    }
}

void FileLoadStation(CompressorStation& station, ifstream& in){
    if (in.is_open()) {
        getline(in >> ws, station.name);
        in >> station.total_workshops >> station.active_workshops >> station.efficiency;
        cout << "������ �� ����� � �� ��������" << endl; 
    }
}


void FileWriteAll(const Pipe& pipe, const CompressorStation& station) {
    if (pipe.label.empty() && station.name.empty()) {
        cout << "� ��� ��� ������ ��� ������!" << endl;
        return;
    }
    ofstream out;
    out.open("Data.txt");
    if (out.is_open())
    {
        if (!pipe.label.empty()) {
            FileWritePipe(pipe, out);
            cout << "������ � ����� ��������!" << endl;
        }
        if (!station.name.empty()) {
            FileWriteStation(station, out);
            cout << "������ � �� ��������!" << endl;
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
    pipe = {};
    station = {};
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
        cout << "\n����:\n";
        cout << "1. �������� �����\n";
        cout << "2. �������� �������\n";
        cout << "3. �������� ���� ��������\n";
        cout << "4. ������������� ����� (������� '� �������')\n";
        cout << "5. ������������� ������� (������/������� ����)\n";
        cout << "6. ��������� ������\n";
        cout << "7. ��������� ������\n";
        cout << "8. �����\n";

        int choice;
        cout << "�������� �������� (������� �����): ";
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
                cout << "��� �����.\n";
            if (stationExists)
                get_data(station);
            else
                cout << "��� �������.\n";
            break;
        case 4:
            if (pipeExists) 
                switch_status(pipe);
            else 
                cout << "����� �� ���������.\n";
            break;
        case 5:
            if (stationExists) {
                cout << "1. ��������� ���\n2. ���������� ���\n";
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
                    cout << "������� �� ����������";
                    break;
                }
            }
            else
                cout << "������� �� ���������.\n";
            break;
        case 6:
            FileWriteAll(pipe, station);
            break;
        case 7:
            FileLoadAll(pipe, station);
            if (pipe.length < 0) {
                pipeExists = false;
            } else pipeExists = true;
            if (station.total_workshops < 0) {
                stationExists = false;
            } else stationExists = true;
            break;
        case 8:
            cout << "����� �� ���������.\n";
            return;
        default:
            cout << "������� �� ����������. ���������� �����.\n";
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}