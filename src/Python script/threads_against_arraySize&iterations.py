"""
This program is use to determine the effect of optimized command against array size and iteration.
@Author: Shun Lyu
@Date: 7/Oct/2019
"""
import matplotlib.pyplot as plt


if __name__ == "__main__":
    
    # Against array size   Parallel/Section
    """    
    process_time_th1 = [0.66 , 5.45, 16.35, 39.40, 78.81, 145.59, 241.16]#[1.12, 8.86, 30.73, 68.03, 142.20, 245.73, 359.27]#
    process_time_th2 = [0.47 , 4.95, 15.44, 37.28, 73.72, 128.45, 207.27]#[0.77, 5.15, 17.82, 39.75, 82.42, 139.98, 227.81]#
    process_time_th3 = [0.55 , 4.65, 15.88, 36.84, 71.51, 127.45, 179.80]#[0.76, 6.55, 20.74, 48.65, 97.63, 173.28, 247.41]#
    process_time_th4 = [0.52 , 4.46, 14.37, 34.23, 65.95, 109.33, 178.08]#[0.56, 4.09, 13.6, 34.65, 76.34, 141.914, 222.68]#
    process_time_th5 = [0.61 , 4.84, 15.46, 34.44, 65.89, 114.54, 181.24]#[0.61, 4.14, 13.85, 34.72, 78.04, 139.56, 229.01]#
    process_time_th6 = [0.57 , 4.53, 15.12, 34.36, 66.37, 122.35, 189.53]#[0.62, 4.67, 14.98, 37.52, 79.30, 144.67, 233.85]#
    """
    process_time_th1 = [1.1093, 8.07, 27.75, 67.81, 142.90, 282.96, 448.13, 676.77]
    process_time_th2 = [0.8001, 6.25, 21.37, 51.7, 115.16, 204.13, 320.7, 489.47]
    process_time_th3 = [0.7669, 6.07, 20.97, 53.65, 108.55, 188.18, 300.47, 451.71]
    process_time_th4 = [0.7521, 5.99, 21.19, 52.96, 104.82, 182.31, 287.39, 430.23]
    process_time_th5 = [0.7712, 6.00, 21.32, 56.19, 106.54, 185.44, 298.84, 449.24]
    process_time_th6 = [0.66, 6.08, 21.42, 53.30, 106.74, 185.88, 302.15, 454.763]
    process_time_th7 = [0.78, 6.13, 21.58, 53.29, 105.97, 183.31, 293.34, 439.44]
    process_time_th8 = [0.833, 6.14, 21.55, 51.19, 101.43, 177.01, 277.41, 414.89]
    



    # All final result are agree to -0.0024781
    array_size = [101,201,301,401,501,601,701, 801]
    
    plt.figure()
    plt.plot(array_size, process_time_th1, label='1 Core')
    plt.plot(array_size, process_time_th2, label='2 Core')
    plt.plot(array_size, process_time_th3, label='3 Core')
    plt.plot(array_size, process_time_th4, label='4 Core')
    plt.plot(array_size, process_time_th5, label='5 Core')
    plt.plot(array_size, process_time_th6, label='6 Core')
    plt.plot(array_size, process_time_th7, label='7 Core')
    plt.plot(array_size, process_time_th8, label='8 Core')

    plt.ylabel("Time (s)")
    plt.xlabel("Size of array N")
    plt.title("Effect of thread number on execution time(Parallel)")
    plt.legend(loc="best")
    
    plt.show()
