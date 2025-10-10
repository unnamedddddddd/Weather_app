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

    curl_global_init(CURL_GLOBAL_DEFAULT);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    QApplication app(argc, argv);

    WeatherApp window;
    window.setWindowTitle("Weather Application");
    window.resize(500, 400);
    window.show(); 

    curl_global_cleanup();

    return app.exec();
    
    
}

