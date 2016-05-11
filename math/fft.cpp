//v size must be 2^k
typedef long double LD;
typedef complex<LD> CLD;
typedef vector<CLD> VCLD;
const LD PI = acosl(-1);
inline void fft(VCLD &v, bool inv = false) {
    int n = v.size();
    for (int i = 1, j = 0; i < n; i++) {
        for (int k = n >> 1; k > (j ^= k); k >>= 1);
        if (i < j) swap(v[i], v[j]);
    }
    for (int step = 2; step <= n; step <<= 1) {
        int mh = step >> 1;
        for (int i = 0; i < mh; i++) {
            CLD w = exp(CLD(0,(inv ? -1 : 1) * i * PI / mh));
            for (int j = i; j < n; j += step) {
                int k = j + mh;
                CLD x = v[j], y = w * v[k];
                v[j] = x + y;
                v[k] = x - y;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            v[i] /= n;
        }
    }
}
