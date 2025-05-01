import numpy as np
import matplotlib.pyplot as plt

# Параметры
N = 8
x = np.linspace(0, 2 * np.pi, N, endpoint=False)
y = np.cos(x) + np.sin(x)

# Прямое БПФ
Y_fft = np.fft.fft(y)

# Обратное БПФ
y_reconstructed = np.fft.ifft(Y_fft)

# Построение графиков
plt.figure(figsize=(10, 8))

# 1. Исходная функция — только линия
plt.subplot(3, 1, 1)
plt.plot(x, y, color='blue')
plt.title("Исходная функция: y = cos(x) + sin(x)")
plt.xlabel("x"); plt.ylabel("y"); plt.grid(True)

# 2. Спектр — столбики
plt.subplot(3, 1, 2)
plt.stem(np.arange(N), np.abs(Y_fft))
plt.title("Спектр (модуль БПФ)")
plt.xlabel("k"); plt.ylabel("|Y(k)|"); plt.grid(True)

# 3. Восстановленный сигнал — линия с точками
plt.subplot(3, 1, 3)
plt.plot(x, y_reconstructed.real, color='green', marker='o')
plt.title("Восстановленная функция после обратного БПФ")
plt.xlabel("x"); plt.ylabel("Re(y)"); plt.grid(True)

plt.tight_layout()
plt.show()
