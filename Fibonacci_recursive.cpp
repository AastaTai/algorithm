#include<iostream>
#include <time.h>
using namespace std;

int Fibonacci(int n){
    if(n == 1 || n == 2){
        return 1;
    }
    else if( n >= 3 ){
        return Fibonacci(n-1) + Fibonacci(n-2);
    }
}

int main(){
    int num;
    cin >> num;

    double START,END;
	START = clock();
	for(int i=1; i<=num; i++){
        cout << Fibonacci(i) << endl;
	}

    END = clock();
    cout << "進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
}


