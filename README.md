# Complex Network Models in C++

This repository contains C++ implementations of three classical complex network models.

## Models

### Erdős–Rényi Random Graph
- G(N,p)
- G(N,M)

### Watts–Strogatz Small-World Network
- Regular ring lattice
- Random rewiring

### Scale-Free Network
- Preferential attachment
- Power-law degree distribution

## Requirements

- C++17
- Eigen

## Compilation

```bash
g++ -std=c++17 main.cpp -I /path/to/eigen
```

## Outputs

- Adjacency matrices
- Edge lists
- Degree distributions
- Network statistics