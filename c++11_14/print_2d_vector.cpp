#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Iterate over vector of vectors and for each of the 
nested vector print its contents
*/
template <typename T>
std::ostream & operator << (std::ostream & os, const vector< vector<T> > & matrix)
{
    for(int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.at(i).size(); j++)
        {
            os<<matrix[i][j]<<", ";
        }
        os<<endl;
    }
    os<<endl;     
    return os;
}

void example2(vector<vector<int>> & matrix)
{
    cout << matrix;
}

// c++14
int example1(vector<vector<int>> & matrix)
{

    // Print 2D vector / matrix
    for_each(matrix.begin(),
             matrix.end(),
            [](const auto & row ) {
                    for_each(row.begin(), row.end(),
                        [](const auto & elem){
                            cout<<elem<<", ";
                        });
                        cout<<endl;
                    });
    cout<<endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    // Initializing a 2D Vector i.e. vector of vectors
    vector<vector<int>> matrix = {
                                {1, 2, 3, 4, 5 },
                                {6, 7, 8, 9, 10 },
                                {5, 6, 8, 1, 12 },
                                {1, 7, 2, 4, 18 },
                            };

    example1(matrix);
    example2(matrix);
    return 0;
}
