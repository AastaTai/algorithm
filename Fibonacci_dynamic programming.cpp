#include<iostream>
#include <time.h>
using namespace std;

int Fibonacci(int f[], int num)
{
    f[0] = 1;
    f[1] = 1;
    cout << f[0] << endl << f[1] << endl;
    for (int i=2; i<=num; ++i){
        f[i] = f[i-1] + f[i-2];
        cout << f[i] << endl;
    }
    return 0;
}

int main(){
    int num = 0;
    cin >> num;
    int f[num];

    double START,END;
	START = clock();

    Fibonacci(f, num-1);

    END = clock();
    cout << "進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
}


