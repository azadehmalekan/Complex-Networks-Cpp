#include "Net_components.h"

#include <queue>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;


Components Net_components(const MatrixXd& Network)
{
    const int N = Network.rows();

    // Store whether each node has already been visited
    vector<bool> visited(N, false);

    // Output structure
    Components result;

    result.Number = 0;
    result.LargestSize = 0;


    // Go through all nodes
    for (int start = 0; start < N; ++start)
    {
        // Skip nodes that already belong to a component
        if (visited[start])
            continue;


        // New connected component
        queue<int> Queue;

        vector<int> component;


        // Start BFS from this node
        Queue.push(start);
        visited[start] = true;


        // BFS
        while (!Queue.empty())
        {
            // Take the first node from the queue
            int node = Queue.front();
            Queue.pop();


            // Save this node in the current component
            component.push_back(node);


            // Search for neighbors
            for (int j = 0; j < N; ++j)
            {
                if (Network(node, j) != 0 &&
                    !visited[j])
                {
                    // Mark node as visited
                    visited[j] = true;

                    // Add node to queue
                    Queue.push(j);
                }
            }
        }


        // Size of this component
        int componentSize = component.size();


        // Save nodes of this component
        result.Nodes.push_back(component);


        // Save its size
        result.Size.push_back(componentSize);


        // Increase number of components
        result.Number++;


        // Update largest component
        if (componentSize > result.LargestSize)
        {
            result.LargestSize = componentSize;
        }
    }


    return result;
}
