template<class T>
struct Matrix {
    int row, column;
    vector<vector<T>> v;
    Matrix(int n) : row(n), column(n), v(n, vector<T>(n)) {}
    Matrix(int r, int c) : row(r), column(c), v(r, vector<T>(c)) {}
    vector<T> &operator[](int n) {
        return v[n];
    }
    const vector<T> &operator[](int n) const {
        return v[n];
    }
    Matrix operator+(const Matrix &b) const {
        const Matrix &a = *this;
        assert(a.row == b.row);
        assert(a.column == b.column);
        int n = a.size();
        Matrix r(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i][j] = a[i][j] + b[i][j];
            }
        }
        return r;
    }
    Matrix operator*(const Matrix &b) const {
        const Matrix &a = *this;
        assert(a.column == b.row);
        Matrix r(a.row, b.column);
        for (int i = 0; i < r.row; i++) {
            for (int j = 0; j < r.column; j++) {
                for (int k = 0; k < a.column; k++) {
                    r[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return r;
    }
    void GE() { //not work for integer
        for (int i = 0, dr = 0; dr < row && i < column; i++) {
            for (int j = dr; j < row; j++) {
                if (v[j][i] != 0) {
                    for (int k = 0; k < column; k++) {
                        swap(v[dr][k], v[j][k]);
                    }
                    break;
                }
            }
            if (v[dr][i] != 0) {
                for (int j = 0; j < row; j++) {
                    if (j == dr) continue;
                    T B = v[j][i] / v[dr][i];
                    for (int k = 0; k < column; k++) {
                        v[j][k] -= v[dr][k] * B;
                    }
                }
                dr++;
            }
        }
    }
    T det() const {
        assert(row == column);
        Matrix m = *this;
        m.GE();
        T r = 1;
        for (int i = 0; i < m.row; i++) {
            r *= m[i][i];
        }
        return r;
    }
    Matrix inv() const {
        assert(row == column);
        Matrix m(row, 2 * column);
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) {
                if (j < column) {
                    m[i][j] = v[i][j];
                } else if (i == j - column) {
                    m[i][j] = 1;
                } else {
                    m[i][j] = 0;
                }
            }
        }
        m.GE();
        Matrix r(row, column);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                r[i][j] = m[i][row + j] / m[i][i];
            }
        }
        return r;
    }
    friend istream& operator>>(istream &in, Matrix &m) {
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) {
                in >> m[i][j];
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream &out, const Matrix &m) {
        for (int i = 0; i < m.row; i++) {
            for (int j = 0; j < m.column; j++) {
                if (j) out << ' ';
                out << setw(14) << fixed << setprecision(7) << m[i][j];
            }
            out << endl;
        }
        return out;
    }
};
