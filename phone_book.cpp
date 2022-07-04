#include <iostream>
#include <cstring>
#include <limits> 
using namespace std;


struct Subscriber {

    void repr(){
        cout << this->name << "\t" << this->phone << "\t\t" << this->year << endl;
    }

    char name[25];
    unsigned year;
    char phone[7];
};


Subscriber* addStruct(Subscriber * subscribers, unsigned * count){
    (*count)++;
	if (*count == 1){		
		subscribers = new Subscriber[*count];
	} else {
		Subscriber* tempSubscribers = new Subscriber[*count];

		for (int i = 0; i < *count; i++){
			tempSubscribers[i] = subscribers[i];
		}
		delete [] subscribers;
		subscribers = tempSubscribers;		
    }			
	return subscribers;
}


void setData(Subscriber * subscribers, unsigned count){
    count--;
    cout << "Фамилия: ";
    cin >> subscribers[count].name;
    cout << "Год установки телефона: ";
    cin >> subscribers[count].year;
    while (cin.fail()){
        cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> subscribers[count].year;
    }
    cout << "Номер телефона: ";
    cin >> subscribers[count].phone;
    cout << endl;
}


void showData(Subscriber * subscribers, unsigned count, char const name[25] = ""){
	if (count > 0) {
        cout << endl << "=============================================" << endl;
        cout << "№\t" << "Фамилия\t" << "Номер телефона\t" << "Год установки" << endl;
        cout << "=============================================" << endl;
        for (int i = 0; i < count; i++){	
            if (name == "" || strcmp(subscribers[i].name, name) == 0){
                cout << i + 1 << "\t";
                subscribers[i].repr();
            }
        }
        cout << "=============================================" << endl;
        cout << endl;
    } else {
        cout << "Справочник пуст" << endl;
    }
}


void countData(Subscriber * subscribers, unsigned count, unsigned year){
    if (count > 0) {
        int number = 0;
        for (int i = 0; i < count; i++){	
            if (subscribers[i].year >= year) number++;
        }
        cout << endl << "Количество установленных телефонов начиная с " << year << " года: " << number << endl;
        cout << endl;
    } else {
        cout << "Справочник пуст" << endl;
    }
}


Subscriber * removeData(Subscriber * subscribers, unsigned * count, char phone_number[]){
    if (*count == 0) {
        cout << "Справочник пуст" << endl;
        return subscribers;
    }
    bool is_found = false;
    for (int i = 0; i < *count; i++){
        if (strcmp(subscribers[i].phone, phone_number) == 0){
            (*count)--;
            if (*count == 0) {
                delete [] subscribers;
                subscribers = 0;
            } else {
                subscribers[i] = subscribers[*count];
                Subscriber* tempSubscribers = new Subscriber[*count];
                for (int i = 0; i < *count; i++){
                    tempSubscribers[i] = subscribers[i];
                }
                delete [] subscribers;
                subscribers = tempSubscribers;
            }
            cout << "Абонент удален из справочника" << endl;
            is_found = true;
            break;
        }
    }
    if (!is_found) {
        cout << "В справочнике отсутсвуют абоненты с таким номером телефона" << endl;
    }
    return subscribers;
}

int editData(Subscriber * subscribers, unsigned count, char phone_number[]){
    if (count == 0) {
        cout << "Справочник пуст" << endl;
        return 0;
    }
    bool is_found = false;
    for (int i = 0; i < count; i++){
        if (strcmp(subscribers[i].phone, phone_number) == 0){
            int field = 0;
            cout << "Выберите поле для редактирования (1 - фамилия, 2 - год установки телефона, 3 - номер телефона): ";
            cin >> field;
            while (cin.fail()){
                cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введено неверное значение. Повторите ввод: ";
                cin >> field;
            }
            cout << "Введите новое значение для выбранного поля: ";
            if (field == 1) {
                cin >> subscribers[i].name;
            } else if (field == 2) {
                cin >> subscribers[i].year;
                while (cin.fail()){
                    cin.clear();
                    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Введено неверное значение. Повторите ввод: ";
                    cin >> subscribers[i].year;
                }
            } else if (field == 3) {
                cin >> subscribers[i].phone;
            } else {
                cout << "Введено неверное значение" << endl;
            }
            is_found = true;
            break;
        }
    }
    if (!is_found) {
        cout << "В справочнике отсутсвуют абоненты с таким номером телефона" << endl;
    }
    return 0;
}

