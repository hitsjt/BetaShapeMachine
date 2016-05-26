#include "TestSNL.hpp"
#include "../Plugins/S12/S12_Common.hpp"
#include "../Plugins/S12/S12_ShapeBNet.hpp"
#include "../Plugins/S12/S12_ShapeBNetNode.hpp"

using namespace S12;



//////////////// TESTING FUNCTIONS ///////////////////
//
//void testFactorOperations()
//{
//  RootNode a;
//  a.domain_size = 2;
//  a.initialize();
//  a.cpt.resize(2);
//  a.cpt[0] = 0.8;
//  a.cpt[1] = 0.2;
//  a.name = "r";
//  RootNode b;
//  b.name = "s";
//  b.domain_size = 2;
//  b.parents.push_back((SNL::Node*)&a);
//  b.initialize();
//  for (size_t i = 0; i < b.cpt.size(); i++)
//  {
//    vector<size_t> values;
//    size_t d = b.getValues(i, values);
//    if (d == 0 && values[0] == 0)
//      b.cpt[i] = 0.5;
//    else if (d == 1 && values[0] == 0)
//      b.cpt[i] = 0.2;
//    else if (d == 0 && values[0] == 1)
//      b.cpt[i] = 0.3;
//    else if (d == 1 && values[0] == 1)
//      b.cpt[i] = 0;
//  }
//  a.getFactor();
//  b.getFactor();
//  std::cout << a.factor;
//  std::cout << b.factor;
//  vector<Factor*> factors_to_multiply;
//  factors_to_multiply.push_back(&a.factor);
//  factors_to_multiply.push_back(&b.factor);
//  Factor f = Factor::multiply(factors_to_multiply);
//  for (size_t i = 0; i < f.b.size(); i++)
//  {
//    vector<size_t> values = f.getValues(i);
//    std::cout << f.bdnodes[0]->getName() << " " << f.bdnodes[1]->getName() << std::endl;
//    std::cout << values << " " << f.b[i] << std::endl;
//  }
//
//  vector< Node* > marg;
//  marg.push_back(&a);
//  Factor fm = Factor::marginalize( &f, marg );
//  for (size_t i = 0; i < fm.b.size(); i++)
//  {
//    vector<size_t> values = fm.getValues(i);
//    std::cout << fm.bdnodes[0]->getName() << std::endl;
//    std::cout << values << " " << fm.b[i] << std::endl;
//  }
//
//}


/////////////////////////////////////////////



