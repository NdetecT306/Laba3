#include <iostream>
#include <cmath>
#include <numeric>
#include <iomanip>
using namespace std;
double sum(int a, int b, int rounds = 1000) 
{ 
    double sum = 0;
    for (int n = 1; n <= rounds; ++n) {
        sum += pow(n, a) / pow(b, n);
    }
    return sum;
}
int NOD(int a, int b)
{
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return NOD(a % b, b);
    return NOD(a, b % a);
}
int main() {
    int a, b;
    cin >> a >> b;
    if (a < 1 || a > 10 || b < 1 || b > 10)
    {
        cout << "Неверный ввод" << endl;
        return 1;
    }
    if (b <= 1 && a > 0)
    {
        cout << "infinity" << endl;
        return 1;
    }
    double summa = sum(a, b);
    double checks = 10;
    double num = round(summa * checks);
    double denominator = checks;
    double common_divisor = NOD(num, denominator);
    num /= common_divisor;
    denominator /= common_divisor;
    if (abs(summa - num / denominator) < 1) {
        cout << num << "/" << denominator << endl;
    }
    else
    {
        cout << "irrational" << endl;
    }
    return 0;
}
