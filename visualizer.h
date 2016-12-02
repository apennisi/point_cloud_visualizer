#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types_conversion.h>

namespace utils
{
  class CloudVisualizer
  {
    public:
      explicit CloudVisualizer(const std::string& _name);
      void addCloud(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& _cloud);
      void addCloud(const pcl::PointCloud< pcl::PointXYZ >::Ptr& _cloud);
    private:
      void visualize();
    private:
      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloudXYZ;
      std::mutex mtx;
      std::string name;
      std::thread visualizer_thread;
      std::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
      bool update;
      boost::mutex updateModelMutex;
  };
}

#endif
