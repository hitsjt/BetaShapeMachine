#include "Sample.h"


Sample::Sample(void)
{
	vec3 p(0,0,0);
	vec3 n(0,0,1);
	position = p;
	normal = n;
	weight = 0;
	face_id = -1;
	sample_features.clear();
	patch_id = -1;
	sample_features.clear();
	is_sigular = 0;
}


Sample::~Sample(void)
{

}


Sample::Sample(vec3 pos, vec3 nor, float weg, int id )
{
	position = pos;
	normal = nor;
	weight = weg;
	face_id = id;
	sample_features.clear();
	is_sigular = 0;
}



float Sample::dist_with_normal(Sample p1)
{
	float d_e = dist(position, p1.position);
	vec3 v = position - p1.position;
	v = normalize(v);
	float c_1 = normal DOT v;
	float c_2  = p1.normal DOT v;
	return (acos(c_1) -  acos(c_2))/(c_1 - c_2 )*d_e;
}

float Sample::dist_feature(Sample p1, int feature_type)
{
	float dis_ed = dist(position,p1.position);
	float dis_sdf = 0;
	for(size_t i = 0; i < sdf.size(); i++)
	{
		dis_sdf += (sdf[i] - p1.sdf[i])*(sdf[i] - p1.sdf[i]); 
	}
	float dis_agd = (angel_geo_dis[0] - p1.angel_geo_dis[0])*(angel_geo_dis[0] - p1.angel_geo_dis[0]);
	if(feature_type == 0)
	{
		return dis_ed;
	}
	if(feature_type == 1)
	{
		return sqrt(dis_ed*dis_ed + dis_sdf);
	}
	if(feature_type == 2)
	{
		return sqrt(dis_ed*dis_ed + dis_sdf + dis_agd);
	}
	float dis_sc = 0;
	for(size_t i = 0; i < shape_context.size(); i++)
	{
		dis_sc += (shape_context[i] - p1.shape_context[i])*(shape_context[i] - p1.shape_context[i]); 
	}
	if(feature_type == 3)
	{
		return sqrt(dis_ed*dis_ed + dis_sdf + dis_agd + dis_sc);
	}
	return 0;
}

float Sample::dist_with_feature(Sample p1)
{
	float dis_diff = dist(position, p1.position);
	float diff_sc = 0;
	float diff_cur = 0;
	return 0;
}

float Sample::dis_curvature(Sample p1)
{
	float diff_cur = 0;
	for(size_t i = 0; i < curvature.size(); i++)
	{
		diff_cur += (p1.curvature[i] - curvature[i])*(p1.curvature[i] - curvature[i]);
	}
	return sqrt(diff_cur);
}

float Sample::dis_shapeconetx(Sample p1)
{
	float diff_sc = 0;
	for(size_t i =0; i < shape_context.size(); i++)
	{
		diff_sc += (p1.shape_context[i] - shape_context[i])*(p1.shape_context[i] - shape_context[i]);
	}
	return sqrt(diff_sc);
}