import math
import numpy as np
import matplotlib.pyplot as plt

def load_threshold_csv(filename):
    """
    CSV формата:
    Размер массива,Рандомные числа,Отсортированы по невозрастанию,Почти отсортированный массив
    ...
    """
    data = np.loadtxt(filename, delimiter=",", skiprows=1)
    n = data[:, 0]
    random_vals = data[:, 1]
    reversed_vals = data[:, 2]
    almost_vals = data[:, 3]
    return n, random_vals, reversed_vals, almost_vals


def plot_threshold(filename, threshold, out_png=None):
    n, rnd, rev, alm = load_threshold_csv(filename)

    plt.figure()
    plt.plot(n, rnd, label="случайный")
    plt.plot(n, rev, label="обратно отсортированный")
    plt.plot(n, alm, label="почти отсортированный")
    plt.xlabel("Размер массива n")
    plt.ylabel("Время, мкс")
    plt.title(f"MERGE+INSERTION SORT, threshold = {threshold}")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    if out_png is not None:
        plt.savefig(out_png, dpi=300)
    plt.show()


def load_dop_csv(filename):
    """
    CSV формата:
    Размер массива,30,50,100,125,170
    ...
    """
    data = np.loadtxt(filename, delimiter=",", skiprows=1)
    n = data[:, 0]
    t30 = data[:, 1]
    t50 = data[:, 2]
    t100 = data[:, 3]
    t125 = data[:, 4]
    t170 = data[:, 5]
    return n, t30, t50, t100, t125, t170


def plot_dop_all(filename, out_png=None):
    n, t30, t50, t100, t125, t170 = load_dop_csv(filename)

    plt.figure()
    plt.plot(n, t30, label="threshold = 30")
    plt.plot(n, t50, label="threshold = 50")
    plt.plot(n, t100, label="threshold = 100")
    plt.plot(n, t125, label="threshold = 125")
    plt.plot(n, t170, label="threshold = 170")
    plt.xlabel("Размер массива n")
    plt.ylabel("Время, мкс")
    plt.title("Случайные массивы, сравнение разных threshold")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    if out_png is not None:
        plt.savefig(out_png, dpi=300)
    plt.show()


def plot_dop_zoom(filename, n_min, n_max, out_png=None):
    n, t30, t50, t100, t125, t170 = load_dop_csv(filename)
    mask = (n >= n_min) & (n <= n_max)

    plt.figure()
    plt.plot(n[mask], t30[mask], label="threshold = 30")
    plt.plot(n[mask], t50[mask], label="threshold = 50")
    plt.plot(n[mask], t100[mask], label="threshold = 100")
    plt.plot(n[mask], t125[mask], label="threshold = 125")
    plt.plot(n[mask], t170[mask], label="threshold = 170")
    plt.xlabel("Размер массива n")
    plt.ylabel("Время, мкс")
    plt.title(f"Случайные массивы, n от {n_min} до {n_max}")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    if out_png is not None:
        plt.savefig(out_png, dpi=300)
    plt.show()


def plot_all_thresholds_random(thr_files, thresholds, out_png=None):
    """
    thr_files  – список файлов threshold_X.csv
    thresholds – соответствующие значения порога
    строится один график: только случайные массивы для разных threshold.
    """
    plt.figure()
    for filename, thr in zip(thr_files, thresholds):
        n, rnd, _, _ = load_threshold_csv(filename)
        plt.plot(n, rnd, label=f"threshold = {thr}")
    plt.xlabel("Размер массива n")
    plt.ylabel("Время, мкс")
    plt.title("Случайные массивы, сравнение различных threshold")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    if out_png is not None:
        plt.savefig(out_png, dpi=300)
    plt.show()


if __name__ == "__main__":
    plot_threshold("threshold_0.csv", 0, "thr0.png")
    plot_threshold("threshold_5.csv", 5, "thr5.png")
    plot_threshold("threshold_10.csv", 10, "thr10.png")
    plot_threshold("threshold_15.csv", 15, "thr15.png")
    plot_threshold("threshold_30.csv", 30, "thr30.png")
    plot_threshold("threshold_50.csv", 50, "thr50.png")

    # Сравнение порогов на случайных массивах
    thr_files = [
        "threshold_0.csv",
        "threshold_5.csv",
        "threshold_10.csv",
        "threshold_15.csv",
        "threshold_30.csv",
        "threshold_50.csv",
    ]
    thresholds = [0, 5, 10, 15, 30, 50]
    plot_all_thresholds_random(thr_files, thresholds, "random_thresholds.png")

    # Дополнительный лист: сравнение threshold = 30, 50, 100, 125, 170
    plot_dop_all("help_list.csv", "dop_all.png")

    # При необходимости – «зум» по диапазону n (например, только маленькие размеры):
    plot_dop_zoom("help_list.csv", 500, 3000, "dop_zoom_small.png")
    plot_dop_zoom("help_list.csv", 3000, 10000, "dop_zoom_large.png")
