#include <mpi/mpi.h>
#include <iostream>
using namespace std;

int main() 
{
    double a ,b ,c ,d ,e ,x ,y ,z , w ;
    int mpi_rank, mpi_size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    /*
    - Asumiendo que solo el nodo maestro tiene los 
    datos al inicio
    - Maximo de procesos usables: 4
    */
    // primer bloque 
    switch (mpi_rank)
    {
    case 0:
        // compartir los datos
            // mandar los datos
            // MPI_Send(&a, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&c, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Send(&d, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            // empezar los calculos
            // modifica a, lee b
            calculo_1(a, b);
            // modifica b, lee b
            calculo_2(b, b);
            // espera a que los demas terminen
            MPI_Recv(&c, 1, MPI_INT, 1, 0, );
            MPI_Recv(&d);
            // calcular e con los datos recibidos
            e = a + b *c + d;
            // enviar e
            MPI_Send(&e, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        break;
    case 1:
            MPI_Recv(&c);
            MPI_Recv(&d);
            // empezar los calculos
            // modifica c, lee d
            calculo_3(c, d);
            // modifica d, lee d
            calculo_4(d, d);
            // mandar nuevos datos al maestro para calcular e
            MPI_Send(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&d, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            // recibir e, se queda aqui hasta que master le envie e
            MPI_Recv(&e);
            break;
    default:
    // no hace nada 
        break;
    }
    // - - - - - - - - -- -
    // segundo bloque
    switch (mpi_rank)
    {
    case 0:
        // master manda b a p1
        MPI_Send(&b, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        // modifica x, lee a, e y b
        calculo_5 (x , a /e , b / e ) ;
        // recibe y, z
        MPI_Recv(&y);
        MPI_Recv(&z);
        w = x + y + z;
        break;
    
    case 1:
        // manda e y c a p2
        MPI_Send(&e, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(&c, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        // recibe b de master
        MPI_Recv(&b);
        // modifica y, lee b y e
        calculo_6 (y , b / e) ;
        // manda y a maestro
        MPI_Send(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        break;

    case 2:
        // recibe b de p1
        MPI_Recv(&e);
        // recibe c de p1
        MPI_Recv(&c);
        // modifica z, lee c y e
        calculo_7 (z , c / e) ;
        // manda z a maestro
        MPI_Send(&z, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        break;
    default:
        break;
    }
}