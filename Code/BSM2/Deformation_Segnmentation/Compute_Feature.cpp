
#include "Compute_Feature.h"
#include "f2c.h"
#include "clapack.h"
#include "blaswrap.h"

Compute_Feature::Compute_Feature(void)
{
	normal_map_res = 4;
	geodesic_distances = NULL;
	geodesic_closest_samples = NULL;
}

Compute_Feature::Compute_Feature(vector<Sample> point_set)
{
	sample_set = point_set;
	geodesic_distances = NULL;
	geodesic_closest_samples = NULL;
}

Compute_Feature::~Compute_Feature(void)
{
	if ( geodesic_distances != NULL && sample_set.size() > 0) 
	{
		for (size_t i = 0; i < sample_set.size(); i++) 
		{
			delete[] geodesic_distances[i];
			delete[] geodesic_closest_samples[i];
		}

		delete[] geodesic_distances;
		delete[] geodesic_closest_samples;
	}
}

float Compute_Feature::rayShoot(vec& line, point& origin, float limdist)
{
	float eps = 1e-5f;
	Ray3 ray(Vector3(origin[0] + eps * line[0], origin[1] + eps * line[1], origin[2] + eps * line[2]), Vector3(line[0], line[1], line[2]));
	Real hit_time = tree->rayIntersectionTime(ray);
	if (hit_time >= 0)
		return hit_time;
	else
		return -1.0f;
}

void Compute_Feature::exportPCA()
{
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		Eigen::Matrix3d local_covariance_matrix = Eigen::Matrix3d::Constant(3, 3, 0);
		Eigen::Vector3d centroid(0, 0, 0);
		vector<int> near_list;
		near_list.clear();
		for (int j = 0; j < sample_set.size(); j++)
		{
			if (j != i)
			{
				vec3 diff = sample_set[i].position - sample_set[j].position;
				if (len(diff) < 0.2)
				{
					Eigen::Vector3d v(diff[0], diff[1], diff[2]);
					centroid += v;
					near_list.push_back(j);
				}

			}
		}
		centroid /= (float)near_list.size();

		for (int kn = 0; kn < near_list.size(); kn++)
		{
			vec3 diff = sample_set[i].position - sample_set[near_list[kn]].position;
			Eigen::Vector3d v(diff[0], diff[1], diff[2]);
			v = v - centroid;
			local_covariance_matrix += v * v.transpose();
		}

		local_covariance_matrix /= (float)near_list.size();
		Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver;
		eigensolver.compute(local_covariance_matrix);
		Eigen::JacobiSVD<Eigen::MatrixXd> svd(local_covariance_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
		Eigen::Vector3d e_v = eigensolver.eigenvalues();
		float sum_e = abs(e_v(2)) + abs(e_v(1)) + abs(e_v(0));
		if (abs(svd.matrixV()(0, 0)) > abs(svd.matrixV()(1, 0)) && abs(svd.matrixV()(0, 0)) > abs(svd.matrixV()(2, 0)))
		{
			sample_set[i].pca[0] = abs(e_v(0) / sum_e);
		}
		if (abs(svd.matrixV()(1, 0)) > abs(svd.matrixV()(0, 0)) && abs(svd.matrixV()(1, 0)) > abs(svd.matrixV()(2, 0)))
		{
			sample_set[i].pca[0] = abs(e_v(1) / sum_e);
		}
		if (abs(svd.matrixV()(2, 0)) > abs(svd.matrixV()(0, 0)) && abs(svd.matrixV()(2, 0)) > abs(svd.matrixV()(1, 0)))
		{
			sample_set[i].pca[0] = abs(e_v(2) / sum_e);
		}
		if (abs(svd.matrixV()(0, 1)) > abs(svd.matrixV()(1, 1)) && abs(svd.matrixV()(0, 1)) > abs(svd.matrixV()(2, 1)))
		{
			sample_set[i].pca[1] = abs(e_v(0) / sum_e);
		}
		if (abs(svd.matrixV()(1, 1)) > abs(svd.matrixV()(0, 1)) && abs(svd.matrixV()(1, 1)) > abs(svd.matrixV()(2, 1)))
		{
			sample_set[i].pca[1] = abs(e_v(1) / sum_e);
		}
		if (abs(svd.matrixV()(2, 1)) > abs(svd.matrixV()(0, 1)) && abs(svd.matrixV()(2, 1)) > abs(svd.matrixV()(1, 1)))
		{
			sample_set[i].pca[1] = abs(e_v(2) / sum_e);
		}
		if (abs(svd.matrixV()(0, 2)) > abs(svd.matrixV()(1, 2)) && abs(svd.matrixV()(0, 2)) > abs(svd.matrixV()(2, 2)))
		{
			sample_set[i].pca[2] = abs(e_v(0) / sum_e);
		}
		if (abs(svd.matrixV()(1, 2)) > abs(svd.matrixV()(0, 2)) && abs(svd.matrixV()(1, 2)) > abs(svd.matrixV()(2, 2)))
		{
			sample_set[i].pca[2] = abs(e_v(1) / sum_e);
		}
		if (abs(svd.matrixV()(2, 2)) > abs(svd.matrixV()(0, 2)) && abs(svd.matrixV()(2, 2)) > abs(svd.matrixV()(1, 2)))
		{
			sample_set[i].pca[2] = abs(e_v(2) / sum_e);
		}
		/*sample_set[i].pca[0] = abs(e_v(2)/sum_e);
		sample_set[i].pca[1] = abs(e_v(1)/sum_e);
		sample_set[i].pca[2] = abs(e_v(0)/ sum_e);*/
		sample_set[i].sample_features.clear();
		sample_set[i].sample_features.push_back(sample_set[i].pca[0]);
		sample_set[i].sample_features.push_back(sample_set[i].pca[1]);
		sample_set[i].sample_features.push_back(sample_set[i].pca[2]);
	}
}


