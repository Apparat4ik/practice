#include <random>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits>


using namespace std;


vector<int8_t> Dec_to_Bin(int64_t num){  // перевод числа из десятичной системы счисления в двоичную
    vector<int8_t> binnum;
    while (num > 0){
        binnum.push_back(num % 2);
        num /= 2;
    }
    return binnum;
}


int64_t Mod_pow(int64_t a, int64_t x, const int64_t& p){   // ф-ция, которая быстро ищет a^(2^z) mod p
    a %= p;
    int64_t result = 1;
    while (x > 0){
        if (x == 1){       // когда степень = 1 записываем итоговый результат
            result = (result * a) % p;
        }
        a = (a * a) % p;   // возводим в квадрат
        x /= 2;            // делим степень на 2
    }
    return result;
}


int64_t AxmodpLog(int64_t a, int64_t x, const int64_t& p){    // вычисление a^x mod p через представление степени в двоичном виде
    if (x == 1){return a % p;}
    if (x == 0){return 1;}
    
    int max_pow_of2 = static_cast<int>(floor(log2(x)));    // максимальная степень двойки (длина двоичного представления числа)
    
    vector<int64_t> row_of_a;
    for (int i = 0; i <= max_pow_of2; i++){
        row_of_a.push_back(Mod_pow(a, pow(2, i), p));     // запиываем ряд <a, a^2, a^4, ... a^(2^z)>
    }
    
    vector<int8_t> binx = Dec_to_Bin(x);
    int64_t result = 1;
    for (int i = 0; i < max_pow_of2; i++){                // перемножаем значения ряда, на индекса которых в двоичном представлении числа стоит 1
        if (binx[i] == 1){
            result = (result * max_pow_of2) % p;
        }
    }
    return result;
}




int64_t Axmodp(int64_t a, int64_t x, const int64_t& p){    // вычисление a^x mod p классическое
    int64_t degree;
    if (x == 0){
        return a % p;
    } else if (x == p-1){
        degree = p - 1;
    } else {
        degree = x % (p - 1);     // укорачиваем степень по теореме Ферма
    }
    
    int64_t result = 1;
    for (int64_t i = 1; i <= degree; i++){     // быстрое возведение в степень
        result *= a;
        result %= p;
    }
    return result;
}



bool GCD_is1(int64_t a, int64_t b){    // проверка: НОД = 1?
    while (a % b > 0){
        int64_t r = a % b;
        a = b;
        b = r;
    }
    if (b != 1){
        return false;
    }
    return true;
}


bool Primary(const int64_t& p, const int16_t& k){    // провекра на простоту модуля p
    if (p == 2 || p == 3 || p == 5){
        return true;
    }
    
    if (p <= 1 || p % 2 == 0 || p % 3 == 0 || p % 5 == 0){
        return false;
    }
    
    mt19937_64 a_r; // берем случайное число
    int64_t a;
    for (int i = 0; i < k; i++){    // проверка идет k раз для точности проверки
        a = (a_r() % (p - 2)) + 2;
        if (Axmodp(a, (p-1), p) != 1 || !GCD_is1(a, p)){     // проверка по теореме Ферма
            return false;
        }
    }
    
    return true;
}

template<typename T>
T CorrectInput(T min_value, T max_value = numeric_limits<T>::max()){      // функция для проверки корректности вводимых чисел
    T value;
    cin >> value;
    if (cin.fail() || value < min_value || value > max_value){    // вводимое значение не должно быть строкой и входить в указанный диапазон
        stringstream serr;
        serr << "Некорректный ввод. Вы должны ввести число в диапазоне <" << min_value << ", " << max_value << ">";
        throw invalid_argument(serr.str());
    }
    return value;
}


int main(){
    try {
        cout << "Введите певрое число и его степнь через пробел: " << '\t';
        int64_t a1 = CorrectInput<int64_t>(0);
        int64_t x1 = CorrectInput<int64_t>(0);
        
        
        cout << "Введите второе число и его степнь через пробел: " << '\t';
        int64_t a2 = CorrectInput<int64_t>(0);
        int64_t x2 = CorrectInput<int64_t>(0);
        
        
        cout << "Введите число, по модулю которого числа будут сравниваться: " << '\t';
        int64_t p = CorrectInput<int64_t>(1);
        

        cout << "Введите число проверок по теореме Ферма (не больше 200): " << '\t';
        int16_t k = CorrectInput<int16_t>(1, 200);
        
        

        if (!Primary(p, k)) {
            cout << "Число p составное, введите простое число" << endl;
        }
        if (AxmodpLog(a1, x1, p) == AxmodpLog(a2, x2, p)) {
            cout << "Числа равны по модулю" << endl;
        } else {
            cout << "Числа не равны по модулю, остатки первого и второго соответственно: " <<Axmodp(a1, x1, p) << ' ' << Axmodp(a2, x2, p) << endl;
        }
    } catch (exception& s){
        cerr << s.what();
    }
    return 0;
}

