# Point Cloud Visualizer
Point Cloud Visualizer is a tool for visualizing a point cloud that can be updated
without locking the main execution of the program.

## Requirements

The following packages are required to build:

* PCL (tested 1.7)
* Boost

## Usage

```c++
utils::CloudViewer viewer("Point Cloud");
viewer.addCloud(cloud);
```

You can add PointXYZRGB and PointXYZ cloud types.
