#include<iostream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

long long int find_max(long long int a, long long int b, long long int c, long long int d){
    long long int M = a;
    if(b>M) M=b;
    if(c>M) M=c;
    if(d>M) M=d;
    return M;
}

long long int find_min(long long int a, long long int b, long long int c, long long int d){
    long long int m = a;
    if(b<m) m = b;
    if(c<m) m = c;
    if(d<m) m = d;
    return m;
}

void bracket(int r, int c, int len, int Cut[][150], int left[], int right[], int L[][150], int R[][150], int Mm){
    int n = Cut[r][c];
    if(Mm == 0){
        n = Cut[c][r];
    }
    int MaxOrNot = Mm;

    if(abs(r-c)+1 >= 3){
        if(n != 1 && n != len){
            if(n-r+1 >= 2){
                left[r] += 1;
                right[n+1] += 1;
            }
            if(c-(n+1)+1 >= 2){
                left[n+1] += 1;
                right[c+1] += 1;
            }
        }else if(n == 1){
            left[n+1] += 1;
            right[c+1] += 1;
        }
        else if(n == len){
            left[r] += 1;
            right[c+1] += 1;
        }

        if(MaxOrNot == 1)
            if(L[r][c] == 1) Mm = 1;
            else if (L[r][c] == 0) Mm = 0;
        else if(MaxOrNot == 0)
            if(L[c][r] == 1) Mm = 1;
            else if(L[c][r] == 0) Mm = 0;
        bracket(r, n, len, Cut, left, right, L, R, Mm);

        if(MaxOrNot == 1)
            if(R[r][c] == 1) Mm = 1;
            else if (R[r][c] == 0) Mm = 0;
        else if(MaxOrNot == 0)
            if(R[c][r] == 1) Mm = 1;
            else if(R[c][r] == 0) Mm = 0;
        bracket(n+1, c, len, Cut, left, right, L, R, Mm);
    }
    else{
        return;
    }
}

bool isOperator(char op){
    return (op == '+' || op == '-' || op == '*');
}

void maxValue(string s){
    vector<long long int> num;
    vector<char> op;
    string tmp = "";

    // store operators and numbers
    for(int i=0; i<s.length(); i++){
        if(isOperator(s[i])){
            op.push_back(s[i]);
            num.push_back(atoi(tmp.c_str()));
            tmp = "";
        }
        else{
            tmp += s[i];
        }
    }
    num.push_back(atoi(tmp.c_str()));

    long long int max_int = 9223372036854775807;
    int len = num.size();
    long long int Val[len+1][len+1];
    int Cut[len+1][150];
    int L[len+1][150]; // 1->Max  0->min
    int R[len+1][150];

    // initializing Val 2D array
    for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            Cut[i][j] = 0;
            L[i][j] = 0;
            R[i][j] = 0;
            if(i > j){
                Val[i][j] = max_int;
            }else{
                if(i == j){
                    Val[i][j] = num[i-1];
                }else{
                    Val[i][j] = -10000;
                }
            }
        }
    }

    long long int M = 9223372036854775807;
    long long int m = -9223372036854775807;
    int cut = -1;

    long long int a = 0;
    long long int b = 0;
    long long int e = 0;
    long long int d = 0;

    for(int c=1; c<len; c++){
        int row = 1;
        int col = row+c;
        while(row < len && col <= len){
            for(int i=row; i<col; i++){
                cut = i;
                if(op[i-1] == '+'){
                    a = Val[row][i] + Val[i+1][col];
                    b = Val[row][i] + Val[col][i+1];
                    e = Val[i][row] + Val[i+1][col];
                    d = Val[i][row] + Val[col][i+1];
                }else if(op[i-1] == '-'){
                    a = Val[row][i] - Val[i+1][col];
                    b = Val[row][i] - Val[col][i+1];
                    e = Val[i][row] - Val[i+1][col];
                    d = Val[i][row] - Val[col][i+1];
                }else if(op[i-1] == '*'){
                    a = Val[row][i] * Val[i+1][col];
                    b = Val[row][i] * Val[col][i+1];
                    e = Val[i][row] * Val[i+1][col];
                    d = Val[i][row] * Val[col][i+1];
                }
                M = find_max(a, b, e, d);
                m = find_min(a, b, e, d);

                if(M > Val[row][col]){
                    Val[row][col] = M;
                    Cut[row][col] = cut;
                    if(M==a){
						L[row][col]=1;
						R[row][col]=1;
					}
					else if(M==b){
						L[row][col]=1;
						R[row][col]=0;
					}
					else if(M==e){
						L[row][col]=0;
						R[row][col]=1;
					}
					else if(M==d){
						L[row][col]=0;
						R[row][col]=0;
					}
                }
                if(m < Val[col][row]){
                    Val[col][row] = m;
                    Cut[col][row] = cut;
                    if(m==a){
						L[col][row]=1;
						R[col][row]=1;
					}
					else if(m==b){
						L[col][row]=1;
						R[col][row]=0;
					}
					else if(m==e){
						L[col][row]=0;
						R[col][row]=1;
					}
					else if(m==d){
						L[col][row]=0;
						R[col][row]=0;
					}
                }
            }
            row++;
            col++;
        }
    }

    int r = 1;
    int c = len;
    int left[len+2];
    int right[len+2];
    for(int i=0; i<=len+1; i++){
        left[i] = right[i] = 0;
    }
    cout << Val[r][c] << endl;
    // record where is the brackets
    bracket(r, c, len, Cut, left, right, L, R, 1);

    //print the outcome
    for(int i=0; i<len; i++){
        if(i == 0){
            if(left[i+1] > 0){
                for(int t=1; t<=left[i+1]; t++) cout << "(";
            }
            cout << num[i];
            cout << op[i];
            if(right[i+2] > 0){
                for(int t=1; t<=right[i+2]; t++) cout << ")";
            }
            if(left[i+2] > 0){
                for(int t=1; t<=left[i+2]; t++) cout << "(";
            }
        }else if(i == len-1){
            cout << num[i];
            if(right[i+2] > 0){
                for(int t=1; t<=right[i+2]; t++) cout << ")";
            }
        }
        else{
            cout << num[i];
            if(right[i+2] > 0){
                for(int t=1; t<=right[i+2]; t++) cout << ")";
            }
            cout << op[i];
            if(left[i+2] > 0){
                for(int t=1; t<=left[i+2]; t++) cout << "(";
            }
        }
    }
}
int main(){
    string expression = "";
    cin >> expression;
    maxValue(expression);
    return 0;
}

/*
Test
5-8+7*4-8+9
200
5-((8+7)*(4-(8+9)))
-
2+7*5
45
(2+7)*5
-
1+2*3+4*5
105
(1 + 2)*(3 + 4)*5
-
2+4*7-5*8
296
(((2+4)*7)-5)*8

*/
