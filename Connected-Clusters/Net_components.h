#ifndef NET_COMPONENTS_H
#define NET_COMPONENTS_H

#include <vector>
#include <Eigen/Dense>

struct Components
{
    std::vector<std::vector<int>> Nodes;
    std::vector<int> Size;
    int Number;
    int LargestSize;
};

Components Net_components(const Eigen::MatrixXd& Network);

#endif
