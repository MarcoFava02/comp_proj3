import matplotlib.pyplot as plt
import numpy as np
import matplotlib
import sys


# import and save the data from the files
F = 4
f = F/10

filename_i = "outsider_zoom4_iter.txt"
filename_n = "outsider_zoom4_noiter.txt"

data_i = np.loadtxt(filename_i)
data_n = np.loadtxt(filename_n)

wV_i = data_i[:,0]
in_i = data_i[:,1]
wV_n = data_n[:,0]
in_n = data_n[:,1]

# Variables used in the plots
lin = 1             # line width of the plots
font_axl = 16       # font size of the axis label
font_ttl = 18       # font size of the title
font_ax = 12        # font size of the axis
font_lg = 13        # font size of the legend


# crete the plot
plt.plot(wV_i,in_i,lw=lin,label=f'interactions')
plt.plot(wV_n,in_n,lw=lin,label=f'no interactions')

plt.xlabel('$\omega_V$ [MHz]',fontsize=font_axl)
plt.ylabel('% of particles',fontsize=font_axl)
plt.xticks(fontsize=font_ax)
plt.yticks(fontsize=font_ax)
plt.legend(fontsize=font_lg)
plt.grid()
plt.show()