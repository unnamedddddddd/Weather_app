#pragma once
#include <fstream>
#include <map>
using namespace std;

size_t WriteCallBack(void* received_data_chunk, size_t size_of_element, size_t number_of_elements, string* my_result_string) {
    size_t total_received_bytes = size_of_element * number_of_elements;

    my_result_string->append((char*)received_data_chunk, total_received_bytes);
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
    string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + api + "&units=metric&lang=en";
    return url;
}

string PerformCURLRequest(const string &city) {
    CURL* curl;
    string result;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, CorrectURL(URLEncode(city)).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    return result;
}