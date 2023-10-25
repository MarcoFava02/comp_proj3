import matplotlib.pyplot as plt
import numpy as np
import matplotlib
import sys
from mpl_toolkits.mplot3d import Axes3D

# Checking the number of command-line arguments:
if len(sys.argv) != 5:
    script_name = sys.argv[0]
    print("Error: Wrong number of input arguments.")
    print(f"Usage: {script_name} <\"true\"/\"false\"/\"both\" to have interaction or not or both> <integer number of steps> <fe=Forward-Euler, rk=RK4> <letter of a problem \"a\" to \"d\">")
    sys.exit(1)

# Save the command-line arguments:
do_interation = sys.argv[1]         # if the data of the simulation has interaction between the particles, possible to have both data with and without interaction: "true", "false", "both"
n = int(sys.argv[2])                # nuber of steps used to run the simulation
method = sys.argv[3]                # method used to do get the data: "fe"=Forward Fulero, "rk"=Runge Kutta
prob = sys.argv[4]                  # here I can choose what problem I am solving, letters from "a" to "d"


# Variables used in the plots
lin = 1             # line width of the plots
font_axl = 16       # font size of the axis label
font_ttl = 18       # font size of the title
font_ax = 12        # font size of the axis
font_lg = 13        # font size of the legend

## Interation between the two particles
if (do_interation.lower() == "true") or (do_interation.lower() == "both"):
    
    # Import the data saved in the same directory
    filename_inter = "data_inter_" + method + str(n) + ".txt"
    data_inter = np.loadtxt(filename_inter)

    # Save the variables
    t_i = data_inter[:,0]

    x_i1 = data_inter[:,1]
    y_i1 = data_inter[:,2]
    z_i1 = data_inter[:,3]
    vx_i1 = data_inter[:,4]
    vy_i1 = data_inter[:,5]
    vz_i1 = data_inter[:,6]

    x_i2 = data_inter[:,7]
    y_i2 = data_inter[:,8]
    z_i2 = data_inter[:,9]
    vx_i2 = data_inter[:,10]
    vy_i2 = data_inter[:,11]
    vz_i2 = data_inter[:,12]


## No interation between the two particles
if (do_interation.lower() == "false") or (do_interation.lower() == "both"):

    # Import the data saved in the same directory
    filename_nointer = "data_nointer_" + method + str(n) + ".txt"
    data_nointer = np.loadtxt(filename_nointer)

    # save the variables
    t_n = data_nointer[:,0]

    x_n1 = data_nointer[:,1]
    y_n1 = data_nointer[:,2]
    z_n1 = data_nointer[:,3]
    vx_n1 = data_nointer[:,4]
    vy_n1 = data_nointer[:,5]
    vz_n1 = data_nointer[:,6]

    x_n2 = data_nointer[:,7]
    y_n2 = data_nointer[:,8]
    z_n2 = data_nointer[:,9]
    vx_n2 = data_nointer[:,10]
    vy_n2 = data_nointer[:,11]
    vz_n2 = data_nointer[:,12]


########## PROBLEM 8a ##########
##--> Simulation of a single particle for a total time of 50 mu s and 4000 steps. 
##--> Make a plot of the motion in the z direction as a function of time.

if prob == "a":
    # Some calculations
    q = 1
    V = 2.41e6
    m = 40.078
    d = 500
    omegaz = np.sqrt(2*q*V/m/d**2)  #compute the pulsation on z
    T = 2*np.pi/omegaz
    print(T)                        #the corrisponding period

    # Find the first max, after the one in t=0, to show that it corresponds to the expected period
    start_index = 700
    max_index = np.argmax(z_n1[700:800])
    t_max = t_n[max_index + start_index]
    z_max = z_n1[max_index + start_index]


    # Prepare the plot
    plt.plot(t_n,z_n1,'-',lw=lin,label=f"Particle $a$, T={T:.2f}")      #plot (t,z(t))
    plt.scatter(t_max,z_max,label=f'max = ({t_max:.2f},{z_max:.0f})')
    plt.xlabel('t [s]',fontsize=font_axl)
    plt.ylabel('z [$\mu m$]',fontsize=font_axl)

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(loc="upper right",fontsize=font_lg)
    plt.grid()
    plt.show()



########## PROBLEM 8b ##########
##--> Simulation of two particles for a total time of 50 mu s and 4000 steps. 
##--> Make a plot of the motion in the x-y plane with and without particle interactions.

