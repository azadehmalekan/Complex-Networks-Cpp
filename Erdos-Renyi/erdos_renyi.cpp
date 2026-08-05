#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <fstream>

using namespace std;
using namespace Eigen;


int main()
{

    /*
        Erdős–Rényi random graph models:

        1) G(N,p)
           - N nodes
           - Each possible edge is created independently
             with probability p

        2) G(N,M)
           - N nodes
           - Exactly M edges are randomly placed
    */


    // Network parameters

    const int number_nodes = 5000;

    const double probability = 0.2;     // Probability in G(N,p)

    const int number_edges = 2500000;      // Number of edges in G(N,M)



    /*
        Random number generator
    */

    random_device rd;
    mt19937 generator(rd());


    uniform_real_distribution<double> random_probability(0.0,1.0);



    /*
        Adjacency matrices

        A_P -> G(N,p)
        A_M -> G(N,M)

        A(i,j)=1 : edge exists
        A(i,j)=0 : no edge

        Undirected network:

        A(i,j)=A(j,i)

    */


    MatrixXi A_P = MatrixXi::Zero(number_nodes, number_nodes);
    VectorXi degree_P = VectorXi::Zero(number_nodes);

    MatrixXi A_M = MatrixXi::Zero(number_nodes, number_nodes);
    VectorXi degree_M = VectorXi::Zero(number_nodes);



    /************************************************************

                     ER MODEL G(N,p)

    ************************************************************/


    for(int i=0; i<number_nodes-1; i++)
    {

        for(int j=i+1; j<number_nodes; j++)
        {

            double r = random_probability(generator);


            if(r < probability)
            {
                A_P(i,j)=1;
                A_P(j,i)=1;
            }

        }

    }



    /*
        Calculate average degree

        k_i = sum_j A(i,j)

    */


    double degree_sum = 0;


    for(int i=0; i<number_nodes; i++)
    {
        degree_sum += A_P.row(i).sum();
        degree_P(i) = A_P.row(i).sum();
       // cout<< degree_P(i)<<endl;
    }


    double average_degree = degree_sum / number_nodes;



    cout << "Erdos-Renyi G(N,p)" << endl;

    cout << "Nodes = "
         << number_nodes << endl;


    cout << "Average degree = "
         << average_degree << endl;


    cout << "Theoretical average degree = "
         << probability*(number_nodes-1)
         << endl;




    /*
        Save adjacency matrix of G(N,p)

    */


   /* ofstream adjacency_file("erdos_renyi_adjacency_matrix.txt");


    for(int i=0; i<number_nodes; i++)
    {
        for(int j=0; j<number_nodes; j++)
        {
            adjacency_file << A_P(i,j) << " ";
        }

        adjacency_file << endl;
    }


    adjacency_file.close();*/



    /*
        Save edge list

        Format:

        node1 node2

    */



     ofstream edge_file("erdos_renyi_edge_list.txt");


    for(int i=0; i<number_nodes; i++)
    {
        for(int j=i+1; j<number_nodes; j++)
        {
            if(A_P(i,j)==1)
            {
                edge_file << i << " "
                          << j << endl;
            }
        }
    }


    edge_file.close();





    ofstream degree_file("erdos_renyi_degree_list.txt");


    for(int i=0; i<number_nodes; i++)
    {

        degree_file << degree_P(i) << endl;

    }


    degree_file.close();

    /************************************************************

                     ER MODEL G(N,M)

    ************************************************************/


    if(number_edges > number_nodes*(number_nodes-1)/2)
    {
        cout << "Error: Too many edges requested!"
             << endl;

        return 1;
    }



    uniform_int_distribution<int> random_node(0,number_nodes-1);



    int edges_created = 0;



    while(edges_created < number_edges)
    {

        int i = random_node(generator);

        int j = random_node(generator);



        /*
            Conditions:

            1) No self-loop
            2) No duplicate edge

        */


        if(i != j && A_M(i,j)==0)
        {

            A_M(i,j)=1;
            A_M(j,i)=1;


            edges_created++;

        }

    }




    /*
        Count edges

    */


    int total_edges = 0;


    for(int i=0; i<number_nodes; i++)
    {
        for(int j=i+1; j<number_nodes; j++)
        {
            total_edges += A_M(i,j);

        }
    }

     for(int i=0; i<number_nodes; i++)
    {

        degree_M(i) = A_M.row(i).sum();
       // cout<< degree_M(i)<<endl;
    }

    cout << endl;

    cout << "Erdos-Renyi G(N,M)" << endl;

    cout << "Nodes = "
         << number_nodes << endl;


    cout << "Edges = "
         << total_edges << endl;




    /*
        Save G(N,M) edge list

    */


    ofstream GM_edge_file("erdos_renyi_GNM_edge_list.txt");


    for(int i=0; i<number_nodes; i++)
    {

        for(int j=i+1; j<number_nodes; j++)
        {

            if(A_M(i,j)==1)
            {
                GM_edge_file << i
                             << " "
                             << j
                             << endl;
            }

        }

    }


    GM_edge_file.close();

       ofstream GM_degree_file("erdos_renyi_degree_GM_list.txt");


    for(int i=0; i<number_nodes; i++)
    {

         GM_degree_file << degree_M(i) << endl;

    }


    GM_degree_file.close();



    cout << endl;

    cout << "Files saved successfully." << endl;



    return 0;
}
