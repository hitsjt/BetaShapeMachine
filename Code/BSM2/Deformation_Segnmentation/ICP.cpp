#include "ICP.h"


ICP::ICP(void)
{

}


ICP::~ICP(void)
{

}

ICP::ICP(vector<vec3> s_p, vector<vec3> t_p)
{
	s_point = s_p;
	t_point =t_p;
}


void ICP::Translation()
{
	vec3 center_s(0,0,0);
	for(size_t i = 0; i < s_point.size(); i++)
	{
		center_s += s_point[i];
	}
	center_s /= s_point.size();
	center_t[0] = 0.0f;
	center_t[1] = 0.0f;
	center_t[2] = 0.0f;
	for(size_t i = 0; i < t_point.size(); i++)
	{
		center_t += t_point[i];
	}
	center_t /= t_point.size();

	for(size_t i = 0; i < s_point.size(); i++)
	{
		s_point[i] -= center_s;
	}

	for(size_t i = 0; i < t_point.size(); i++)
	{
		t_point[i] -= center_t;
	}

}

void ICP::Scale()
{
	
	vec3 scale_s(0,0,0);
	vec3 scale_t(0,0,0);

	for(size_t i = 0; i < s_point.size(); i++)
	{
		scale_s[0] += s_point[i][0]*s_point[i][0];
		scale_s[1] += s_point[i][1]*s_point[i][1];
		scale_s[2] += s_point[i][2]*s_point[i][2];
	}
	scale_s /= s_point.size();

	for(size_t i = 0; i < t_point.size(); i++)
	{
		scale_t[0] += t_point[i][0]*t_point[i][0];
		scale_t[1] += t_point[i][1]*t_point[i][1];
		scale_t[2] += t_point[i][2]*t_point[i][2];
	}

	 scale_t /=  t_point.size();

	 for(size_t i = 0; i < s_point.size(); i++)
	{
		s_point[i][0] *= sqrt(scale_t[0]/scale_s[0]);
		s_point[i][1] *= sqrt(scale_t[1]/scale_s[1]);
		s_point[i][2] *= sqrt(scale_t[2]/scale_s[2]);
	}


}

void ICP::Rotation()
{
	vector<int> p_correspondence;
	p_correspondence.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < t_point.size(); i++)
	{
		points.push_back( NamedPoint(t_point[i][0], t_point[i][1], t_point[i][2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < s_point.size();i++)
	{
		NamedPoint query( s_point[i][0], s_point[i][1], s_point[i][2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		p_correspondence.push_back(nearest_point_id);
	}
	Eigen::Matrix3d matrix_pq = Eigen::Matrix3d::Constant(3,3,0);
	for(size_t j = 0; j < s_point.size() ; j++)
	{
		int p_index = p_correspondence[j];
		vec3 p_q = s_point[j];
		vec3 p_p = t_point[p_index];
		matrix_pq(0,0) += p_q[0] * p_p[0];
		matrix_pq(0,1) += p_q[1] * p_p[0];
		matrix_pq(0,2) += p_q[2] * p_p[0];
		matrix_pq(1,0) += p_q[0] * p_p[1];
		matrix_pq(1,1) += p_q[1] * p_p[1];
		matrix_pq(1,2) += p_q[2] * p_p[1];
		matrix_pq(2,0) += p_q[0] * p_p[2];
		matrix_pq(2,1) += p_q[1] * p_p[2];
		matrix_pq(2,2) += p_q[2] * p_p[2];
	}
	matrix_pq = matrix_pq/ (double)s_point.size();
	Eigen::JacobiSVD<Eigen::Matrix3d> svd(matrix_pq, Eigen::ComputeThinU | Eigen::ComputeThinV);
	Eigen::Matrix3d matrix_r = svd.matrixU()*svd.matrixV().transpose();

	vec3 r_x(matrix_r(0,0),matrix_r(0,1),matrix_r(0,2));
	vec3 r_y(matrix_r(1,0),matrix_r(1,1),matrix_r(1,2));
	vec3 r_z(matrix_r(2,0),matrix_r(2,1),matrix_r(2,2));

	for(size_t i = 0; i < s_point.size(); i++)
	{
		vec3 pos = s_point[i];
		vec3 pos_new((r_x DOT pos), (r_y DOT pos), (r_z DOT pos));
		s_point[i] = pos_new;
	}

}

vector<vec3> ICP::RunICP( )
{
	Translation();
	for(int ite = 0; ite < 20; ite++)
	{
		//Scale();
		Rotation();
	}
	for(size_t i = 0; i < s_point.size(); i++)
	{
		s_point[i] += center_t;
	}

	return s_point;
}
