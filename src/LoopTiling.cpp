#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <vector>
#include <queue>
#include <cmath>
#include <sdsl/bit_vectors.hpp>

/* Arity used for K2-Tree */
#define K 2

/* Block size for a cache in 64-bit architecture =  128 */
#define TILE_SIZE ((int) 128)

using namespace std;

class K2_tree
{
private:
    int m_x;
    int m_y;
    int** matrix; // declare array as a pointer pointer

public:
    K2_tree(int rows, int columns) {
        m_x = rows;
        m_y = columns;
        /* Dynamically allocate memory */
        matrix = new int*[m_x];
        for(int i = 0; i < m_x; i++) {
            matrix[i] = new int[m_y];
        }
        for(int i = 0; i < m_x; i++) {
            for(int j = 0; j < m_y; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    ~K2_tree() {
        /* Releasing previously allocated array */
        for(int i = 0; i < m_x; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    int& operator()(int i, int j)
    {
        return matrix[i][j];
    }

    const int& operator()(int i, int j) const
    {
        return matrix[i][j];
    }

    int get_cols() const
    {
        return m_y;
    }

    int get_rows() const
    {
        return m_x;
    }

    void link_bit(int x, int y) {
        matrix[x][y] = 1;
    }
    void print_matrix() {
        for(int i = 0; i < m_x; i++) {
            for(int j = 0; j < m_x; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
};

struct k2_tree_node
{
    int i, j, level;

    k2_tree_node() = default;
    k2_tree_node(int i, int j, int level) :
        i(i), j(j), level(level) { }
};

template <typename T>
double time_diff(const T& start, const T& stop)
{
    chrono::duration<double> time = stop - start;
    return time.count();
}

template <typename Fun>
double average_time(Fun&& func, const K2_tree& mat, int n, const bool expected_result)
{
    int numRep = 10, number_children = pow(K,2), power = log2 (K);
    double sum = 0;

    for (int r = 0; r != numRep; r++)
    {
        auto t1 = chrono::steady_clock::now();
        func(mat, n, number_children, power);
        auto t2 = chrono::steady_clock::now();
        sum += time_diff(t1, t2);
    }
    return sum / numRep;
}
int build_from_matrix_helper_sequential (const K2_tree& mat, k2_tree_node& matrix, int n)
{
    int i, j, ii, jj;
    const auto max_size_i = matrix.i+n, max_size_j = matrix.j+n;
    const auto min_size_i = matrix.i, min_size_j = matrix.j;

    int found = 0;

    for(ii = min_size_i; (ii < max_size_i)  && !found; ii+= TILE_SIZE)
    {
        for(jj = min_size_j; (jj < max_size_j)  && !found; jj+= TILE_SIZE)
        {
            for (i = ii; i < min(max_size_i,ii + TILE_SIZE) && !found; ++i)
            {
                for (j = jj; j < min(max_size_j,jj + TILE_SIZE)  && !found; ++j)
                {
                    if (mat(i, j) == 1)
                    {
                        found = 1;
                        break;
                    }
                }
            }
        }
    }
    return found;
}

void build_from_matrix(const K2_tree& mat, int size, int number_children, int power)
{
    queue<k2_tree_node> q;
    q.push({0, 0, 0}); // Inserts the matrix starting at (0,0) which is at level 0
    sdsl::bit_vector k_t, k_l;
    int vet_size = 0;
    size <= 32768 ? vet_size = size * size : vet_size = size * 50 ;
    k_t = sdsl::bit_vector(vet_size, 0);
    k_l = sdsl::bit_vector(k_t.size() * number_children, 0);
    size_t t = 0, l=0;

    while (!q.empty())
    {
        auto matrix = q.front(); // Get matrix
        auto rt = -1, rl = -1;
        auto matrix_size = size / (1 << power * (matrix.level));

        if(matrix_size == 1) // Leaf level base case
        {
            rl = mat(matrix.i, matrix.j);
            k_l[l] = rl;
            l++;
        }
        else if(matrix_size == 0)
            break;
        else if (size == matrix_size)
            build_from_matrix_helper_sequential(mat,matrix,matrix_size);
        else
        {
            rt = build_from_matrix_helper_sequential(mat,matrix,matrix_size);
            k_t[t] = rt;
            t++;
        }
        q.pop();

        if(rt==0) {
            continue;    // The matrix only has zeros, there is no need to process the children
        }

        int child_size = size / (1 << power * (matrix.level + 1)); // Calculate the size of each child submatrix
        /* Performs the divisions in K ^ 2 submatrices */
        for(int i=0; i<K; i++)
        {
            for(int j=0; j<K; j++)
            {
                k2_tree_node node;
                node.i = matrix.i + i * child_size;
                node.j = matrix.j + j* child_size;
                node.level = matrix.level+1;
                q.push(node);
            }
        }
    }
    ofstream K_T ("./outputs/KT_2.sdsl"), K_L ("./outputs/KL_2.sdsl");
    k_t.resize(t);
    k_l.resize(l);

    sdsl::serialize(k_t, K_T);
    sdsl::serialize(k_l, K_L);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: file" << endl;
        return 1;
    }
    ifstream file(argv[1]);

    unsigned size, n;
    file >> size; // Number of vertex in the WebGraph
    int xi, yj;
    float tam = log2(size); // For testing based on final arity

    if (!file) {
        cout << "Failed to open the file";    // In case error during opening
    }

    /* Maintains original size or calculates approximate size with K^|log K n| */
    (tam == (int)log2(size)/(int)log2(2)) ? n = size :  n = 1 << ((int) floor(log2(size)) + 1);
    cout << "# Matrix size analyzed = "<< n << endl;

    K2_tree matrix(n,n);

    while (true)
    {
        if (!(file >> xi)) {
            break;
        }
        if (!(file >> yj)) {
            break;
        }
        matrix.link_bit(xi-1, yj-1);
    }
    file.close();

    /* Benchmark time calculation module */
    auto time = average_time(build_from_matrix, matrix, n, true);

    cout << "Build from Matrix Sequential with Tiling time = " << time << "\n" <<endl;

    return 0;
}
