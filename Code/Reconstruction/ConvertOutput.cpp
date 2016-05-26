#include <Thea/Common.hpp>
#include <Thea/FilePath.hpp>
#include <Thea/FileSystem.hpp>
#include <Thea/Vector3.hpp>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>

using namespace std;
using namespace Thea;

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    THEA_CONSOLE << "Usage: " << argv[0] << " <training-dir> <synth-file>";
    return -1;
  }

  string training_dir = FileSystem::resolve(argv[1]);
  string synth_file = FileSystem::resolve(argv[2]);

  // Decompose synthesized data into parts and points
  typedef pair<long, string> TrainingLabelAndSource;
  typedef VectorN<3, double> DVec3;
  typedef pair<long, DVec3> PointIDAndPosition;
  typedef map< TrainingLabelAndSource, TheaArray<PointIDAndPosition> > PartPointMap;
  PartPointMap part_points;
  {
    ifstream in(synth_file.c_str());
    if (!in)
    {
      THEA_ERROR << "Could not open input file '" << synth_file << '\'';
      return -1;
    }

    DVec3 pos;
    long point_id, training_label;
    string src_mesh;
    string line;
    while (getline(in, line))
    {
      istringstream line_in(line);
      if (!(line_in >> pos[0] >> pos[1] >> pos[2] >> point_id >> training_label >> src_mesh))
      {
        THEA_ERROR << "Could not parse line: " << line;
        return -1;
      }

      part_points[TrainingLabelAndSource(training_label, src_mesh)].push_back(PointIDAndPosition(point_id, pos));
    }

    THEA_CONSOLE << "Synthesized shape '" << FilePath::objectName(synth_file) << "' has " << part_points.size() << " parts";
    for (PartPointMap::const_iterator pi = part_points.begin(); pi != part_points.end(); ++pi)
    {
      THEA_CONSOLE << "  -- label " << pi->first.first <<", source '" << pi->first.second << "', " << pi->second.size()
                   << " points";
    }
  }

  // Read mapping between labels
  typedef pair<long, long> LabelAndLayoutPosition;
  typedef map<LabelAndLayoutPosition, long> LabelMap;
  LabelMap label_map;
  {
    ifstream in(FilePath::concat(training_dir, "label_map.txt").c_str());
    if (!in)
    {
      THEA_ERROR << "Could not open label mapping";
      return -1;
    }

    string line;
    while (getline(in, line))
    {
      istringstream line_in(line);
      LabelAndLayoutPosition src;
      long dst;
      if (!(line_in >> dst >> src.first >> src.second))
      {
        THEA_ERROR << "Could not read label mapping from line '" << line << '\'';
        return -1;
      }

      label_map[src] = dst;
    }
  }

  // Set up mappings to assembly-based domain parts
  typedef map<TrainingLabelAndSource, long> PartMap;
  PartMap part_map;
  {
    ifstream in(FilePath::concat(training_dir, "src_parts.txt").c_str());
    if (!in)
    {
      THEA_ERROR << "Could not open part list for assembly-based domain";
      return -1;
    }

    THEA_CONSOLE << "\nMapping parts to assembly-based domain";

    string src_mesh;
    long num_parts;
    while (in >> src_mesh >> num_parts)
    {
      if (num_parts < 0)
      {
        THEA_ERROR << "Source mesh '" << src_mesh << "' has " << num_parts << " parts";
        return -1;
      }

      replace(src_mesh.begin(), src_mesh.end(), '.', '_');

      long part_id, label_id, layout_pos_id;
      for (long i = 0; i < num_parts; ++i)
      {
        if (!(in >> part_id >> label_id >> layout_pos_id))
        {
          THEA_ERROR << "Could not read part " << i << " of source mesh '" << src_mesh << '\'';
          return -1;
        }

        LabelMap::const_iterator existing = label_map.find(LabelAndLayoutPosition(label_id, layout_pos_id));
        if (existing != label_map.end())
        {
          for (PartPointMap::const_iterator pi = part_points.begin(); pi != part_points.end(); ++pi)
          {
            if (pi->first == TrainingLabelAndSource(existing->second, src_mesh))
            {
              part_map[pi->first] = part_id;

              THEA_CONSOLE << "  -- mapped training part " << src_mesh << '(' << existing->second << ") to domain part "
                           << part_id << " (" << label_id << ", " << layout_pos_id << ')';

              break;
            }
          }
        }
      }
    }

    if (part_map.size() != part_points.size())
    {
      THEA_ERROR << "Number of mapped parts (" << part_map.size() << ") != number of parts in synthesized shape ("
                 << part_points.size() << ')';
      return -1;
    }
  }

  // Export points per part
  {
    THEA_CONSOLE << "\nExporting points per part";

    string synth_dir = FilePath::parent(synth_file);
    string out_dir = FilePath::concat(synth_dir, "parts");
    FileSystem::createDirectory(out_dir);

    string pts_dir = FilePath::concat(training_dir, patternMatch(synth_file, "*dense*") ? "dense" : "sparse");

    ostringstream cmdline, simple_cmdline;

    cmdline << "~/LibMBA/Code/Build/Output/bin/AssembleDeformed";
    simple_cmdline << "~/LibMBA/Code/Build/Output/bin/Assemble";

    string domain;
    size_t last_underscore = synth_dir.find_last_of('_');
    if (last_underscore == string::npos || last_underscore == synth_dir.length() - 1)
      domain = "~/ModelingHighLevelAttrib/Data/Domains/Animals";
    else
    {
      string domain_name = synth_dir.substr(last_underscore + 1);
      domain_name[0] = (char)std::toupper(domain_name[0]);
      domain = "~/ModelingHighLevelAttrib/Data/Domains/" + domain_name;
    }

    cmdline << ' ' << domain;
    simple_cmdline << ' ' << domain;

    string basename = FilePath::completeBaseName(synth_file);
    string prefix = FilePath::concat(out_dir, basename);
    for (PartPointMap::const_iterator pi = part_points.begin(); pi != part_points.end(); ++pi)
    {
      bool skip = true;
      for (LabelMap::const_iterator lj = label_map.begin(); lj != label_map.end(); ++lj)
        if (lj->second == pi->first.first && lj->first.second == 1)
        {
          skip = false;
          break;
        }

      if (skip)
      {
        THEA_CONSOLE << "  -- skipping part " << pi->first.second << '(' << pi->first.first << "): not generator part";
        continue;
      }

      PartMap::const_iterator domain_part = part_map.find(pi->first);
      if (domain_part == part_map.end())
      {
        THEA_ERROR << "Part " << pi->first.second << '(' << pi->first.first << ") not mapped to domain part";
        return -1;
      }

      string out_path = prefix + format(".%ld.pts", pi->first.first);
      ofstream out(out_path.c_str(), ios::binary);
      if (!out)
      {
        THEA_ERROR << "Could not open output file '" << out_path << '\'';
        return -1;
      }

      for (array_size_t j = 0; j < pi->second.size(); ++j)
      {
        DVec3 const & pos = pi->second[j].second;
        long point_id = pi->second[j].first;
        out << pos[0] << ' ' << pos[1] << ' ' << pos[2] << " 0 0 0 " << point_id << endl;
      }

      cmdline << " \\\n"
              << "    \\\n"
              << "    " << domain_part->second << " \\\n"
              << "    '" << FilePath::concat(pts_dir, pi->first.second + format("/%ld.pts", pi->first.first)) << "' \\\n"
              << "    '" << out_path << '\'';

      simple_cmdline << ' ' << domain_part->second;

      THEA_CONSOLE << "  -- exported part " << pi->first.second << '(' << pi->first.first << ") to '" << out_path << '\'';
    }

    // Write full cmdline
    {
      string mesh_dir = FilePath::concat(synth_dir, "assembled");
      FileSystem::createDirectory(mesh_dir);
      string mesh_path = FilePath::concat(mesh_dir, basename + ".obj");

      cmdline << " \\\n"
              << "    \\\n"
              << "    '" << mesh_path << '\'';

      string cmd_dir = FilePath::concat(synth_dir, "cmd");
      FileSystem::createDirectory(cmd_dir);
      string cmd_path = FilePath::concat(cmd_dir, basename) + ".sh";
      ofstream cmd_out(cmd_path.c_str(), ios::binary);
      if (!cmd_out)
      {
        THEA_ERROR << "Could not open file '" << cmd_path << " for writing assembly command";
        return -1;
      }

      cmd_out << "#!/bin/bash\n\n"
              << cmdline.str() << endl;

      THEA_CONSOLE << "Wrote command-line to '" << cmd_path << '\'';
    }

    // Write simple cmdline
    {
      string mesh_dir = FilePath::concat(synth_dir, "assembled_nodeform");
      FileSystem::createDirectory(mesh_dir);
      string mesh_path = FilePath::concat(mesh_dir, basename + ".obj");

      simple_cmdline << " '" << mesh_path << '\'';

      string simple_cmd_dir = FilePath::concat(synth_dir, "cmd_nodeform");
      FileSystem::createDirectory(simple_cmd_dir);
      string simple_cmd_path = FilePath::concat(simple_cmd_dir, basename) + ".sh";
      ofstream simple_cmd_out(simple_cmd_path.c_str(), ios::binary);
      if (!simple_cmd_out)
      {
        THEA_ERROR << "Could not open file '" << simple_cmd_path << " for writing simple assembly command";
        return -1;
      }

      simple_cmd_out << "#!/bin/bash\n\n"
              << simple_cmdline.str() << endl;

      THEA_CONSOLE << "Wrote simple command-line to '" << simple_cmd_path << '\'';
    }
  }

  return 0;
}
