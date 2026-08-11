#include "Net_clustering.h"

using namespace std;
using namespace Eigen;

pair<vector<double>, double>
Net_clustering(const MatrixXd& Network)
{
    const int N = Network.rows();

    // Degree
    VectorXd degree = Network.rowwise().sum();

    // A^2
    MatrixXd A2 = Network * Network;

    vector<double> CC(N, 0.0);

    double MC = 0.0;

    for (int i = 0; i < N; ++i)
    {
        double k = degree(i);

        if (k < 2)
            continue;

        // Diagonal element of A^3
        double A3ii = 0.0;

        for (int j = 0; j < N; ++j)
        {
            A3ii += A2(i, j) * Network(j, i);
        }

        // Local clustering coefficient
        CC[i] = A3ii / (k * (k - 1));

        MC += CC[i];
    }

    // Average clustering coefficient
    MC /= N;

    return {CC, MC};
}
