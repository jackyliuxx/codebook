typedef long long LL;
struct Bigint {
    static const int M = 10000;
    
    int sign;
    vector<int> v;

    Bigint() : sign(1) {};
    Bigint(LL n) {
        if (n < 0)
            sign = -1, n = -n;
        else
            sign = 1;
        while (n) {
            v.push_back(n % M);
            n /= M;
        }
    }
    Bigint(const string &s) {
        int sp;
        if (!s.empty() && s[0] == '-')
            sign = -1, sp = 1;
        else
            sign = 1, sp = 0;
        int b = 1;
        for (int i = s.size() - 1; i >= sp; i--) {
            if (b == 1) v.push_back(0);
            v.back() += (s[i] - '0') * b;
            b *= 10;
            if (b >= M) b = 1;
        }
        rbz();
    }
    void rbz() {
        while (!v.empty() && v.back() == 0)
            v.pop_back();
        if (v.empty())
            sign = 1;
    }
    int len() const {
        return v.size();
    }
    int compare(const Bigint &b) const {
        const Bigint &a = *this;
        if (b.sign != a.sign) return a.sign - b.sign;
        int r = 0;
        if (a.len() != b.len()) r = a.len() - b.len();
        for (int i = a.len() - 1; i >= 0 && r == 0; i--)
            r = a.v[i] - b.v[i];
        return (a.sign == -1 ? -r : r);
    }
    bool operator<(const Bigint &b) const {
        return compare(b) < 0;
    }
    bool operator<=(const Bigint &b) const {
        return compare(b) <= 0;
    }
    bool operator>(const Bigint &b) const {
        return compare(b) > 0;
    }
    bool operator>=(const Bigint &b) const {
        return compare(b) >= 0;
    }
    bool operator==(const Bigint &b) const {
        return compare(b) == 0;
    }
    bool operator!=(const Bigint &b) const {
        return compare(b) != 0;
    }
    Bigint operator-() const {
        Bigint r = *this;
        r.sign = -r.sign;
        return r;
    }
    Bigint operator+(const Bigint &b) const {
        const Bigint &a = *this;
        if (a.sign == -1) return b - (-a);
        if (b.sign == -1) return a - (-b);
        int l = max(a.len(), b.len());
        Bigint r;
        r.v.assign(l + 1, 0);
        for (int i = 0; i < l; i++) {
            if (i < a.len()) r.v[i] += a.v[i];
            if (i < b.len()) r.v[i] += b.v[i];
            if (r.v[i] > M) {
                r.v[i + 1] += r.v[i] / M;
                r.v[i] %= M;
            }
        }
        r.rbz();
        return r;
    }
    Bigint operator-(const Bigint &b) const {
        const Bigint &a = *this;
        if (a.sign == -1) return -(-a + b);
        if (b.sign == -1) return a + (-b);
        if (a < b) return -(b - a);
        Bigint r = a;
        for (int i = 0; i < b.len(); i++) {
            r.v[i] -= b.v[i];
            if (r.v[i] < 0) {
                r.v[i] += M;
                r.v[i + 1]--;
            }
        }
        r.rbz();
        return r;
    }
    Bigint operator*(const Bigint &b) const {
        const Bigint &a = *this;
        Bigint r;
        r.v.assign(a.len() + b.len() + 1, 0);
        r.sign = a.sign * b.sign;
        for (int i = 0; i < a.len(); i++) {
            for (int j = 0; j < b.len(); j++) {
                int k = i + j;
                r.v[k] += a.v[i] * b.v[j];
                if (r.v[k] >= M) {
                    r.v[k + 1] += r.v[k] / M;
                    r.v[k] %= M;
                }
            }
        }
        r.rbz();
        return r;
    }
    Bigint operator/(const Bigint &b) const {
        const Bigint &a = *this;
        if (a.len() < b.len()) return 0;
        Bigint r;
        r.v.assign(a.len() - b.len() + 1, 0);
        r.sign = a.sign * b.sign;
        Bigint na, nb = b, nr;
        na.v.assign(a.v.end() - b.len() + 1, a.v.end() + 0);
        nb.sign = 1;
        nr.v.assign(1, 0);
        for (int i = a.len() - b.len(); i >= 0; i--) {
            na = na * M + a.v[i];
            int fr = 0, to = M;
            while (to - fr > 1) {
                nr.v[0] = (fr + to) / 2;
                if (nb * nr <= na)
                    fr = nr.v[0];
                else
                    to = nr.v[0];
            }
            na = na - nb * fr;
            r.v[i] = fr;
        }
        r.rbz();
        return r;
    }
    Bigint operator%(const Bigint &b) const {
        const Bigint &a = *this;
        return a - (a / b) * b;
    }
    friend istream& operator>>(istream &in, Bigint &n) {
        string s;
        in >> s;
        n = s;
        return in;
    }
    friend ostream& operator<<(ostream &out, const Bigint &n) {
        if (n.sign == -1) out << '-';
        if (n.v.empty()) {
            out << 0;
        } else {
            out << n.v.back();
        }
        for (int i = n.len() - 2; i >= 0; i--) {
            out << setw(4) << setfill('0') << n.v[i];
        }
        return out;
    }
};
