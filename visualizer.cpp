#include "visualizer.h"

using namespace utils;

CloudVisualizer::CloudVisualizer(const std::string& _name)
    : name(_name)
{
  viewer = std::shared_ptr<pcl::visualization::PCLVisualizer>(new pcl::visualization::PCLVisualizer("Viewer"));
  viewer->setBackgroundColor(0.33f, 0.33f, 0.33f);
  viewer->initCameraParameters();
  viewer->setCameraPosition(0.0f, 0.0f, 0.0f,
			    0.0f, 0.0f, 1.0f,
			    0.0f, 1.0f, 0.0f);
  
  visualizer_thread = std::thread(&CloudVisualizer::visualize, this);
  update = false;
}

void CloudVisualizer::visualize()
{
  while(!viewer->wasStopped())
  {
    mtx.lock();
    if(update)
    {
      if(!viewer->updatePointCloud(cloud, name))
      {
	//DO NOTHING
      }
      update = false;
    }
    mtx.unlock();
  }
}

void CloudVisualizer::addCloud(const pcl::PointCloud< pcl::PointXYZRGB >::Ptr& _cloud)
{
  mtx.lock();
  if(!update)
  {
    cloud = _cloud;
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgbHandler(_cloud);
    viewer->removePointCloud(name);
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, rgbHandler, name);
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.5, name);
    update = true;
    viewer->spinOnce();
  }
  mtx.unlock();
}

void CloudVisualizer::addCloud(const pcl::PointCloud< pcl::PointXYZ >::Ptr& _cloud)
{
    mtx.lock();
    if(!update)
    {
        cloudXYZ = _cloud;
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloudXYZ, 0, 255, 0); //Green
        viewer->removePointCloud(name);
        viewer->addPointCloud<pcl::PointXYZ> (cloudXYZ, single_color, name);
        viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, name);
        update = true;
        viewer->spinOnce();
    }
    mtx.unlock();
}

