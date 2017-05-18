import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc("text", usetex = True)

reticulo1 = np.loadtxt("Canal_ionico.txt")
reticulo2 = np.loadtxt("Canal_ionico1.txt")
datos1 = np.loadtxt("caminata1.txt")
datos2 = np.loadtxt("caminata2.txt")

fig, ax = plt.subplots(figsize = (5,5))
ax.scatter(reticulo1[:,0], reticulo1[:,1], s = 10, alpha = 0.5)
radio = np.amax(datos1[:,2])
index = np.argmax(datos1[:,2])
ax.scatter(datos1[index,0], datos1[index,1])
theta = np.linspace(0, 2*np.pi, 1000)
circulo_x = radio*np.cos(theta) + datos1[index,0]
circulo_y = radio*np.sin(theta) + datos1[index,1]
ax.plot(circulo_x, circulo_y)
ax.set_xlabel(r"$x(\AA)$")
ax.set_ylabel(r"$y(\AA)$")
ax.set_title(r"$x=%f\AA$, $y=%f\AA$, $r=%f\AA$" % (datos1[index,0], datos1[index,1], radio)) 
fig.savefig("canal_ionico_1.pdf")
plt.close(fig)

fig, ax = plt.subplots(figsize = (5,5))
ax.scatter(reticulo2[:,0], reticulo2[:,1], s = 10, alpha = 0.5)
radio = np.amax(datos2[:,2])
index = np.argmax(datos2[:,2])
ax.scatter(datos2[index,0], datos2[index,1])
theta = np.linspace(0, 2*np.pi, 1000)
circulo_x = radio*np.cos(theta) + datos2[index,0]
circulo_y = radio*np.sin(theta) + datos2[index,1]
ax.plot(circulo_x, circulo_y)
ax.set_xlabel(r"$x(\AA)$")
ax.set_ylabel(r"$y(\AA)$")
ax.set_title(r"$x=%f\AA$, $y=%f\AA$, $r=%f\AA$" % (datos2[index,0], datos2[index,1], radio)) 
fig.savefig("canal_ionico_2.pdf")
plt.close(fig)

fig, ax = plt.subplots(1, 2, figsize = (5,5))
ax[0].hist(datos1[:,0])
ax[0].set_xlabel(r"$x(\AA)$")
ax[0].set_title(r"Histograma $x$")
ax[1].hist(datos1[:,1])
ax[1].set_xlabel(r"$y(\AA)$")
ax[1].set_title(r"Histograma $y$")
plt.tight_layout()
fig.savefig("histograma_1.pdf")
plt.close(fig)

fig, ax = plt.subplots(1, 2, figsize = (5,5))
ax[0].hist(datos2[:,0])
ax[0].set_xlabel(r"$x(\AA)$")
ax[0].set_title(r"Histograma $x$")
ax[1].hist(datos2[:,1])
ax[1].set_xlabel(r"$y(\AA)$")
ax[1].set_title(r"Histograma $y$")
plt.tight_layout()
fig.savefig("histograma_2.pdf")
plt.close(fig)
