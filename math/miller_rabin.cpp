typedef long long LL;
inline LL mul(LL a, LL b, LL M) {
    //return a * b % M;
    LL r = 0;
    a %= M;
    b %= M;
    while (b) {
        if (b & 1) r = (r + a >= M ? r + a - M : r + a);
        a = (a + a >= M ? a + a - M : a + a);
        b >>= 1;
    }
    return r;
}

inline LL power(LL a, LL b, LL M) {
    LL r = 1;
    while (b) {
        if (b & 1) r = mul(r, a, M);
        a = mul(a, a, M);
        b >>= 1;
    }
    return r;
}

bool miller_rabin(LL n, LL a) {
    if (a % n == 0) return true;
    if (__gcd(a, n) != 1) return false;
    LL s = 0, d = n - 1;
    while (!(d & 1)) {
        s++;
        d >>= 1;
    }
    LL x = power(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }
    for (int i = 1; i < s; i++) {
        x = mul(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

bool isprime(LL n) {
    if (n < 2) return false;
    vector<LL> a = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    //vector<LL> a = {2, 7, 61};
    for (auto i : a) {
        if (!miller_rabin(n, i)) {
            return false;
        }
    }
    return true;
}
