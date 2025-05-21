#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
vector<pair<double, double>> cofe(double Tk, double Ts, double r, double time, double dt) 
{
    vector<pair<double, double>> Vec_coffee;
    double t = 0.0;
    double T = Tk;
    while (t <= time)
    {
        Vec_coffee.push_back({ t, T });
        double dTdt = -r * (T - Ts);
        T = T + dTdt * dt;
        t += dt;
    }
    return Vec_coffee;
}
pair<double, double> approx(const vector<pair<double, double>>& coffee)
{
    int n = coffee.size();
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;
    for (const auto& el : coffee) 
    {
        sum_x += el.first;
        sum_y += el.second;
        sum_xy += el.first * el.second;
        sum_x2 += pow(el.first, 2);
    }
    double a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double b = (sum_y - a * sum_x) / n;
    return {a, b};
}
int main() 
{
    setlocale(LC_ALL, "rus");
    double Tk, Ts, r, time = 30, dt = 0.1;
    cout << "Введите начальную температуру кофе (T): ";
    cin >> Tk;
    if (Tk > 100 || Tk<0)
    {
        cout << "У Вас ОЧЕНЬ странный кофе";
        return 1;
    }
    cout << "Введите температуру окружающей среды (Ts): ";
    cin >> Ts;
    if (Tk == Ts)
    {
        cout << "С кофе ничего не произойдет";
        return 1;
    }
    cout << "Введите коэффициент остывания (r): ";
    cin >> r;
    vector<pair<double, double>> CoolCoffee = cofe(Tk, Ts, r, time, dt);
    cout << "\nРезультаты моделирования остывания кофе:\n";
    cout << "Время(x)\tТемпература(y)\n";
    cout << fixed << setprecision(2); 
    for (const auto& el : CoolCoffee) {
        cout << el.first << "\t\t" << el.second << endl;
    }
    pair<double, double> params = approx(CoolCoffee);
    cout << "\nПараметры аппроксимирующей прямой:\n";
    cout << "a = " << params.first << endl << "b = " << params.second << endl;
    return 0;
}

