#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

void ParseResult(const string &result) {
    try {

        json j = json::parse(result);

        if (j.contains("cod") && j["cod"] != 200) {
            cout << "Error API: " << j["message"] << endl;
        }
        else
        {
            cout << endl;
            cout << "=== WEATHER ===" << endl;
            cout << "City: " << j["name"] << endl;
            cout << "Temperature: " << fixed << setprecision(1)
                << (j["main"]["temp"].get<double>()) << "°C" << endl;
            cout << "Feels like: " << (j["main"]["feels_like"].get<double>()) << "°C" << endl;
            cout << "Weather: " << j["weather"][0]["description"].get<string>() << endl;
            cout << "Humidity: " << j["main"]["humidity"] << "%" << endl;
            cout << "Pressure: " << j["main"]["pressure"] << " hPa" << endl;
            cout << "Wind: " << j["wind"]["speed"] << " m/s" << endl;
        }
    }
    catch (const exception& e) {
        cout << u8"Error parsing: " << e.what() << endl;
    }
}
