#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include"DeformFromShape.h"
#include"Similarity_Marix.h"
#include"CheckFeature.h"

using namespace std;



int main2(int argc, char* argv[])
{
	CheckFeature test;
	test.LoadFeature(test.t_sample,argv[1]);
	test.OutPutFeature(argv[2],argv[3]);
	test.LoadFeature(test.s_sample,argv[4]);
	test.CheckDiff();
	return 0;
}

int main7(int argc, char* argv[])
{

	DeformFromShape test;
	test.LoadTargetSampleWithPreSeg(argv[1],argv[2]);
	test.outPutSampleFeature(argv[3]);
	return 0;
}

int main9(int argc, char* argv[])
{

	DeformFromShape test;
	test.SetValidGroup(argv[1]);
	//test.GetSampleFromMatching(argv[2]);
	test.GetSampleFromBaseShapesWithMesh(argv[2],argv[3]);
	//test.GetTargetSample(argv[4]);
	test.LoadTargetSampleWithPreSeg(argv[4],argv[7]);
	test.SetColor();
	test.ScaleSample();
	test.BuiltShapeConnection();
	test.Deformation_With_Seg();
	test.OutPutAndVisual(argv[5],argv[6]);
	return 0;
}

int main33(int argc, char* argv[])
{
	Similarity_Marix test;
	test.RunInPairs(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8]);
	return 0;
}

int main111(int argc, char* argv[])
{
	Similarity_Marix test;
	//test.GetMeanShapes(argv[1]);
	//test.LoadMesh(argv[2]);
	//test.OutPutMatrixWithMean();
	//test.LoadMesh(argv[1]);
	test.laodSamplePoint(argv[1]);
	test.OutPutMatrixWithSize(stoi(argv[2]));
}


int main55(int argc, char* argv[])
{
	Shape test;
	test.GetShape(argv[1]);
	test.GetSamplePoint(std::stoi(argv[2]));
	//test.SaveSampleSDF(argv[2]);
	test.OutPutSampleAndFeature(argv[3],argv[4],argv[5]);
	return 0;
}

int main(int argc, char* argv[])
{
	SegMeshFace seg;
	seg.LoadData(argv[1],argv[2]);
	seg.SegFace();
	seg.SetSmoothWeight(std::stof(argv[3]));
	seg.GraphCut_new();
	seg.OutPutSeg(argv[4]);
	seg.OutPutSegFile(argv[5]);
	return 0;
}