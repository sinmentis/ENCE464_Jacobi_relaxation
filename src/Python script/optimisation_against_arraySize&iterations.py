"""
This program is use to determine the effect of optimized command against array size and iteration.
@Author: Shun Lyu
@Date: 7/Oct/2019
"""
import matplotlib.pyplot as plt

if __name__ == "__main__":
    
    # Against array size
    process_time_o0 = [13.25, 100.69, 367.151, 517.8, 1670.01, 2058.57, 2950.06, 6245.18]
    process_time_o1 = [9.8, 79.2, 190.87, 222.74, 495.62,586.566, 780.495, 1864.75]
    process_time_o2 = [0.76, 6.23, 21.61, 53.79, 107.14, 187.9, 303.483, 450.562]
    process_time_o3 = [0.79, 6.02, 21.4, 53.6, 106.79, 189.70, 298.31, 448.58]
    array_size = [100,200,300,400,500,600,700,800]
    print(len(process_time_o0))
    print(len(process_time_o1))
    print(len(process_time_o3))
    print(len(process_time_o2))
    plt.figure()
    plt.plot(array_size, process_time_o0, label='NO Optimized')
    plt.plot(array_size, process_time_o1, label='Optimized o1')
    plt.plot(array_size, process_time_o2,marker="v", label='Optimized o2')
    plt.plot(array_size, process_time_o3, label='Optimized o3')
    
    plt.ylabel("Time (s)")
    plt.xlabel("Array size")
    plt.title("Effect of Optimisation on execution time")
    plt.legend(loc="best")

    plt.show()
