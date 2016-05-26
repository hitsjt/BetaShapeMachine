#include "SamplePoissonDisk.h"
const double SamplePoissonDisk::RELATIVE_RADIUS = 0.76;
float mSample_MinimumSampleRate = 0.8;
int mSample_MaximumFailedCount = 10000;
SamplePoissonDisk::SamplePoissonDisk(void)
{

}

SamplePoissonDisk::SamplePoissonDisk(vector<ivec3> face_list, vector<vec3> position, vector<vec3> normal)
{
	mpMeshIndices = face_list;
	mpMeshVertices = position;
	mpMeshNormals = normal;
}

SamplePoissonDisk::~SamplePoissonDisk()
{

	clearUp();
}

bool SamplePoissonDisk::runSampling(int numSamples)
{

	if( !calculateCDF() ) return false;
	cout << "end cdf" << endl;
	long long n = numSamples; // be careful! may be very large
	mSamples.clear();

	while( (double)mSamples.size() < numSamples * mSample_MinimumSampleRate)
	{
		// not enough samples, redo sampling

		if( !buildGrids( (int)n ) ) return false;
		if( !generateSamples( (int)n ) ) return false;
		n = n * numSamples / max(1, (int)mSamples.size());
	}
	cout << "sampling" << endl;
	return true;
}

bool SamplePoissonDisk::calculateCDF() 
{

	mTotalArea = 0.0;

	// accumulate triangle area
	mTriangleAreaCDF.clear();
	for(ivec3 &idx : (mpMeshIndices))
	{
		vec3 v[3];
		for(int j=0; j<3; j++) v[j] = (mpMeshVertices)[idx[j]];
		vec3 p_n =  (v[1]-v[0]) CROSS (v[2]-v[0]);
		mTotalArea += len(p_n);
		mTriangleAreaCDF.push_back(mTotalArea);
	}

	if(mTotalArea == 0) {
		cout << "Error: empty mesh" << endl;
		return false;
	}

	// normalize CDF
	double denom = 1.0 / mTotalArea;
	for(double &it : mTriangleAreaCDF) {
		it *= denom;
	}

	return true;
}

bool SamplePoissonDisk::buildGrids(int numSamples) {

	int numFaces = (int)mpMeshIndices.size();

	// calculate bounding box
	mBBMin = vec3( FLT_MAX,  FLT_MAX,  FLT_MAX);
	mBBMax = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	{
		for(ivec3 &idx : (mpMeshIndices)) {
			for(int j=0; j<3; j++) {
				vec3 v = (mpMeshVertices)[idx[j]];
				mBBMin.min(v);
				mBBMax.max(v);
			}
		}
	}

	mSampleRadius = sqrt(mTotalArea / (sqrt(3.0)*numSamples/2)) * RELATIVE_RADIUS;

	// calculate grid size

	const int maxGirdSize = 500; // UNDONE: param

	vec3 bbSize = mBBMax - mBBMin;
	double maxBBSize = (double) max(bbSize[0], max(bbSize[1], bbSize[2]));

	mGridRadius = max(mSampleRadius, maxBBSize/maxGirdSize);
	mGridSize[0] = clamp((int)ceil( (double)bbSize[0] / mGridRadius ), 1, maxGirdSize);
	mGridSize[1] = clamp((int)ceil( (double)bbSize[1] / mGridRadius ), 1, maxGirdSize);
	mGridSize[2] = clamp((int)ceil( (double)bbSize[2] / mGridRadius ), 1, maxGirdSize);

	return true;
}

int SamplePoissonDisk::clamp(int value, int min, int max)
{
	if(value < min)
	{
		value =  min;
	}
	if(value > max)
	{
		value = max;
	}
	return value;
}

