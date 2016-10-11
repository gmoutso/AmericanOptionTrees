import sys
import matplotlib as cm
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import AOread

filename = sys.argv[1]
metadata, data = AOread.parseAOfile(filename)
time,spots = AOread.timespots(metadata)
nooptions = metadata['options']
logspots=np.log(spots)

cmRed=plt.get_cmap('Reds')
cmBlue=plt.get_cmap('Blues')
fig=plt.figure()
    
def plotone(n):
    # get option data
    option = data[:,n,0]
    optionb = data[:,n,1]
    optionITM = option[optionb==1]
    optionOTM = option[optionb==0]
    timeITM=time[optionb==1]
    timeOTM=time[optionb==0]
    spotsITM=spots[optionb==1]
    spotsOTM=spots[optionb==0]

    # plot left graph
    ax=plt.subplot(nooptions,2,2*n+1)
    ax.autoscale(tight=False)
    scat1= ax.scatter(timeITM,spotsITM,marker='o',c=optionITM,cmap=cmRed, edgecolors='none')
    scat2= ax.scatter(timeOTM,spotsOTM,marker='o',c=optionOTM,cmap=cmBlue, edgecolors='none')
    ax.set_yscale('log')
    ax.set_xlabel('time')
    ax.set_ylabel('spot')
    ax.set_title('American Put Option heatmap')
    fig.colorbar(scat1)
    fig.colorbar(scat2)

    # plot right graph
    ax=plt.subplot(nooptions,2,2*n+2,projection='3d')
    ax.plot_trisurf(time,logspots,option,cmap=cmBlue, antialiased=False,linewidth=0)
    #ax.set_yscale('log')
    #ax.zaxis.set_major_locator(LinearLocator(10))
    #ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
    #fig.colorbar(surf, shrink=0.5, aspect=5)
    ax.set_xlabel('time')
    ax.set_ylabel('logspot')
    ax.set_zlabel('price')
    ax.set_title('American Put Option price surface')

for n in range(nooptions):
    plotone(n)
    
plt.show()
