
from turtle import width
import matplotlib.pyplot as plt
import numpy as np


def read_n_plot(name, name2, name3):#plot cells
    with open(name+".txt", "r") as file:
        data = file.readline().strip().split()
        board = [];
        for el in data:
            board.append(float(el))
    with open(name2+".txt", "r") as file:
        data2 = file.readline().strip().split()
        board2 = [];
        for el in data2:
            board2.append(float(el))
    with open(name3+".txt", "r") as file:
        data3 = file.readline().strip().split()
        board3 = [];
        for el in data3:
            board3.append(float(el))

        
    plt.figure(figsize = (10, 6))
    plt.plot(range(len(board)), board, color="blue", linewidth=2)
    plt.plot(range(len(board2)), board2, color="red", linewidth=2)
    plt.plot(range(len(board3)), board3, color="black", linewidth=2)
    plt.title(name)
    plt.ylabel(("Density of living cells [%]"))
    plt.xlabel("Time [step]")
    plt.show()

read_n_plot("Spots_Density_100x100_1","Spots_Density_100x100_2","Spots_Density_100x100_3")
read_n_plot("Spots_Density_300x300_1","Spots_Density_300x300_2","Spots_Density_300x300_3")
