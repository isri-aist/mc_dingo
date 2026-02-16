#include "dingo.h"

#include <RBDyn/parsers/urdf.h>

namespace {

// This is set by CMake, see CMakeLists.txt
static const std::string MC_DINGO_DESCRIPTION_PATH =
    "@DINGO_DESCRIPTION_PATH@";

} // namespace

namespace mc_robots {

DingoRobotModule::DingoRobotModule()
 : mc_rbdyn::RobotModule(MC_DINGO_DESCRIPTION_PATH, "dingo") {
  // True if the robot has a fixed base, false otherwise
  bool fixed = false;

  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load rsdf
  rsdf_dir = path + "/rsdf/" + name ;
  
  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {};
  _commonSelfCollisions = _minimalSelfCollisions;

  // Ref joint order
  _ref_joint_order = {};
}

} // namespace mc_robots