void sortData(Subscriber * subscribers, unsigned count){
    if (count > 1){
        Subscriber tmp;
        for(int i = 0; i < count - 1; ++i){            
            for(int j = 0; j < count - 1; ++j){     
                if (subscribers[j + 1].year < subscribers[j].year) 
                {
                    tmp = subscribers[j + 1];
                    subscribers[j + 1] = subscribers[j];
                    subscribers[j] = tmp;
                }
            }
        }
    }
}


int dumpData(Subscriber * subscribers, unsigned count, char file_name[]){
    strcat(file_name, ".dat");
    FILE * file;
    file=fopen(file_name, "wb");
    if (file == 0){
        cout << "Ошибка при открытии файла" << endl;
        return 10;
    }
    fputc(count, file);
    fwrite(subscribers, sizeof(Subscriber), count, file);
    cout<< "Данные успешно записаны в файл" <<endl;
    fclose(file);
    return 0;
}

Subscriber * loadData(Subscriber * subscribers, char file_name[], unsigned * count){
    strcat(file_name, ".dat");
    FILE * file;
    file=fopen(file_name, "rb");
    if (file == 0){
        cout << "Файл с таким именем не найден" << endl;
        return subscribers;
    }
    *count = fgetc(file);
    subscribers = new Subscriber[*count];
    fread(subscribers, sizeof(Subscriber), *count, file);
    cout<< "Данные успешно загружены из файла" <<endl;
    fclose(file);
    return subscribers;
}


int main() {

    Subscriber *subscribersArray = 0;
    unsigned subscribersCount = 0;

    while (true)
    {
        cout << "**********************************************************" << endl;
        cout << "***********************Главное меню***********************" << endl;
        cout << "1. Добавление абонента" << endl;
        cout << "2. Вывод списка абонентов" << endl;
        cout << "3. Удаление абонента по номеру телефона" << endl;
        cout << "4. Поиск номеров по фамилии" << endl;
        cout << "5. Редактирование абонента по номеру телефона" << endl;
        cout << "6. Сохранить справочник в файл" << endl;
        cout << "7. Загрузить справочник из файла" << endl;
        cout << "8. Вывести количество установленных телефонов с ХХХХ года" << endl;
        cout << "**********************************************************" << endl;

        char action;
		cin >> action;

		switch (action){
		case '1': {
            int continueInput = 0;
            do {
                if (subscribersCount >= 20){
                    cout << "В справочнике 20 записей" << endl;
                    break;
                }
                subscribersArray = addStruct(subscribersArray, &subscribersCount);
                setData(subscribersArray, subscribersCount);
                // subscribersCount++;
                if (subscribersCount <= 20) {
                    cout << "Продолжить ввод данных (1 - да, 0 - нет): " ;
                    cin >> continueInput;
                    while (cin.fail()){
                        cin.clear();
                        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Введено неверное значение. Повторите ввод: ";
                        cin >> continueInput;
                    }
                }
            } while (continueInput != 0);
            break;
        }
		case '2': {
            sortData(subscribersArray, subscribersCount);
            showData(subscribersArray, subscribersCount);
            break;
        }
		case '3': {
            char phone_number[7];
            cout << "Введите номер телефона абонента: ";
            cin >> phone_number;
            subscribersArray = removeData(subscribersArray, &subscribersCount, phone_number);
            break;
        }
        case '4': {
            char last_name[7];
            cout << "Введите фамилию абонента: ";
            cin >> last_name;
            showData(subscribersArray, subscribersCount, last_name);
            // subscribersArray = removeData(subscribersArray, &subscribersCount, phone_number);
            break;
        }
        case '5': {
            char phone_number[7];
            cout << "Введите номер телефона абонента: ";
            cin >> phone_number;
            editData(subscribersArray, subscribersCount, phone_number);
            break;
        }
        case '6': {
            char file_name[25];
            cout << "Введите имя файла: ";
            cin >> file_name;
            dumpData(subscribersArray, subscribersCount, file_name);
            break;
        }
        case '7': {
            char file_name[25];
            cout << "Введите имя файла: ";
            cin >> file_name;
            subscribersArray = loadData(subscribersArray, file_name, &subscribersCount);
            break;
        }
        case '8': {
            unsigned year;
            cout << "Введите год: ";
            cin >> year;
            while (cin.fail()){
                cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введено неверное значение. Повторите ввод: ";
                cin >> year;
            }
            countData(subscribersArray, subscribersCount, year);
            break;
        }
		case '0': exit(10);
		default: cout << "Введено неверное значение" << endl;
			break;
		}
    }
    delete [] subscribersArray;
    return 0;
}
