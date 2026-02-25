#include "dingo.h"

#include <mc_dingo/config.h>
#include <RBDyn/parsers/urdf.h>

namespace mc_robots
{

DingoRobotModule::DingoRobotModule()
: mc_rbdyn::RobotModule(DINGO_DESCRIPTION_PATH, "dingo", std::string(DINGO_URDF_DIR) + "/dingo.urdf")
{
  // True if the robot has a fixed base, false otherwise
  bool fixed = false;

  // Makes all the basic initialization that can be done from an URDF file
  init(rbd::parsers::from_urdf_file(urdf_path, fixed));

  // Automatically load rsdf
  rsdf_dir = path + "/rsdf/" + name;

  // Define a minimal set of self-collisions
  _minimalSelfCollisions = {};
  _commonSelfCollisions = _minimalSelfCollisions;

  // Ref joint order
  _ref_joint_order = {};
}

} // namespace mc_robots