void Compute_Feature::exportSDF(TriMesh *mesh)
{
	cout << "begin finding near " << endl;
	bulitNear();
	cout << "begin get GeodesicDistances" << endl;
	computeGeodesicDistances();
	vector<MyCustomTriangle> triangles;    // list of triangles for ray-triangle intersections	
	bool *done = new bool[mesh->faces.size()];
	mesh->bbox.valid = false; mesh->need_bbox();
	triangles.clear();
	delete tree;
	for (size_t i = 0; i < mesh->faces.size(); i++)
	{
		Vector3 v[3] = { Vector3(mesh->vertices[mesh->faces[i][0]][0], mesh->vertices[mesh->faces[i][0]][1], mesh->vertices[mesh->faces[i][0]][2]),
			Vector3(mesh->vertices[mesh->faces[i][1]][0], mesh->vertices[mesh->faces[i][1]][1], mesh->vertices[mesh->faces[i][1]][2]),
			Vector3(mesh->vertices[mesh->faces[i][2]][0], mesh->vertices[mesh->faces[i][2]][1], mesh->vertices[mesh->faces[i][2]][2]) };
		MyCustomTriangle tri(MyCustomTriangleVertexTriple(v[0], v[1], v[2], i));
		triangles.push_back(tri);
	}

	tree = new TKDTree(triangles.begin(), triangles.end());
	std::cout << "Re-created AABB tree for ray-triangle intersections" << std::endl;

	sdfs.resize(NUM_SDF_FEATURES_PER_ANGLE * NUM_SDF_FEATURES_PER_BASE);
	for (int j = 0; j < NUM_SDF_FEATURES_PER_ANGLE * NUM_SDF_FEATURES_PER_BASE; j++)
	{
		sdfs[j].resize(sample_set.size());
	}
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		sample_set[i].sdf.resize(NUM_SDF_FEATURES_PER_ANGLE  * NUM_SDF_FEATURES_PER_BASE);
	}
	std::cout << "Computing SDF features for mesh " << std::endl;
	for (size_t i = 0; i < sample_set.size(); i++)
	{

		vector<float> sdf;
		float dist2center = 0.0f;
		vec v = -sample_set[i].normal;
		point o = sample_set[i].position;
		point rcenter;
		vec u = sample_set[i].position - sample_set[geodesic_closest_samples[i][1]].position;
		u = normalize(u);
		vec3 uv = u CROSS v;
		u = normalize(uv);

		// sdf computation
		for (float angle = 0; angle <= ANGLE3_SDF; angle += ANGLE_STEP)
		{
			vec3 uu = cosd(angle)*v + (1 - cosd(angle))*(v DOT u)*u + sind(angle)*(u CROSS v);
			vec tv = normalize(uu);
			for (float rotangle = 0; rotangle < 360; rotangle += ROT_ANGLE_STEP)
			{
				vec3 uuu = cosd(rotangle)*tv + (1 - cosd(rotangle))*(tv DOT v)*v + sind(rotangle)*(v CROSS tv);
				vec ttv = normalize(uuu);
				float sdf_ttvo = rayShoot(ttv, o, -1);
				//float sdf_ttvo = checkClosestLineIntersection(ttv, o, pointsamples[i]->faceid, mesh, done);
				if (sdf_ttvo > 0.0f)
					sdf.push_back(sdf_ttvo);
			}

			if (sdf.size() == 0)
				sdf.push_back(EPSILON);
			float minimun_sdf = FLT_MAX;
			for (int ii = 0; ii < sdf.size(); ii++)
			{
				if (sdf[ii] < minimun_sdf)
				{
					minimun_sdf = sdf[ii];
				}
			}
			dist2center = 0.5f * minimun_sdf;
			rcenter = o + dist2center * v;
			sample_set[i].sdf[0] = median(sdf);
			sdfs[0][i] = median(sdf);
		}
		sdf.clear();
	} // end of basic sdf computation per point sample

	// sdf renormalization
	for (size_t j = 0; j < NUM_SDF_FEATURES_PER_ANGLE; j++)
	{
		sdfs[j] = removePositiveOutliers(sdfs[j], .9f);

		float maxsdf = 0.5; //maximum( sdfs[j] );
		for (size_t i = 0; i < sample_set.size(); i++)
			sdfs[j][i] /= maxsdf;

		for (size_t i = 0; i < sample_set.size(); i++)
		{
			for (int base = 1; base < NUM_SDF_FEATURES_PER_BASE; base++) // always start from 1, make sure the fiest element of BASES_SDF is 1 (no use of log then).
			{
				size_t basepos = base * NUM_SDF_FEATURES_PER_ANGLE;
				sdfs[basepos + j][i] = log(sdfs[j][i] * BASES_SDF[base] + 1.0f) / log(BASES_SDF[base] + 1.0f);
			}
		}
	} // end of sdf remonormalization
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		for (size_t j = 0; j < sample_set[i].sdf.size(); j++)
		{
			sample_set[i].sdf[j] = sdfs[j][i];
			sample_set[i].sample_features.push_back(sdfs[j][i]);
		}
	}
}

