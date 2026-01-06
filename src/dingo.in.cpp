#include "dingo.h"

#include <RBDyn/parsers/urdf.h>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

namespace {

// This is set by CMake, see CMakeLists.txt
static const std::string MC_DINGO_DESCRIPTION_PATH =
    "@MC_DINGO_DESCRIPTION_PATH@";

} // namespace

namespace mc_robots {

DingoRobotModule::DingoRobotModule()
    : mc_rbdyn::RobotModule(MC_DINGO_DESCRIPTION_PATH, "dingo") {
  // True if the robot has a fixed base, false otherwise
  bool fixed = true;
  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load the convex hulls associated to each body
  std::string convexPath = path + "/convex/" + name + "/";
  bfs::path p(convexPath);
  if (bfs::exists(p) && bfs::is_directory(p)) {
    std::vector<bfs::path> files;
    std::copy(bfs::directory_iterator(p), bfs::directory_iterator(),
              std::back_inserter(files));
    for (const bfs::path &file : files) {
      size_t off = file.filename().string().rfind("-ch.txt");
      if (off != std::string::npos) {
        std::string name = file.filename().string();
        name.replace(off, 7, "");
        _convexHull[name + "_link"] = std::pair<std::string, std::string>(
              name + "_link", file.string());
      }
    }
  }

  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {};
  _commonSelfCollisions = _minimalSelfCollisions;

  // Ref joint order
  _ref_joint_order = {"left_wheel", "right_wheel"};

  // Stance: joint name, angle in degrees
  std::map<std::string, double> starting{
      {"left_wheel", 0.0},
      {"right_wheel", 0.0},
  };

  for (const auto &j : mb.joints()) {
    if (j.name() != "Root" && j.dof() > 0) {
      _stance[j.name()] = {starting.at(j.name())};
    }
  }
}

} // namespace mc_robots
