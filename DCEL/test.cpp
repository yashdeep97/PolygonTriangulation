#include <iostream> 
#include <vector>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]){
    //Initializing the points
    srand(14);
    vector<int> points_idx;
    int range=atoi(argv[1]);
    int num_point=0;
    ofstream fout;
    fout.open("test.txt");
    fout << range << "\n";
    while(num_point!=range){
        double x1=3*((double)(rand()%range))/((rand()%range) + 1);
        double y1=3*((double)(rand()%range))/((rand()%range) + 1);
        if(isinf(x1) || isinf(y1)){
            continue;
        }
        int idx=num_point;
        num_point++;
        fout << x1 << " " << y1 << " " << "0\n";
    }

    return 0;
}