bool
	testS12(int argc, char * argv[])
{
	// Get the path containing the executable
	string bin_path = parent(argv[0]);

	// Try to load the S12 plugin from the same parent directory as the executable
#ifdef _MSC_VER
#if !defined(NDEBUG) || defined(_DEBUG)
	string plugin_path = bin_path + "\\..\\Debug\\SNLPluginS12d";
#else
	string plugin_path = bin_path +  "\\..\\Release\\SNLPluginS12";
#endif
#else
#if !defined(NDEBUG) || defined(_DEBUG)
	string plugin_path = getFullPath(bin_path, "SNLPluginS12d");
#else
	string plugin_path = getFullPath(bin_path, "SNLPluginS12");
#endif
#endif

	cout << "Loading plugin: " << plugin_path << endl;
	SNL::Plugin * s12_plugin = SNL::PluginManager::load(plugin_path);

	// Start up the plugin
	s12_plugin->startup();

	// We should now have a S12 network factory
	SNL::NetworkFactory * factory = SNL::NetworkManager::getFactory("S12");

	// Create a network
	SNL::Network * nw = factory->createNetwork("My S12 Network");


	//==========================================================================================================================
	// TESTS BEGIN
	//==========================================================================================================================

	//testFactorOperations();
	//return 0;

	vector<Label*> __labels;
	vector<MeshPart*> __parts;
	vector<Mesh*> __meshes;

	//string input_path = "Tables/V/";
	string input_path = "C:/Users/V/Desktop/ModelingHighLevelAttrib/Data/Domains/Web/V/";
	//string input_path = "/home/sidch/LocalExploration/Data/Domains/Airplanes/V/";

	string meshFileListName = input_path + "meshlist.txt";
	ifstream meshFileListFile(meshFileListName.c_str());
	if (!meshFileListFile.good())
	{
		std::cerr << "fatal error reading mesh file list " << meshFileListName << std::endl;
		exit(-1);
	}
	size_t i = 0;
	while ( meshFileListFile.good() )
	{
		string inputFileName;
		meshFileListFile >> inputFileName;
		if ( !meshFileListFile.good() )
			break;
		string currentObjFilename = input_path + inputFileName;
		TriMesh* mesh = TriMesh::read(currentObjFilename.c_str(), i);
		if (mesh == NULL || mesh->parts.empty() )
		{
			std::cout << "Mesh is null or has 0 faces / 0 parts! Skipping this mesh..." << std::endl;
			continue;
		}
		i++;
		__meshes.push_back(mesh);

		for (size_t p = 0; p < mesh->parts.size(); p++ )
		{
			bool found_label = false;
			for (size_t l = 0; l < __labels.size(); l++)
			{
				if (mesh->parts[p]->label == __labels[l]->name)
				{
					MeshPart *part = new MeshPart(__labels[l], mesh, mesh->parts[p], __parts.size());
					__labels[l]->parts.push_back( part );
					__parts.push_back( part );
					found_label = true;
					break;
				}
			}
			if (!found_label)
			{
				Label *label = new Label(mesh->parts[p]->label, __labels.size() );
				__labels.push_back(label);
				MeshPart *part = new MeshPart(label, mesh, mesh->parts[p], __parts.size());
				label->parts.push_back( part );
				__parts.push_back( part );
			}
		}
	}
	meshFileListFile.close();

	string data_path = input_path;
	for (size_t l = 0; l < __labels.size(); l++)
	{
		if (!__labels[l]->load_data((char*)data_path.c_str(), __parts, __labels))
			std::cout << "Could not load labels file. Probably you changed the meshlist.txt file while switching from data extraction to learning mode." << std::endl;
	}
	for (size_t p = 0; p < __parts.size(); p++)
	{
		if (!__parts[p]->load_data((char*)data_path.c_str(), __parts, true))
			std::cout << "Could not load parts file. Probably you changed the meshlist.txt file while switching from data extraction to learning mode." << std::endl;
	}


	///////////////////////////////////////////////////////////////
	// Step 2: Learning
	//////////////////////////////////////////////////////////////

	// Sid use the following to train, convert to strings if you want.
	ShapeBNet* bnet = (ShapeBNet*)nw;
	//bnet->options.set("learn_tree_only", 0);
	bnet->setTrainingData(__labels, __parts, __meshes);
	//bnet->train();
	//bnet->save("webpages.full.bnet");

	bnet->load("webpages.full.bnet");

	bnet->init();
	boost::timer t;

	ofstream ff("shape_styles_mesh_to_ids.txt");
	for (size_t m = 0; m < __meshes.size(); m++)
		ff << __meshes[m]->filename << " " << bnet->root_node->style_id[m] << std::endl;
	ff.close();

	// size_t trylabel = 0;
	// for ( size_t p = 0; p < __parts.size(); p++)
	// {
	//  if ( __parts[p]->sublabel_id == 1 && __parts[p]->label->id ==  trylabel && !__parts[p]->features.empty() )
	//    bnet->gaussian_nodes[trylabel]->observation = __parts[p]->features;
	// }
	//bnet->setObservation( bnet->cardinality_nodes[7], 2 );
	//bnet->setObservation( bnet->cardinality_nodes[8], 2 );
	//bnet->setObservation( bnet->cardinality_nodes[1], 1 );
	//bnet->setObservation( bnet->layout_nodes[0], 1 );

	bnet->doInference();

	vector< double > root_probabilities( bnet->root_node->domain_size, 0.0 );
	vector< double > label_probabilities( __labels.size(), 0.0 );
	vector< double > non_label_probabilities( __labels.size(), 0.0 );
	for (size_t l = 0; l < __labels.size(); l++)
	{
		std::cout << __labels[l]->name << std::endl;
		Factor factor = bnet->query(l, true);

		size_t root_node_pos = factor.getVariablePosition(bnet->root_node);
		size_t cardinality_node_pos = factor.getVariablePosition(bnet->cardinality_nodes[l]);
		size_t exists_node_pos = factor.getVariablePosition(bnet->cardinality_nodes[l]->e);
		size_t layout_node_pos = factor.getVariablePosition(bnet->layout_nodes[l]);

		for (size_t i = 0; i < factor.b.size(); i++)
		{
			vector<size_t> values = factor.getValues(i);
			root_probabilities[ values[  root_node_pos ] ] += factor.b[i];

			//bool entry_good_to_sum = (values[ layout_node_pos ] > 0) & (values[ exists_node_pos ] == 1) & (bnet->cardinality_nodes[l]->values[ values[ cardinality_node_pos ] ] > 0); // style >0 exists
			bool entry_good_to_sum = (values[ layout_node_pos ] > 0);
			if ( entry_good_to_sum )
				label_probabilities[ l ] += factor.b[i];
			else
				non_label_probabilities[ l ] += factor.b[i];
		}
	}
	selfdiv( root_probabilities, (double)__labels.size() );
	std::cout << "***Time: " << t.elapsed() << std::endl;
	std::cout << root_probabilities << std::endl;
	for (size_t l = 0; l < __labels.size(); l++)
	{
		std::cout << __labels[l]->id << " " << __labels[l]->name << " " << label_probabilities[l] << " " << non_label_probabilities[l] << std::endl;
	}

	/*
	std::cout << __parts[349]->id << " " << __parts[349]->label->name << std::endl;
	std::cout << __parts[8]->id << " " << __parts[8]->label->name << std::endl;
	std::cout << __parts[380]->id << " " << __parts[380]->label->name << std::endl;
	std::cout << __parts[353]->id << " " << __parts[353]->label->name << std::endl;
	std::cout << __parts[355]->id << " " << __parts[355]->label->name << std::endl;
	std::cout << __parts[367]->id << " " << __parts[367]->label->name << std::endl;
	std::cout << __parts[280]->id << " " << __parts[280]->label->name << std::endl;
	std::cout << __parts[386]->id << " " << __parts[386]->label->name << std::endl;
	std::cout << __parts[249]->id << " " << __parts[249]->label->name << std::endl;
	std::cout << __parts[9]->id << " " << __parts[9]->label->name << std::endl;
	std::cout << __parts[373]->id << " " << __parts[373]->label->name << std::endl;*/

	//   std::cout << __parts[607]->id << " " << __parts[607]->label->name << std::endl;
	//   std::cout << __parts[6]->id << " " << __parts[6]->label->name << std::endl;
	//   std::cout << __parts[861]->id << " " << __parts[861]->label->name << std::endl;
	//   std::cout << __parts[723]->id << " " << __parts[723]->label->name << std::endl;
	//   std::cout << __parts[360]->id << " " << __parts[360]->label->name << std::endl;
	//   std::cout << __parts[705]->id << " " << __parts[705]->label->name << std::endl;
	//   std::cout << __parts[496]->id << " " << __parts[496]->label->name << std::endl;
	//   std::cout << __parts[319]->id << " " << __parts[319]->label->name << std::endl;
	//   std::cout << __parts[347]->id << " " << __parts[347]->label->name << std::endl;
	//   std::cout << __parts[862]->id << " " << __parts[862]->label->name << std::endl;
	//   std::cout << __parts[58]->id << " " << __parts[58]->label->name << std::endl;
	//   std::cout << __parts[54]->id << " " << __parts[54]->label->name << std::endl;
	//   std::cout << __parts[76]->id << " " << __parts[76]->label->name << std::endl;
	//   std::cout << __parts[630]->id << " " << __parts[630]->label->name << std::endl;
	//   std::cout << __parts[378]->id << " " << __parts[378]->label->name << std::endl;
	//   std::cout << __parts[588]->id << " " << __parts[588]->label->name << std::endl;
	//   


	/*  for (size_t l = 0; l < __labels.size(); l++)
	{
	string newpath = "animals_renders";
	mkdir(newpath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	newpath += "/" + __labels[l]->name;
	mkdir( newpath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	for ( size_t p = 0; p < __labels[l]->parts.size(); p++)
	{
	char command[4096];
	sprintf(command, "cp /home/v/LocalExploration/Data/Domains/Animals/Parts/Thumbnails/%d.png %s/",  (int)__labels[l]->parts[p]->id, newpath.c_str() );
	system(command);
	}
	}*/    

	//   for (size_t l = 0; l < __labels.size(); l++)
	//   {
	//     string newpath = "airplanes_renders";
	//     mkdir(newpath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	//     newpath += "/" + __labels[l]->name;
	//     mkdir( newpath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	//     for ( size_t p = 0; p < __labels[l]->parts.size(); p++)
	//     {
	//       char command[4096];
	//       sprintf(command, "cp /home/v/LocalExploration/Data/Domains/Airplanes/Parts/Thumbnails/%d.png %s/",  (int)__labels[l]->parts[p]->id, newpath.c_str() );
	//       system(command);
	//     }
	//   }
	//   
	//   std::cout << __parts[607]->id << " " << __parts[607]->label->name << std::endl;
	//   std::cout << __parts[6]->id << " " << __parts[6]->label->name << std::endl;
	//   std::cout << __parts[861]->id << " " << __parts[861]->label->name << std::endl;
	//   std::cout << __parts[723]->id << " " << __parts[723]->label->name << std::endl;
	//   std::cout << __parts[360]->id << " " << __parts[360]->label->name << std::endl;
	//   std::cout << __parts[705]->id << " " << __parts[705]->label->name << std::endl;
	//   std::cout << __parts[496]->id << " " << __parts[496]->label->name << std::endl;
	//   std::cout << __parts[319]->id << " " << __parts[319]->label->name << std::endl;
	//   std::cout << __parts[347]->id << " " << __parts[347]->label->name << std::endl;
	//   std::cout << __parts[862]->id << " " << __parts[862]->label->name << std::endl;
	//   std::cout << __parts[58]->id << " " << __parts[58]->label->name << std::endl;
	//   std::cout << __parts[54]->id << " " << __parts[54]->label->name << std::endl;
	//   std::cout << __parts[76]->id << " " << __parts[76]->label->name << std::endl;
	//   std::cout << __parts[630]->id << " " << __parts[630]->label->name << std::endl;
	//   std::cout << __parts[378]->id << " " << __parts[378]->label->name << std::endl;
	//   std::cout << __parts[588]->id << " " << __parts[588]->label->name << std::endl;
	//   
	//   

	for (size_t l = 0; l < __labels.size(); l++)
	{
		char filename[4096];
		sprintf(filename, "L_s_%d.txt", l);
		ofstream f( filename );
		f << l << std::endl;
		f << __labels[l]->name << std::endl;
		f << __labels[l]->parts.size() << std::endl;

		int domain_size = bnet->root_node->domain_size * bnet->layout_nodes[l]->domain_size;

		for (size_t p = 0; p < __labels[l]->parts.size(); p++ )
		{
			f << __labels[l]->parts[p]->id << " " << domain_size;
			for (size_t d = 0 ; d < bnet->root_node->domain_size; d++)
			{
				for (size_t d2 = 0 ; d2 < bnet->layout_nodes[l]->domain_size; d2++)
				{
					f << " " << bnet->layout_nodes[l]->Plr[ __labels[l]->parts[p]->mesh->id ][d2][d];
				}
			}
			f << std::endl;
		}
	}



	for (size_t l = 0; l < __labels.size(); l++)
	{
		for (size_t p = 0; p < __labels[l]->parts.size(); p++ )
		{
			delete __labels[l]->parts[p]->trimesh_part;
			delete __labels[l]->parts[p];
		}
		delete __labels[l];
	}
	for (size_t m = 0; m < __meshes.size(); m++)
	{
		delete __meshes[m];
	}

	// Destroy the network
	factory->destroyNetwork(nw);

	// Cleanup and quit
	s12_plugin->shutdown();

	return true;
}


