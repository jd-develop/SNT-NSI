# coding:utf-8
import time


def taille_binaire1(n):
    # nb_sums = 0
    # nb_products = 0
    k = 1
    p = 2
    while p < n:
        k += 1
        p *= 2
        # nb_sums += 1
        # nb_products += 1
    return k  # , nb_sums, nb_products


def taille_binaire2(n):
    # nb_sums = 0
    # nb_products = 0
    k = 1
    while 2**k < n:
        k += 1
        # nb_products += k-1
        # nb_sums += 1
    return k  # , nb_sums, nb_products


# print(taille_binaire1(100))  # (7, 6, 6)
# print(taille_binaire2(100))  # (7, 6, 21)

def get_func_time(func, *args, **kwargs):
    start_time = time.time()
    func(*args, **kwargs)
    return float(time.time() - start_time)


values = [0, 1, 5, 8, 26, 54, 900, 1_000_000, 1e300]
temps_1 = [get_func_time(taille_binaire1, i) for i in values]
temps_2 = [get_func_time(taille_binaire2, i) for i in values]

assert len(temps_1) == len(temps_2) == len(values)
for i, e in enumerate(values):
    print(f"Pour la valeur {e:>7} : temps 1 {str(temps_1[i]*1000)+'ms':<23} et temps 2 {str(temps_1[i]*1000)+'ms'}.")
