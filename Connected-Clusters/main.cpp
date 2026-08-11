#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

#include "Net_components.h"

using namespace std;
using namespace Eigen;


int main()
{
    // --------------------------------------------------
    // Input network file
    // --------------------------------------------------

    const string filename = "network-sf.txt";


    // --------------------------------------------------
    // Open network file
    // --------------------------------------------------

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Cannot open file "
             << filename << endl;

        return 1;
    }


    // --------------------------------------------------
    // Read edges and find the number of nodes
    // --------------------------------------------------

    vector<pair<int, int>> edges;

    int node1;
    int node2;

    int N = 0;

    while (file >> node1 >> node2)
    {
        edges.push_back({node1, node2});

        // Find the largest node index
        N = max(N, node1 + 1);
        N = max(N, node2 + 1);
    }

    file.close();


    cout << "Network file loaded." << endl;
    cout << "Number of nodes = " << N << endl;
    cout << "Number of edges = "
         << edges.size() << endl;


    // --------------------------------------------------
    // Create adjacency matrix
    // --------------------------------------------------

    MatrixXd Network =
        MatrixXd::Zero(N, N);


    // --------------------------------------------------
    // Fill adjacency matrix
    // --------------------------------------------------

    for (const auto& edge : edges)
    {
        int i = edge.first;
        int j = edge.second;

        Network(i, j) = 1.0;
        Network(j, i) = 1.0;
    }


    cout << "Network loaded successfully."
         << endl;


    // --------------------------------------------------
    // Find connected components
    // --------------------------------------------------

    Components result =
        Net_components(Network);


    // --------------------------------------------------
    // Print summary
    // --------------------------------------------------

    cout << endl;

    cout << "--------------------------------"
         << endl;

    cout << "Connected components results"
         << endl;

    cout << "--------------------------------"
         << endl;


    cout << "Number of connected components = "
         << result.Number << endl;


    cout << "Largest component size = "
         << result.LargestSize << endl;


    // --------------------------------------------------
    // Print all components
    // --------------------------------------------------

    cout << endl;

    for (int i = 0; i < result.Number; ++i)
    {
        cout << "Component "
             << i + 1
             << " | Size = "
             << result.Size[i]
             << " | Nodes: ";

        for (int node : result.Nodes[i])
        {
            cout << node << " ";
        }

        cout << endl;
    }


    // --------------------------------------------------
    // Save all components to file
    // --------------------------------------------------

    ofstream output(
        "connected_components.txt"
    );


    if (!output.is_open())
    {
        cerr << "Error: Cannot create output file."
             << endl;

        return 1;
    }


    output << "Number of nodes = "
           << N << "\n";

    output << "Number of edges = "
           << edges.size() << "\n";

    output << "Number of connected components = "
           << result.Number << "\n";

    output << "Largest component size = "
           << result.LargestSize << "\n\n";


    // Save every component
    for (int i = 0; i < result.Number; ++i)
    {
        output << "Component "
               << i + 1
               << " Size "
               << result.Size[i]
               << ": ";

        for (int node : result.Nodes[i])
        {
            output << node << " ";
        }

        output << "\n";
    }


    output.close();


    cout << endl;

    cout << "Connected components saved to:"
         << endl;

    cout << "connected_components.txt"
         << endl;


    return 0;
}
