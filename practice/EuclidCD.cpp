#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <cstdint>


using namespace std;


int64_t ExtendedEuclid(int64_t a, int64_t b){   // расщиренный алгоритм Евклида
    vector<int64_t> U = {a, 1, 0};   // строка таблицы Евклида под индексом j-2
    vector<int64_t> V = {b, 0, 1};   // строка таблицы Евклида под индексом j-1
    vector<int64_t> T = {0, 0, 0};   // строка таблицы Евклида под индексом j
    while (V[0] != 0){
        int64_t q = U[0] / V[0];     // q - частное
        T = {U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2]};   // в текущую строку записывается остаток, x, y
        U = V;  // остальные строки смещаются на одну позицию вниз
        V = T;
    }
    
    if (U[0] != 1){
        stringstream serr;
        serr << "Числа c и m не взаимно простые, значит нет такого числа d, что c*d mod m = 1";
        throw logic_error(serr.str());
    }
    
    return U[1];
}

template<typename T>
T CorrectInput(T min_value = numeric_limits<T>::min(), T max_value = numeric_limits<T>::max()){
    T value;
    cin >> value;
    if (cin.fail() || value < min_value || value > max_value){
        stringstream serr;
        serr << "Некорректный ввод. Вы должны ввести число в диапазоне <" << min_value << ", "  << max_value << ">";
        throw invalid_argument(serr.str());
    }
    return value;
}

int main(){
    try {
        cout << "Вычислим такое число d: c*d mod m = 1" << endl;
        cout << "Введите числа c (число для обратного элемента) и m (модуль): " << endl;
        int64_t c = CorrectInput<int64_t>();
        int64_t m = CorrectInput<int64_t>();
        
        int64_t d = ExtendedEuclid(c, m);
        cout << "d = " << d << endl;
        cout << c << "*" << d << " mod " << m << " = " << (c * d) % m << endl;
    } catch (exception& s){
        cerr << s.what();
    }
    
    return 0;
}
