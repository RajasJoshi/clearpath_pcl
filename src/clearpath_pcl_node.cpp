#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <iomanip>

using std::placeholders::_1;
class PointCloudPrinter : public rclcpp::Node
{
public:
  PointCloudPrinter() : Node("pointcloud_printer_cpp")
  {
    subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/j100_0000/sensors/lidar3d_0/points", 10, std::bind(&PointCloudPrinter::print_pointcloud, this, _1));
  }

private:
  void print_pointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
  {
    // Convert to PCL PointCloud with intensity
    pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_cloud(new pcl::PointCloud<pcl::PointXYZI>);
    pcl::fromROSMsg(*msg, *pcl_cloud);

    // Print the point cloud data
    for (const auto &point : pcl_cloud->points)
    {
      RCLCPP_INFO(this->get_logger(), "(%.3f, %.3f, %.3f, %.3f)", point.x, point.y, point.z, point.intensity);
    }
    RCLCPP_INFO(this->get_logger(), "-----\n"); // Separator
  }

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PointCloudPrinter>());
  rclcpp::shutdown();
  return 0;
}
