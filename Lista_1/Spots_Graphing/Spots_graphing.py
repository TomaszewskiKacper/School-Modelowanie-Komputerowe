
from turtle import width
import matplotlib.pyplot as plt
import numpy as np


def read_n_plot(name):#plot cells
    with open(name+".txt", "r") as file:
        data = file.readline().strip().split()
        board = [];
        for el in data:
            board.append(float(el))


        
        plt.figure(figsize = (10, 6))
        plt.plot(range(len(board)), board, color="blue", linewidth=2)
        plt.title(name)
        plt.ylabel(("Density of living cells [%]"))
        plt.xlabel("Time [step]")
        plt.show()

read_n_plot("Spots_Density")
