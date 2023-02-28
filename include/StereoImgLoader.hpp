#pragma once

#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <limits>

struct Image {
  cv::Mat data;
  double timestamp;
};
using StereoImage = std::pair<Image, Image>;

class StereoImgLoader
{
public:
  enum class ImgSource : unsigned char {
    IS_ROSBAG=0,
    IS_VIDEO=1,
    IS_DIRECTORY=1,
    IS_CAMERA=2
  };

private:
  ImgSource img_source_;

  //--- INITIALIZE VIDEOCAPTURE
  cv::VideoCapture cap;
  // open the default camera using default API
  // cap.open(0);
  // OR advance usage: select any API backend
  int deviceID = 0;             // 0 = open default camera
  int apiID = cv::CAP_ANY;      // 0 = autodetect default API
  int MAX_FRAME_NUM = 1000000;
  int current_frame_num = 0;

  cv::Size * raw_img_size_ = nullptr;
  cv::Size * out_img_size_ = nullptr;

public:
  StereoImgLoader()=delete;
  StereoImgLoader(ImgSource img_source, const std::string & arg_1);

  StereoImgLoader(ImgSource img_source, const std::string & arg_1,
                                        const std::string & arg_2);

  StereoImgLoader(ImgSource img_source, const std::string & arg_1,
                                        const std::string & arg_2,
                                        const std::string & arg_3);

  StereoImgLoader(ImgSource img_source, const int cam_id_1);
  StereoImgLoader(ImgSource img_source, const int cam_id_1,
                                        const int cam_id_2);

  ~StereoImgLoader();

  void _initializeWithRosbag(const std::string & rosbag_file_path,
                             const std::string & mono_topic_name);

  // void _initializeWithRosbag(const std::string & rosbag_file_path,
  //                            const std::string & left_topic_name,
  //                            const std::string & right_topic_name);

  // void _initializeWithDirectory(const std::string & directory_path);

  // void _initializeWithVideo(const std::string & mono_video_path);
  // void _initializeWithVideo(const std::string & left_video_path,
  //                           const std::string & right_video_path);

  // void _initializeWithCamera(const int mono_cam_id);
  // void _initializeWithCamera(const int left_cam_id, const int right_cam_id);

  auto getMonoImg() -> Image;
  auto getStereoImg() -> StereoImage;

  void setResizeScale(const double & scale);
};

std::string cv_type2str(int type);
