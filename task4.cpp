#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    cout << "Введите количество элементов последовательности: ";
    int n;
    cin >> n;
    if (n < 4 || n > 50001) 
    {
        cout << "Неправильный ввод" << endl;
        return 1;
    }
    cout << "Введите максимальное количество взятых элементов: ";
    int m;
    cin >> m;
    if (m < 3 || m > 101) 
    {
        cout << "Неправильный ввод" << endl;
        return 1;
    }
    if (m >= n) 
    {
        cout << "Слушай, а ловко ты это придумал. Я даже сначала не понял. Молодец!" << endl;
        return 1;
    }
    vector<int> posl(n);
    for (int i = 0; i < n; ++i) 
    {
        cin >> posl[i];
    }
    int sumPasha = 0;
    int sumVika = 0;
    bool Turn = true; 
    int ind = 0;
    while (ind < n) {
        int bestMove = 0;
        int bestSum = numeric_limits<int>::min(); 
        for (int k = 1; k <= min(m, n - ind); ++k) {
            int currentSum = 0;
            for (int i = 0; i < k; ++i) {
                currentSum += posl[ind + i];
            }
            if (currentSum > bestSum) {
                bestSum = currentSum;
                bestMove = k;
            }
        }
        if (Turn)
        {
            sumPasha += bestSum;
        }
        else
        {
            sumVika += bestSum;
        }
        ind += bestMove;
        Turn = !Turn;
    }
    if (sumPasha > sumVika) 
    {
        cout << "1" << endl;
    }
    else 
    {
        cout << "0" << endl;
    }
    return 0;
}
