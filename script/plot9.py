import matplotlib.pyplot as plt
import numpy as np
import matplotlib
import sys


# import and save the data from the files
F = [1,4,7]
f = [element/10 for element in F]   #parameter used in the simulation to compute the voltage

filename1 = "outsider_1.txt"
filename4 = "outsider_4.txt"
filename7 = "outsider_7.txt"

data1 = np.loadtxt(filename1)
data4 = np.loadtxt(filename4)
data7 = np.loadtxt(filename7)

wV_1 = data1[:,0]
in_1 = data1[:,1]
wV_4 = data4[:,0]
in_4 = data4[:,1]
wV_7 = data7[:,0]
in_7 = data7[:,1]


# Variables used in the plots
lin = 1             # line width of the plots
font_axl = 16       # font size of the axis label
font_ttl = 18       # font size of the title
font_ax = 12        # font size of the axis
font_lg = 13        # font size of the legend


# crete the plot    --    plot the % of remaining particles in the trap as a function of \omega_V
plt.plot(wV_1,in_1,lw=lin,label=f'f = {f[0]:.1f}')
plt.plot(wV_4,in_4,lw=lin,label=f'f = {f[1]:.1f}')
plt.plot(wV_7,in_7,lw=lin,label=f'f = {f[2]:.1f}')

plt.xlabel('$\omega_V$ [MHz]',fontsize=font_axl)
plt.ylabel('% of particles',fontsize=font_axl)
plt.xticks(fontsize=font_ax)
plt.yticks(fontsize=font_ax)
plt.legend(fontsize=font_lg)
plt.grid()
plt.show()