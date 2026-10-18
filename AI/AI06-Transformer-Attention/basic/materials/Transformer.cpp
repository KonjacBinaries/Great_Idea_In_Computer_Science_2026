#include <iostream>
#include <cmath>
using namespace std;
const int MAXL(35);
class Matrix{
    private:
        int m_, n_; // m * n
        double value_[MAXL][MAXL];
        bool prohibited_[MAXL][MAXL];
    public:
        void operator()(int m, int n) {
            m_ = m;
            n_ = n;
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    value_[i][j] = 0;
                    prohibited_[i][j] = false;
                }
            }
            return;
        }
        friend istream &operator>>(istream &ism, Matrix &mtr);
        friend ostream &operator<<(ostream &osm, Matrix &mtr);
        friend Matrix operator*(const Matrix &A, const Matrix &B);
        void operator/=(double val) {
            for (int i = 1; i <= m_; ++i) {
                for (int j = 1; j <= n_; ++j) {
                    value_[i][j] /= val;
                }
            }
        }
        void operator^=(bool causal) {
            if (causal) {
                for (int i = 1; i <= m_; ++i) {
                    for (int j = i + 1; j <= n_; ++j) {
                        prohibited_[i][j] = true;
                    }
                }
            }
            for (int i = 1; i <= m_; ++i) {
                double maxa = value_[i][1];
                for (int j = 2; j <= n_; ++j) {
                    if (prohibited_[i][j]) break;
                    maxa = max(maxa, value_[i][j]);
                }
                for (int j = 1; j <= n_; ++j) {
                    if (prohibited_[i][j]) break;
                    value_[i][j] -= maxa;
                }
            }
            for (int i = 1; i <= m_; ++i) {
                double sum = 0.0;
                for (int j = 1; j <= n_; ++j) {
                    if (prohibited_[i][j]) value_[i][j] = 0.0;
                    else value_[i][j] = exp(value_[i][j]);
                    sum += value_[i][j];
                }
                for (int j = 1; j <= n_; ++j) {
                    value_[i][j] /= sum;
                }
            }
            return;
        } // softmax
        Matrix T() {
            Matrix qwq;
            qwq(n_, m_);
            for (int i = 1; i <= n_; ++i) {
                for (int j = 1; j <= m_; ++j) {
                    qwq.value_[i][j] = value_[j][i];
                }
            }
            return qwq;
        }
}X, W_Q, W_K, W_V, Q, K, V, S, A, O, Temporary;
istream &operator>>(istream &ism, Matrix &mtr) {
    for (int i = 1; i <= mtr.m_; ++i) {
        for (int j = 1; j <= mtr.n_; ++j) {
            ism >> mtr.value_[i][j];
        }
    }
    return ism;
}
ostream &operator<<(ostream &osm, Matrix &mtr) {
    for (int i = 1; i <= mtr.m_; ++i) {
        for (int j = 1; j <= mtr.n_; ++j) {
            osm << mtr.value_[i][j] << ' ';
        }
    }
    return osm;
}
Matrix operator*(const Matrix &A, const Matrix &B) {
    int m = A.m_, p = A.n_, n = B.n_;
    Temporary(m, n);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= p; ++k) {
                Temporary.value_[i][j] += A.value_[i][k] * B.value_[k][j];
            }
        }
    }
    return Temporary;
}

int n, d_model, d_k, d_v;
bool causal;
int main() {
    cin >> n >> d_model >> d_k >> d_v >> causal;
    X(n, d_model);
    W_Q(d_model, d_k);
    W_K(d_model, d_k);
    W_V(d_model, d_v);
    cin >> X >> W_Q >> W_K >> W_V;
    Q = X * W_Q;
    K = X * W_K;
    V = X * W_V;
    S = Q * K.T();
    S /= sqrt(d_k * 1.0);
    A = S;
    A ^= causal;
    O = A * V;
    cout << Q << endl;
    cout << K << endl;
    cout << V << endl;
    cout << S << endl;
    cout << A << endl;
    cout << O << endl;
    return 0;
}