if prob == "b":
    # prepare the circular models:
    R_small = 20        # R_{-}
    R_big = 44.62       # R_{+}
    theta = np.linspace(0, 2*np.pi, 100)
    x_big = R_big * np.cos(theta)
    y_big = R_big * np.sin(theta)
    x_small = R_small * np.cos(theta)
    y_small = R_small * np.sin(theta)


    # Interaction between the two particles
    plt.plot(x_i1,y_i1,lw=lin,label='Particle $a$')     #plot (x,y), particle a
    plt.plot(x_i2,y_i2,lw=lin,label='Particle $b$')     #plot (x,y), particle b
    plt.xlabel('x [$\mu m$]',fontsize=font_axl)
    plt.ylabel('y [$\mu m$]',fontsize=font_axl)
    
    # Label the first points
    plt.scatter(x_i1[0],y_i1[0],label=f'$r_a(0) = ({x_i1[0]:.0f},{y_i1[0]:.0f})$')
    plt.scatter(x_i2[0],y_i2[0],label=f'$r_b(0) = ({x_i2[0]:.0f},{y_i2[0]:.0f})$')

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()

    
    # No interaction between the two particles
    plt.plot(x_n1,y_n1,lw=lin,label='Particle $a$')     #plot (x,y), particle a
    plt.plot(x_n2,y_n2,lw=lin,label='Particle $b$')     #plot (x,y), particle b
    plt.plot(x_big,y_big,'g',lw=1)
    plt.plot(x_small,y_small,'g',lw=1)
    plt.xlabel('x [$\mu m$]',fontsize=font_axl)
    plt.ylabel('y [$\mu m$]',fontsize=font_axl)
    
    # Label the first points
    plt.scatter(x_n1[0],y_n1[0],label=f'$r_a(0) = ({x_n1[0]:.0f},{y_n1[0]:.0f})$')
    plt.scatter(x_n2[0],y_n2[0],label=f'$r_b(0) = ({x_n2[0]:.0f},{y_n2[0]:.0f})$')

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()



########## PROBLEM 8c ##########
##--> Simulation of two particles for a total time of 50 mu s and 4000 steps. 
##--> Make a plot of the trajectories in the (x,v_x) and (z,v_z) planes with and without particle interactions.

if prob == "c":
    # prepare the line for the second graph of this section
    vx_max = [31.72]*100        # v_x max value is 31.72 m/s 
    x = np.linspace(-50,50,len(vx_max))

    # prepare the point for the last graph of this section
    vz_max = 13.88              # v_z max value is 13.88 m/s 
    z = 0                       # and it corresponds to z=0 mu s


    ## Interaction between the two particles, plane (x,v_x)
    plt.plot(x_i1,vx_i1,lw=lin,label='Particle $a$')     #plot (x,v_x), particle a
    plt.plot(x_i2,vx_i2,lw=lin,label='Particle $b$')     #plot (x,v_x), particle b
    plt.xlabel('x [$\mu m$]',fontsize=font_axl)
    plt.ylabel('$v_x$ [$\mu m/\mu s$]',fontsize=font_axl)
    
    # Label the first points
    plt.scatter(x_i1[0],vx_i1[0],label=f'$(x(0),v_x(0))_a = ({x_i1[0]:.0f},{vx_i1[0]:.0f})$')
    plt.scatter(x_i2[0],vx_i2[0],label=f'$(x(0),v_x(0))_b = ({x_i2[0]:.0f},{vx_i2[0]:.0f})$')

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()


    ## No interaction between the two particles, plane (x,v_x)
    plt.plot(x_n1,vx_n1,lw=lin,label='Particle $a$')     #plot (x,v_x), particle a
    plt.plot(x_n2,vx_n2,lw=lin,label='Particle $b$')     #plot (x,v_x), particle b
    plt.plot(x,vx_max,'-k',lw=lin,label='$v_x^{max}=31.72m/s$')
    plt.xlabel('x [$\mu m$]',fontsize=font_axl)
    plt.ylabel('$v_x$ [$\mu m/\mu s$]',fontsize=font_axl)
    
    # Label the first points
    plt.scatter(x_n1[0],vx_n1[0],label=f'$(x(0),v_x(0))_a = ({x_n1[0]:.0f},{vx_n1[0]:.0f})$')
    plt.scatter(x_n2[0],vx_n2[0],label=f'$(x(0),v_x(0))_b = ({x_n2[0]:.0f},{vx_n2[0]:.0f})$')

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()

    
    ## Interaction between the two particles, plane (z,v_z)
    plt.plot(z_i1,vz_i1,lw=lin,label='Particle $a$')     #plot (x,v_z), particle a
    plt.plot(z_i2,vz_i2,lw=lin,label='Particle $b$')     #plot (x,v_z), particle b
    plt.xlabel('y [$\mu m$]',fontsize=font_axl)
    plt.ylabel('$v_z$ [$\mu m/\mu s$]',fontsize=font_axl)
    
    # Label the first points
    plt.scatter(z_i1[0],vz_i1[0],label=f'$(z(0),v_z(0))_a = ({z_i1[0]:.0f},{vz_i1[0]:.0f})$')
    plt.scatter(z_i2[0],vz_i2[0],label=f'$(z(0),v_z(0))_b = ({z_i2[0]:.0f},{vz_i2[0]:.0f})$')

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()


    ## No interaction between the two particles, plane (z,v_z)
    plt.plot(z_n1,vz_n1,lw=lin,label='Particle $a$')     #plot (x,v_z), particle a
    plt.plot(z_n2,vz_n2,lw=lin,label='Particle $b$')     #plot (x,v_z), particle b
    plt.xlabel('y [$\mu m$]',fontsize=font_axl)
    plt.ylabel('$v_z$ [$\mu m/\mu s$]',fontsize=font_axl)
    
    # Label the first points and max
    plt.scatter(z_n1[0],vz_n1[0],label=f'$(z(0),v_z(0))_a = ({z_n1[0]:.0f},{vz_n1[0]:.0f})$')
    plt.scatter(z_n2[0],vz_n2[0],label=f'$(z(0),v_z(0))_b = ({z_n2[0]:.0f},{vz_n2[0]:.0f})$')
    plt.scatter(z,vz_max,label='$v_z^{max}=13.88m/s$',c="black")

    # Make the plot
    plt.xticks(fontsize=font_ax)
    plt.yticks(fontsize=font_ax)
    plt.legend(fontsize=font_lg,loc="lower left")
    plt.grid()
    plt.axis('equal')
    plt.show()



