#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <random>

using namespace std;
using namespace Eigen;


// Number of nodes
const int n = 1000;


// Initial degree of each node
const int K = 6;


// Rewiring probability
const double rewiring_probability = 0.1;



int main()
{

    int i, j, k;
    int s;



    /*
        Check parameters

        K must be even and smaller than n

    */

    if(K >= n || K % 2 != 0)
    {
        cout << "Error: K must be even and smaller than n"
             << endl;

        return 1;
    }




    /*
        Adjacency matrix

        SW(i,j)=1 -> connected nodes
        SW(i,j)=0 -> no connection

    */


    MatrixXi SW = MatrixXi::Zero(n,n);
    VectorXi degree = VectorXi::Zero(n);





    /*
        CR stores the original neighbors
        before rewiring

    */


    MatrixXi CR(n,K/2);






    /*
        Step 1:

        Construct regular ring lattice

        Each node connects to K/2 nodes
        on each side

    */


    for(i=0; i<n; i++)
    {

        k = 0;


        for(j=1; j<=K/2; j++)
        {


            // periodic boundary condition

            int right = (i+j)%n;

            int left = (i-j+n)%n;



            // connect right neighbor

            SW(i,right)=1;
            SW(right,i)=1;


            CR(i,k)=right;

            k++;




            // connect left neighbor

            SW(i,left)=1;
            SW(left,i)=1;


        }

    }







    /*
        Step 2:

        Rewire edges with probability p

    */


    random_device rd;

    mt19937 gen(rd());


    uniform_real_distribution<double> probability(0.0,1.0);


    uniform_int_distribution<int> random_node(0,n-1);





    for(i=0; i<n; i++)
    {

        for(j=0; j<K/2; j++)
        {


            double q = probability(gen);



            if(q < rewiring_probability)
            {


                // old neighbor

                s = CR(i,j);




                // remove old edge

                SW(i,s)=0;

                SW(s,i)=0;





                int new_node;



                // choose new node

                do
                {

                    new_node = random_node(gen);


                }

                while(
                    new_node == i ||
                    SW(i,new_node)==1
                );






                // create new edge

                SW(i,new_node)=1;

                SW(new_node,i)=1;


            }

        }

    }








    /*
        Count edges

    */


    int edges = 0;



    for(i=0; i<n; i++)
    {

        for(j=i+1; j<n; j++)
        {

            edges += SW(i,j);

        }

    }





    cout << "Small-world network generated"
         << endl;


    cout << "Nodes = "
         << n
         << endl;


    cout << "Edges = "
         << edges
         << endl;








    /*
        Save adjacency matrix

    */


    ofstream matrix_file("SW.txt");



    if(matrix_file.is_open())
    {

        matrix_file << SW << endl;

        matrix_file.close();

    }







    /*
        Save edge list

        Format:

        node1 node2

    */


    ofstream edge_file("small_world_edge_list.txt");



    if(edge_file.is_open())
    {


        for(i=0; i<n; i++)
        {

            for(j=i+1; j<n; j++)
            {


                if(SW(i,j)==1)
                {

                    edge_file << i
                              << " "
                              << j
                              << endl;

                }

            }

        }


        edge_file.close();

    }


     for(int i=0; i<n; i++)
    {

        degree(i) = SW.row(i).sum();

    }


ofstream degree_file("small_world_degree_list.txt");


    for(int i=0; i<n; i++)
    {

         degree_file << degree(i) << endl;

    }


    degree_file.close();


    cout << "Files saved successfully."
         << endl;



    return 0;

}
