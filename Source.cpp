#include <iostream>
#include<vector>
#include <math.h>
#include <locale>
using namespace std;

vector<bool> generator() {
    vector<bool> number;
    srand(time(0));
    for (int i = 0; i < 128; i++) {
        unsigned long long rand_num = rand() % 32767;
        bool binary_num = rand_num % 2;
        number.push_back(binary_num);
    }
    return number;
}
void test_1(vector<bool> number)
{
    double sum_n = 0;
    for (auto i : number)
    {
        if (i == 0) sum_n += -1;
        else sum_n += 1;
    }
    sum_n /= sqrt(128);
    cout << "Первый тест: " << erfc(sum_n / sqrt(2));
}

void test_2(vector<bool> number)
{
    double psi = 0;
    for (auto i : number) if (i == 1) psi++;
    psi /= 128;
    if (fabs(psi - 0.5) >= 2 / sqrt(128)) cout << 0;
    else
    {
        int V_n = 0;
        for (size_t i = 0; i < number.size() - 1; i++) if (number[i] != number[i + 1]) V_n++;
        cout << "Второй тест: " << erfc(fabs(V_n - 256 * psi * (1 - psi)) / (32 * psi * (1 - psi)));
    }
}

void test_3(vector<bool> number)
{
    vector<size_t> v = { 0, 0, 0, 0 };
    for (size_t i = 0; i < number.size(); i += 8) {
        size_t count = 0, max = 0;
        for (size_t j = i; j < (i + 8); j++) {
            if (number[j] == 1) {
                count++;
            }
            else {
                if (count > max)max = count;
                count = 0;
            }
        }
        if (count > max)max = count;
        if (max <= 1)v[0] += 1;
        if (max == 2)v[1] += 1;
        if (max == 3)v[2] += 1;
        if (max >= 4)v[3] += 1;
    }
    double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 }, xi = 0;
    for (int i = 0; i < 4; i++) xi += pow(v[i] - 16 * pi[i], 2) / (16 * pi[i]);
    cout << "Третий тест: " << xi / 2;
}


int main() {
    setlocale(LC_ALL, "Russian");
    vector<bool> number = generator();
    for (auto i : number) {
        cout << i;
    }
    cout << endl;
    test_1(number);
    cout << endl;
    test_2(number);
    cout << endl;
    test_3(number);
    return 0;
}
