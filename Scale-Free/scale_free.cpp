#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include <fstream>




using namespace std;

int main()
{

    int N = 5;
    int new_node;
    int sum_degree ;
    int Final_node = 500;
    int i;
    int j;
    int m = 3;
    double sum_prob;

    std::vector<std::pair<int,int>> edges;
    std::vector<double> degree(N,0);
    std::vector<double> prob(N,0);


    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0, 1);



for( i=0; i<N; i++)
    {edges.push_back({i,(i+1)%N});}



for (auto edge : edges)
{
    i= edge.first;
    j = edge.second;

    degree[i]++;
    degree[j]++;
}
    sum_degree = 0;
    for( i=0; i<N; i++)
    {
             sum_degree += degree[i];

    }

      for(i=0; i<N; i++)
    {

             prob[i] = degree[i] / sum_degree;
    }


   // std::discrete_distribution<int> node_dist(prob.begin(), prob.end());










    for(new_node=N; new_node<=Final_node; new_node++)
{


    // add new node
    degree.push_back(0);
    prob.push_back(0);


    // calculate total degree
    sum_degree=0;

    for(int i = 0; i < degree.size(); i++)
{
    sum_degree += degree[i];
}


// calculate probabilities
    for(int i=0; i<=new_node; i++)
    {
        prob[i]=degree[i]/sum_degree;

    }

         // create weighted distribution
    discrete_distribution<int> node_dist(
        prob.begin(),
        prob.begin()+new_node
    );

    vector<int> targets;

while(targets.size() < m)
{
    int target = node_dist(gen);

    // avoid duplicate connections
    bool exists = false;

    for(int x : targets)
    {
        if(x == target)
        {
            exists = true;
            break;
        }
    }

    if(!exists)
        targets.push_back(target);
}

for(int target : targets)
{
    edges.push_back({new_node,target});

    degree[target]++;
}

degree[new_node] = m;



// calculate total degree again
sum_degree = 0;

for(int i = 0; i <= new_node; i++)
{
    sum_degree += degree[i];
}



    // calculate probabilities
for(int i = 0; i <= new_node; i++)
{
    prob[i] = degree[i] / sum_degree;


     }

}
cout<< sum_degree<<endl;
sum_prob = 0;
for(i = 0; i <=Final_node; i++)
{
    sum_prob += prob[i];

}



double max_degree = 0;


for(auto d : degree)
{
    if(d > max_degree)
        max_degree = d;
}


cout << "Maximum degree = "
     << max_degree
     << endl;


ofstream edge_file("scale_free_edge_list.txt");


for(auto edge : edges)
{
    edge_file << edge.first
              << " "
              << edge.second
              << endl;
}


edge_file.close();

ofstream degree_file("scale_free_degree_list.txt");

for(int i=0; i<degree.size(); i++)
{
    degree_file << degree[i] << endl;
}

degree_file.close();
cout<<"Number of nodes:"<<Final_node<<"\t"<<"Total probability:"<<sum_prob <<endl;

double avg_degree=0;

for(auto d: degree)
{
    avg_degree += d;
}

avg_degree /= degree.size();

cout<<"Average degree = "<<avg_degree<<endl;

    return 0;
}
