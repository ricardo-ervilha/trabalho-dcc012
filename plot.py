#!/usr/bin/python

import matplotlib.pyplot as plt
import matplotlib
import numpy as np
from numpy import loadtxt

matplotlib.use("TkAgg")  # abrir gráfico pelo terminal --> # sudo apt install python3-tk

comparacoesInsercao = loadtxt(
    "comparacoesInsercao.dat", comments="#", delimiter=" ", unpack=True
)

xa = comparacoesInsercao[0]
ya = comparacoesInsercao[1]

comparacoesBusca = loadtxt("comparacoesBusca.dat", comments="#", delimiter=" ", unpack=True)
xe = comparacoesBusca[0]
ye = comparacoesBusca[1]

fig1, ax1 = plt.subplots(figsize=(8,8))
plt.plot(xa, ya, marker='o')
plt.title("Comprações Inserção")
plt.xlabel('Ordem')
plt.ylabel('Comparações ')
plt.grid(True)

for x1, y1 in zip(xa, ya):
    str_xy1 = '({},{})'.format(x1, y1)
    ax1.annotate(str_xy1, xy=(x1, y1))


fig2, ax2 = plt.subplots(figsize=(8,8))
plt.plot(xe, ye,marker='o')
plt.title("Comprações Busca")
plt.xlabel('Ordem')
plt.ylabel('Comparações')

for x2, y2 in zip(xe, ye):
    str_xy2 = '({},{})'.format(x2, y2)
    ax2.annotate(str_xy2, xy=(x2, y2))

plt.grid(True)
plt.show()
