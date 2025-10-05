#include <iostream>
#include <curl/curl.h>
#include <string>
#include <Windows.h>
#include "json.hpp"
#include "weather_client.h"

using json = nlohmann::json;
using namespace std;

int main() {
    try {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        string city;
        cout << u8"Введите город: "; getline(cin,city);
        string result = PerformCURLRequest(city);

        json j = json::parse(result);
        if (j.contains("cod") && j["cod"] != 200) {
            cout << "Ошибка API: " << j["message"] << endl;
        }
        cout << "Weather: " << j["name"].get<string>() << endl;
        cout << "Cloud: " << j["weather"][0]["main"].get<string>() << endl;

        return 0;
    }
    catch (const exception& e) {
        cout << "Ошибка парсинга: " << e.what() << endl;
    }
}

