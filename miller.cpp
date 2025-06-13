#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>
#include <locale>
#include <cstdint> 
using namespace std;
const int N = 10;
// Функция решета Эратосфена
vector<int> ERATOS(int lim) {
    vector<bool> prime(lim + 1, true);
    prime[0] = prime[1] = false;
    for (int p = 2; p * p <= lim; ++p) { 
        if (prime[p]) {
            for (int i = p * p; i <= lim; i += p) {
                prime[i] = false;
            }
        }
    }
    vector<int> ans;
    for (int p = 2; p <= lim; ++p) {
        if (prime[p]) ans.push_back(p);
    }
    return ans;
}
// Быстрое бинарное возведение в степень
int power(int a, int x, int p) {
    int res = 1;
    a %= p;
    if (a == 0) return 0;
    while (x > 0) {
        if (x & 1) res = (1LL * res * a) % p; 
        a = (1LL * a * a) % p;             
        x >>= 1;
    }
    return res;
}
// Вектор aj рандомных чисел
vector<int> RandomNumbers(int t, int start, int end) {
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) VremVec[i] = distribution(generator);
    return VremVec;
}
// Вектор рандомных простых чисел из решета
int Random(const vector<int>& primes) {
    if (primes.empty()) return 0;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(0, primes.size() - 1);
    return primes[distribution(generator)];
}
// Рандомная степень
int RandomStep() {
    int start = 1, end = 7;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}
// Тест Миллера-Рабина
bool MillerRabin(int64_t n, int t) {  
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    int s = 0;
    int64_t r = n - 1;
    while (r % 2 == 0) {
        s++;
        r /= 2;
    }
    for (int i = 0; i < t; ++i) {
        int64_t a = 2 + rand() % (n - 3); 
        int64_t x = power(a, r, n);
        if (x == 1 || x == n - 1) continue;
        for (int j = 0; j < s - 1; ++j) {
            x = power(x, 2, n);
            if (x == n - 1) break;
        }
        if (x != n - 1) return false;
    }
    return true;
}
// Тест Миллера
bool MILLER(int64_t n, int t, const vector<int>& Decom) {
    if (n <= 1) return false; //База
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    vector<int> VecAj = RandomNumbers(t, 2, n - 1);//aj
    for (int a : VecAj) { 
        int result = power(a, n - 1, n);//Проверка условия aj^(n-1)mod n
        if (result != 1) {
            return false;
        }
    }
    if (Decom.empty()) return true; //Если вектор qi пуст - ложь
    for (const auto& qi : Decom) {//Далее поход по всем qi с рассчетом условий
        bool all_one = true;
        for (int a : VecAj) {
            if ((n - 1) % qi != 0) return false;
            int64_t x = (n - 1) / qi;
            int64_t result = power(a, x, n); //Проверка результата
            if (result == 1) continue; 
            else {
                all_one = false; //сли какой-либо из результатов не равен единице - взять другое qi
                break;
            }
        }
        if (all_one) return false;//сли все результаты равны «1», то идти на Выход с сообщением «вероятно, n – составное число»
    }
    return true;//Идти на Выход с сообщением «n – простое число»
}
// Проверка длины числа
int length(int n) {
    int l = 0;
    do {
        l++;
        n /= 10;
    } while (n);
    return l;
}
// Функция для вычисления длины числа в битах(побитовый сдвиг)
int bitLength(int64_t n) {
    int len = 0;
    while (n > 0) {
        n >>= 1;
        len++;
    }
    return len;
}
// Генерация m
int64_t generateM(int l, const vector<int>& primes, vector<int>& VecPrimes, vector<int>& VecPowers) {
    int64_t m = 1;
    VecPrimes.clear();
    VecPowers.clear();
    while (bitLength(m) != l) {
        m = 1;
        VecPrimes.clear();
        VecPowers.clear();
        while (bitLength(m) < l) {
            int randPrime = Random(primes);
            int randPower = RandomStep();
            VecPrimes.push_back(randPrime);
            VecPowers.push_back(randPower);
            int64_t temp = 1;
            int64_t primePower = power(randPrime, randPower, 1e9+7);  
            temp = (1LL * m * primePower);
            if(bitLength(temp) > l) {
              break;
            }
            m = temp;
        }
    }
    return m;
}
int main() {
    setlocale(LC_ALL, "rus");
    int lim = 500;
    vector<int> primes = ERATOS(lim);
    cout << "Выводим решето Эратосфена:" << endl;
    for (int e : primes) {
        cout << e << " ";
    }
    cout << endl;
    int t = 1;
    int l = 15; // Битовая длина числа n 
    int yes = 0;
    cout << "------------------------------------------------------------------" << endl;
    cout << "|  №  |     p     |  Длина m (бит) | Длина n (бит) | Результат теста |   k  |" << endl;
    cout << "------------------------------------------------------------------" << endl;
    for (int i = 1; yes < 10; i++) { //Проходим, пока не будет 10 простых чисел по МИЛЛЕРУ (можно исправить, заменив result наобработку Миллера-Рабина)
        vector<int> VecPrimes; //Векторы корней и степеней
        vector<int> VecPowers;
        int64_t m = generateM(l - 1, primes, VecPrimes, VecPowers);  
        int64_t n = 2 * m + 1;
        if (bitLength(n) != l) {
          continue;
        }
        vector<int> decom;
        decom.push_back(2);
        for (int j = 0; j < VecPrimes.size(); ++j) {
            for (int le = 0; le < VecPowers[j]; ++le) {
                decom.push_back(VecPrimes[j]);
            }
        }
        bool result = MILLER(n, t, decom); 
        int k = 0; 
        if (!result) {
            for (int j = 0; j < 50; ++j) {
                if (MillerRabin(n, t)) {
                    k++;
                }
            }
        }
        cout << setw(5) << i << " | " << setw(13) << n << " | " << setw(8) << bitLength(m)
             << " | " << setw(6) << bitLength(n) << " | " << setw(17) << (result ? "+" : "-") << " | " << setw(4) << k << endl;

        if (result) {
            yes++;
        }
    }
    return 0;
}
