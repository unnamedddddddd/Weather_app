#pragma once
#include <QtWidgets/QLabel>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream> 
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

QString ParseResult(const string& result) {
    if (result.empty()) return "Empty response from server";

    QString weatherText = "=== WEATHER ===\n\n";

    json j;

    auto parse_result = json::parse(result, nullptr, false);
    if (parse_result.is_discarded()) {
        return "Invalid JSON format";
    }
    j = parse_result;

    if (j.contains("cod") && j["cod"].is_number()) {
        int code = j["cod"].get<int>();
        if (code != 200) {
            QString errorMsg = "API Error";
            if (j.contains("message") && j["message"].is_string()) {
                errorMsg += ": " + QString::fromStdString(j["message"].get<string>());
            }
            return errorMsg;
        }
    }

    if (j.contains("name") && j["name"].is_string()) {
        cout << (j["name"].get<string>()) + "\n";
        weatherText += "City: " + QString::fromUtf8(j["name"].get<string>().c_str()) + "\n";
    }
    else {
        weatherText += "City: Unknown\n";
    }

    if (j.contains("main") && j["main"].is_object()) {
        auto& main = j["main"];

        if (main.contains("temp") && main["temp"].is_number()) {
            double temp = main["temp"].get<double>();
            weatherText += "Temperature: " + QString::number(temp, 'f', 1) + " C\n";
        }

        if (main.contains("feels_like") && main["feels_like"].is_number()) {
            double feels_like = main["feels_like"].get<double>();
            weatherText += "Feels like: " + QString::number(feels_like, 'f', 1) + " C\n";
        }

        if (main.contains("humidity") && main["humidity"].is_number()) {
            int humidity = main["humidity"].get<int>();
            weatherText += "Humidity: " + QString::number(humidity) + "%\n";
        }

        if (main.contains("pressure") && main["pressure"].is_number()) {
            int pressure = main["pressure"].get<int>();
            weatherText += "Pressure: " + QString::number(pressure) + " hPa\n";
        }
    }

    if (j.contains("weather") && j["weather"].is_array() && !j["weather"].empty()) {  
        weatherText += "Weather: " + QString::fromUtf8(j["weather"][0]["description"].get<std::string>().c_str()) + "\n";
    }
   
    if (j.contains("wind") && j["wind"].is_object() && j["wind"].contains("speed") && j["wind"]["speed"].is_number()) {
        double windSpeed = j["wind"]["speed"].get<double>();
        weatherText += "Wind: " + QString::number(windSpeed, 'f', 1) + " m/s";
    }
     
    return weatherText;
}