#pragma once
#include <QtWidgets/QApplication>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

using namespace std;

class WeatherApp : public QWidget {
public:
    WeatherApp(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLineEdit* cityInput = new QLineEdit();
        cityInput->setPlaceholderText("Enter city");
        cityInput->setFont(QFont("Arial", 12));
        layout->addWidget(cityInput);

        QPushButton* weatherButton = new QPushButton("Get Weather");
        weatherButton->setFont(QFont("Arial", 12));
        layout->addWidget(weatherButton);

        QLabel* resultLabel = new QLabel("Click button to get weather");
        layout->addWidget(resultLabel);

        resultLabel->setText("Weather information will appear here...\nEnter city and click the button.");
        resultLabel->setWordWrap(true);
        resultLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        resultLabel->setMinimumSize(450, 250);

        resultLabel->setStyleSheet(
            "QLabel {"
            "   background-color: #f0f0f0;"
            "   border: 2px solid #cccccc;"
            "   border-radius: 5px;"
            "   padding: 15px;"
            "   font-family: Arial;"
            "   font-size: 16px;"
            "   color: #333333;"
            "}"
        );

        connect(weatherButton, &QPushButton::clicked, [=]() {
            QString city = cityInput->text();
            string cityStd = city.toUtf8().constData();

            if (city.isEmpty()) {
                resultLabel->setText("Please enter a city!");
                return;
            }

            string fullURL = CorrectURL(cityStd); // Убрал URLEncode
            cout << "Полный URL: '" << fullURL << "'" << std::endl;

            string result = PerformCURLRequest(cityStd);
            cout << "Длина ответа: " << result.length() << std::endl;

            if (result.empty()) {
                resultLabel->setText("Empty response from server");
                return;
            }

            cout << "Ответ API: " << result.substr(0, 100) << "..." << endl;

            QString weatherText = ParseResult(result);

            if (weatherText.isEmpty()) {
                resultLabel->setText("No weather data received");
                return;
            }

               resultLabel->setText(weatherText);

            });
    }
};