########## PROBLEM 8d ##########
##--> Simulation of two particles for a total time of 50 mu s and 4000 steps. 
##--> Make a 3D plot of the trajectories with and without particle interactions.

if prob == "d":

    ## no interaction
    #create the figure
    ax = plt.figure().add_subplot(projection='3d')
    
    #create the 3D plot
    ax.plot(x_n1,y_n1,z_n1,lw=lin,label='Particle $a$')     #plot (x,y,z), particle a
    ax.plot(x_n2,y_n2,z_n2,lw=lin,label='Particle $b$')     #plot (x,y,z), particle b
    ax.set_xlabel('x [$\mu m$]',fontsize=font_axl)
    ax.set_ylabel('y [$\mu m$]',fontsize=font_axl)
    ax.set_zlabel('y [$\mu m$]',fontsize=font_axl)
    
    # Label the first points
    ax.scatter(x_n1[0],y_n1[0],z_n1[0],label=f'$r(0)_a = ({x_n1[0]:.0f},{y_n1[0]:.0f},{z_n1[0]:.0f})$')
    ax.scatter(x_n2[0],y_n2[0],z_n2[0],label=f'$r(0)_b = ({x_n2[0]:.0f},{y_n2[0]:.0f},{z_n2[0]:.0f})$')

    # Make the plot
    ax.tick_params(axis='x', labelsize=font_ax)
    ax.tick_params(axis='y', labelsize=font_ax)
    ax.tick_params(axis='y', labelsize=font_ax)
    ax.legend(fontsize=font_lg,bbox_to_anchor=(0.6,0.8))
    plt.show()

    ## interaction
    #create the figure
    ax = plt.figure().add_subplot(111,projection='3d')
    
    #create the 3D plot
    ax.plot(x_i1,y_i1,z_i1,lw=lin,label='Particle $a$')     #plot (x,y,z), particle a
    ax.plot(x_i2,y_i2,z_i2,lw=lin,label='Particle $b$')     #plot (x,y,z), particle b
    ax.set_xlabel('x [$\mu m$]',fontsize=font_axl)
    ax.set_ylabel('y [$\mu m$]',fontsize=font_axl)
    ax.set_zlabel('y [$\mu m$]',fontsize=font_axl)
    
    # Label the first points
    ax.scatter(x_i1[0],y_i1[0],z_i1[0],label=f'$(x(0),v_x(0))_a = ({x_i1[0]:.0f},{vx_i1[0]:.0f})$')
    ax.scatter(x_i2[0],y_i2[0],z_i2[0],label=f'$(x(0),v_x(0))_b = ({x_i2[0]:.0f},{vx_i2[0]:.0f})$')

    # Make the plot
    ax.tick_params(axis='x', labelsize=font_ax)
    ax.tick_params(axis='y', labelsize=font_ax)
    ax.tick_params(axis='y', labelsize=font_ax)
    ax.legend(fontsize=font_lg,bbox_to_anchor=(0.6,1.2))
    plt.show()

