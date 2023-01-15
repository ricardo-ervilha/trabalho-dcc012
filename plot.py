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

plt.subplot(1, 2, 1) # row 1, col 2 index 1
plt.plot(xa, ya)
plt.title("Comprações Inserção")
plt.xlabel('Ordem')
plt.ylabel('Comparações ')

plt.subplot(1, 2, 2) # index 2
plt.plot(xe, ye)
plt.title("Comprações Busca")
plt.xlabel('Ordem')
plt.ylabel('Comparações')

plt.grid(True)
plt.show()
