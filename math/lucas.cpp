typedef long long LL;
vector<LL> F;
inline void build_F(LL M) {
    F = vector<LL>(M);
    F[0] = 1;
    for (int i = 1; i < M; i++) {
        F[i] = F[i - 1] * i % M;
    }
}

LL C(LL n, LL m, LL M) {
    if (m == 0)
        return 1;
    if (m > n)
        return 0;
    if (n < M) {
        return F[n] * inv(F[m] * F[n - m] % M, M) % M;   //extgcd.cpp
    } else {
        return C(n / M, m / M, M) * C(n % M, m % M, M) % M;
    }
}
