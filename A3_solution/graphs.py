%matplotlib inline

import math
import numpy as np
import matplotlib.pyplot as plt

def load_threshold(filename):
    """
    Читает файл threshold_X.csv формата:
    Размер массива,Рандомные числа,Отсортированы по невозрастанию,Почти отсортированный массив
    N, rand_time, desc_time, almost_time
    """
    sizes = []
    rand = []
    desc = []
    almost = []
    first = True
    with open(filename, encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split(",")
            if first:
                first = False
                continue
            sizes.append(int(parts[0]))
            rand.append(float(parts[1]))
            desc.append(float(parts[2]))
            almost.append(float(parts[3]))
    return (
        np.array(sizes),
        np.array(rand),
        np.array(desc),
        np.array(almost),
    )
sizes_q, q_rand, q_desc, q_almost = load_threshold("threshold_0.csv")
intro_file = "threshold_5.csv"
sizes_i, i_rand, i_desc, i_almost = load_threshold(intro_file)
if not np.array_equal(sizes_q, sizes_i):
    raise ValueError("Размеры массивов в threshold_0 и {} не совпадают".format(intro_file))

sizes = sizes_q

print("Размеры массивов:", sizes[:10], "... (всего", len(sizes), ")")
print("QUICK TIMES (rand/desc/almost):", q_rand[:3], q_desc[:3], q_almost[:3], "...")
print("INTRO TIMES (rand/desc/almost):", i_rand[:3], i_desc[:3], i_almost[:3], "...")
def draw_single(x, y, title, ylabel, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(x, y, marker="o", linewidth=1.5, markersize=4)
    plt.xlabel("Размер массива N")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.show()
def draw_compare(x, y1, y2, label1, label2, title, ylabel, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(x, y1, marker="o", linewidth=1.5, markersize=4, label=label1)
    plt.plot(x, y2, marker="s", linewidth=1.5, markersize=4, label=label2)
    plt.xlabel("Размер массива N")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(filename, dpi=300)
    plt.show()
draw_single(
    sizes, q_rand,
    "QUICK SORT на массивах рандомных чисел",
    "Время, мс",
    "quick_random.png",
)

draw_single(
    sizes, q_desc,
    "QUICK SORT на массивах, отсортированных по невозрастанию",
    "Время, мс",
    "quick_desc.png",
)

draw_single(
    sizes, q_almost,
    "QUICK SORT на почти отсортированных массивах",
    "Время, мс",
    "quick_almost.png",
)
draw_single(
    sizes, i_rand,
    "INTROSORT на массивах рандомных чисел",
    "Время, мс",
    "intro_random.png",
)

draw_single(
    sizes, i_desc,
    "INTROSORT на массивах, отсортированных по невозрастанию",
    "Время, мс",
    "intro_desc.png",
)

draw_single(
    sizes, i_almost,
    "INTROSORT на почти отсортированных массивах",
    "Время, мс",
    "intro_almost.png",
)
draw_compare(
    sizes, q_rand, i_rand,
    "QUICK SORT", "INTROSORT",
    "Сравнение QUICK SORT и INTROSORT (рандомные массивы)",
    "Время, мс",
    "cmp_random.png",
)

draw_compare(
    sizes, q_desc, i_desc,
    "QUICK SORT", "INTROSORT",
    "Сравнение QUICK SORT и INTROSORT (невозрастающий порядок)",
    "Время, мс",
    "cmp_desc.png",
)

draw_compare(
    sizes, q_almost, i_almost,
    "QUICK SORT", "INTROSORT",
    "Сравнение QUICK SORT и INTROSORT (почти отсортированные массивы)",
    "Время, мс",
    "cmp_almost.png",
)
