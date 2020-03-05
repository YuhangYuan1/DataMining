#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

void kMeans()
{
    fstream file;

    file.open("input2.txt");

    vector<int> number;
    int tempnumber;

    while(!file.eof())
    {
        file >> tempnumber;
        cout << tempnumber << endl;
        number.push_back(tempnumber);
    }



    file.close();           //close the file
}

int main()
{
    kMeans();

    return 0;
}
