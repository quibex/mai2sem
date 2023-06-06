

void build_pref_func(char *s, int *p, int n){
    p[0] = 0;
    for (int i = 1; i < n; i++){
        int j = p[i-1];
        // if (s[j] == s[i]){
        //     p[i] == j+1;
        //     continue;
        // }
        while ((j > 0) && (s[j] != s[i])){
            j = p[j-1];
        }
        if (s[j] == s[i]) {
            p[i] = j + 1;
        }
        else {
            p[i] = 0;
        }
    }
}

int kmp(char *t, char *s){
    int m = strlen(s);
    int n = strlen(t);
    int p[m];
    build_pref_func(s, p, m);
    int j = 0;
    for (int i = 0; i < n; i++){
        while ((j > 0) && (t[i] == s[j])) j = p[j-1];
        if (t[i] == s[j]){
            j++;
        } else {j = 0;}
        if (j == m) return i-m;
    }
    return n-1;
}