#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

const double PI = 3.141592653589793238460;
using namespace std;
using Complex = complex<double>;
using VecComplex = vector<Complex>;

void fft(VecComplex& a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    VecComplex a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    for (int i = 0; 2 * i < n; i++) {
        double angle = 2 * PI * i / n * (invert ? -1 : 1);
        Complex w(cos(angle), sin(angle));
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
    }
}

void printVector(const VecComplex& v, const string& label) {
    cout << "\n--- " << label << " ---\n";
    for (int i = 0; i < v.size(); ++i) {
        cout << "X[" << i << "] = " << v[i] << "  | Magnitude = " << abs(v[i]) << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    const int N = 8;
    VecComplex signal(N);

    double step = 2 * PI / N;

    cout << "--- Исходная функция: y(x) = cos(x) + sin(x) ---\n";
    for (int i = 0; i < N; ++i) {
        double x = i * step;
        signal[i] = cos(x) + sin(x);
        cout << "x[" << i << "] = " << x << "  | y[" << i << "] = " << signal[i].real() << "\n";
    }

    // Прямое БПФ
    VecComplex spectrum = signal;
    fft(spectrum, false);
    printVector(spectrum, "Прямое БПФ (FFT)");

    // Обратное БПФ
    fft(spectrum, true);
    printVector(spectrum, "Обратное БПФ (IFFT) - восстановленный сигнал");

    return 0;
}
