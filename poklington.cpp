#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <set>
#include <locale>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdint> 
using namespace std;
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
int64_t generateRandomNumber(int numBits) {
    if (numBits <= 0) {
        return 0;
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int64_t> distribution(0, (1LL << numBits) - 1);
    return distribution(generator);
}
vector<int> RandomNumbers(int t, int start, int end) { //Вектор aj
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) VremVec[i] = distribution(generator);
    return VremVec;
}
vector<int> ERATOS(int lim) //Функция решета Эратосфена для 500 чисел
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
    for (int p = 2; p <= lim; ++p) {
        if (prime[p]) ans.push_back(p);
    }
    return ans;
}
int Random(const vector<int>& primes) {  //Вектор рандомных простых чисел из решета Эратосфена
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
int length(int64_t n) { //Определение длины числа в битах
    int len = 0;
    while (n > 0) {
        len++;
        n >>= 1;
    }
    return len;
}
bool Pockl(int64_t n, int t, const vector<int>& Decom) {//Функция по Поклингтону
    if (n <= 1) return false; //Самые бащовые случаи
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    vector<int> VecAj = RandomNumbers(t, 2, n - 1); //Вектор aj
    for (int a : VecAj) { // Для каждого aj
        int result = power(a, n - 1, n); // Вычисляем a^(n-1) mod n
        if (result != 1) {
            return false; 
        }
    }
    if (Decom.empty()) return true; //Если нет Канонического разложения - ложь
    for (const auto& qi : Decom) { //Для всех элементов разложения
        bool check = false;
        for (int a : VecAj) {
            if ((n - 1) % qi != 0) {
                return false;
            }
            int64_t x = (n - 1) / qi;
            int64_t result = power(a, x, n); //Расчет a^((n-1)/q)mod n
            if (result != 1) {
                continue;
            }
            check = true;
            break;
        }
        if (!check) {
            return true;
        }
    }
    return false; 
}
// Тест Миллера-Рабина 
bool PrimeMillerRabin(int64_t n, int t) {  // принимаем int64_t на вход
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    int s = 0;
    int64_t r = n - 1;
    while (r % 2 == 0) {
        s++;
        r /= 2;
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int64_t> distribution(2, n - 2);
    for (int i = 0; i < t; ++i) {
        int64_t a = distribution(generator); 
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
int main(){
    setlocale(LC_ALL, "rus");
    int lim = 500;
    vector<int> primes = ERATOS(lim); //Генерируем решето
    cout << "Выводим решето Эратосфена:" << endl; //Выводим решето
    for (int e : primes) {
        cout << e << " ";
    }
    cout << endl;
    int l = 10; // Требуемый размер простого числа (количество бит)
    int yes = 0;
    int t = 1;
    int num_experiments = 10;
    vector<int> found_primes;
    int k = 0;
    int primes_found = 0;
    cout << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << setw(5) << "№" << " | " << setw(12) << "p" << " | " << setw(7) << "Test" << " | " << setw(5) << "k" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 1; yes < 10; i++) {
        int64_t F = 1;
        vector<int> VecPrimes; // Каноническое разложение
        int FLength = (l / 2) + 1; // F - на 1 бит больше половины заданной длины
        int curlen = 0;
        while (curlen < FLength) {
            int randPrime = Random(primes); //Рандомное число
            int randPower = RandomStep(); //Рандомная степень
            int peremlen = length(pow(randPrime, randPower));
            if (curlen + peremlen <= FLength) { //Проверка длины
                VecPrimes.push_back(randPrime);
                int64_t power_of_prime = 1;
                for (int j = 0; j < randPower; ++j) {
                    if (power_of_prime > numeric_limits<int64_t>::max() / randPrime) {
                        F = numeric_limits<int64_t>::max();
                        break;
                    }
                    power_of_prime *= randPrime;
                }
                if (F == numeric_limits<int64_t>::max()) {
                    break;
                }
                if (F > numeric_limits<int64_t>::max() / power_of_prime) {
                    F = numeric_limits<int64_t>::max();
                    break; 
                }
                else{
                    F *= power_of_prime;
                }
                curlen = length(F);
            }
            else {
                break;
            }
        }
        if (VecPrimes.empty()) continue; // Пропускаем, если пустой
        int RLength = FLength - 1;  
        if (RLength <= 0) continue;
        int64_t R;
        do {
            R = generateRandomNumber(RLength); //генерируем четное R
        } while (R % 2 != 0);
        if (R > numeric_limits<int64_t>::max() / F)
        {
             continue; 

        }
        int64_t n = R * F + 1; //Рассчет n
        if (length(n) == l) {
            vector<int> uniquePrime;
            for (int prime : VecPrimes) //Делаем все числа уникальными
            {
                if (find(uniquePrime.begin(), uniquePrime.end(), prime) == uniquePrime.end())
                {
                    uniquePrime.push_back(prime);
                }
            }
            bool is_pocklington_prime = Pockl(n, t, uniquePrime);
            if (is_pocklington_prime) {
                cout << setw(5) << i << " | " << setw(10) << n << " | " << setw(10) << "+" << " | " << setw(5) << k << endl;
                yes++;
            } 
            else {
                bool miller_rabin_passed = true;
                for(int j = 0; j < 30; j++)
                {
                    if (!PrimeMillerRabin(n, t)) {
                        miller_rabin_passed = false;
                        break; 
                    }
                    k++;
                }
                if(miller_rabin_passed){
                    cout << setw(5) << i << " | " << setw(10) << n << " | " << setw(10) << "-" << " | " << setw(5) << k << endl;

                }
                else{
                    cout << setw(5) << i << " | " << setw(10) << n << " | " << setw(10) << "-" << " | " << setw(5) << k << endl;
                }
                k = 0;

            }
        }
    }
    cout << endl;
    return 0;
}