/*
/ /////////////////////////////////
// OLD  TESTS


//==========================================================================================================================
// TESTS BEGIN
//==========================================================================================================================

// SID, SET INPUT PATH.
//const char *input_path = "Tables/";
const char *input_path = "../../../../../Data/Domains/myAirplanes/";
//const char *input_path = "../../../../../Data/Domains/myAnimals/";
//const char *input_path = "../../../../../Data/Domains/myAnimals/";


// SID, IT NEEDS THE MESHLIST.TXT here, meshes must be the same order with the order used to extracted the metadata.
// Meshes and meshlist.txt should be in the <Domain> folder. In Domain/Metadata, the metadata should exist.
// You can modify this code, making sure that Part, Label, and Mesh metadata have the correct info.
char currentObjFilename[4096];
vector<Label*> labels;
vector<MeshPart*> parts;
vector<Mesh*> meshes;

char meshFileListName[4096];
strcpy(meshFileListName, input_path);
strcat(meshFileListName, "meshlist.txt");
ifstream meshFileListFile(meshFileListName);
if (!meshFileListFile.good())
{
std::cerr << "fatal error reading mesh file list " << meshFileListName << std::endl;
return -1;
}

size_t i = 0;
while ( meshFileListFile.good() )
{
char inputFileName[4096];
meshFileListFile >> inputFileName;
if ( !meshFileListFile.good() )
break;
strcpy(currentObjFilename, input_path);
strcat(currentObjFilename, inputFileName);

TriMesh* mesh = TriMesh::read(currentObjFilename, i);
if (mesh == NULL || mesh->faces.empty() || mesh->parts.empty() )
{
std::cout << "Mesh is null or has 0 faces / 0 parts! Skipping this mesh..." << std::endl;
continue;
}
i++;
meshes.push_back(mesh);

for (size_t p = 0; p < mesh->parts.size(); p++ )
{
bool found_label = false;
for (size_t l = 0; l < labels.size(); l++)
{
if (mesh->parts[p]->label == labels[l]->name)
{
MeshPart *part = new MeshPart(labels[l], mesh, mesh->parts[p], parts.size());
labels[l]->parts.push_back( part );
parts.push_back( part );
found_label = true;
break;
}
}
if (!found_label)
{
Label *label = new Label(mesh->parts[p]->label, labels.size() );
labels.push_back(label);
MeshPart *part = new MeshPart(label, mesh, mesh->parts[p], parts.size());
label->parts.push_back( part );
parts.push_back( part );
}
}
}
meshFileListFile.close();


// SID, P_*.txt and L_*.txt should be inside Metadata/
char data_path[4096];
strcpy( data_path, input_path);
strcat( data_path, "Metadata/");
for (size_t l = 0; l < labels.size(); l++)
{
if (!labels[l]->load_data(data_path, parts, labels))
std::cout << "Could not load labels file. Probably you changed the meshlist.txt file while switching from data extraction to learning mode." << std::endl;
}
for (size_t p = 0; p < parts.size(); p++)
{
if (!parts[p]->load_data(data_path, parts))
std::cout << "Could not load parts file. Probably you changed the meshlist.txt file while switching from data extraction to learning mode." << std::endl;
}

///////////////////////////////////////////////////////////////
// Step 2: Learning
//////////////////////////////////////////////////////////////

// Sid use the following to train, convert to strings if you want.
ShapeBNet* bnet = (ShapeBNet*)nw;
char output_path[4096];
strcpy( output_path, input_path);
char part_path[4096];
strcpy( part_path, data_path);
strcat( part_path, "parts/");
// SET THIS FOR TREE MODE LEARNING!!!!!!!
bnet->options.set("learn_tree_only", 1);
// DO THIS ALWAYS BEFORE TRAIN.
bnet->setTrainingData(labels, parts, meshes);
//bnet->train();
// SAVE WHEREVER YOU WANT.
//bnet->save("tmp.bnet");

bnet->load("airplane.tree.bnet");
bnet->init();

//bnet->gaussian_nodes[15]->observation = bnet->gaussian_nodes[15]->gaussians[1].mean;

//   for (size_t i = 0; i <  bnet->cardinality_nodes[6]->cpt.size(); i++)
//   {
//     vector<size_t> values;
//     size_t d = bnet->cardinality_nodes[6]->getValues(i, values);
//     std::cout <<  bnet->cardinality_nodes[6]->cpt[i] << " "  << bnet->cardinality_nodes[6]->values[d] << " " << values[0] << " " << values[1] << std::endl;
//   }


vector< double > root_probabilities( bnet->root_node->domain_size, 0.0 );
vector< double > label_probabilities( labels.size(), 0.0 );
for (size_t l = 0; l < labels.size(); l++)
{
CGNode *cgnode = bnet->bpgraph->findNode( "Atree_query" + toString( l ) );
bnet->doInference( cgnode->bnodes );  // this stores the resuling factor at the involved nodes in the bnet
Factor factor = bnet->cardinality_nodes[l]->factor;
//for (size_t i = 0; i < factor.bdnodes.size(); i++)
//  std::cout << factor.bdnodes[i]->name << std::endl;

for (size_t i = 0; i < factor.b.size(); i++)
{
vector<size_t> values = factor.getValues(i);
root_probabilities[ values[0] ] += factor.b[i];
//      if ( values[1] > 0 )
//        label_probabilities[ l ] += factor.b[i];

//if ( bnet->cardinality_nodes[l]->values[  values[2] ] > 0 )
//label_probabilities[ l ] += factor.b[i];
if ( values[1] > 0 )
label_probabilities[ l ] += factor.b[i];
}
}

std::cout << root_probabilities << std::endl;
for (size_t l = 0; l < labels.size(); l++)
{
std::cout << labels[l]->name << " " << label_probabilities[l] << std::endl;
}



//for (size_t x = 0; x < bnet->bpgraph->cgnodes.size(); x++)
//  bnet->doInference(bnet->bpgraph->cgnodes[x]->bnodes);


bnet->load("airplane.tree.bnet");
//bnet->gaussian_nodes[0]->observation.push_back(0.5);
//bnet->gaussian_nodes[0]->observation.push_back(1);
//bnet->gaussian_nodes[0]->observation.push_back(0.2);
//bnet->gaussian_nodes[0]->observation.push_back(1);
//bnet->gaussian_nodes[0]->observation.push_back(0.01);
//bnet->gaussian_nodes[0]->observation.push_back(0.5);
boost::timer t;
bnet->init();
std::cout << t.elapsed() << std::endl;
boost::timer t2;
// SID, THIS FOR LOOP THING COULD BE PARALLELIZED, doInference IS EXPENSIVE.
for (size_t x = 0; x < bnet->bpgraph->cgnodes.size(); x++)
bnet->doInference(bnet->bpgraph->cgnodes[x]->bnodes);
std::cout << t2.elapsed() << std::endl;

for (size_t l = 0; l < labels.size(); l++)
{
for (size_t p = 0; p < labels[l]->parts.size(); p++ )
{
delete labels[l]->parts[p]->trimesh_part;
delete labels[l]->parts[p];
}
delete labels[l];
}
for (size_t m = 0; m < meshes.size(); m++)
{
delete meshes[m];
}

*/
