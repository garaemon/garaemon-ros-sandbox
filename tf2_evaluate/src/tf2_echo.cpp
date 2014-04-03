#include <ros/ros.h>
#include <tf2_ros/buffer_client.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "tf2_echo");
  ros::NodeHandle node;
  
  ros::Rate rate(1.0);
  
  tf2_ros::BufferClient client ("tf2_buffer_server", 10, ros::Duration(2.0));
  //tf2_ros::TransformListener listener(core);
  client.waitForServer();
  std::string from(argv[1]);
  std::string to(argv[2]);
  
  while(node.ok()) {
    
    try {
      geometry_msgs::TransformStamped trans = client.lookupTransform(from, to, ros::Time(0.0), ros::Duration(1.0));
      ROS_INFO("- Translation: [%f, %f, %f]",
               trans.transform.translation.x,
               trans.transform.translation.y,
               trans.transform.translation.z);
               
      ROS_INFO("- Rotation in Quaternion: [%0.3f, %0.3f, %0.3f, %0.3f]",
               trans.transform.rotation.x,
               trans.transform.rotation.y,
               trans.transform.rotation.z,
               trans.transform.rotation.w);
    }
    catch (std::runtime_error e) {
      ROS_WARN_STREAM("failed to loolup transform from " << from << " to " << to);
    }
    ros::spinOnce();
    rate.sleep();
  }
  
  return 0;
}