bool SamplePoissonDisk::generateSamples(int numSamples) {

	int numFaces = (int)mpMeshIndices.size();

	// init grids

	long long gridAllSize = mGridSize[0]*mGridSize[1]*mGridSize[2];
	if(gridAllSize > 200000000LL) {
		// requires too much memory, infeasible
		mSamples.clear();
		return true;
	}
	mGrids.clear();
	mGrids.resize((int)gridAllSize, vector<int>(0));

	// Poisson disk sampling

	mSamples.clear();
	mSamples.resize(numSamples);
	int failCount = 0;
	int sampleID;
	for(sampleID=0; sampleID<numSamples; sampleID++) {

		// choose a triangle based on CDF
		int faceID;
		{
			double rng = getPreciseRandomNumber();
			// binary search
			int p1 = -1;
			int p2 = numFaces-1;
			while(p1+1 < p2) {
				int pm = (p1+p2)/2;
				if(mTriangleAreaCDF[pm] < rng) {
					p1 = pm;
				} else {
					p2 = pm;
				}
			}
			faceID = p2;
		}

		// sample within a triangle
		Sample sample;
		{
			ivec3 idx = mpMeshIndices[faceID];
			vec3 v[3];
			for(int j=0; j<3; j++) v[j] = (mpMeshVertices)[idx[j]];

			double rng1 = (float)(rand())/RAND_MAX;
			double rng2 = (float)(rand())/RAND_MAX;
			float r1 = (float)(1 - sqrt(rng1));
			float r2 = (float)(rng2 * sqrt(rng1));

			sample.position = v[0] + (v[1]-v[0]) * r1 + (v[2]-v[0]) * r2;
			vec3 p_n =  (v[1]-v[0]) CROSS (v[2]-v[0]);
			p_n =  normalize(p_n);
			sample.normal = p_n;
			sample.face_id = faceID;
		}

		// check grid
		bool valid = true;
		int gridPos;
		{
			vec3 relPos = sample.position - mBBMin;
			int gridX = clamp( (int)floor( (double)relPos[0] / mGridRadius ), 0, mGridSize[0]-1 );
			int gridY = clamp( (int)floor( (double)relPos[1] / mGridRadius ), 0, mGridSize[1]-1 );
			int gridZ = clamp( (int)floor( (double)relPos[2] / mGridRadius ), 0, mGridSize[2]-1 );
			gridPos = (gridX * mGridSize[1] + gridY) * mGridSize[2] + gridZ;

			// check within 3x3x3 neighbor cells
			for(int offsetX=-1; offsetX<=1; offsetX++) {
				int clampX = clamp(gridX+offsetX, 0, mGridSize[0]-1);
				if(gridX+offsetX != clampX) continue;
				for(int offsetY=-1; offsetY<=1; offsetY++) {
					int clampY = clamp(gridY+offsetY, 0, mGridSize[1]-1);
					if(gridY+offsetY != clampY) continue;
					for(int offsetZ=-1; offsetZ<=1; offsetZ++) {
						int clampZ = clamp(gridZ+offsetZ, 0, mGridSize[2]-1);
						if(gridZ+offsetZ != clampZ) continue;

						int checkPos = (clampX * mGridSize[1] + clampY) * mGridSize[2] + clampZ;
						for(int nbID : mGrids[checkPos]) {
							Sample &neighbor = mSamples[nbID];
							if((sample.normal DOT neighbor.normal) > 0) { // normal compatible

								vec3 &p1 = sample.position;
								vec3 &n1 = sample.normal;
								vec3 &p2 = neighbor.position;
								vec3 &n2 = neighbor.normal;
								vec3 v = p2-p1;

								// estimate geodesic distance
								float dist = len(v);
								v = normalize(v);
								float c1 = (n1 DOT v);
								float c2 = (n2 DOT v);
								dist *= fabs(c1-c2) < 1e-7 ? (1.0f/sqrt(1.0f-c1*c1)) : (asin(c1)-asin(c2))/(c1-c2);

								//float dist = len(v) + len(n1 - n2)*0.05;

								// use L1 distance
								//float dist = fabs(v[0]) + fabs(v[1]) + fabs(v[2]);

								// use Euclid distance
								//float dist = v.length();

								if( dist < mSampleRadius ) {
									valid = false;
									break;
								}
							}
						}
						if(!valid) break;
					}
					if(!valid) break;
				}
				if(!valid) break;
			}
		}

		// process sample (accept or discard)
		if (valid) {
			//cout << "\rSampling: " << (sampleID+1) << " / " << numSamples << "        ";
			mGrids[gridPos].push_back(sampleID);
			mSamples[sampleID] = sample;
			failCount = 0;
		} else {
			sampleID--;
			failCount++;
			if(failCount > mSample_MaximumFailedCount) break;
		}
	}

	mSamples.resize(sampleID);

	return true;
}



void SamplePoissonDisk::clearUp() {

	mTriangleAreaCDF.clear();
	mGrids.clear();
	mSamples.clear();
}

double SamplePoissonDisk::getPreciseRandomNumber() {

	long long rng = rand()*(RAND_MAX+1)+rand();
	return double(rng) / ((RAND_MAX+1)*(RAND_MAX+1));
}

vector<Sample> SamplePoissonDisk::GetSample(int numSamples)
{
	runSampling(numSamples);
	vector<Sample> m_sample;
	m_sample.clear();
	for (int i = 0; i < mSamples.size(); i++)
	{
		if (checkVisibility(mSamples[i]))
		{
			m_sample.push_back(mSamples[i]);
		}
	}
	return m_sample;
}

bool SamplePoissonDisk::checkVisibility(Sample &sample)
{
	return true;
}