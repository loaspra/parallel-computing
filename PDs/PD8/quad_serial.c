#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <mpi/mpi.h>

int main(int argc, char *argv[]);
double f( double x );
double cpu_time( void );
void timestamp( void );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
{
  MPI_Init(&argc, &argv);
  int world_rank, world_size;  
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  double a = 0.0;
  double b = 10.0;
  double error;
  double exact = 0.49936338107645674464;
  int i;
  int n = 10000000;
  double local_sum, global_sum;
  double wtime;
  double wtime1;
  double wtime2;
  double x;
  if(world_rank == 0)
  {
    timestamp();
    printf ( "\n" );
    printf ( "QUAD_SECUENCIAL:\n" );
    printf ( "  Integral de f(x)= 50/(pi * (2500 * x * x + 1)).\n" );
    printf ( "A (inicio) = %f\n", a );
    printf ( "B (fin)= %f\n", b );
    printf ( "  N = %d\n", n );
    printf ( "valor exacto = %24.16f\n", exact );
    printf ( "\n" );
    wtime1 = MPI_Wtime();
  }

  local_sum = 0.0;
  // printf("p: %d goes from %d to %d\n", world_rank, world_rank * n/world_size, (world_rank + 1) * n/world_size);
  for(i = world_rank * n/world_size; i < (world_rank + 1) * n/world_size; i++)
  {
    x = ( ( n - i - 1 ) * a + ( i ) * b ) / ( n - 1 );
    local_sum = local_sum + f(x);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  // printf("p: %d suma local: %f \n", world_rank, local_sum);
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  // printf("P: %d End reduce\n", world_rank);
  if(world_rank == 0)
  {
    wtime2 = MPI_Wtime();

    global_sum = ( b - a ) * global_sum / ( double ) n;
    error = fabs( global_sum - exact );
    wtime = wtime2 - wtime1;

    printf ( "\n" );
    printf ( "  Estimate = %24.16f\n", global_sum );
    printf ( "  Error    = %e\n", error );
    printf ( "  Time     = %f\n", wtime );
  /*
    Terminate.
  */
    printf ( "\n" );
    printf ( "QUAD_SERIAL:\n" );
    printf ( "  Normal end of execution.\n" );
    printf ( "\n" );
    timestamp ( );
  }

  return 0;
}

// DONT
double f(double x)
{
  double pi = 3.141592653589793;
  double value;

  value = 50.0 / ( pi * ( 2500.0 * x * x + 1.0 ) );

  return value;
}

// DONT
double cpu_time ( void )
{
  double value;

  value = ( double ) clock ( ) / ( double ) CLOCKS_PER_SEC;

  return value;
}


// DONT
void timestamp( void )
{
  #define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
  #undef TIME_SIZE
}
