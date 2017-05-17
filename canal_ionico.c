#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int arr(int i, int j);
float norm(float x, float y);
float distance(float x1, float y1, float x2, float y2);

void main(void)
{
	/*Se cuenta el numero de datos en el archivo*/
	FILE *in; 
	in = fopen("Canal_ionico.txt", "r");
	int test;
	float var;
	int ndata=0;
	do
	{
		test = fscanf(in, "%f\n", &var);
		if(test != EOF)
		{
			ndata ++;
		}
	}
	while(test != EOF);
	fclose(in);

	/*Se guardan los datos en una lista*/
	in = fopen("Canal_ionico.txt", "r");
	float posiciones[ndata];
	int i;
	for(i = 0; i < ndata; i ++)
	{
		fscanf(in, "%f\n", &posiciones[i]);
	}
	fclose(in);

	int nit = 200000;
	float posiciones_walk[2*nit];
	float radio_walk[nit];
	
	/*Se hayan los valores maximos y minimos en la lista y se inicializan las caminatas*/
	float x_max = posiciones[arr(0,0)];
	float x_min = x_max;
	float x_dmax = x_max;
	float y_max = posiciones[arr(0,1)];
	float y_min = y_max;
	float y_dmax = y_max;
	float x_new;
	float y_new;
	float d_new;
	for(i = 1; i < ndata/2; i ++) 
	{
		x_new = posiciones[arr(i,0)];
		y_new = posiciones[arr(i,1)];
		if(x_new > x_max)
		{
			x_max = x_new;
		}
		else if(x_new < x_min)
		{
			x_min = x_new;
		}
		if(y_new > y_max)
		{
			y_max = y_new;
		}
		else if(y_new < y_min)
		{
			y_min = y_new;
		}
	}
	float x_medio = (x_max + x_min)/2;
	float y_medio = (y_max + y_min)/2;
	for(i = 1; i < ndata/2; i ++) 
	{
		x_new = posiciones[arr(i,0)];
		y_new = posiciones[arr(i,1)];
		d_new = distance(x_new, y_new, x_medio, y_medio);
		if(d_new > distance(x_dmax, y_dmax, x_medio, y_medio))
		{
			x_dmax = x_new;
			y_dmax = y_new;
		}
	} 
	float d_max = distance(x_dmax, y_dmax, x_medio, y_medio);
	srand(time(NULL));
	posiciones_walk[arr(0,0)] = rand()*(x_max - x_min)/RAND_MAX + x_min;
	posiciones_walk[arr(0,1)] = rand()*(y_max - y_min)/RAND_MAX + y_min;
	radio_walk[0] = distance(posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], posiciones[arr(0,0)], posiciones[arr(0,1)]);
	float radio_new;
	for(i = 1; i < ndata; i ++)
	{
		radio_new = distance(posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], posiciones[arr(i,0)], posiciones[arr(i,1)]);
		if(radio_new < radio_walk[0])
		{
			radio_walk[0] = radio_new;
		}
	}

	/*Se realiza la caminata*/
	in = fopen("caminata1.txt", "w");
	fprintf(in, "%f %f %f\n", posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], radio_walk[0]);
	float sigma = 1;
	float radio_tentativo;
	float alpha;
	float beta;
	int j;
	for(i = 1; i < nit; i ++)
	{
		float U = (float)rand()/(float)RAND_MAX;
		float V = (float)rand()/(float)RAND_MAX;
		float X = sqrt(-2*log(U))*cos(2*M_PI*V);
		float Y = sqrt(-2*log(U))*sin(2*M_PI*V);
		x_new = sigma*X + posiciones_walk[arr(i-1,0)];
		y_new = sigma*Y + posiciones_walk[arr(i-1,1)];
		if(distance(x_new, y_new, x_medio, y_medio) < d_max)
		{
			radio_tentativo = distance(x_new, y_new, posiciones[arr(0,0)], posiciones[arr(0,1)]); 
			for(j = 1; j < ndata; j ++)
			{
				radio_new = distance(x_new, y_new, posiciones[arr(j,0)], posiciones[arr(j,1)]);
				if(radio_new < radio_tentativo)
				{
					radio_tentativo = radio_new;
				}
			}
			alpha = radio_tentativo/radio_walk[i-1];
			if(alpha > 1)
			{
				posiciones_walk[arr(i,0)] = x_new;
				posiciones_walk[arr(i,1)] = y_new;
				radio_walk[i] = radio_tentativo;
			}
			else if(rand()/RAND_MAX < alpha)
			{		
				posiciones_walk[arr(i,0)] = x_new;
				posiciones_walk[arr(i,1)] = y_new;
				radio_walk[i] = radio_tentativo;
			}
			else
			{
				posiciones_walk[arr(i,0)] = posiciones_walk[arr(i-1,0)];
				posiciones_walk[arr(i,1)] = posiciones_walk[arr(i-1,1)];
				radio_walk[i] = radio_walk[i-1];
			}
			fprintf(in, "%f %f %f\n", posiciones_walk[arr(i,0)], posiciones_walk[arr(i,1)], radio_walk[i]);
		}
	}
	fclose(in);
	
	/*Se repite todo*/
	in = fopen("Canal_ionico1.txt", "r");
	ndata=0;
	do
	{
		test = fscanf(in, "%f\n", &var);
		if(test != EOF)
		{
			ndata ++;
		}
	}
	while(test != EOF);
	fclose(in);

	/*Se guardan los datos en una lista*/
	in = fopen("Canal_ionico1.txt", "r");
	for(i = 0; i < ndata; i ++)
	{
		fscanf(in, "%f\n", &posiciones[i]);
	}
	fclose(in);

	/*Se hayan los valores maximos y minimos en la lista y se inicializan las caminatas*/
	x_max = posiciones[arr(0,0)];
	x_min = x_max;
	x_dmax = x_max;
	y_max = posiciones[arr(0,1)];
	y_min = y_max;
	y_dmax = y_max;
	for(i = 1; i < ndata/2; i ++) 
	{
		x_new = posiciones[arr(i,0)];
		y_new = posiciones[arr(i,1)];
		if(x_new > x_max)
		{
			x_max = x_new;
		}
		else if(x_new < x_min)
		{
			x_min = x_new;
		}
		if(y_new > y_max)
		{
			y_max = y_new;
		}
		else if(y_new < y_min)
		{
			y_min = y_new;
		}
	}
	x_medio = (x_max + x_min)/2;
	y_medio = (y_max + y_min)/2;
	for(i = 1; i < ndata/2; i ++) 
	{
		x_new = posiciones[arr(i,0)];
		y_new = posiciones[arr(i,1)];
		d_new = distance(x_new, y_new, x_medio, y_medio);
		if(d_new > distance(x_dmax, y_dmax, x_medio, y_medio))
		{
			x_dmax = x_new;
			y_dmax = y_new;
		}
	} 
	d_max = distance(x_dmax, y_dmax, x_medio, y_medio);
	srand(time(NULL));
	posiciones_walk[arr(0,0)] = rand()*(x_max - x_min)/RAND_MAX + x_min;
	posiciones_walk[arr(0,1)] = rand()*(y_max - y_min)/RAND_MAX + y_min;
	radio_walk[0] = distance(posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], posiciones[arr(0,0)], posiciones[arr(0,1)]);	
	for(i = 1; i < ndata; i ++)
	{
		radio_new = distance(posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], posiciones[arr(i,0)], posiciones[arr(i,1)]);
		if(radio_new < radio_walk[0])
		{
			radio_walk[0] = radio_new;
		}
	}

	/*Se realiza la caminata*/
	in = fopen("caminata2.txt", "w");
	fprintf(in, "%f %f %f\n", posiciones_walk[arr(0,0)], posiciones_walk[arr(0,1)], radio_walk[0]);
	for(i = 1; i < nit; i ++)
	{
		float U = (float)rand()/(float)RAND_MAX;
		float V = (float)rand()/(float)RAND_MAX;
		float X = sqrt(-2*log(U))*cos(2*M_PI*V);
		float Y = sqrt(-2*log(U))*sin(2*M_PI*V);
		x_new = sigma*X + posiciones_walk[arr(i-1,0)];
		y_new = sigma*Y + posiciones_walk[arr(i-1,1)];
		if(distance(x_new, y_new, x_medio, y_medio) < d_max)
		{
			radio_tentativo = distance(x_new, y_new, posiciones[arr(0,0)], posiciones[arr(0,1)]); 
			for(j = 1; j < ndata; j ++)
			{
				radio_new = distance(x_new, y_new, posiciones[arr(j,0)], posiciones[arr(j,1)]);
				if(radio_new < radio_tentativo)
				{
					radio_tentativo = radio_new;
				}
			}
			alpha = radio_tentativo/radio_walk[i-1];
			if(alpha > 1)
			{
				posiciones_walk[arr(i,0)] = x_new;
				posiciones_walk[arr(i,1)] = y_new;
				radio_walk[i] = radio_tentativo;
			}
			else if(rand()/RAND_MAX < alpha)
			{		
				posiciones_walk[arr(i,0)] = x_new;
				posiciones_walk[arr(i,1)] = y_new;
				radio_walk[i] = radio_tentativo;
			}
			else
			{
				posiciones_walk[arr(i,0)] = posiciones_walk[arr(i-1,0)];
				posiciones_walk[arr(i,1)] = posiciones_walk[arr(i-1,1)];
				radio_walk[i] = radio_walk[i-1];
			}
			fprintf(in, "%f %f %f\n", posiciones_walk[arr(i,0)], posiciones_walk[arr(i,1)], radio_walk[i]);
		}
	}
	fclose(in);
}
/*Convierte posiciones (i,j) de una matriz de 2 filas a posiciones en una lista*/
int arr(int i, int j)
{
	return i*2 + j;
}

float norm(float x, float y)
{
	return sqrt(x*x + y*y);
}

float distance(float x1, float y1, float x2, float y2)
{
	float radio_molecula = 1;
	return norm(x2 - x1, y2 - y1) - radio_molecula;
} 
