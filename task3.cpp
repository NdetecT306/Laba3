#include <iostream>
#include <cmath>
#include <numeric>
#include <iomanip>
using namespace std;
double sum(int a, int b, int rounds = 1000) { 
    double sum = 0;
    for (int n = 1; n <= rounds; ++n) {
        sum += pow(n, a) / pow(b, n);
    }
    return sum;
}
int main() {
    int a, b;
    cin >> a >> b;
    if (a < 1 || a > 10 || b < 1 || b > 10){ //Базовый случай
        cout << "Неверный ввод" << endl;
        return 1;
    }
    if (b <= 1 && a > 0){ //Бесконечность
        cout << "infinity" << endl;
        return 1;
    }
    double summa = sum(a, b);
    double checks = 10000;
    double num = round(summa * checks);
    double denom= checks;
    if (abs(summa - num / denom) < 1) {
        cout << num << "/" << denom << endl;
    }
    else{
        cout << "irrational" << endl;
    }
    return 0;
}

