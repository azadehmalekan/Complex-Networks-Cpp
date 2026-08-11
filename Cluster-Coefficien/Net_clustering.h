#ifndef NET_CLUSTERING_H
#define NET_CLUSTERING_H

#include <Eigen/Dense>
#include <vector>
#include <utility>

std::pair<std::vector<double>, double>
Net_clustering(const Eigen::MatrixXd& Network);

#endif
