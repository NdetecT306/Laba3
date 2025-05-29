#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;
const int N = 10;
vector<int> ERATOS(int lim) //Функция решета 
{
    vector<bool> prime(lim + 1, true);
    prime[0] = prime[1] = false;
    for (int p = 2; p <= sqrt(lim); ++p) {
        if (prime[p]) {
            for (int i = p * p; i <= lim; i += p) {
                prime[i] = false;
            }
        }
    }
    vector<int> ans;
    for (int p = 2; p <= lim; ++p) { //Если простое - записываем в конечный вектор
        if (prime[p]) ans.push_back(p);
    }
    return ans;
}
int power(int a, int x, int p) { //Быстрое бинарное возведение в степень
    int res = 1;
    a %= p;
    if (a == 0) return 0;
    while (x > 0) {
        if (x % 2 == 1) res = (res * a) % p;
        a = (a * a) % p;
        x = x / 2;
    }
    return res;
}
vector<int> RandomNumbers(int t, int start, int end) { //Вектор aj
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) VremVec[i] = distribution(generator);
    return VremVec;
}
int Random(const vector<int>& primes) { //Вектор рандомных простых чисел
    if (primes.empty()) return 0;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(0, primes.size() - 1);
    return primes[distribution(generator)];
}
int RandomStep() { //Рандомная степень
    int start = 1, end = 7;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}
bool MillerRabin(int n, int t) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    int s = 0;
    int r = n - 1;
    while (r % 2 == 0) {
        s++;
        r /= 2;
    }
    for (int i = 0; i < t; ++i) {
        int a = 2 + rand() % (n - 3);
        int x = power(a, r, n);
        if (x == 1 || x == n - 1) continue;
        for (int j = 0; j < s - 1; ++j) {
            x = power(x, 2, n);
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}
bool MILLER(int n, int t, const vector<int>& Decom) { //Вводим число, надежность и разложение 
    if (n <= 1) return false; //Если n <=1 - заведомо не подходит
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false; 
    vector<int> VecAj = RandomNumbers(t, 2, n - 1); // Выбираем t чисел: 1 < a < n 
    for (int a : VecAj) { // Для каждого a
        int result = power(a, n - 1, n); // Вычисляем a^(n-1) mod n
        if (result != 1) { // Если какой-либо из результатов не равен «1», то идти на Выход с сообщением «n –составное число».
            return false;
        }
    }
    if (Decom.empty()) return true; 
    for (const auto& qi : Decom) { //Разложение числа
        bool all_one = true; 
        for (int a : VecAj) { //Для всех a
            if ((n - 1) % qi != 0) return false;
            int x = (n - 1) / qi; // Считаем степень для a
            int result = power(a, x, n);//Считаем a^((p-1)/qi mod n или a^xmod n
            if (result == 1) continue;
            else {
                all_one = false;
                break; 
            }
        }
        if (all_one) return false;  
    }
    return true;
}
int length(int n) {//Проверка длины числа
    int l = 0;
    do {
        l++;
        n /= 10;
    } while (n);
    return l;
}
int main()
{
    setlocale(LC_ALL, "rus"); //Русский
    int lim = 500; //500 чисел
    vector<int> primes = ERATOS(lim); //Генерируем решето
    cout << "Выводим решето Эратосфена:" << endl; //Говорим что выводим решето
    for (int e : primes) {//Сам вывод
        cout << e << " ";
    }
    cout << endl;
    int t = 50;//Итерации для тестов
    int l_min = 3; //Длины чисел m и n
    int l_max = 4;
    int k = 0;
    int countSost = 0;
    vector<int> primeNumbers;
    vector<int> generatedNumbers;
    int yes = 0;
    cout << "-------------------------------------------------" << endl;
    cout << "|  №  |   p   | Результат теста |   k   |" << endl;
    cout << "-------------------------------------------------" << endl;
    for (int i = 1; yes < 10; i++) {
        int m = 1; //m = 1
        vector<int> VecPrimes; // Каноническое разложение
        vector<int> VecPowers; // Степени простых чисел
        while (length(m) < l_min) {
            int randPrime = Random(primes);
            int randPower = RandomStep();
            VecPrimes.push_back(randPrime);
            VecPowers.push_back(randPower);
            m *= pow(randPrime, randPower);
        }
        while (length(m) > l_max - 1 && m > 1) {
            int lastPrime = VecPrimes.back();
            int lastPower = VecPowers.back();
            VecPrimes.pop_back();
            VecPowers.pop_back();
            m /= pow(lastPrime, lastPower); // Уменьшаем m
            // Генерируем новое простое число и степень
            int newRandPrime = Random(primes);
            int newRandPower = RandomStep();
            VecPrimes.push_back(newRandPrime);
            VecPowers.push_back(newRandPower);
            m *= pow(newRandPrime, newRandPower);
            if (length(m) < l_min) {
                VecPrimes.push_back(lastPrime);
                VecPowers.push_back(lastPower);
                m *= pow(lastPrime, lastPower);
            }
        }
        int n = 2 * m + 1;
        if (length(n) < l_max) {
            int newRandPrime = Random(primes);
            int newRandPower = RandomStep();
            VecPrimes.push_back(newRandPrime);
            VecPowers.push_back(newRandPower);
            m *= pow(newRandPrime, newRandPower);
            n = 2 * m + 1;
        }
        while (length(n) > l_max + 1) {
            int lastPrime = VecPrimes.back();
            int lastPower = VecPowers.back();
            VecPrimes.pop_back();
            VecPowers.pop_back();
            m /= pow(lastPrime, lastPower); // Уменьшаем m
            int newRandPrime = Random(primes);
            int newRandPower = RandomStep();
            VecPrimes.push_back(newRandPrime);
            VecPowers.push_back(newRandPower);
            m *= pow(newRandPrime, newRandPower);
            n = 2 * m + 1;
        }
        bool duplicate = false;
        for (int num : generatedNumbers) {
            if (num == n) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            continue;
        }
        generatedNumbers.push_back(n);
        vector<int> decom; // Разложение n-1 (2*m) = простые делители m
        for (int j = 0; j < VecPrimes.size(); ++j) {
            for (int l = 0; l < VecPowers[j]; ++l) {
                decom.push_back(VecPrimes[j]);
            }
        }
        if (MILLER(n, t, decom)) {
            cout << setw(5) << i << " | " << setw(10) << n << " | " << setw(10) << "+" << " | " << setw(5) << k << endl;
            primeNumbers.push_back(n);
            yes++;

        }
        else {
            if (MillerRabin(n, t)) {
                k++; // Увеличиваем k, если MillerRabin считает число простым
            }
            cout << setw(5) << i << " | " << setw(10) << n << " | " << setw(10) << "-" << " | " << setw(5) << k << endl;
        }
    }
    return 0;
}
