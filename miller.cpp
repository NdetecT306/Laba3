#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

vector<int> ERATOS(int limit) {
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
int power(int a, int x, int p) {
    int res = 1;
    a = a % p;
    if (a == 0) return 0;
    while (x > 0) {
        if (x % 2 == 1) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x = x / 2;
    }
    return res;
}
vector<int> RandomNumbers(int t, int start, int end) {
    vector<int> VremVec(t);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < t; ++i) {
        VremVec[i] = distribution(generator);
    }
    return VremVec;
}
vector<pair<int, int>> primeFactorization(int n) {
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
bool millerRabin(int n, int k) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    int s = 0;
    int r = n - 1;
    while (r % 2 == 0) {
        s++;
        r /= 2;
    }
    for (int i = 0; i < k; ++i) {
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
bool ERROR(int n, int t, const vector<pair<int, int>>& Decom) {
    if (n <= 1) return false;
    if (n == 2) return false;
    vector<int> VecAj = RandomNumbers(t, 2, n - 1);
    for (int a : VecAj) {
        int result = power(a, n - 1, n);
        if (result != 1) {
            return true;
        }
    }
    if (Decom.empty()) return false;
    for (const auto& elem : Decom) {
        int qi = elem.first;
        bool check = true;
        for (int a : VecAj) {
            int x = (n - 1) / qi;
            if ((n - 1) % qi != 0) {
                return false;
            }
            int result = power(a, x, n);
            if (result != 1) {
                check = false;
                break;
            }
        }
        if (check) {
            return true;
        }
    }
    return false;
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
int main() {
    setlocale(LC_ALL, "rus");
    int eratosLimit =500; 
    vector<int> primes = ERATOS(eratosLimit);
    cout << "Простые числа до " << eratosLimit << ": ";
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl << "Простые числа, проверенные тестом Миллера:" << endl;
    int length = 4;
    int t = 50;
    int found_count = 0;
    vector<int> found_primes;
    cout << "N\t+/-\tk" << endl;
    for (int i = 0; i < 1000 && found_count < 10; ++i) {
        int k = 0;
        int answer = generateRandomNumber(length);
        vector<pair<int, int>> primeDecom = primeFactorization(answer - 1);
        if (!ERROR(answer, t, primeDecom)) {
            if (millerRabin(answer, t)) {
                cout << answer << "\t" << "+" << "\t" << k << endl;
                found_count++;
            }
            else
            {
                k++;
                cout << answer << "\t" << "-" << "\t" << k << endl;
            }
        }
    }
    cout << endl;
    return 0;
}
