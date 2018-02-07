#include <pcl/gpu/containers/device_array.h>
#include <pcl/gpu/features/features.hpp>
//#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/fpfh.h>

//__global__ void kernel(pcl::gpu::PtrSz<pcl::PointXYZ> device){
//    /// check kernel_containers.h to figure out what PtrSz means ///
//    device[0].x+=1;
//    pcl::PointXYZRGB q=device[0].data;
//}


int main() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//    pcl::gpu::DeviceArray<pcl::PointXYZ> d_pointcloud;
    /// DeviceArray serves as a data storage in GPU ///
    pcl::io::loadPCDFile("..//data//model.pcd", *cloud);

    /// Use upload and download methods to transfer the date between CPU and GPU ///
    /// cloud.points in fact is a vector, whose type is identical with DeviceArray ///

    /// Transfer the data from CPU to GPU ///
//    d_pointcloud.upload(cloud->points);
//    kernel<<< 9, 1 >>>(cloud_device);
    /// Transfer the data from GPU to CPU ///
//    d_pointcloud.download(cloud->points);

    pcl::PointCloud<pcl::Normal> h_normal;

    pcl::gpu::Feature::PointCloud d_cloud;
    d_cloud.upload(cloud->points);
    pcl::gpu::Feature::Normals    d_normal;
    pcl::gpu::NormalEstimation    normal_estimator;
    normal_estimator.setInputCloud(d_cloud);
    /// max_results: max number of returned points for each query ///
    normal_estimator.setRadiusSearch(0.1, d_cloud.size());
    normal_estimator.compute(d_normal);
    d_cloud.download(cloud->points);
}