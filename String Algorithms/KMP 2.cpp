//TC-O(N+m)
#include<bits/stdc++.h>
using namespace std;

vector<int> computePrefixLength(string pat){//TC-O(N)
    int len=pat.length();
    vector<int> longestPrefix(len);
    for(int i=1,j=0;i<len;++i){
        while(j>0 && pat[i]!=pat[j]){
            j=longestPrefix[j-1];
        }
        if(pat[i]==pat[j]){
            longestPrefix[i]=++j;
        }else{
            longestPrefix[i]=longestPrefix[j];
        }
    }
    return longestPrefix;
}

void KMP(string str,string pat){
    int n = str.size();
    int m = pat.size();
    vector<int> longestPrefix = computePrefixLength(pat);
    int cnt=0;
    for(int i=0,k=0;i<n;i++){
        while(k>0&&pat[k]!=str[i]){
            k=longestPrefix[k-1];
        }
        if(str[i]==pat[k]){
            k++;
        }
        if(k==m){
            //cout << i - m + 1 << "\n";//for indexes
            cnt++;//count no of occurences
            k=longestPrefix[k-1];
        }
    }
    cout<<cnt;
}


int main(){
    string txt="";cin>>txt;
    string pattern="";cin>>pattern;
    // for(int i=0;i<(int)prefix.size();++i)
    //     cout<<prefix[i]<<" ";
    // cout<<endl;
    KMP(txt,pattern);
    return 0;
}
