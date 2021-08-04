
vector<vector<int>> TABLE;
vector<int> logs;

struct sparse_table {

    int maxn;
    int k;

    sparse_table (int n) {
        maxn = n;
        logs.resize(maxn+1, 0);

        for (int i = 2; i <= maxn; i++) logs[i] = logs[i >> 1] + 1;

        k = logs[maxn] + 1;

        TABLE.resize(maxn, vector<int> (k));
        
    }

    void create_table (vector<int> &A) {

        for (int i = 0; i < maxn; i++) TABLE[i][0] = A[i];

        for (int i = 1; i < k; i++) {

            for (int j = 0; j + (1 << i) - 1 < maxn; j++) {
                TABLE[j][i] = TABLE[j][i-1] + TABLE[j + (1 << (i-1))][i-1];
            }

        }

    }

    // indexing should be zero based

    int query (int x, int y) {

        int gap = (y - x) + 1;
        int lg = logs[gap];
        
        return max(TABLE[x][lg], TABLE[y - (1 << lg) + 1][lg]);
    }

    int query_sum (int x, int y) {

        long long ans = 0;

        int gap = y - x + 1;

        int log_gap = logs[gap];

        for (int i = log_gap; i >= 0; i--) {
            if ((1 << i) <= (y - x + 1)) {
                ans += (long long) TABLE[x][i];
                x += (1 << i);
            }
        }

        return ans;
    }

};
