/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, Ryohei Ueda and JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/o2r other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <ros/ros.h>
#include <tf2_ros/buffer_client.h>
#include <boost/lexical_cast.hpp>


int main(int argc, char** argv) {
  ros::init(argc, argv, "tf2_publisher");
  ros::NodeHandle node;
  
  
  
  tf2_ros::BufferClient client ("tf2_buffer_server", 10, ros::Duration(2.0));

  // x y z qx qy qz qw from to milsec
  client.waitForServer();

  int counter = 1;
  double x = boost::lexical_cast<double>(argv[counter++]);
  double y = boost::lexical_cast<double>(argv[counter++]);
  double z = boost::lexical_cast<double>(argv[counter++]);
  double qx = boost::lexical_cast<double>(argv[counter++]);
  double qy = boost::lexical_cast<double>(argv[counter++]);
  double qz = boost::lexical_cast<double>(argv[counter++]);
  double qw = boost::lexical_cast<double>(argv[counter++]);
  std::string from(argv[counter++]);
  std::string to(argv[counter++]);
  double rate_time = boost::lexical_cast<double>(argv[counter++]);
  
  ROS_INFO("publish following transformation from %s to %s:",
           from.c_str(), to.c_str());
  ROS_INFO("- Translation [%0.3f, %0.3f, %0.3f]", x, y, z);
  ROS_INFO("- Rotation    [%0.3f, %0.3f, %0.3f, %0.3f]", qx, qy, qz, qw);

  ros::Rate rate(1000.0 / rate_time);
  
  while(node.ok()) {
    
    try {
      // geometry_msgs::TransformStamped trans = client.lookupTransform(from, to, ros::Time(0.0), ros::Duration(1.0));
      // ROS_INFO("- Translation: [%f, %f, %f]",
      //          trans.transform.translation.x,
      //          trans.transform.translation.y,
      //          trans.transform.translation.z);
               
      // ROS_INFO("- Rotation in Quaternion: [%0.3f, %0.3f, %0.3f, %0.3f]",
      //          trans.transform.rotation.x,
      //          trans.transform.rotation.y,
      //          trans.transform.rotation.z,
      //          trans.transform.rotation.w);
    }
    catch (std::runtime_error e) {
      ROS_WARN_STREAM("failed to loolup transform from " << from << " to " << to);
    }
    ros::spinOnce();
    rate.sleep();
  }
  
  return 0;
}
