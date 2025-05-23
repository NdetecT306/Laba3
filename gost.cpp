#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <set>
#include <locale>
using namespace std;
int power(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (1LL * res * base) % mod;
        base = (1LL * base * base) % mod;
        exp >>= 1;
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
bool diemietko_test(int p, int N)
{
    return (power(2, p - 1, p) == 1) && (power(2, N, p) != 1);
}
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}
int binaryLength(int n) {
    int length = 0;
    while (n > 0) {
        n >>= 1;
        length++;
    }
    return length;
}
int main() {
    setlocale(LC_ALL, "rus");
    int eratosLimit = 500;
    vector<int> primes = ERATOS(eratosLimit);
    cout << "Простые числа до " << eratosLimit << ": ";
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;
    int t = 10;
    int colvo = 0;
    cout << "Поиск p с использованием теста Дьемиетко:" << endl;
    cout << "p\t+/-\tq" << endl;
    for (int q_index = 0; q_index < primes.size(); q_index++) {
        int q = primes[q_index];
        int q_length = binaryLength(q);
        int target_length = t / 2;
        if (q_length != target_length) {
            continue;
        }
        int N_min = ceil(pow(2, t - 1) / q);
        if (N_min % 2 != 0) {
            N_min++;
        }
        for (int N = N_min; N < N_min + 100000 && colvo < 10; N += 2)
        {
            int p = N * q + 1;
            if (p > pow(2, t + 5)) {
                break;
            }
            if (diemietko_test(p, N)) {
                cout << p << "\t+\t" << q << endl;
                colvo++;
            }
            else {
                cout << p << "\t-\t" << q << endl;
            }

        }
    }
    return 0;
}
