#include <iostream>
#include <vector>


using namespace std;




vector<int> Sieve(int n, vector<int>& not_prime) {                 // нахождение простых чисел через решето Эратосфена
    vector<bool> is_prime(n + 1, true);
    
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            for (int j = 2*i; j <= n; j += i)
                is_prime[j] = false;
    
    vector<int> pr_num;
    
    for (int i = 2; i <= n; i++){
        if (is_prime[i]){
            pr_num.push_back(i);
        }
    }
    return pr_num;
}



int main(){
    
    
    return 0;
}
