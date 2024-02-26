
import matplotlib.pyplot as plt
import numpy as np

rolls = [0,0,0,0,0,0,0,0,0,0,0,0];

def read_n_plot(name):#plot board moves
    with open(name+".txt", "r") as file:
        data = file.readline().strip().split()
        roll = file.readline().strip().split()
        board = [];
        for el in data:
            board.append(float(el))
        for index, el in enumerate(roll):
            rolls[index] += float(el)


        plt.figure(figsize = (10, 6))
        plt.bar(range(1,41), board, color="blue", edgecolor = "black", width = 1)
        plt.title(name)
        plt.ylabel(("szansa staniecia na polu [%]"))
        plt.xlabel("pole")
        plt.show()

read_n_plot("monopol_100")
read_n_plot("monopol_1000000")
read_n_plot("monopol_jail_1000000")
read_n_plot("monopol_jail_100")

for ind, el in enumerate(rolls):
    rolls[ind]/=(100*2)+(1000000 * 2)
    rolls[ind]*=100

plt.figure(figsize = (10, 6))
plt.bar(range(1,13), rolls, color="blue", edgecolor = "black", width = 1)
plt.title("rozlozenie wartosci rzutow 2 kostkami")
plt.ylabel(("szansa [%]"))
plt.xlabel("wyrzucona wartosc")
plt.show()