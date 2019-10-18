"""
This program is use to print.
@Author: Shun Lyu
@Date: 7/Oct/2019
"""
import matplotlib.pyplot as plt
FILENAME = "RESULT.txt"

def read_file():
    lines = open(FILENAME).readlines()
    result = []
    for line in lines:
        result.append(line.strip())
    return result  

def plot(lines):
        
    plt.figure()
    plt.plot(range(len(lines)), lines)
    
    plt.ylabel("Y")
    plt.xlabel("X")
    plt.title("Distribution")
    plt.legend(loc="best")

    plt.show()

if __name__ == "__main__":
    
    lines = read_file()
    plot(lines)
