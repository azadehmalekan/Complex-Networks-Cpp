#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <algorithm>

#include "Net_clustering.h"

using namespace std;
using namespace Eigen;

int main()
{
    const string filename = "network-sf.txt";

    // -----------------------------------------
    // 1. Find the largest node ID
    // -----------------------------------------

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Cannot open file "
             << filename << endl;

        return 1;
    }

    int node1, node2;
    int maxNode = -1;

    while (file >> node1 >> node2)
    {
        maxNode = max(maxNode, node1);
        maxNode = max(maxNode, node2);
    }

    file.close();

    // Number of nodes
    const int N = maxNode + 1;

    cout << "Number of nodes = "
         << N << endl;

    // -----------------------------------------
    // 2. Create adjacency matrix
    // -----------------------------------------

    MatrixXd Network =
        MatrixXd::Zero(N, N);

    // -----------------------------------------
    // 3. Read network again
    // -----------------------------------------

    file.open(filename);

    if (!file.is_open())
    {
        cerr << "Error: Cannot open file "
             << filename << endl;

        return 1;
    }

    while (file >> node1 >> node2)
    {
        Network(node1, node2) = 1.0;
        Network(node2, node1) = 1.0;
    }

    file.close();

    cout << "Network loaded successfully."
         << endl;

    // -----------------------------------------
    // 4. Calculate clustering coefficient
    // -----------------------------------------

    auto [CC, MC] = Net_clustering(Network);

    // -----------------------------------------
    // 5. Save clustering coefficient of each node
    // -----------------------------------------

    ofstream output("clustering_coefficient-sf.txt");

    if (!output.is_open())
    {
        cerr << "Error: Cannot create output file."
             << endl;

        return 1;
    }

    for (int i = 0; i < N; ++i)
    {
        output << i << " "
               << CC[i] << "\n";
    }

    output.close();

    // -----------------------------------------
    // 6. Save average clustering coefficient
    // -----------------------------------------

    ofstream average_output(
        "average_clustering-sf.txt"
    );

    if (!average_output.is_open())
    {
        cerr << "Error: Cannot create output file."
             << endl;

        return 1;
    }

    average_output << MC << "\n";

    average_output.close();

    // -----------------------------------------
    // 7. Print result
    // -----------------------------------------

    cout << "Average clustering coefficient = "
         << MC << endl;

    return 0;
}
