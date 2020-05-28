// obstacleTracker.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Feature {
private:
	float angle;
public:
	void setAngle(float);
	float getAngle();
	Feature(float newAngleFeature) {
		//Feature is being created with input;
		angle = newAngleFeature;
	}
	Feature() {
		//Feature is being created without input ;
		angle = 0;
	}
	~Feature() {
		//Feature is being deleted;
	}
};

class Cluster {
private:
	float center;
	vector<Feature> clusterPoints;
public:
	vector<float> distances;	//this vector can save the distances between the points to be used by kmeans for example.
	Cluster() {
		//Cluster is being created;
		center = 0;
	}
	~Cluster() {
		//Cluster is being deleted;
	}
	void addFeature(Feature);
	void setCenter(float);
	float getCenter();
	vector<Feature>& getCluster();
};
