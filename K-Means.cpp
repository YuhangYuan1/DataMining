//Author Jason Yuan , 3/5/2020
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <string>

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

       kMeans(string, string);
       int distCalculator(int, int, int, int);
       bool updateCentroid();
       void reClustering();
       void outPutGenerator(string);
};

kMeans::kMeans(string inputFileName, string outputFileName)
{
    ifstream fin;

    fin.open(inputFileName.c_str()); //open the input file

    while(!fin.eof())
    {
        fin >> object;
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

    for(int i = 3; i < database.size(); i+= 2)
    {
        if(database[i] > yMax)
            yMax = database[i];

        if(database[i] < yMin)
            yMin = database[i];
    }

    //seed point 1
    centroidPoint1x = xMin + rand() % (xMax - xMin + 1);
    centroidPoint1y = yMin + rand() % (yMax - yMin + 1);

    //seed point 2
    centroidPoint2x = xMin + rand() % (xMax - xMin + 1);
    centroidPoint2y = yMin + rand() % (yMax - yMin + 1);

    cout << "seed point 1 is (" << centroidPoint1x << " , " << centroidPoint1y << "), ";
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

    /*examine unit
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
    */

    /*** end of centroid points initializing ***/

    while(updateCentroid())
    {
        reClustering();
    }

    outPutGenerator(outputFileName);

    fin.close();           //close the input file
}

int kMeans::distCalculator(int x1, int x2, int y1, int y2)
{
    return sqrt(pow((x1 - x2), 2.0) + pow ((y1 - y2), 2.0));
}

bool kMeans::updateCentroid()
{
    int sumX = 0,
        sumY = 0,
        preCentroPoint1x = centroidPoint1x,
        preCentroPoint1y = centroidPoint1y,
        preCentroPoint2x = centroidPoint2x,
        preCentroPoint2y = centroidPoint2y;

    //update centroidPoint1x
    for(int i = 0; i < cluster1.size(); i += 2)
    {
        sumX += cluster1[i];
    }

    centroidPoint1x = sumX / cluster1.size();

    //update centroidPoint1y
    for(int i = 1; i < cluster1.size(); i += 2)
    {
        sumY += cluster1[i];
    }

    centroidPoint1x = sumX / cluster1.size();

    //update centroidPoint2x
    for(int i = 0; i < cluster2.size(); i += 2)
    {
        sumX += cluster2[i];
    }

    centroidPoint1x = sumX / cluster2.size();

    //update centroidPoint2y
    for(int i = 1; i < cluster2.size(); i += 2)
    {
        sumY += cluster2[i];
    }

    centroidPoint1x = sumY / cluster2.size();

    if(preCentroPoint1x == centroidPoint1x && preCentroPoint2x == centroidPoint2x && preCentroPoint1y == centroidPoint1y && preCentroPoint2y == centroidPoint2y)
    {
        cout << "updated centroid point 1 is still (" << centroidPoint1x << " , " << centroidPoint1y << ") STOP updating!" << endl;
        cout << "updated centroid point 2 is still (" << centroidPoint2x << " , " << centroidPoint2y << ") STOP updating!" << endl;
        cout << "******Process Finished, NEW Clusters defined for input!******" << endl;
        return false;
    }

    else
    {
        cout << "updated centroid point 1 is (" << centroidPoint1x << " , " << centroidPoint1y << ") ,";
        cout << "updated centroid point 2 is (" << centroidPoint2x << " , " << centroidPoint2y << ")" << endl;
        return true;
    }
}

void kMeans::reClustering()
{
    //reclustering cluster1
    for(int i = 0; i < cluster1.size(); i += 2)
    {
        if(distCalculator(cluster1[i], centroidPoint1x, cluster1[i + 1], centroidPoint1y) > distCalculator(cluster1[i], centroidPoint2x, cluster1[i + 1], centroidPoint2y))
        {
            cluster2.push_back(cluster1[i]);
            cluster2.push_back(cluster1[i + 1]);
            cluster1.erase(cluster1.begin() + i - 1);
            cluster1.erase(cluster1.begin() + i);
        }
    }

    //reclustering cluster2
    for(int i = 0; i < cluster2.size(); i += 2)
    {
        if(distCalculator(cluster2[i], centroidPoint1x, cluster2[i + 1], centroidPoint1y) < distCalculator(cluster2[i], centroidPoint2x, cluster2[i + 1], centroidPoint2y))
        {
            cluster1.push_back(cluster2[i]);
            cluster1.push_back(cluster2[i + 1]);
            cluster2.erase(cluster1.begin() + i - 1);
            cluster2.erase(cluster1.begin() + i);
        }
    }
}

void kMeans::outPutGenerator(string fileName)
{
    ofstream fout;
    fout.open(fileName.c_str());    //open the output file

    /*** output for objects in cluster1 ***/

    for(int i = 0; i < cluster1.size(); i += 2)
    {
        fout << cluster1[i];
        fout << "    	";
        fout << cluster1[i + 1];
        fout << "    	";
        fout << "1";
        fout << endl;
    }

    /*** output for objects in cluster2 ***/
    for(int i = 0; i < cluster2.size(); i += 2)
    {
        fout << cluster2[i];
        fout << "    	";
        fout << cluster2[i + 1];
        fout << "    	";
        fout << "2";
        fout << endl;
    }

    cout <<  fileName << " is generated! " << endl;
    cout << endl;

    fout.close();                //close the output file
}

int main()
{
    kMeans k1("input1.txt", "output1.txt");
    kMeans k2("input2.txt", "output2.txt");
    kMeans k3("input3.txt", "output3.txt");
    kMeans k4("input4.txt", "output4.txt");

    return 0;
}
