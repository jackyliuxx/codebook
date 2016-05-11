const int MAXN = (1 << 20);
vector<int> primes;
typedef pair<int, int> PII;
int fpf[MAXN]; //first prime factor
void getprimes(int n) {
    vector<int> &r = primes;
    memset(fpf, 0, sizeof(fpf));
    for (int i = 2; i < n; i++) {
        if (fpf[i] == 0) {
            r.push_back(i);
            fpf[i] = i;
        }
        for (size_t j = 0; j < r.size() && i * r[j] < n; j++) {
            fpf[i * r[j]] = r[j];
            if (i % r[j] == 0)
                break;
        }
    }
}

inline void addfactor(vector<PII> &fac, int x) {
    if (!fac.empty() && fac.back().first == x) {
        fac.back().second++;
    } else {
        fac.push_back({x, 1});
    }
}

vector<PII> factor(int n) {
    vector<PII> fac;
    size_t i = 0;
    while (n >= MAXN && primes[i] * primes[i] <= n) {
        if (n % primes[i] == 0) {
            addfactor(fac, primes[i]);
            n /= primes[i];
        } else {
            i++;
        }
    }
    if (n >= MAXN) {
        addfactor(fac, n);
    } else {
        while (n > 1) {
            addfactor(fac, fpf[n]);
            n /= fpf[n];
        }
    }
    return fac;
}

int phi(int n) {
    auto fac = factor(n);
    int r = n;
    for (auto i : fac) {
        r /= i.first;
        r *= (i.first - 1);
    }
    return r;
}
