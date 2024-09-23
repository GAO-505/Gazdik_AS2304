#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Pipe {
    string label; // ��� �������
    int length; // ����� �����
    short diametr; // ������� �����
    bool repair; // � ������� ��� ���

    void set_data() { //���� ������
        cout << "������� �������� �����(����): ";
        cin >> label;
        cout << "������� ����� �����: ";
        cin >> length;
        cout << "������� ������� �����: ";
        cin >> diametr;
        cout << "��������/������������� (������ 1 ��� 0): ";
        cin >> repair;
    }
    void get_data() { // ����� ������
        cout << "\n�������� �����: " << label << endl;
        cout << "����� �����: " << length << endl;
        cout << "������� �����: " << diametr << endl;
        cout << "��������� �����: " << repair << endl;
    }
    void switch_status() { // ����� ������� �������
        repair = !repair;
        cout << "��������� ����� ��������!" << endl;
    }
};

struct CompressorStation {
    string name; // �������� �������
    int total_workshops; // ����� ���-�� �����
    int active_workshops; // ���-�� �������� �����
    float efficiency; // �������������

    void set_data() { // ���� ������
        cout << "������� �������� �� (����): ";
        cin >> name;
        cout << "������� ���-�� ����� ��: ";
        cin >> total_workshops;
        do {//�������� �� ����������
            cout << "������� ���-�� �������� ����� �� (<= ������ ���-��): ";
            cin >> active_workshops;
        } while (active_workshops > total_workshops);
        cout << "������������� �� (�����): ";
        cin >> efficiency;
    }
    void get_data() { // ����� ������
        cout << "\n�������� ��: " << name << endl;
        cout << "���-�� ����� ��: " << total_workshops << endl;
        cout << "���-�� �������� ����� ��: " << active_workshops << endl;
        cout << "������������� ��: " << efficiency << endl;
    }
    void StartWorkShop() {
        int count;
        do { 
            cout << "������� ����� ���������? (>0): ";
            cin >> count;
        } while (count < 1);

        if (active_workshops == total_workshops) {
            cout << "��� ���� ��� ��������" << endl;
        }
        else if (active_workshops + count > total_workshops) {
            active_workshops = total_workshops;
            cout << "������ ���� �����" << endl;
        }
        else if (active_workshops + count < total_workshops) {
            active_workshops += count;
            cout << count << " ����� ������ ������" << endl;
        }
        
    }
    void StopWorkShop() {
        int count;
        do {
            cout << "������� ����� ����������? (>0): ";
            cin >> count;
        } while (count < 1);

        if (active_workshops == 0) {
            cout << "��� ���� ��� �����������" << endl;
        }
        else if (active_workshops - count > 0) {
            active_workshops -= count;
            cout << count << " ����� �����������" << endl;
            
        }
        else if (active_workshops - count <= 0) {
            active_workshops = 0;
            cout << "��������� ���� �����" << endl;
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

// ������� ���� ���������
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
        cout << "0. �����\n";
        cout << "�������� ��������: ";

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
            else cout << "����� �� ���������.\n";
            if (stationExists) station.get_data();
            else cout << "������� �� ���������.\n";
            break;
        case 4:
            if (pipeExists) pipe.switch_status();
            else cout << "����� �� ���������.\n";
            break;
        case 5:
            if (stationExists) {
                cout << "1. ��������� ���\n2. ���������� ���\n";
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
                    cout << "������� �� ����������";
                    break;
                }
            }
            else cout << "������� �� ���������.\n";
            break;
        case 6:
            if (pipeExists && stationExists) FileWrite(pipe, station);
            else cout << "������ ��� ���������� ��������.\n";
            break;
        case 7:
            FileLoad(pipe, station);
            pipeExists = true;
            stationExists = true;
            break;
        case 0:
            cout << "����� �� ���������.\n";
            return;
        default:
            cout << "������� �� ����������. ���������� �����.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    menu();
    return 0;
}