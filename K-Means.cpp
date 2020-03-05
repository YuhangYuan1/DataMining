#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>

using namespace std;

class kMeans
{
    private:

       int object;
       int xMax;
       int yMax;
       int xMin;
       int yMin;
       int centroidPoint1x;
       int centroidPoint1y;
       int centroidPoint2x;
       int centroidPoint2y;

    public:

       vector<int> database;
       vector<int> cluster1;
       vector<int> cluster2;

       kMeans();
       int distCalculator(int, int, int, int);
       void clustering();

};

kMeans::kMeans()
{
    fstream file;

    file.open("input1.txt"); //open the file

    while(!file.eof())
    {
        file >> object;
        database.push_back(object);
    }

    /***initialize centroid points***/

    xMax = database[0];
    yMax = database[1];

    xMin = database[0];
    yMin = database[1];

    for(int i = 2; i < database.size(); i+= 2)
    {
        if(database[i] > xMax)
            xMax = database[i];

        if(database[i] < xMin)
            xMin = database[i];
    }

    cout << "xMax is :" << xMax << "xMin is :" << xMin <<endl;

    for(int i = 3; i < database.size(); i+= 2)
    {
        if(database[i] > yMax)
            yMax = database[i];

        if(database[i] < yMin)
            yMin = database[i];
    }

    cout << "yMax is :" << yMax << "yMin is :" << yMin << endl;

    //seed point 1
    centroidPoint1x = xMin + rand() % (xMax - xMin + 1);
    centroidPoint1y = yMin + rand() % (yMax - yMin + 1);

    //seed point 2
    centroidPoint2x = xMin + rand() % (xMax - xMin + 1);
    centroidPoint2y = yMin + rand() % (yMax - yMin + 1);

    cout << "seed point 1 is (" << centroidPoint1x << " , " << centroidPoint1y << ")" << endl;
    cout << "seed point 2 is (" << centroidPoint2x << " , " << centroidPoint2y << ")" << endl;

    //initial clustering
    for(int i = 0; i < database.size(); i += 2)
    {
        if(distCalculator(database[i], centroidPoint1x, database[i + 1], centroidPoint1y) < distCalculator(database[i], centroidPoint2x, database[i + 1], centroidPoint2y))
        {
            cluster1.push_back(database[i]);
            cluster1.push_back(database[i + 1]);
        }

        else
        {
            cluster2.push_back(database[i]);
            cluster2.push_back(database[i + 1]);
        }
    }

    //examine unit
    cout << "data in cluster1: " << endl;
    for(int i = 0; i< cluster1.size(); i++)
    {
        cout << cluster1[i] << endl;
    }

    cout << "data in cluster2: " << endl;
    for(int i = 0; i< cluster2.size(); i++)
    {
        cout << cluster2[i] << endl;
    }

    /*** end of centroid points initializing ***/
    
    clustering();

    file.close();           //close the file
}

int kMeans::distCalculator(int x1, int x2, int y1, int y2)
{
    return sqrt(pow((x1 - x2), 2.0) + pow ((y1 - y2), 2.0));
}

void kMeans::clustering()
{
    cout << "clustering() function is called!";
}

int main()
{

    kMeans input1;

    return 0;
}
