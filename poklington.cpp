#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <algorithm>
#include <locale>
#include <set>
using namespace std;
int power(int a, int x, int p) {
    int res = 1;
    a = a % p;
    if (a == 0) return 0;
    while (x > 0) {
        if (x % 2 == 1) {
            res = (long long)res * a % p;
            if (res < 0) res += p;
        }
        a = (long long)a * a % p;
        if (a < 0) a += p;
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
int gcd(int a, int b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}
bool pocklingtonTest(int n, int a) {
    int n_minus_one = n - 1;
    vector<pair<int, int>> factors = primeFactorization(n_minus_one);
    if (factors.empty()) {
        return false;
    }
    if (power(a, n_minus_one, n) != 1) {
        return false;
    }
    for (const auto& factor : factors) {
        int q = factor.first;
        int gcd_val = gcd(abs(power(a, n_minus_one / q, n) - 1), n);
        if (gcd_val == 1) {
            return true;
        }
    }
    return false;
}
int generateRandomEven(int bits) {
    if (bits <= 1) {
        return 0;
    }
    int min_val = (1 << (bits - 1));
    int max_val = (1 << bits) - 1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generator(seed);
    uniform_int_distribution<int> distribution(min_val, max_val);
    int random_number = distribution(generator);
    if (random_number % 2 != 0) {
        random_number--;
    }
    return random_number;
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
bool ERROR(int answer, int t, vector<pair<int, int>> primeDecom) {
    return false;
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

int main() {
    setlocale(LC_ALL, "rus");
    int eratosLimit = 500;
    vector<int> primes = ERATOS(eratosLimit);
    cout << "Простые числа до " << eratosLimit << ": ";
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl << "Простые числа, проверенные тестом Поклингтона:" << endl;
    int length = 4;
    int t = 50;
    int found_count = 0;
    vector<int> found_primes;
    cout << "N\t+/-\tk" << endl;
    srand(time(0));
    for (int i = 0; i < 1000 && found_count < 10; ++i) {
        int k = 0;
        int answer = generateRandomNumber(length);
        bool pocklington_passed = false;
        for (int a_test_count = 0; a_test_count < 1; ++a_test_count) {
            int a = 2 + rand() % (answer - 3);
            if (pocklingtonTest(answer, a)) {
                pocklington_passed = true;
                break;
            }
            k++; 
        }
        if (pocklington_passed && millerRabin(answer, t)) {
            cout << answer << "\t" << "+" << "\t" << k << endl;
            found_count++;
            found_primes.push_back(answer);
        }
        else {
            cout << answer << "\t" << "-" << "\t" << k << endl;
        }
    }
    cout << endl;
    return 0;
}
