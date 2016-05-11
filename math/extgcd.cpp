int extgcd(int a, int b, int &x, int &y) {
    int r = a;
    if (b) {
        r = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1, y = 0;
    }
    return r;
}

int inv(int n, int M) {
    int x, y;
    extgcd(n, M, x, y);
    return (x < 0 ? M + x : x);
}