void Compute_Feature::exportSpinImage()
{
	int numbins = (int)SPIN_RESOLUTION;
	//spins.resize( numbins * numbins );
	//for (size_t j = 0; j < numbins * numbins; j++) 
	//{
		//spins[j].resize( pointsamples.size() );
	//}
	for(size_t i = 0; i < sample_set.size(); i++)
	{
		sample_set[i].spin_image.resize(numbins * numbins);
		sample_set[i].var_si.resize(numbins * numbins);
	}

	//float SPIN_DISTANCE_SUPPORT = mesh->bsphere.r * 2.0f;

	//// initializations of spin image bins
	Bin2D** spin = new Bin2D*[ numbins ];
	for( size_t x = 0; x < SPIN_RESOLUTION; x++ ) 
	{
		spin[x] = new Bin2D[ numbins ];
	}
	float* binWeights = new float[ numbins * numbins ];
	float norm = 1.0f / float( sample_set.size() );

	//std::cout << std::endl << "Computing spin images for mesh " << mesh->filename << std::endl;
	for( size_t i = 0; i < sample_set.size(); i++ ) 
	{
		for( size_t x = 0; x < numbins; x++ ) 
		{
			for( size_t y = 0; y < numbins; y++ ) 
			{
				spin[x][y].reset();
			}
		}

		for (size_t k = 0; k < sample_set.size(); k++) 
		{
			if ( (sample_set[k].normal DOT sample_set[i].normal) < 0.0f )
				continue;

			vec diff = sample_set[k].position - sample_set[i].position;
			float beta = sample_set[i].normal DOT diff;
			float alpha = sqrt( len2(diff) - beta*beta );
			float ic = (SPIN_DISTANCE_SUPPORT/2.0f - beta/2.0f) / SPIN_BIN_SIZE;
			float jc = alpha / SPIN_BIN_SIZE;

			float sumw = 0.0f;
			size_t ii = 0;
			for (size_t x = 0; x < numbins; x++) 
			{
				for (size_t y = 0; y < numbins; y++) 
				{
					float cx = x + .5f;
					float cy = y + .5f;
					float w = 0.0f;
					if ( (fabs(ic - cx) <= 2.5f) && (fabs(jc - cy) <= 2.5f) ) 
					{
						w = exp( -( (ic - cx)*(ic - cx) + (jc - cy)*(jc - cy) ) / .2f );
						if (w < .02f)
							w = 0.0f;
					}
					binWeights[ii] = w;
					ii++;
					sumw += w;
				}
			}

			ii = 0;
			for (size_t x = 0; x < numbins; x++) 
			{
				for (size_t y = 0; y < numbins; y++) 
				{
					spin[x][y].increaseValue( norm * (binWeights[ii] / (sumw+EPSILON))  );
					ii++;
				}
			}
		}

		size_t ii = 0;
		for( size_t x = 0; x < numbins; x++ ) 
		{
			for( size_t y = 0; y < numbins; y++ ) 
			{
				sample_set[i].spin_image[ii] = spin[x][y].value;
				ii++;
			}
		}
	}
	std::cout << 100.0f << "% complete\t\t\t\r";

	for( size_t x = 0; x < numbins; x++ ) 
	{
		delete[] spin[x];
	}
	delete[] spin;
	delete[] binWeights;

	for(size_t i =0; i < sample_set[0].var_si.size(); i++)
	{
		vector<float> si;
		si.clear();
		for(size_t j = 0; j < sample_set.size(); j++)
		{
			si.push_back(sample_set[j].spin_image[i]);
		}
		float var = getfeatureVar(si);
		for(size_t j = 0; j < sample_set.size(); j++)
		{
		  sample_set[j].var_si[i] = var;
		}
	}
}

void Compute_Feature::exportNormalMap()
{
	vector<NamedPoint> points;
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		points.push_back( NamedPoint(  sample_set[i].position[0], sample_set[i].position[1], sample_set[i].position[2], i ) );
	}
	PKDTree stree(points.begin(), points.end());
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		NamedPoint query( sample_set[i].position[0], sample_set[i].position[1], sample_set[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(100);
		// build frame
		vec3 frame_x = sample_set[i].normal;
		vec3 ori(1,0,0);
		vec3 frame_y = frame_x.cross(ori);
		frame_y = normalize(frame_y);
		vec3 frame_z = frame_x.cross(frame_y);
		frame_z =  normalize(frame_z);
		vector<float> proj_y ;
		vector<float> proj_z;
		proj_y.clear();
		proj_z.clear();
		float max_y = -100;
		float min_y = 100;
		float max_z = -100;
		float min_z = 100;
		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			vec3 p = sample_set[k_closest_elems[kn].getIndex()].position - sample_set[i].position;
			float p_y = p DOT frame_y;
			float p_z = p DOT frame_z;
			if(p_y > max_y )
			{
				max_y = p_y;
			}
			if(p_z > max_z )
			{
				max_z = p_z;
			}
			if(p_y < min_y)
			{
				min_y = p_y;
			}
			if(p_z < min_z)
			{
				min_z = p_z;
			}
			proj_y.push_back(p_y);
			proj_z.push_back(p_z);
		}
		vector<float> normal_map;
		float dis_y = (max_y - min_z)/normal_map_res;
		float dis_z =  (max_z - min_z)/normal_map_res;
		normal_map.resize( normal_map_res*normal_map_res, 0);

		for(size_t jj = 0; jj <  proj_y.size(); jj++)
		{
			int p_y = (int)floor( ( proj_y[jj] - min_y )/ dis_y );
			int p_z = (int)floor( (proj_z[jj] - min_z )/ dis_z );
			normal_map[p_y * normal_map_res + p_z]++;
		}
		sample_set[i].sample_features.insert(sample_set[i].sample_features.end(), normal_map.begin(), normal_map.end());
	}
}

