//https://hackmd.io/@Inversionpeter/rkv5WiksD
//Weights and Measures == turtle
//greedy, AC in oj
#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <time.h>
using namespace std;

struct job{
    int runtime;
    int deadline;
    int id;
};

bool comp(job a, job b){
    return a.deadline < b.deadline;
}

inline bool operator<(const job &lhs, const job &rhs){
    return lhs.runtime < rhs.runtime;
}

int main(){
    int n = 0;
    cin >> n;
    double START,END;

    job *a = new job[n+1];

    for(int i=0;i<n;i++){
        int r = 0;
        int d = 0;
        cin >> r >> d;
        if(r >= 1 && r <= 100000 && d >= 1 && d <= 100000){
            a[i].runtime = r;
            a[i].deadline = d;
            a[i].id = i+1;
        }
    }

    START = clock();
    sort(a, a+n, comp);
    vector<job> ans;
    priority_queue <job> PQ;
    int total = 0;
    int count = 0;
    job temp;

    for(int i=0; i<n; i++){
        PQ.push(a[i]);
        total = total + a[i].runtime;
        if(total > a[i].deadline){ // do not fit
            temp = PQ.top();
            PQ.pop();
            total = total - temp.runtime;
        }
        else if(total <= a[i].deadline){ // fit
            count++;
        }
    }

    END = clock();
    cout << endl;
    cout << "進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
/*
    for(int i=0; i<count; i++){
        ans.push_back(PQ.top());
        PQ.pop();
    }

    sort(ans.begin(), ans.end(), comp);
    for(int i=0; i<ans.size();i++){
        cout << ans[i].id;
        if(i!=ans.size()-1)
            cout << " ";
    }
*/
}
