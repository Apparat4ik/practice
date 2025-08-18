#include <iostream>
#include <vector>
#include <stdint.h>
#include <random>


using namespace std;


random_device rd;
mt19937 gen(rd());




vector<uint64_t> pr_num;

vector<uint64_t> Sieve(int n) {                 // нахождение простых чисел через решето Эратосфена
    vector<bool> is_prime(n + 1, true);
    
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            for (int j = 2*i; j <= n; j += i)
                is_prime[j] = false;
    
    for (int i = 2; i <= n; i++){
        if (is_prime[i]){
            pr_num.push_back(i);
        }
    }
    return pr_num;
}


// Быстрое возведение в степень по модулю
uint64_t Mod_pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
    if (modulus == 1) return 0;

    uint64_t result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent >>= 1;
    }

    return result;
}



vector<pair<uint64_t, uint64_t>> Decomposition(uint64_t n) {   // каноническое рахложение числа
    vector<pair<uint64_t, uint64_t>> dcompsitn;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                count++;
                n /= i;
            }
            dcompsitn.push_back({i, count});
        }
    }
    if (n > 1) {
        dcompsitn.push_back({n, 1});
    }
    return dcompsitn;
}



// Тест Миллера для проверки простоты
bool MillerTest(uint64_t n, int t) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    // Факторизуем n-1
    auto factors = Decomposition(n - 1);

    // Генератор случайных чисел
  
    uniform_int_distribution<uint64_t> dis(2, n - 1);

    // Выполняем t проверок
    vector<uint64_t> randNum;
    for (uint64_t test = 0; test < t; ++test) {
        uint64_t a = dis(gen);
        randNum.push_back(a);
    }
    for (auto a : randNum) {
        // Проверка малой теоремы Ферма
        if (Mod_pow(a, n - 1, n) != 1) {
            return false;
        }
    }

    // Дополнительные проверки для каждого простого множителя

    for (const auto& factor : factors) {
        bool all_equal_one = true;
        for (auto a : randNum) {
            uint64_t exp = (n - 1) / factor.first;
            uint64_t result = Mod_pow(a, exp, n);

            if (result != 1) {
                all_equal_one = false;
                break;
            }
        }
        if (all_equal_one) {
            return false;
        }
    }

    return true;
}


uint64_t Just_P_Gen(int k, const int& t) {
    uint64_t n_min = 1 << (k - 2), n_max = (1 << (k - 1)) - 1;
    uint64_t p = 0, m = 1;
    while (!MillerTest(p, t)) {
        m = 1;
        while (!(n_min < m && m < n_max) && (m > 0)) {
            int32_t primeIt = gen() % pr_num.size();
            uint64_t primeExp = gen() % 3;
            m *= pow(pr_num[primeIt], primeExp);
            while (m >= n_max) {
                m /= pow(pr_num[primeIt], primeExp);
                if (primeIt - 1 < 0) {
                    break;
                }
                m *= pow(pr_num[--primeIt], primeExp);
            }
        }
        p = 2 * m + 1;
    }
    
    return p;
}


pair<uint64_t, uint64_t> P_and_G_Gen(const int& k,const int& t){
    uint64_t p = Just_P_Gen(20, 10);
    uint64_t q = (p - 1) / 2, g = 0;
    do {
        if (!MillerTest(q, 10)){
            p = Just_P_Gen(k, t);
            q = (p - 1) / 2;
        }
        g = gen() % (p - 1);
    } while (Mod_pow(g, q, p) == 1);
    cout << Mod_pow(g, q, p) << endl;
    return {p, g};
}





int main(){
    Sieve(500);
    pair<uint64_t, uint64_t> p_and_g = P_and_G_Gen(20, 10);

    
    
    return 0;
}
