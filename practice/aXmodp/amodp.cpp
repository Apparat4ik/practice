#include <iostream>

using namespace std;

bool Primary(int n){
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0){return false;}
    }
    return true;
}

int main(){
    int a;
    cin >> a;
    
    int x;
    cin >> x;
    
    int p;
    cin >> p;
    
    if (Primary(p) == false){
        return 0;
    }
    
    
    
    return 0;
}
