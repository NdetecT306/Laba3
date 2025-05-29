#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <set>
#include <locale>
#include <algorithm>
#include <iomanip>
using namespace std;
const int N = 10;
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
int generateRandomNumber(int length) {
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
vector<int> RandomNumbers(int t, int start, int end) { //Вектор aj
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) VremVec[i] = distribution(generator);
    return VremVec;
}
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
    for (int p = 2; p <= lim; ++p) {
        if (prime[p]) ans.push_back(p);
    }
    return ans;
}
int Random(const vector<int>& primes) {  //Вектор рандомных простых чисел
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
int length(int n) {
    int l = 0;
    do {
        l++;
        n /= 10;
    } while (n);
    return l;
}
bool Pockl(int n, int t, const vector<int>& Decom) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    vector<int> VecAj = RandomNumbers(t, 2, n - 1);
    for (int a : VecAj) { // Для каждого a
        int result = power(a, n - 1, n); // Вычисляем a^(n-1) mod n
        if (result != 1) {
            return false;
        }
    }
    if (Decom.empty()) return true;
    for (const auto& qi : Decom) {
        bool check = false;
        for (int a : VecAj) {
            if ((n - 1) % qi != 0) {
                return false; //Cannot use Pocklington if (n-1) % qi != 0
            }
            int x = (n - 1) / qi;
            int result = power(a, x, n);
            if (result == 1) {  // Modified here: Changed != to ==
                continue; // a is not a witness for qi
            }
            check = true; // a is a witness for qi
            break;
        }
        if (!check) {
            return false; // No witness found for qi
        }
    }
    return true;
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
    int l = 4; // Требуемый размер простого числа (количество десятичных цифр)
    int yes = 0;
    int t = 50;
    int num_experiments = 10;
    vector<int> found_primes;
    int rejected_count = 0;
    int primes_found = 0;
    cout << endl;
    cout << "===================================================================" << endl;
    cout << setw(5) << "№" << " | " << setw(12) << "p" << " | " << setw(7) << "Test" << " | " << setw(5) << "k" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 1; yes < 10; i++) {
        int F = 1;
        vector<int> VecPrimes; // Каноническое разложение
        int curlen = 0;
        while (curlen < l / 2 + 1) {
            int randPrime = Random(primes);
            int randPower = RandomStep();
            int peremlen = length(pow(randPrime, randPower));
            if (curlen + peremlen <= l / 2 + 1) {
                VecPrimes.push_back(randPrime);
                F *= pow(randPrime, randPower);
                curlen = length(F); // Update current length
            }
            else {
                break;
            }
        }
        if (VecPrimes.empty()) continue; // Skip if F is empt
        int R_length = l - length(F);//Длина R
        if (R_length <= 0) continue;
        int R;
        do {
            R = generateRandomNumber(R_length);
        } while (R % 2 != 0);
        int n = R * F + 1; 
        if (length(n) == l) {
            vector<int> uniquePrime;
            for (int prime : VecPrimes)
            {
                if (find(uniquePrime.begin(), uniquePrime.end(), prime) == uniquePrime.end())
                {
                    uniquePrime.push_back(prime);
                }
            }
            char pocklTestResult = '-';
            if (Pockl(n, t, uniquePrime)) {
                pocklTestResult = '+';
            }
            char millerRabinTestResult = '-';
            if (MillerRabin(n, t)) {
                millerRabinTestResult = '+';
            }
            if (!Pockl(n, t, uniquePrime) && MillerRabin(n, t)) {
                rejected_count++;
            }
            if (Pockl(n, t, uniquePrime) && MillerRabin(n, t)) yes++;
            cout << setw(5) << i << " | " << setw(12) << n << " | " << setw(7) << millerRabinTestResult << " | " << setw(5) << rejected_count << endl;
        }
    }
    cout << endl;
    return 0;
}
