#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
//Высчитываем y согласно x
double charts(double x) {
    double result = 0;
    if (x >= -4 && x <= 0) {
        double perem = 4 - (x + 2) * (x + 2);
        result = sqrt(perem);
    }
    else if (x > 0 && x < 0.5) {
        result = 0;
    }
    else if (x >= 0.5 && x <= 2) {
        result = log(x) / x;
    }
    else if (x > 2) {
        result = 1;
    }
    return result;
}
//Задаем начало, конец и шаг(со знаком). Проходим по циклу и выдаем точки.
int main() {
    setlocale(LC_ALL, "rus");
    double x_start, x_end, dx, y, digit;
    cout << "Введите начало прохода: ";
    cin >> x_start;
    cout << "Введите конец прохода: ";
    cin >> x_end;
    cout << "Введите шаг прохода со знаком (никакой, если от меньшего к большему, -, если от большего к меньшему): ";
    cin >> dx;
    cout << "Ведите ожидаемую точность посчитанного числа (мало ли, вдруг вы хотите разногласий): ";
    cin >> digit;
    if (x_start < -4 || x_end < -4) {
        cout << "Выход за границу графика" << endl;
        return 0;
    }
    if ((x_start < x_end && dx < 0) || (x_start > x_end && dx > 0)) {
        cout << "Невозможный проход по графику" << endl;
        return 0;
    }
    cout << "---------------" << endl;
    cout << "|   x  |   y  |" << endl;
    cout << "---------------" << endl;
    cout << fixed << setprecision(digit);
    if (x_start < x_end) {
        for (double x = x_start; x <= x_end; x += dx) 
        {
            y = charts(x);
            cout << "| " << setw(3) << x << " | " << setw(3) << y << " |" << endl;
        }
    }
    else if (x_start > x_end) {
        for (double x = x_start; x >= x_end; x += dx) {
            y = charts(x);
            cout << "| " << setw(3) << x << " | " << setw(3) << y << " |" << endl;
        }
    }
    cout << "-----------------" << endl;
    return 0;
}
