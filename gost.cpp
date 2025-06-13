#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <random>
#include <locale>
using namespace std;
int power(int a, int x, int p) { //Быстрое бинарное возведение в степень
    int res = 1;
    a %= p;
    while (x > 0) {
        if (x % 2 == 1) res = (res * a) % p;
        a = (a * a) % p;
        x >>= 1;
    }
    return res;
}
vector<int> RandomNumbers(int t, int start, int end) { //Рандомный вектор
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) {
        VremVec[i] = distribution(generator);
    }
    return VremVec;
}
vector<pair<int, int>> primeFactorization(int n) { //Рандомный вектор из корней
    vector<pair<int, int>> factors;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            factors.push_back({ i, count });
        }
    }
    if (n > 1) {
        factors.push_back({ n, 1 });
    }
    return factors;
}
int generateRandomNumber(int length) { //Генерация рандоиной длины
    if (length <= 0) {
        return 0;
    }
    int min_val = pow(10, length - 1);
    int max_val = pow(10, length) - 1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(min_val, max_val);
    return distribution(generator);
}
bool millerRabin(int n, int k) { //Миллер-Рабин на всякий
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    int s = 0;
    int r = n - 1;
    while (r % 2 == 0) {
        s++;
        r /= 2;
    }
    for (int i = 0; i < k; i++) {
        int a = 2 + rand() % (n - 3);
        int x = power(a, r, n);

        if (x == 1 || x == n - 1)
            continue;
        int j = 1;
        for (; j < s; j++) {
            x = power(x, 2, n);
            if (x == n - 1)
                break;
        }
        if (j == s)
            return false;
    }
    return true;
}
vector<int> ERATOS(int limit) { //Решето
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }
    vector<int> primes;
    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}
int binaryLength(int n) {//Длина в битах (побитовый сдвиг)
    int length = 0;
    while (n > 0) {
        n >>= 1;
        length++;
    }
    return length;
}
int generatePrimeGOST(int t, int q, int& uVal) { //генерация простоты числа для ГОСТа
    double n = pow(2, t - 1);
    double per = n / q;
    int N = ceil(per);
    if (N % 2 != 0) {
        N++;
    }
    int u = 0;
    while (true) {
        int p = (N + u) * q + 1;
        if (p > pow(2, t + 5)) {
            return -1; 
        }
        if (power(2, p - 1, p) == 1 && power(2, N + u, p) != 1) {
            uVal = u;
            return p;
        }
        u += 2;
    }
}
int main() { //Ну и main для генерации 10 простых чисел определенной длины
    setlocale(LC_ALL, "rus");
    int eratosLimit = 500;
    vector<int> primes = ERATOS(eratosLimit);
    int t = 13; 
    int numPrimesToGenerate = 10;
    cout << "-------------------------------------" << endl;
    cout << setw(5) << "№" << " | " << setw(15) << "p (ГОСТ)" << " | "<< setw(5) << "+/-" << " | " << endl;
    cout << "-------------------------------------" << endl;
    int rejectedCount = 0;
    vector<int> rejectedNumbers;
    for (int i = 0; i < numPrimesToGenerate; ++i) {
        int q_index = i % primes.size();
        int q = primes[q_index];
        int u_value = 0;
        int p_gost = generatePrimeGOST(t, q, u_value);
        if (p_gost == -1) {
            cout << setw(5) << i + 1 << " | " << setw(15) << "Не найдено" << " | "<< setw(5) << "-" << " | " << endl;
            continue;
        }
        bool mr_test = millerRabin(p_gost, 20);
        cout << setw(5) << i + 1 << " | " << setw(15) << p_gost << " | "<< setw(5) << (mr_test ? "+" : "-") << " | " << endl;
        if (!mr_test) {
            rejectedCount++;
            rejectedNumbers.push_back(p_gost);
        }
    }
    cout << "-------------------------------------" << endl;
    return 0;
}
