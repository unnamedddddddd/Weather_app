#include <iostream>
#include <curl/curl.h>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <QtWidgets/QApplication>
#include "Headers/json.hpp"
#include "Headers/weather_client.h"
#include "Headers/Weather_parser.h"
#include "Headers/QtGUI.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);


       
    
        Test();
  

        QApplication app(argc, argv);

        WeatherApp window;
        window.setWindowTitle("Weather Application");
        window.resize(400, 300);
        window.show();

        return app.exec();









       /* string choice = "y";

        while (choice == "y" || choice == "yes" || choice == "1") {
            string city;
            cout << "Enter the city: "; getline(cin,city);

            string result = PerformCURLRequest(city);
            ParseResult(result);           
            cout << endl;

            cout << "Continue? (yes/no): ";
            getline(cin, choice);
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes" || choice == "y" || choice == "1") {
                cout << "Continuing..." << endl;
                cout << endl;
            }
            else if (choice == "no" || choice == "n" || choice == "0") {
                cout << "Exiting..." << endl;
                return 0;
            }
            else {
                cout << "Invalid choice" << endl;
                cout << endl;
                return 0;
            }
        }*/
        return 0;
    }
    catch (const invalid_argument& e) {
        cerr << u8"Ошибка : " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << u8"Ошибка: " << e.what() << endl;
    }
}

