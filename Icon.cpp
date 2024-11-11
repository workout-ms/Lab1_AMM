#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum TariffType 
{
    LOCAL = 1,
    LONG_DISTANCE = 2,
    INTERNATIONAL = 3
};

bool isValidNumber( string& input) 
{
    for (char c : input) 
    {
        if (!isdigit(c)) 
        {
            cout << "Ошибка: ввод должен состоять только из цифр." << endl;
            return false;
        }
    }
    return true;
}


string tariffTypeToString(TariffType type)
{
    switch (type) 
    {
    case LOCAL: return "Местный";
    case LONG_DISTANCE: return "Междугородний";
    case INTERNATIONAL: return "Международный";
    default: return "Неизвестный тип";
    }
}


class Tariff
{
private:
    string destination;  
    double price;        
    TariffType type;    
public:
    Tariff(string dest, double pr, TariffType tp) : destination(dest), price(pr), type(tp) {}

    string getDest() 
    {
        return destination;
    }

    double getPrice() 
    {
        return price;
    }

    string getType() 
    {
        return tariffTypeToString(type);
    }
};


class Client 
{
private:
    string lastName;    
    vector<pair<Tariff, double>> calls; 
public:
    Client(string name) : lastName(name) {}

    
    void addCall(Tariff tariff, double duration)
    {
        calls.push_back(make_pair(tariff, duration));
    }

    
    double calculateTotal()
    {
        double total = 0;
        for (auto& call : calls) 
        {
            total += call.first.getPrice() * call.second; 
        }
        return total;
    }

    string getLastName() 
    {
        return lastName;
    }

    vector<pair<Tariff, double>> getCalls()
    {
        return calls;
    }
};


class ATC 
{
private:
    vector<Tariff> tariffs;       
    vector<Client> clients;        
    double totalRevenue = 0;       
    static ATC* instancePtr;
    ATC() {}
public:
    ATC(const ATC* obj) = delete;

    static ATC* getInstance() 
    {
        if (instancePtr == nullptr) 
        {
            instancePtr = new ATC;
        }
        return instancePtr;
    }

 
    void addTariff(string destination, double price, TariffType type)
    {
        tariffs.push_back(Tariff(destination, price, type));
    }


    void registerCall(string lastName, string destination, double duration, TariffType type) 
    {
        Client* client = findClient(lastName);
        Tariff* tariff = findTariff(destination, type);
        if (tariff != nullptr)
        {
            if (client == nullptr) 
            {
                
                clients.push_back(Client(lastName));
                client = &clients.back();
            }
            client->addCall(*tariff, duration);
            totalRevenue += tariff->getPrice() * duration;
            cout << "Звонок на " << destination << " для клиента " << lastName << " успешно зарегистрирован."<<endl;
        }
        else 
        {
            cout << "Тариф на " << destination << " не найден для типа звонка"<<endl;
        }
    }

   
    double calculateTotalRevenue()
    {
        return totalRevenue;
    }

    
    Client* findClient(string lastName) 
    {
        for (auto& client : clients)
        {
            if (client.getLastName() == lastName)
            {
                return &client;
            }
        }
        return nullptr;
    }

    
    Tariff* findTariff(string destination, TariffType type) 
    {
        for (auto& tariff : tariffs)
        {
            if (tariff.getDest() == destination && tariff.getType() == tariffTypeToString(type))
            {
                return &tariff;
            }
        }
        return nullptr;
    }

   
    void printTariffs() {
        cout << "Список тарифов:" << endl;
        for (auto& tariff : tariffs)
        {
            cout << "Туда куда должны позвонить: " << tariff.getDest() << ", Цена: " << tariff.getPrice() << " руб./мин, Класс: " << tariff.getType() << endl;
        }
    }

   
    void printClientCalls(string lastName) 
    {
        Client* client = findClient(lastName);
        if (client != nullptr)
        {
            cout << "Звонки клиента " << lastName << ":\n";
            for (auto& call : client->getCalls())
            {
                cout << "Туда куда мы позвонили: " << call.first.getDest() << ", Длительность: " << call.second << " мин, Стоимость: " << call.first.getPrice() * call.second << " руб."<<endl;
            }
            cout << "Общая стоимость звонков: " << client->calculateTotal() << " руб."<<endl;
        }
        else 
        {
            cout << "Клиент с фамилией " << lastName << " не найден."<<endl;
        }
    }

    ~ATC()
    {
        tariffs.clear();
        clients.clear();
    }
};

ATC* ATC::instancePtr = nullptr;

int main() 
{
    setlocale(LC_ALL, "RU");

    string command;
    do
    {
        cout << "Список команд:" << endl
            << "1 - Добавить тариф" << endl
            << "2 - Вывести список тарифов" << endl
            << "3 - Зарегистрировать звонок" << endl
            << "4 - Вывести информацию о клиенте" << endl
            << "5 - Рассчитать общую стоимость всех звонков" << endl
            << "6 - Завершить работу" << endl;
        cout << "Введите команду: ";
        cin >> command;
        cout << "\n";
        if (!(command == "1" || command == "2" || command == "3" || command == "4" || command == "5" || command == "6")) cout << "Неправильная команда" << endl;

        else if (command == "1") 
        {
            ATC* office = ATC::getInstance();
            string dest, prc, tup;
            TariffType type;
            cout << "Туда куда должны позвонить" << endl;
            cin >> dest;
            do 
            {
                cout << "Введите цену за минуту" << endl;
                cin >> prc;
            } while (!isValidNumber(prc));
            do 
            {
                cout << "Выберите тип тарифа (1 - местный, 2 - междугородний, 3 - международный)" << endl;
                cin >> tup;
            } while (!(tup == "1" || tup == "2" || tup == "3"));

            if (tup == "1")
                type = LOCAL;
            else if (tup == "2") 
                type = LONG_DISTANCE;
            else 
                type = INTERNATIONAL;

            office->addTariff(dest, stod(prc), type);
        }

        else if (command == "2")
        {
            ATC* office = ATC::getInstance();
            office->printTariffs();
        }

        else if (command == "3") 
        {
            ATC* office = ATC::getInstance();
            string lastName, destin;
            double duration;
            TariffType type;
            string tup;

            cout << "Куда мы звоним?" << endl;
            cin >> destin;

            do 
            {
                cout << "Длительность звонка (в минутах)" << endl;
                cin >> duration;
            } while (duration <= 0);

            cout << "Фамилия клиента" << endl;
            cin >> lastName;

            do
            {
                cout << "Выберите тип звонка (1 - местный, 2 - междугородний, 3 - международный)" << endl;
                cin >> tup;
            } while (!(tup == "1" || tup == "2" || tup == "3"));
            if (tup == "1") 
                type = LOCAL;
            else if (tup == "2") 
                type = LONG_DISTANCE;
            else 
                type = INTERNATIONAL;
            office->registerCall(lastName, destin, duration, type);
        }

        else if (command == "4")
        {
            ATC* office = ATC::getInstance();
            string lastName;
            cout << "Фамилия клиента" << endl;
            cin >> lastName;
            office->printClientCalls(lastName);
        }

        else if (command == "5") 
        {
            ATC* office = ATC::getInstance();
            cout << "Общая сумма всех звонков: " << office->calculateTotalRevenue() << " руб."<<endl;
        }

    } while (command != "6");
    cout << "Наконец-то" << endl;

    return 0;
}