void Compute_Feature::exportShapeContex()
{
	size_t numSCfeatures = 0;
	for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
	{
		for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
		{
			for( size_t y = 0; y < NUM_ANGLE_BINS[j]; y++ ) 
			{
				numSCfeatures++;
			}
		}
	}

	for(size_t i = 0; i < sample_set.size(); i++)
	{
		sample_set[i].shape_context.resize(numSCfeatures);
		sample_set[i].angel_geo_dis.resize(NUM_FEATURES_GD);
		sample_set[i].var_sc.resize(numSCfeatures);
	}
	// scs.resize( numSCfeatures );
	// agds.resize( NUM_FEATURES_GD );
	float GEODESIC_FEATURES[ NUM_FEATURES_GD ];

	/*for (size_t j = 0; j < numSCfeatures; j++) 
	{
	scs[j].resize( pointsamples.size() );
	}
	for (size_t j = 0; j < NUM_FEATURES_GD; j++) 
	{
	agds[j].resize( pointsamples.size() );
	}*/

	//// initializations of bins & corresponding features
	Bin2D*** bins = new Bin2D**[ NUM_BINNING_TYPES_GD ];
	for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
	{
		bins[j] = new Bin2D*[ NUM_GD_BINS[j] ];
		for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
		{
			bins[j][x] = new Bin2D[  NUM_ANGLE_BINS[j] ];
		}
	}

	for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
	{
		float s = (float)NUM_GD_BINS[j]+1;
		float D = GD_MAX[j] * normalizationFactor;
		for( size_t x = 0; x < s-1; x++ ) 
		{
			float startx = 0.0f;
			float endx = 0.0f;
			if (GD_LOGP[j] <= 0.0f) 
			{
				startx = D * (float)x/(float)NUM_GD_BINS[j];
				endx = D * (float)(x+1)/(float)NUM_GD_BINS[j];
			} 
			else 
			{
				startx = pow( (-log((s-x)/s) ), GD_LOGP[j] ) * (D / pow( log(s), GD_LOGP[j]) );
				endx = pow( (-log((s-x-1)/s) ), GD_LOGP[j] ) * (D / pow( log(s), GD_LOGP[j]) ); 
			}
			for( size_t y = 0; y < NUM_ANGLE_BINS[j]; y++ ) 
			{
				float starty = MIN_SC_ANGLE + (MAX_SC_ANGLE-MIN_SC_ANGLE) * (float)y/(float)NUM_ANGLE_BINS[j];
				float endy =  MIN_SC_ANGLE + (MAX_SC_ANGLE-MIN_SC_ANGLE) * ((float)y+1)/(float)NUM_ANGLE_BINS[j];
				bins[j][x][y].x1 = startx;
				bins[j][x][y].x2 = endx;
				bins[j][x][y].y1 = starty;
				bins[j][x][y].y2 = endy;
			}
		}
	}
	float norm = 1.0f / float( sample_set.size() );

	//std::cout << std::endl << "Computing geodesic features and shape context for mesh " << mesh->filename << std::endl;
	for( size_t i = 0; i < sample_set.size(); i++ ) 
	{

		for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
		{
			for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
			{
				for( size_t y = 0; y < NUM_ANGLE_BINS[j]; y++ ) 
				{
					bins[j][x][y].reset();
				}
			}
		}

		size_t* adjacentPoints = geodesic_closest_samples[i];
		float* geodDistances = geodesic_distances[i];
		for (size_t k = 0; k < sample_set.size(); k++) 
		{
			float angle = getAngleFromUnitVectors( normalize ((vec3)(sample_set[ adjacentPoints[k] ].position - sample_set[i].position)), (-sample_set[ adjacentPoints[k] ].normal) ) - 90.0f;
			for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
			{
				for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
				{
					for( size_t y = 0; y < NUM_ANGLE_BINS[j]; y++ ) 
					{
						if (bins[j][x][y].contains( geodDistances[k], angle)) 
						{
							bins[j][x][y].increaseValue( norm * (1.0f / ( ( geodDistances[k]/normalizationFactor) + .1f)) );
						}
					}
				}
			}
		}

		for (size_t j = 0; j < NUM_FEATURES_GD; j++) 
		{
			GEODESIC_FEATURES[j] = -0.0f;
		}
		for (size_t k = 0; k < sample_set.size(); k++) 
		{
			GEODESIC_FEATURES[0] += geodDistances[k];
			GEODESIC_FEATURES[1] += geodDistances[k] * geodDistances[k];
			GEODESIC_FEATURES[2] += geodDistances[k] * geodDistances[k] * geodDistances[k] * geodDistances[k];
			GEODESIC_FEATURES[3] += pow( geodDistances[k], 8.0f);
			GEODESIC_FEATURES[4] += pow( geodDistances[k], 0.5f);
			GEODESIC_FEATURES[5] += pow( geodDistances[k], 0.25f );
		}
		for (size_t j = 0; j <= 5; j++) 
		{
			GEODESIC_FEATURES[j] *= norm; 
		}

		for (size_t k = 0; k < sample_set.size(); k++) 
		{
			GEODESIC_FEATURES[6] += ( geodDistances[k] - GEODESIC_FEATURES[0] ) * ( geodDistances[k] - GEODESIC_FEATURES[0] );
		}
		GEODESIC_FEATURES[6] *= norm; 

		for (size_t k = 0; k < sample_set.size(); k++) 
		{
			float gdkm = geodDistances[k] - GEODESIC_FEATURES[0];
			GEODESIC_FEATURES[7] +=  gdkm*gdkm*gdkm;
			GEODESIC_FEATURES[8] +=  gdkm*gdkm*gdkm*gdkm;
		}
		GEODESIC_FEATURES[7] *= norm; 
		GEODESIC_FEATURES[8] *= norm; 
		GEODESIC_FEATURES[7] /= sqrt(GEODESIC_FEATURES[6]*GEODESIC_FEATURES[6]*GEODESIC_FEATURES[6]+EPSILON);
		GEODESIC_FEATURES[8] /= (GEODESIC_FEATURES[6]*GEODESIC_FEATURES[6]+EPSILON);

		for (int k = 0; k < sample_set.size(); k++) 
		{
			if ( float(k) / float(sample_set.size())  >= .1 && GEODESIC_FEATURES[9] == -0.0f) 
			{
				GEODESIC_FEATURES[9] = geodDistances[k];
			}
			if ( float(k) / float(sample_set.size()) >= .2 && GEODESIC_FEATURES[10] == -0.0f) 
			{
				GEODESIC_FEATURES[10] = geodDistances[k];
			}
			if (float(k) / float(sample_set.size()) >= .3 && GEODESIC_FEATURES[11] == -0.0f) 
			{
				GEODESIC_FEATURES[11] = geodDistances[k];
			}
			if (float(k) / float(sample_set.size()) >= .4 && GEODESIC_FEATURES[12] == -0.0f) 
			{
				GEODESIC_FEATURES[12] = geodDistances[k];
			}
			if (float(k) / float(sample_set.size()) >= .5 && GEODESIC_FEATURES[13] == -0.0f) 
			{
				GEODESIC_FEATURES[13] = geodDistances[k];
				break;
			}
		}


		size_t ii = 0;
		for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
		{
			for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
			{
				for( size_t y = 0; y < NUM_ANGLE_BINS[j]; y++ ) 
				{
					sample_set[i].shape_context[ii] = bins[j][x][y].value;
					ii++;
				}
			}
		}
		for (size_t j = 0; j < NUM_FEATURES_GD; j++) 
		{
			sample_set[i].angel_geo_dis[j] = GEODESIC_FEATURES[j];
		}
	} // end of loop over each pointsample i

	for ( size_t j = 0; j < NUM_FEATURES_GD; j++ ) 
	{
		float minValue = FLT_MAX;
		for( size_t i = 0; i < sample_set.size(); i++ ) 
		{
			if ( sample_set[i].angel_geo_dis[j] < minValue  )
				minValue = sample_set[i].angel_geo_dis[j];
		}
		for( size_t i = 0; i < sample_set.size(); i++ ) 
		{
			sample_set[i].angel_geo_dis[j] -= minValue;
		}
	}

	std::cout << 100.0f << "% complete\t\t\t\r";

	for( size_t j = 0; j < NUM_BINNING_TYPES_GD; j++ ) 
	{
		for( size_t x = 0; x < NUM_GD_BINS[j]; x++ ) 
		{
			delete[] bins[j][x];
		}
		delete[] bins[j];
	}
	delete[] bins;

	for(size_t i =0; i < numSCfeatures; i++)
	{
		vector<float> sc;
		sc.clear();
		for(size_t j = 0; j < sample_set.size(); j++)
		{
			sc.push_back(sample_set[j].shape_context[i]);
		}
		float var = getfeatureVar(sc);
		for(size_t j = 0; j < sample_set.size(); j++)
		{
		  sample_set[j].var_sc[i] = var;
		}
	}
}

