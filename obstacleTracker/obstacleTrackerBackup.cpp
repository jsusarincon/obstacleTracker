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

string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
}

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

    //Feature p{};
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
            //p.setAngle(stof(csvElement));
            pointCloud.push_back(stof(valueText));
        }
        
    }
    return 0;
}

int main(int argc, char* argv[])
{
	cout << "Finding clusters..." << endl;
    string inputDataPath = ExePath() + "\\example_data\\"+"input0.txt";
    inputDataPath = "E:\\input0.txt";
    //cout << "My data is:" << inputDataPath << "\n";
    //const char* myfileName = inputDataPath.c_str();
    std::cout << "File chosen: " << inputDataPath << std::endl;
    vector<float> pointCloud;
    if (loadFile(inputDataPath, pointCloud)) {
        return 1;
    }
    sort(pointCloud.begin(),pointCloud.end());
    for (auto i: pointCloud) {
        cout << i << " ";
    }
    cout << endl;

    //vector<float> distances;
    //for (int i = 0; i < pointCloud.size() - 1; i++) {
    //    distances.push_back(abs(pointCloud[i]- pointCloud[i+1]));
    //}

    //distances.push_back(abs((pointCloud[0]+360) - pointCloud[pointCloud.size() - 1])); //distance between the first and the last point
    float distanceFirstLast=abs((pointCloud[0] + 360) - pointCloud[pointCloud.size() - 1]); //distance between the first and the last point
    cout << endl;
    cout << endl;
    /*for (auto i : distances) {
        cout << i << " ";
    }
    cout << endl;*/

    

	vector<vector<float> > clusters;
	vector<float> temp;
	clusters.push_back(temp);
	clusters[0].push_back(pointCloud[0]);
    //means.push_back(pointCloud[0]);
    int indextMeans = 0;
	for (int i = 0; i < pointCloud.size() - 1; i++) {
		if (abs(pointCloud[i + 1] - ((pointCloud[i] + pointCloud[i + 1]) / 2)) > 20) {
			vector<float> temp;
			clusters.push_back(temp);
			clusters[clusters.size() - 1].push_back(pointCloud[i + 1]);
            //means.push_back(pointCloud[i + 1]);
            indextMeans++;
		}
		else {
			clusters[clusters.size() - 1].push_back(pointCloud[i + 1]);
            //means[indextMeans]+=pointCloud[i + 1];
		}
	}
    int indxEnd = clusters.size() - 1;
	//if (distances[distances.size() - 1] < 20) {
    if (distanceFirstLast < 20) {
    
        //reverse(clusters[indxEnd].begin(), clusters[indxEnd].end());
        //float flip= clusters[indxEnd][0]; //first value last cluster
        //clusters[indxEnd][0] = clusters[indxEnd][clusters[indxEnd].size()-1];
        //clusters[indxEnd][clusters[indxEnd].size() - 1] = flip;
        clusters[0].insert(clusters[0].begin(),clusters[clusters.size() - 1].begin(), clusters[clusters.size() - 1].end());
        //means[0] += means[means.size()-1];
        clusters.pop_back();
	}

    cout << endl;
    cout << endl;
    for (int i = 0; i < clusters.size(); i++) {
        for (int j = 0; j < clusters[i].size(); j++) {
            cout << clusters[i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    vector<float> centroids;
    vector<vector<float> > distances;
    for (int i = 0; i < clusters.size();i++) {
        temp.clear();
        distances.push_back(temp);
        if (clusters[i].size()>MINFEATURESALLOWED) { //filter out outlier features
            //cout << means[i] / clusters[i].size() << " ";
            //cout << clusters[i][0]<<" "<< clusters[i][clusters[i].size() - 1]<<" "<<(clusters[i][0]+ clusters[i][clusters[i].size() - 1])/2 << " "<<endl;
            //calculate median
            if (clusters[i].size()%2==0) {
                //cout << clusters[i][clusters[i].size() / 2-1] << " ";
                //cout << clusters[i][clusters[i].size() / 2 - 2] << endl;
                float tempDistance = clusters[i][clusters[i].size() / 2 - 1] - clusters[i][clusters[i].size() / 2 - 2];
                if (tempDistance < 0)
                    tempDistance += 360;
                float tempCentroid = clusters[i][clusters[i].size() / 2 - 2] + tempDistance / 2;
                if (tempCentroid >= 360)
                    tempCentroid -= 360;
                centroids.push_back(tempCentroid);
                //centroids.push_back((clusters[i][clusters[i].size() / 2-1]+ (clusters[i][clusters[i].size() / 2-2]))/2);
            }
            else {
                centroids.push_back(clusters[i][floor(clusters[i].size()/2)]);
            }
            /*float totalDistance=0.0;
            for (int j = 0; j < clusters[i].size() - 2; j++) {
                float tempDistance = clusters[i][j+1] - clusters[i][j];
                if (tempDistance < 0)
                    tempDistance += 360;
                distances[distances.size()-1].push_back(tempDistance);
                totalDistance += tempDistance;
            }
            float tempCentroid = clusters[i][0] + totalDistance / 2;
            if (tempCentroid > 360)
                tempCentroid -= 360;
            centroids.push_back(tempCentroid);*/

            cout << centroids[i]<<" ";
        }
        
    }

    cout << endl;
	return 0;
}
