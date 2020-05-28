// obstacleTracker.cpp : Defines the entry point for the application.
//

#include "obstacleTracker.h"
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#define MINFEATURESALLOWED 5

void Feature::setAngle(float newAngle) {
	this->angle = newAngle;
}

float Feature::getAngle() {
	return this->angle;
}

void Cluster::addFeature(Feature newFeature) {
	this->clusterPoints.push_back(newFeature);
}

vector<Feature>& Cluster::getCluster() {
	return clusterPoints;
}

void Cluster::setCenter(float centerValue) {
    this->center = centerValue;
}

float Cluster::getCenter() {
    return this->center;
}


int loadFile(string file_path, vector<float>& pointCloud) {
    ofstream myfile;
    string a;
    fstream file(file_path, ios::in);
    if (!file.is_open())
    {
        cout << "File not found!\n";
        return 1;
    }
    
    std::ifstream features_file(file_path);

    float currentAngle = 0.0;
    string textLine;
    // read every line from the stream
    while (getline(features_file, textLine)) {
        istringstream textStream(textLine);
        vector<string> textColumn;
        string valueText;
        // read every element from the line that is seperated by commas
        // and put it into the vector or strings
        while (getline(textStream, valueText, ',')) {
            pointCloud.push_back(stof(valueText));
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        cout << "Finding clusters..." << endl;
   
        std::cout << "File chosen: " << argv[1] << std::endl;
        vector<float> pointCloud;
        if (loadFile(argv[1], pointCloud)) {
            return 1;
        }
        sort(pointCloud.begin(), pointCloud.end()); //sort values

        float distanceFirstLast = abs((pointCloud[0] + 360) - pointCloud[pointCloud.size() - 1]); //distance between the first and the last point

        vector<Cluster> clusters;
        Cluster tempCluster;

        Feature ft(pointCloud[0]);
        tempCluster.addFeature(ft);
        clusters.push_back(tempCluster);

        for (int i = 0; i < pointCloud.size() - 1; i++) {
            Feature ft2(pointCloud[i + 1]);
            if (abs(pointCloud[i + 1] - ((pointCloud[i] + pointCloud[i + 1]) / 2)) > 20) {
                Cluster tempCluster2;
                tempCluster2.addFeature(ft2);
                clusters.push_back(tempCluster2);
                clusters[clusters.size() - 1].addFeature(ft2);
            }
            else {
                clusters[clusters.size() - 1].addFeature(ft2);
            }
        }

        if (distanceFirstLast < 20) {
            clusters[0].getCluster().insert(clusters[0].getCluster().begin(), clusters[clusters.size() - 1].getCluster().begin(), clusters[clusters.size() - 1].getCluster().end());
            clusters.pop_back();
        }

        cout << endl;
        cout << endl;
        cout << "Printing clusters.." << endl;
        for (int i = 0; i < clusters.size(); i++) {
            for (auto j : clusters[i].getCluster()) {

                cout << j.getAngle() << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        fstream file;
        file.open("output.txt", ios::out);

        cout << "The centroids are: " << endl;
        for (int i = 0; i < clusters.size(); i++) {
            if (clusters[i].getCluster().size() > MINFEATURESALLOWED) { //filter out outlier features
                //calculate median
                float sizeCluster = clusters[i].getCluster().size();
                if (clusters[i].getCluster().size() % 2 == 0) {

                    float tempDistance = clusters[i].getCluster()[sizeCluster / 2 - 1].getAngle() - clusters[i].getCluster()[sizeCluster / 2 - 2].getAngle();
                    if (tempDistance < 0)
                        tempDistance += 360;
                    float tempCentroid = clusters[i].getCluster()[sizeCluster / 2 - 2].getAngle() + tempDistance / 2;
                    if (tempCentroid >= 360)
                        tempCentroid -= 360;
                    clusters[i].setCenter(tempCentroid);
                }
                else {
                    clusters[i].setCenter(clusters[i].getCluster()[floor(sizeCluster / 2)].getAngle());
                }
                file << clusters[i].getCenter() << " ";
                cout << clusters[i].getCenter() << " ";
            }
        }
        file << endl;
        cout << endl;
        file.close();
    }
    else {
        cout << "No path to the File was given, please specify the path as the first argument of the executable. " << endl;
    }
	return 0;
}
