//every point in longestPrefix vector will tell us what is the longest suffix length which is also
//the same as prefix
vector<int> computePrefix(string pat){
    int m = pat.size();
    vector<int> longestPrefix(m);
    for(int i = 1, j = 0; i < m; i++){
        while(j > 0 && pat[j] != pat[i]){
            j = longestPrefix[j - 1];
        }
        if(pat[i] == pat[j]){
            longestPrefix[i] = ++j;
        }
        else{
            longestPrefix[i] = j;
        }
    }
    return longestPrefix;
}
void KMP(string str,string pat){
    int n = str.size();
    int m = pat.size();
    vector<int> longestPrefix = computePrefix(pat);
    for(int i = 0, k = 0; i < n; i++){
        while(k > 0 && pat[k] != str[i]){
            k = longestPrefix[k - 1];
        }
        if(str[i] == pat[k]){
            k++;
        }
        if(k == m){
            cout << i - m + 1 << "\n";
            k = longestPrefix[k - 1];
        }
    }
}
