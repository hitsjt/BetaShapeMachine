#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<sstream>
#include<vector>
#include<ctime>
#include"Sample.h"
#include "TriMesh.h"
#include "namepoint.h"
using namespace std;

#ifndef _LALALALAL_
#define _LALALALAL_
struct MyCustomTriangleVertexTriple
{
	size_t id;
  Vector3 v[3];

  MyCustomTriangleVertexTriple() {}
  MyCustomTriangleVertexTriple(Vector3 const & v0_, Vector3 const & v1_, Vector3 const & v2_, size_t _id)
  {
    v[0] = v0_;
    v[1] = v1_;
    v[2] = v2_;
		id = _id;
  }
  MyCustomTriangleVertexTriple(MyCustomTriangleVertexTriple const & src)
  {
    v[0] = src.v[0];
    v[1] = src.v[1];
    v[2] = src.v[2];
		id = src.id;
  }

  // Get the i'th vertex. This is the operative function that a vertex triple needs to have.
  Vector3 const & getVertex(int i) const { return v[i]; }
};

typedef Triangle3<MyCustomTriangleVertexTriple> MyCustomTriangle;
typedef KDTree3<NamedPoint> PKDTree;
typedef KDTree3<MyCustomTriangle> TKDTree;
#endif

class SamplePoissonDisk
{
public:
	SamplePoissonDisk(void);
	~SamplePoissonDisk();
	SamplePoissonDisk(vector<ivec3> face_list, vector<vec3> position, vector<vec3> normal);

		static const double RELATIVE_RADIUS;
	public:

		bool runSampling(int numSamples);
		bool outputSample(vector<vec3> &outPosition, vector<vec3> &outNormal, float &outRadius);
		bool exportSample(string fileName);
		static bool loadSample(string fileName, Sample &samples);
		int clamp(int value, int min, int max);
		vector<Sample> GetSample(int numSamples);
		bool checkVisibility(Sample &sample);

	private:

		bool calculateCDF();
		bool buildGrids(int numSamples);
		bool generateSamples(int numSamples);

		void clearUp();

	private:

		static double getPreciseRandomNumber(); // higher precision random number generator

	private:

		vector<ivec3> mpMeshIndices;
		vector<vec3> mpMeshVertices;
		vector<vec3> mpMeshNormals;

	private:

		vector<double> mTriangleAreaCDF; // CDF normalized to [0..1] : # of faces
		double mTotalArea; // mesh total area
		double mSampleRadius; // sample points' minimum distance
		double mGridRadius; // grid's side length (may be larger than mSampleRadius)
		vec3 mBBMin; // mesh bounding box corner
		vec3 mBBMax; // mesh bounding box corner
		vector<vector<int>> mGrids; // sampleID : # of samples in grid cell : (gridXSize*gridYSize*gridZSize)
		ivec3 mGridSize; // dimensions of grids
		vector<Sample> mSamples; // sample : # of samples
		vector<MyCustomTriangle> triangles;    // list of triangles for ray-triangle intersections	
		TKDTree* tree;
};

