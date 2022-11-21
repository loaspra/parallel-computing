# include <iostream>
# include <cmath>
# include <ctime>
# include <mpi.h>

double frontera ( double x, double tiempo )
{
  double limite;
  if ( x < 0.5 ) 
    limite = 100.0 + 10.0 * sin ( tiempo );
  else 
    limite = 75.0;
  return limite;
}

double inicial ( double x, double tiempo ) 
{
  double limite;
  limite = 95.0;
  return limite;
}

int main ( int argc, char *argv[] )
{
  MPI_Init(&argc, &argv);

  int world_rank, world_size;  
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int i,j,j_min = 0,j_max = 400,tag;
  int n;
  // definir n dependiendo de si es el proceso root o no
  n = 10;
  MPI_Status status;
  double k = 0.002;
  double tiempo,dt,tmax = 10.0,tmin = 0.0,tnew;
  double u[n + 1],unew[n + 1],x[n + 1],dx;
  double x_max = 1,x_min = 0.0;
  dt = ( tmax - tmin ) / ( double ) ( j_max - j_min );
  dx = ( x_max - x_min ) / ( double ) n / ( double ) world_size;
  double l_x = 0;
  double h_x = n;
  int pos_i = world_rank * n + 1;
  x[0] = world_rank * dx * n;
  for ( i = 1; i <= n; i++)
  {
    x[i]=x[i-1]+dx;
  }
  
  //  Inicializacion.
  tiempo = tmin;
  for ( i = 0; i <= n; i++) 
    u[i] = inicial(x[i], tiempo );
  
  // Valores de temperatura al siguiente intervalo de tiempo
  for ( j = 1; j <= j_max; j++ )
  {
    tnew+=dt; 

    // actualizar temperatura de los cantos
    if (world_rank == world_size - 1)
    {
      unew[n] = 75.0;
      printf("Enviado %f a %d\n", u[0], world_rank - 1);
      MPI_Send(&u, 1, MPI_DOUBLE, world_rank - 1, tag, MPI_COMM_WORLD);
      printf("%d esperando\n", world_rank);
      MPI_Recv(&l_x, 1, MPI_DOUBLE, world_rank - 1, tag, MPI_COMM_WORLD, &status);
      printf("%d recibido\n", world_rank);
    }
    else
    if (world_rank == 0)
    {
      unew[0] = frontera(0, tnew);
      printf("Enviado %f a %d\n", u[n], 1);
      MPI_Send(&u[n], 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
      printf("%d esperando\n", world_rank);
      MPI_Recv(&h_x, 1, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
      printf("%d recibido\n", world_rank);
    }
    else
    {
      // *** enviar ***
      // hacia la izquierda
      MPI_Send(&u, 1, MPI_DOUBLE, world_rank - 1, tag, MPI_COMM_WORLD);
      // hacia la derecha
      MPI_Send(&u[n], 1, MPI_DOUBLE, world_rank + 1, tag, MPI_COMM_WORLD);
      // *** recibir ***
      // desde la izquierda (inicio)
      printf("%d esperando\n", world_rank);
      MPI_Recv(&l_x, 1, MPI_DOUBLE, world_rank - 1, tag, MPI_COMM_WORLD, &status);
      printf("%d recibido\n", world_rank);
      // desde la derecha (fin)
      printf("%d esperando\n", world_rank);
      MPI_Recv(&h_x, 1, MPI_DOUBLE, world_rank + 1, tag, MPI_COMM_WORLD, &status);
      printf("%d recibido\n", world_rank);
    }
    // actualizar temperatura para frontera izquierda  
    printf("%d ready\n", world_rank);  
    MPI_Barrier(MPI_COMM_WORLD);
    unew[0] = u[0] 
    + ( dt * k / dx / dx ) * ( l_x - 2.0 * u[0] + u[1]); 
    // actualizar temperatura para frontera derecha
    unew[n] = u[n] 
    + ( dt * k / dx / dx ) * ( l_x - 2.0 * u[n] + h_x); 
    // actualizar temperatura para no "fronteras"
    for ( i = 1; i < n; i++)
    {
      unew[i] = u[i] 
      + ( dt * k / dx / dx ) * ( u[i-1] - 2.0 * u[i] + u[i+1] ); 
    }
    
  if(world_rank == 0)
  // aplicar condiciones de frontera
      unew[1] = frontera( x[1], tnew );
  if(world_rank == world_size - 1)
      unew[n] = frontera( x[n], tnew );

  // Actualizar tiempo y temperatura
    tiempo = tnew;
    for ( i = 0; i < n; i++ )
    {
      u[i] = unew[i];
      if(j==j_max && i < n)
      {
        printf("p:%d x:%f u:%f\n",world_rank , x[i],u[i]);
      }
    }
  }
  return 0;
}
