#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "TriMesh.h"
#include"Eigen/Dense"
using namespace std;
using namespace trimesh;
#define PI 3.1415926

int main(int argc, char* argv[])
{
	float XSTEP = 30.f;
	float YSTEP = 30.f;
	float ZSTEP = 30.f;

	vector<vec3> samplePos;
	samplePos.clear();
	vector<vec3> sampleNor;
	sampleNor.clear();
	vector<int>  patchid;
	patchid.clear();
	vector<int>  faceid;
	faceid.clear();
	vector<ivec3> sampleColor;
	sampleColor.clear();
	ifstream fin(argv[1]);
	string para;
	vec3 center(0,0,0);
	while(fin >> para)
	{
		if(para == "end_header")
		{
			float x, y, z, nx, ny, nz;
			int face_id, patch_id;
			int c_r,c_g,c_b;
			while(fin >> x >> y >> z >> nx >> ny >> nz >> face_id >> patch_id >> c_r >> c_g >> c_b )
			{
				vec3 pos(x, y, z);
				samplePos.push_back(pos);
				vec3 nor(nx, ny, nz);
				sampleNor.push_back(nor);
				ivec3 col(c_r,c_g,c_b);
				sampleColor.push_back(col);
				patchid.push_back(patch_id);
				faceid.push_back(face_id);
				center += pos;
			}
		}
	}

	cout << samplePos.size() << " total samples " << endl;
	center /= samplePos.size();
	int rotation_index = 0;
	for (float scale = 2.0f; scale < 4.0f; scale += 1.0f)
	{
		for(float x = 0; x < 360; x = x+XSTEP)
		{
			float angel_x = x/180.0f*PI;
			Eigen::Matrix4d rotate_x ;
			rotate_x << 1.0f,0.0f,0.0f,0.0f,
				0.0f,cos(angel_x),-sin(angel_x),0.0f,
				0.0f,sin(angel_x),cos(angel_x),0.0f,
				0.0f,0.0f,0.0f,1.0f;
			//cout << rotate_x << endl;
			for(float y = 0; y < 360; y = y+YSTEP)
			{
				float angel_y = y/180.0f*PI;
				Eigen::Matrix4d rotate_y ;
				rotate_y << cos(angel_y),0.0f,sin(angel_y),0.0f,
					0.0f,1,0,0.0f,
					-sin(angel_y),0,cos(angel_y),0.0f,
					0.0f,0.0f,0.0f,1.0f;
				//cout << rotate_x << endl;
				for(float z = 0; z < 360; z = z+ZSTEP)
				{
					float angel_z = z/180.0f*PI;
					Eigen::Matrix4d rotate_z ;
					rotate_z << cos(angel_z),-sin(angel_z),0.0f,0.0f,
						sin(angel_z),cos(angel_z),0,0.0f,
						0,0,1,0.0f,
						0.0f,0.0f,0.0f,1.0f;
					//cout << rotate_x << endl;
					Eigen::Matrix4d rotate_matrix = rotate_z*rotate_y*rotate_x;
					string ply_name = "sample\\";
					ply_name.append(to_string(rotation_index));
					ply_name.append(".ply");
					cout << ply_name << endl;
					ofstream fout(ply_name);
					fout << "ply" << endl;
					fout << "format ascii 1.0" << endl;
					fout << "element vertex " << samplePos.size() << endl;
					fout << "property float32 x" << endl;
					fout << "property float32 y" << endl;
					fout << "property float32 z" << endl;
					fout << "property float32 nx" << endl;
					fout << "property float32 ny" << endl;
					fout << "property float32 nz" << endl;
					fout << "property uint  faceID" << endl;
					fout << "property uint  segmentID" << endl;
					fout << "property uchar red" << endl;
					fout << "property uchar green" << endl;
					fout << "property uchar blue" << endl;
					fout << "element face 0" << endl;
					fout << "property list uint8 int32 vertex_index" << endl;
					fout << "end_header" << endl;
					string matrix_name = "matrix\\";
					matrix_name.append(to_string(rotation_index));
					matrix_name.append(".txt");
					ofstream fmatrix(matrix_name);
					fmatrix << rotate_matrix << endl;
					fmatrix << scale << " " << scale <<" " << scale <<" " << 1 << endl;
					for(size_t i = 0; i < samplePos.size(); i++)
					{
						Eigen::Vector4d v((samplePos[i][0] - center[0])*scale,(samplePos[i][1]- center[1])*scale,(samplePos[i][2] - center[2])*scale,1.0f);
						Eigen::Vector4d v_rotate = rotate_matrix*v;
						Eigen::Vector4d n(sampleNor[i][0],sampleNor[i][1],sampleNor[i][2],0.0f);
						Eigen::Vector4d n_rotate = rotate_matrix*v;
						fout << v_rotate[0] + center[0]<< " " << v_rotate[1] + center[1]<< " "<< v_rotate[2] + center[2]<< " ";
						fout << n_rotate[0] << " " << n_rotate[1] << " "<< n_rotate[2] << " ";
						fout << faceid[i] << " " << patchid[i] << " ";
						fout << sampleColor[i][0] << " " << sampleColor[i][1] << " " << sampleColor[i][2] << endl;
					}

					rotation_index ++;
					cout << rotation_index << endl;
				}
			}
		}
	}
}