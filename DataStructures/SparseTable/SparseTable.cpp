//
// Created by 秋鱼 on 2022/12/6.
//

#pragma once

using namespace std;

/// =======================================================================================
/// Sparse Table（稀疏表）
/// 一种采用倍增思想的二维表格，通过 O(nlongn) 的时间构建一个二维表格，可以在 O(1) 的时间内查询 [l,r] 间的最值
/// =======================================================================================

template<typename T> requires std::is_arithmetic_v<T>
struct SparseTable {
    vector<vector<T>> ST;     // 二维表格 ST[i][j] 表示 [i, i + 2^j-1] 区间内的最值
    function<T(T, T)> OP;

    /**
     * @brief 根据数组创建稀疏表
     * @param v 下标从 1 开始的数据数组
     * @param n 数据的大小
     */
    SparseTable(const vector<T>& v, int n, function<T(T, T)> op) {
        auto k = static_cast<int>(std::log2(n));
        OP = op;

        ST = vector<vector<T>>(n + 1, vector<T>(k + 1));

        for (int i = 1; i <= n; ++i)
            ST[i][0] = v[i];        // 区间长度为 1 的最值是其本身

        // 根据递推的思想，长度为 2^j 的区间最值，可以看作两个长度为 2^(j-1) 区间的最值
        // 递推公式：ST[i,j] = op(ST[i, j-1], ST[i+2^(j-1), j-1])
        for (int j = 1; j <= k; ++j)
            for (int i = 1; i <= n - (1 << j) + 1; ++i)  // 因为 i+2^j-1 => i <= n-2^j+1
                ST[i][j] = OP(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
    }

    /**
     * @brief 查询 [l,r] 区间的最值
     */
    T query(int l, int r) {
        // 区间长度为 r - l + 1，查询分别以左右端点向后向前的两个区间中的最值
        // 公式：OP(ST[l, k], ST[r-2^k, k]
        auto k = static_cast<int>(std::log2(r - l + 1));

        return OP(ST[l][k], ST[r - (1 << k) + 1][k]);
    }
};

int main() {
    vector<int> v{0, 18, 4, 6, 23, 12, 16, 21, 51, 12, 17};
    
    SparseTable<int> st{v, 10, [](int a, int b){
        return a < b ? b : a;
    }};
    
    cout << st.query(1, 3) << endl;
    cout << st.query(1, 10) << endl;
    cout << st.query(3, 6) << endl;
    cout << st.query(3, 3) << endl;
    cout << st.query(7, 9) << endl;
}