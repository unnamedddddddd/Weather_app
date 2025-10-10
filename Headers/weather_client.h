#pragma once
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

size_t WriteCallBack(char* received_data_chunk, size_t size_of_element, size_t number_of_elements, void* my_result_string) {
    size_t total_received_bytes = size_of_element * number_of_elements;
    string* result = static_cast<string*>(my_result_string);

    if (result && received_data_chunk) {
        result->append(received_data_chunk, total_received_bytes);
    }

    return total_received_bytes;
}

string GetApiKey() {

    ifstream get("config.txt");
    if (get.is_open())
    {
        string api; getline(get,api);
        return api;
        cout << api; 
    }
}

string URLEncode(const string& city) {
    string encoded;
    if (city.empty()) {
        return ""; 
    }
    for (char c : city) {
        if (c == ' ') {
            encoded += "%20";
        }
        else {
            encoded += c;
        }
    }
    return encoded;
}

string CorrectURL(const string& city){
    string api = GetApiKey();
    string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city+ "&appid=" + api + "&units=metric&lang=en";
    return url;
}

string PerformCURLRequest(const string &city) {
    CURL* curl;
    string result;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, CorrectURL(URLEncode(city)).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    else {
     cerr << "Error: Cannot initialize CURL" << endl;
    }

    return result;
}