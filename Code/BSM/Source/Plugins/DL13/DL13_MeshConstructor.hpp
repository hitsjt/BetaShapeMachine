#ifndef __DL13_MESHCONSTRUCTOR_HPP
#define __DL13_MESHCONSTRUCTOR_HPP

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_ShapeGenModel.hpp"
#include "DL13_TrainingData.hpp"
#include "Trimesh2/Vec.hpp"
#include "SidKDTree/KDTree3.hpp"

namespace Thea
{;

struct NamedPoint
{
	Vector3 position;
	size_t  id;

	NamedPoint() {}
	NamedPoint(float x, float y, float z) 
	{
		position = Vector3(x, y, z);
	}
	NamedPoint(float x, float y, float z, const size_t _id) 
	{
		id = _id;
		position = Vector3(x, y, z);
	}
	SMATRIXf convertToEigenVector()
	{
		SVECTORf xyz(3);
		xyz(0) = position[0];
		xyz(1) = position[1];
		xyz(2) = position[2];
		return xyz;
	}
};

template <>
struct PointTraits3<NamedPoint>
{
	static Vector3 const & getPosition(NamedPoint const & np) { return np.position; }
};

template <>
struct IsPoint3<NamedPoint>
{
	static bool const value = true;
};

typedef KDTree3<NamedPoint> PKDTree;

}


namespace SNL {;
namespace DL13 {;

class ShapeDeepGenerativeModel;
class Point;

class SNL_DL13_API MeshConstructor
{
private:
  vector<Point>    valid_sparse_points;
  vector<Point>    valid_dense_points;
	vector<vec>      dense_normals;
	vector<point>		 part_centroids;
	vector<float>    confidence_normals;
	vector<string>   nearest_part_filename_per_sparse_point;
	vector<string>   nearest_part_filename_per_dense_point;
	vector< vector<size_t> > sparse_point_neighbors;
	vector< vector<size_t> > dense_point_neighbors;
	vector<int> component_ids;
	int num_neighbors_for_normal_estimation;
	int num_sparse_neighbors_for_patch_similarity_for_normal_orientation;
	int num_neighbors_for_dense_set;

	ShapeDeepGenerativeModel*		dm;

	//void computeNormals();
	//void orientNormals();
	//void consistentlyOrientNormals();
	//void smoothDensePoints();

	void findPartCentroidsAndSymmetries();
	void findNearestParts();
public:
	MeshConstructor( ShapeDeepGenerativeModel *_dm ): dm(_dm) { };
	void createMesh( const std::string & out_path = "" );	
	int findNumberOfConnectedComponentsInTheSparsePointCloud();
	bool checkIfPartsAgreeWithSymmetricBits();
  vector<Point> smoothSparsePoints(int smoothing_amount_mult = 1);
	
};


}
}

#endif