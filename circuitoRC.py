import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc("text", usetex = True)

datos = np.loadtxt("CircuitoRC.txt")

V0 = 10
def q(t, R, C):
	return V0*C*(1-np.exp(-t/(R*C)))

sigma = 1000
def likelihood(obs, model):
	return np.exp(-0.5*np.sum(((model - obs)/sigma)**2))

R_walk = [10]
C_walk = [10]
like_walk = [likelihood(datos[:,1],q(datos[:,0], R_walk[0], C_walk[0]))]

nit = 200000
sigma2 = 0.1
for n in range(1,nit):
	R_new = np.random.normal(R_walk[n-1],sigma2)
	C_new = np.random.normal(C_walk[n-1],sigma2)
	likelihood_new = likelihood(datos[:,1], q(datos[:,0], R_new, C_new))
	alpha = likelihood_new/like_walk[n-1]
	if(alpha >= 1 or np.random.random() <= alpha):
		R_walk.append(R_new)
		C_walk.append(C_new)
		like_walk.append(likelihood_new)
	else:
		R_walk.append(R_walk[n-1])
		C_walk.append(C_walk[n-1])
		like_walk.append(like_walk[n-1])

index = np.argmax(like_walk)
R = R_walk[index]
C = C_walk[index]
fig, ax = plt.subplots(figsize = (5,5))
ax.plot(datos[:,0], datos[:,1], label = r"Datos observados")
ax.plot(datos[:,0], q(datos[:,0], R, C), label = r"Datos para $R = %f$ y $C = %f$" % (R, C))
ax.set_xlabel(r"$t$")
ax.set_ylabel(r"$q$")
ax.set_title(r"Fit Circuito $RC$")
ax.legend()
plt.savefig("best_fit.pdf")
plt.close(fig)

fig, ax = plt.subplots(1, 2, figsize = (5,5), sharey = True)
ax[0].scatter(R_walk, -np.log(like_walk), alpha = 0.1)
ax[1].scatter(C_walk, -np.log(like_walk), alpha = 0.1)
ax[0].set_xlabel(r"$R$")
ax[1].set_xlabel(r"$C$")
ax[0].set_ylabel(r"$-\ln(L)$")
plt.tight_layout()
plt.savefig("verosimilitud.pdf")
plt.close(fig)

fig, ax = plt.subplots(1, 2, figsize = (5,5), sharey = True)
ax[0].hist(R_walk, 20, normed = True)
ax[1].hist(C_walk, 20, normed = True)
ax[0].set_xlabel(r"$R$")
ax[1].set_xlabel(r"$C$")
ax[0].set_ylabel(r"Frecuencia normalizada")
plt.tight_layout()
plt.savefig("histograma_3.pdf")
