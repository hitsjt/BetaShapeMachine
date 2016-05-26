#include "CheckFeature.h"


CheckFeature::CheckFeature(void)
{

}


CheckFeature::~CheckFeature(void)
{

}


void CheckFeature::LoadFeature(vector<Sample> &samplelist, string file_name)
{
	ifstream fin(file_name);
	samplelist.clear();
	int total_size;
	float x,y,z,nx,ny,nz;
	fin >> total_size;
	for(int i = 0;i <total_size; i++)
	{
		fin >> x >> y >> z >> nx >> ny >> nz;
		vec3 pos(x,y,z);
		vec3 nor(nx,ny,nz);
		Sample p(pos,nor);
		samplelist.push_back(p);
	}
	int feature_size;
	fin >> total_size >> feature_size;
	for(int i = 0;i <total_size; i++)
	{
		samplelist[i].sample_features.resize(feature_size);
		for(int j = 0; j < feature_size; j++)
		{
			fin >> samplelist[i].sample_features[j];
		}
	}
}

float CheckFeature::CheckDiff()
{
	float diff_err = 0;
    vector<NamedPoint> points;
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		points.push_back( NamedPoint(  t_sample[i].position[0], t_sample[i].position[1], t_sample[i].position[2], i ) );
	}
	PKDTree stree(points.begin(), points.end());
	for (size_t i = 0; i < s_sample.size(); i++)
	{
		NamedPoint query( s_sample[i].position[0], s_sample[i].position[1], s_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1); 
		int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		diff_err += Diff(t_sample[nearest_id].sample_features,s_sample[i].sample_features);
	}
	diff_err /= s_sample.size();
	cout << "total err .. " << diff_err << endl;
	return diff_err;
}

float CheckFeature::Diff(vector<float> f1, vector<float> f2)
{
	float diff = 0; 
	for(size_t i =0; i < f1.size(); i++)
	{
		//diff += (f1[i] -f2[i]) *(f1[i] -f2[i]);
		diff += abs(f1[i] -f2[i]);
	}
	return sqrt(diff);
}

void CheckFeature::OutPutFeature(string mesh_name, string file_name)
{
	Shape s_shape;
	s_shape.GetShape(mesh_name);
	s_shape.GetSamplePoint(10000);
	s_sample = s_shape.shape_sample;
	ofstream fout(file_name);
	fout << s_sample.size() << endl;
	for(size_t i = 0; i < s_sample.size(); i++)
	{
		fout << s_sample[i].position[0] << " " << s_sample[i].position[1] <<" "<< s_sample[i].position[2]<<" ";
		fout << s_sample[i].normal[0] << " " << s_sample[i].normal[1] <<" "<< s_sample[i].normal[2]<<endl;
	}
	fout << s_sample.size() <<" "<< s_sample[0].shape_context.size() << endl;
	for(size_t i = 0; i < s_sample.size(); i++)
	{
		for(size_t j = 0; j < s_sample[i].shape_context.size(); j++)
		{
			fout << s_sample[i].shape_context[j] <<" ";
		}
		fout << endl;
	}
}