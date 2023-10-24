import matplotlib.pyplot as plt
import numpy as np
import matplotlib
import sys

# Checking the number of command-line arguments:
if len(sys.argv) != 2:
    script_name = sys.argv[0]
    print("Error: Wrong number of input arguments.")
    print(f"Usage: {script_name} <fe=Forward-Euler, rk=RK4, an=analytical solution>")
    sys.exit(1)

# Save the command-line arguments:
method = sys.argv[1]    # method used to do get the data: "fe"=Forward Fulero, "rk"=Runge Kutta, "an"=Analytical Solution

# Variables used in the program
n = [4000, 8000, 16000, 32000]

# Import the data:
filename0 = "data_nointer_" + method + str(n[0]) + ".txt"
data0 = np.loadtxt(filename0)
filename1 = "data_nointer_" + method + str(n[1]) + ".txt"
data1 = np.loadtxt(filename1)
filename2 = "data_nointer_" + method + str(n[2]) + ".txt"
data2 = np.loadtxt(filename2)
filename3 = "data_nointer_" + method + str(n[3]) + ".txt"
data3 = np.loadtxt(filename3)

# Save the data:
t0 = data0[:,0]
r0 = np.log(data0[:,1])
t1 = data1[:,0]
r1 = np.log(data1[:,1])
t2 = data2[:,0]
r2 = np.log(data2[:,1])
t3 = data3[:,0]
r3 = np.log(data3[:,1])

# Variables used in the plots
lin = 1             # line width of the plots
font_axl = 16       # font size of the axis label
font_ttl = 18       # font size of the title
font_ax = 12        # font size of the axis
font_lg = 13        # font size of the legend
# color = np.array(["red","green","blue","yellow","pink","black","orange","purple","beige","brown","gray","cyan","magenta"])


## compute r_err
# er_max1 = 
# r_err = 


## Create the plot
plt.plot(t0,r0,lw=lin,label=f'n = {n[0]}')
plt.plot(t1,r1,lw=lin,label=f'n = {n[1]}')
plt.plot(t2,r2,lw=lin,label=f'n = {n[2]}')
plt.plot(t3,r3,lw=lin,label=f'n = {n[3]}')
plt.xlabel('t',fontsize=font_axl)
plt.ylabel("log(err)",fontsize=font_axl)
# plt.title('Relative error (r(t))',fontsize=font_ttl)

# Make the plot
plt.xticks(fontsize=font_ax)
plt.yticks(fontsize=font_ax)
plt.legend(fontsize=font_lg)
plt.grid()
plt.show()