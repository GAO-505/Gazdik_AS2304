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
    cin >> pipe.label;
    cout << "������� ����� �����: ";
    pipe.length = GetNumFloat();
    cout << "������� ������� �����: ";
    pipe.diametr = GetNumInt();
    pipe.repair = true;
}

void get_data(Pipe& pipe) { // ����� ������
    cout << "\n�������� �����: " << pipe.label << endl;
    cout << "����� �����: " << pipe.length << endl;
    cout << "������� �����: " << pipe.diametr << endl;
    if (pipe.repair) {
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
    cin >> station.name;
    cout << "������� ���-�� ����� ��: ";
    station.total_workshops = GetNumInt();
    do {//�������� �� ����������
        cout << "������� ���-�� �������� ����� �� (<= ������ ���-��): ";
        station.active_workshops = GetNumInt();
    } while (station.active_workshops > station.total_workshops);
    cout << "������������� �� (�����): ";
    station.efficiency = GetNumFloat();
}

void get_data(CompressorStation &station) { // ����� ������
    cout << "\n�������� ��: " << station.name << endl;
    cout << "���-�� ����� ��: " << station.total_workshops << endl;
    cout << "���-�� �������� ����� ��: " << station.active_workshops << endl;
    cout << "������������� ��: " << station.efficiency << endl;
}

void StartWorkShop(CompressorStation & station) {
    int count;
    do {
        cout << "������� ����� ���������? (>0): ";
        count = GetNumInt();
    } while (count < 1);

    if (station.active_workshops == station.total_workshops) {
        cout << "��� ���� ��� ��������" << endl;
    }
    else if (station.active_workshops + count > station.total_workshops) {
        station.active_workshops = station.total_workshops;
        cout << "������ ���� �����" << endl;
    }
    else if (station.active_workshops + count < station.total_workshops) {
        station.active_workshops += count;
        cout << count << " ����� ������ ������" << endl;
    }

}
void StopWorkShop(CompressorStation & station) {
    int count;
    do {
        cout << "������� ����� ����������? (>0): ";
        count = GetNumInt();
    } while (count < 1);

    if (station.active_workshops == 0) {
        cout << "��� ���� ��� �����������" << endl;
    }
    else if (station.active_workshops - count > 0) {
        station.active_workshops -= count;
        cout << count << " ����� �����������" << endl;

    }
    else if (station.active_workshops - count <= 0) {
        station.active_workshops = 0;
        cout << "��������� ���� �����" << endl;
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
                cout << "����� �� ���������.\n";
            if (stationExists) 
                get_data(station);
            else
                cout << "������� �� ���������.\n";
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
            if (pipeExists && stationExists)
                FileWrite(pipe, station);
            else 
                cout << "������ ��� ���������� ��������.\n";
            break;
        case 7:
            FileLoad(pipe, station);
            pipeExists = true;
            stationExists = true;
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