#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <iostream>

using namespace std;

class WeatherApp : public QWidget {
public:
    WeatherApp(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLineEdit* cityInput = new QLineEdit();
        cityInput->setPlaceholderText("Enter city");
        layout->addWidget(cityInput);

        QPushButton* weatherButton = new QPushButton("Get Weather");
        layout->addWidget(weatherButton);

        QLabel* resultLabel = new QLabel("Click button to get weather");
        layout->addWidget(resultLabel);

        connect(weatherButton, &QPushButton::clicked, [=]() {
            QString city = cityInput->text();
            resultLabel->setText(city);
            });
    }
};

void Test() { cout << "da"; }