void Compute_Feature::bulitNear()
{
	near_points.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < sample_set.size(); i++)
	{
		points.push_back( NamedPoint( sample_set[i].position[0], sample_set[i].position[1], sample_set[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	int  k = 6;
	for(size_t j = 0; j < sample_set.size() ; j++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query( sample_set[j].position[0], sample_set[j].position[1], sample_set[j].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind < k; ind++)
		{
			near.push_back(stree.getElements()[k_closest_elems[ind].getIndex()].id);
		}
		near_points.push_back(near);
	}
}


void Compute_Feature::computeGeodesicDistances()
{
	ProximityGraph *meshgraph = new ProximityGraph( sample_set.size() );
	geodesic_distances = new float*[ sample_set.size() ];
	geodesic_closest_samples = new size_t*[ sample_set.size() ];
	for (size_t i = 0; i < sample_set.size(); i++) 
	{
		geodesic_distances[i] = new float[ sample_set.size() ];
		geodesic_closest_samples[i] = new size_t[ sample_set.size() ];
		for (size_t j = 1; j < near_points[i].size(); j++) 
		{
			add_edge(i, near_points[i][j], dist(sample_set[i].position, sample_set[near_points[i][j]].position), *meshgraph);
		}
	}
	std::cout << "Created graph of " << sample_set.size() << " points" << std::endl;

	boost::johnson_all_pairs_shortest_paths(*meshgraph, geodesic_distances);
	delete meshgraph;
	std::cout << "Geodesic distances are computed... ";

	std::vector<float> geodesic_distances_i( sample_set.size() );
	for (size_t i = 0; i < sample_set.size(); i++) 
	{
		for (size_t j = 0; j < sample_set.size(); j++) 
		{
			geodesic_distances_i[j] = geodesic_distances[i][j];
		}
		sortArrayIndices(geodesic_distances[i], sample_set.size(), geodesic_closest_samples[i] );
		for (size_t j = 0; j < sample_set.size(); j++) 
		{
			geodesic_distances[i][j] = geodesic_distances_i[ geodesic_closest_samples[i][j] ];
		}
	}
	geodesic_distances_i.clear();

	std::cout << "and sorted." << std::endl;
}

void Compute_Feature::getClosestSamples(vector<size_t>& closestSamples, vector<float>& closestDistances,  size_t c, float maxDistance, size_t minNumPoints, float normalThreshold) 
{
	for (size_t i = 1; i < sample_set.size(); i++) 
	{
		if ( closestSamples.size() <= minNumPoints ) 
		{
			if ( ( sample_set[ geodesic_closest_samples[c][i] ].normal DOT sample_set[c].normal ) > normalThreshold ) 
			{
				closestSamples.push_back( geodesic_closest_samples[c][i] );
				closestDistances.push_back( geodesic_distances[c][i] );
			}      
		} 
		else 
		{
			if ( geodesic_distances[c][i] > maxDistance )
				break;
			if ( ( sample_set[ geodesic_closest_samples[c][i] ].normal DOT sample_set[c].normal ) > normalThreshold ) 
			{
				closestSamples.push_back( geodesic_closest_samples[c][i] );
				closestDistances.push_back( geodesic_distances[c][i] );
			}   
		}
	}
}

void Compute_Feature::exportCurvature()
{
	/*curvatures.resize( NUM_CURVATURE_FEATURES_PER_SCALE*NUM_SCALES );
	for (size_t j = 0; j < NUM_CURVATURE_FEATURES_PER_SCALE*NUM_SCALES; j++) 
	{
	curvatures[j].resize( pointsamples.size() );
	}*/
	for(size_t i = 0; i < sample_set.size(); i++)
	{
		sample_set[i].curvature.clear();
		sample_set[i].curvature.resize( NUM_CURVATURE_FEATURES_PER_SCALE);
		sample_set[i].var_cur.resize( NUM_CURVATURE_FEATURES_PER_SCALE);
	}
	vector<size_t> adjacentPoints;
	vector<float> geodDistances;
	adjacentPoints.reserve( sample_set.size() );
	geodDistances.reserve( sample_set.size() );
	for( size_t i = 0; i < sample_set.size(); i++ ) 
	{
		adjacentPoints.clear();
		geodDistances.clear();
		getClosestSamples( adjacentPoints, geodDistances, i, 0.15, 3, 0.0f );
		vec3 n = sample_set[i].normal;
		vec3 t = ( sample_set[i].position - sample_set[ adjacentPoints[0] ].position ) CROSS n;
		t =  normalize(t);
		vec3 s = t CROSS n;
		double C[9] = {t[0], t[1], t[2], s[0], s[1], s[2], n[0], n[1], n[2]};
		char NORM = '1';
		integer M = (integer)adjacentPoints.size() * 3;  // number of rows (data points+normals)
		integer N = 3; // number of unknowns, change to 7 for cubic fit and uncomment the corresponding lines
		integer NRHS = 1;
		integer JPVT[3] = {0, 0, 0};
		integer RANK;
		integer LWORK = 3 * M * N;
		double *WORK = new double[ LWORK ];
		double *B = new double[ M ];
		double *A = new double[ M*N ];
		integer INFO;

		for( int j = 0; j < adjacentPoints.size(); j++ )  // adjacent face 0 is the source face i
		{ 
			vec diff = sample_set[i].position - sample_set[ adjacentPoints[j] ].position;
			double x = C[0] * diff[0] + C[1] * diff[1] + C[2] * diff[2];
			double y = C[3] * diff[0] + C[4] * diff[1] + C[5] * diff[2];
			double z = C[6] * diff[0] + C[7] * diff[1] + C[8] * diff[2];
			double norm = 1.0f / float( sample_set.size() );
			double xn = C[0] * sample_set[ adjacentPoints[j] ].normal[0] + C[1] * sample_set[ adjacentPoints[j] ].normal[1] + C[2] * sample_set[ adjacentPoints[j] ].normal[2];
			double yn = C[3] * sample_set[ adjacentPoints[j] ].normal[0] + C[4] * sample_set[ adjacentPoints[j] ].normal[1] + C[5] * sample_set[ adjacentPoints[j] ].normal[2];
			double zn = C[6] * sample_set[ adjacentPoints[j] ].normal[0] + C[7] * sample_set[ adjacentPoints[j] ].normal[1] + C[8] * sample_set[ adjacentPoints[j] ].normal[2];
			double u = -xn / (zn+EPSILON);
			double v = -yn / (zn+EPSILON);
			//std::cout << std::endl << x << ' ' << y << ' ' << z << std::endl;
			//std::cout << std::endl << adjacentFaces[j] << std::endl;

			A[      3*j   ] = 0.5f * x*x * norm;
			A[  M + 3*j   ] =        x*y * norm;
			A[2*M + 3*j   ] = 0.5f * y*y * norm;
			//A[3*M + 3*j   ] =      x*x*x * norm;
			//A[4*M + 3*j   ] =		 x*x*y * norm;
			//A[5*M + 3*j   ] =      x*y*y * norm;
			//A[6*M + 3*j   ] =      y*y*y * norm;
			B[      3*j	] = z * norm;

			A[      3*j+1 ] =          x * norm;
			A[  M + 3*j+1 ] =          y * norm;
			A[2*M + 3*j+1 ] = 0;
			//A[3*M + 3*j+1 ] = 3.0f * x*x * norm;
			//A[4*M + 3*j+1 ] =	2.0f * x*y * norm;
			//A[5*M + 3*j+1 ] =        y*y * norm;
			//A[6*M + 3*j+1 ] = 0;
			B[      3*j+1 ] = u * norm;

			A[      3*j+2 ] = 0;
			A[  M + 3*j+2 ] =          x * norm;
			A[2*M + 3*j+2 ] =          y * norm;
			//A[3*M + 3*j+2 ] = 0;
			//A[4*M + 3*j+2 ] =	       x*x * norm;
			//A[5*M + 3*j+2 ] = 2.0f * x*y * norm;
			//A[6*M + 3*j+2 ] = 3.0f * y*y * norm;
			B[      3*j+2 ] = v * norm;
		}
		double RCOND = dlange_( &NORM, &M, &N, A, &M, WORK );
		dgelsy_( &M, &N, &NRHS, A, &M, B, &M, JPVT, &RCOND, &RANK, WORK, &LWORK, &INFO );
		double trace = B[0] + B[2];
		double det = B[0] * B[2] - B[1] * B[1];
		double k1 = .5f * ( trace + sqrt( trace*trace - 4.0f * det ) );
		double k2 = .5f * ( trace - sqrt( trace*trace - 4.0f * det ) );
		delete[] A;
		delete[] B;
		delete[] WORK;
		sample_set[i].curvature[0] = (float)k1;
		sample_set[i].curvature[1] = (float)k2;
		sample_set[i].curvature[2] = (float)k1 - (float)k2;
		if ( fabs(k1) < fabs(k2) ) 
		{
			std::swap( k1, k2 );
		}
		sample_set[i].curvature[3] = (float)k1;
		sample_set[i].curvature[4] = (float)k2;
		sample_set[i].curvature[5] = (float)k1 - (float)k2;
		sample_set[i].curvature[6] = (float)(k1+k2)/2;
		sample_set[i].curvature[7] = (float)k1 *(float)k2;
		for (int j = 0; j < 8; j++)  			// don't forget to change this as well, if you change the features
		{
			sample_set[i].curvature[8+j] = fabs( sample_set[i].curvature[j] );
		}
	}

	for(size_t i =0; i <  NUM_CURVATURE_FEATURES_PER_SCALE; i++)
	{
		vector<float> cur;
		cur.clear();
		for(size_t j = 0; j < sample_set.size(); j++)
		{
			cur.push_back(sample_set[j].curvature[i]);
		}
		float var = getfeatureVar(cur);
		for(size_t j = 0; j < sample_set.size(); j++)
		{
		  sample_set[j].var_cur[i] = var;
		}
	}
}

void Compute_Feature::exportPCAFeaturesPerPoint()
{
	//pcadata.resize(NUM_PCA_FEATURES_PER_SCALE * NUM_SCALES);
	//for (int j = 0; j < NUM_PCA_FEATURES_PER_SCALE * NUM_SCALES; j++) 
	//{
		//pcadata[j].resize( pointsamples.size() );
	//
	for(size_t i = 0; i < sample_set.size(); i++)
	{
		sample_set[i].sample_pca.resize(NUM_PCA_FEATURES_PER_SCALE * NUM_SCALES);
	}

	char JOBZ = 'N';
	char UPLO = 'L';
	integer N = 3; 
	double EIG[3]; // eigenvalues in ascending order
	double WORK[5 * 8];
	integer LWORK = 5 * 8;
	integer INFO;

	vector<size_t> adjacentPoints;
	vector<float> geodDistances;
	adjacentPoints.reserve( sample_set.size() );
	geodDistances.reserve( sample_set.size() );

	for (int scale = 0; scale < NUM_SCALES; scale++) 
	{
		//std::cout << std::endl << "Computing pca eigenvalues at scale " << scale << " (" << SCALES[scale] * 4.0f << ") for mesh " << mesh->filename << std::endl;

		for( size_t i = 0; i < sample_set.size(); i++ ) 
		{
			adjacentPoints.clear();
			geodDistances.clear();
			getClosestSamples( adjacentPoints, geodDistances, i, SCALES[scale] * 4.0f, 12,0.0f);

			double *V = new double[ adjacentPoints.size() * 3 ];
			float M[3] = {0.0f, 0.0f, 0.0f};
			for (size_t j = 0; j < adjacentPoints.size(); j++) 
			{
				float x = sample_set[adjacentPoints[j]].position[0];
				float y = sample_set[adjacentPoints[j]].position[1];
				float z = sample_set[adjacentPoints[j]].position[2];
				M[ 0 ] += x;
				M[ 1 ] += y;
				M[ 2 ] += z;
			}
			M[0] /= float( adjacentPoints.size() );
			M[1] /= float( adjacentPoints.size() );
			M[2] /= float( adjacentPoints.size() );

			for (size_t j = 0; j < adjacentPoints.size(); j++) 
			{
				float x = (sample_set[adjacentPoints[j]].position[0] - M[0]); // sqrt( float( adjacentPoints.size() ) );
				float y = (sample_set[adjacentPoints[j]].position[1] - M[1]); // sqrt( float( adjacentPoints.size() ) );
				float z = (sample_set[adjacentPoints[j]].position[2] - M[2]); // sqrt( float( adjacentPoints.size() ) );
				V[ j * 3 ] = x;
				V[ 1 + j * 3 ] = y;
				V[ 2 + j * 3 ] = z;
			}

			double* COV = covar(V, adjacentPoints.size());
			for (int j = 0; j < 9; j++) 
			{
				COV[j] /= float( adjacentPoints.size() );
			}
			dsyev_( &JOBZ, &UPLO, &N, COV, &N, EIG, WORK, &LWORK, &INFO );
			if (INFO != 0) 
			{
				std::cerr << std::endl << "Point " << i << "possibly did not acquire right pca vales during dsyev_ call! INFO = " << INFO << std::endl;
			}
			EIG[0] = sqrt( max<double>(EIG[0], 0.0f) );
			EIG[1] = sqrt( max<double>(EIG[1], 0.0f) );
			EIG[2] = sqrt( max<double>(EIG[2], 0.0f) );
			float sumEIG = 1.0f; //EIG[0] + EIG[1] + EIG[2] + EPSILON;

			sample_set[i].sample_pca[0 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[0] / sumEIG;
			sample_set[i].sample_pca[1 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[1] / sumEIG;
			sample_set[i].sample_pca[2 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[2] / sumEIG;
			sample_set[i].sample_pca[3 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)(EIG[0]+EIG[1]) / sumEIG;
			sample_set[i].sample_pca[4 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)(EIG[0]+EIG[2]) / sumEIG;
			sample_set[i].sample_pca[5 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)(EIG[1]+EIG[2]) / sumEIG;
			//			pcadata[6][i] = EIG[0] + EIG[1] + EIG[2];
			sample_set[i].sample_pca[6 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[0]/(float)(EIG[1]+EPSILON);
			sample_set[i].sample_pca[7 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[0]/(float)(EIG[2]+EPSILON);
			sample_set[i].sample_pca[8 + scale*NUM_PCA_FEATURES_PER_SCALE] = (float)EIG[1]/(float)(EIG[2]+EPSILON);
			sample_set[i].sample_pca[9 + scale*NUM_PCA_FEATURES_PER_SCALE] =  sample_set[i].sample_pca[6 + scale*NUM_PCA_FEATURES_PER_SCALE]+sample_set[i].sample_pca[7 + scale*NUM_PCA_FEATURES_PER_SCALE];
			sample_set[i].sample_pca[10 + scale*NUM_PCA_FEATURES_PER_SCALE] = sample_set[i].sample_pca[6 + scale*NUM_PCA_FEATURES_PER_SCALE]+sample_set[i].sample_pca[8 + scale*NUM_PCA_FEATURES_PER_SCALE];
			sample_set[i].sample_pca[11 + scale*NUM_PCA_FEATURES_PER_SCALE] = sample_set[i].sample_pca[7 + scale*NUM_PCA_FEATURES_PER_SCALE]+sample_set[i].sample_pca[8 + scale*NUM_PCA_FEATURES_PER_SCALE];

			delete[] V;
			delete[] COV;
		}

		
		//for (int j = 0; j < NUM_PCA_FEATURES_PER_SCALE; j++) 
		//{
			//for(size_t i = 0; i < sample_set.size(); i++)
			//{
			  // sample_set[i].sample_pca[j + scale*NUM_PCA_FEATURES_PER_SCALE] = removePositiveOutliers( sample_set[i].sample_pca[j + scale*NUM_PCA_FEATURES_PER_SCALE], .95f );
			//}
		//}

		std::cout << 100.0f << "% complete\t\t\t\r";
  }
}

vector<Sample> Compute_Feature::GetFeaturedSample(int type)
{
	if (type == 0)
	{
		exportPCA();
		//exportShapeContexNew();
		//bulitNear();
		//exportDifferent();
	}
	else
	{
		cout << "begin finding near " << endl;
		bulitNear();
		cout << "begin get GeodesicDistances" << endl;
		computeGeodesicDistances();
		//cout << "begin get Curvature" << endl;
		//exportCurvature();
		cout << "begin get PCA" << endl;
		exportPCA();
		cout << "begin get shape context " << endl;
		exportShapeContex();
		//exportDifferent();
		//exportPCA();
	}
	//cout <<"begin get spin image " << endl;
	//exportSpinImage();
	//cout <<"begin get exportPCAFeaturesPerPoint " << endl;
	//exportPCAFeaturesPerPoint();
	return sample_set;
}

float Compute_Feature::getfeatureVar(vector<float> feature)
{
	float mean = 0;
	for(size_t i = 0; i < feature.size(); i++)
	{
		mean += feature[i];
	}
	mean /= feature.size();
	float var = 0;
	for(size_t i = 0; i < feature.size(); i++)
	{
		var += (feature[i] - mean) * (feature[i] - mean);
	}
	var /= feature.size();
	return var;
}