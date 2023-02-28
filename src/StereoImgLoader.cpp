#include <StereoImgLoader.hpp>

StereoImgLoader::StereoImgLoader(ImgSource img_source, const std::string & arg_1,
                                                       const std::string & arg_2)
  : img_source_(img_source)
{
  ROS_ASSERT(img_source != ImgSource::IS_CAMERA);

  if (img_source == ImgSource::IS_ROSBAG)
  {
    const auto & bagfile_path = arg_1;
    const auto & mono_topic_name = arg_2;
    _initializeWithRosbag(bagfile_path, mono_topic_name);
  }
  else
  {
    ROS_FATAL("Not yet implemented!");
  }
}

// StereoImgLoader::StereoImgLoader()
// {
//   cap.open(deviceID, apiID);
//   if (!cap.isOpened())
//   {
//     std::cerr << "ERROR! Unable to open camera\n";
//     std::exit(1);
//   }
//   img_source_ = ImgSource::IS_CAMERA;
// }

// ~StereoImgLoader::StereoImgLoader()
// {
//   // When everything done, release the video capture object
//   cap.release();
// }

// StereoImgLoader::StereoImgLoader(int cam_id):img_source_(ImgSource::IS_CAMERA)
// {
//     deviceID = cam_id;
//     cap.open(deviceID, apiID);
//     if (!cap.isOpened()) {
//         std::cerr << "ERROR! Unable to open camera\n";
//         std::exit(1);
//     }

//     cv::Mat test_grab;
//     while(!cap.read(test_grab));
//     out_img_size_ = new cv::Size(test_grab.size());
// }
// StereoImgLoader::StereoImgLoader(const cv::String& filename):img_source_(ImgSource::IS_VIDEO)
// {
//     cap.open(filename, apiID);
//     if (!cap.isOpened()) {
//         std::cerr << "ERROR! Unable to open camera\n";
//         std::exit(1);
//     }
// }

// cv::Mat StereoImgLoader::read_image(const cv::String& path)
// {
//     cv::Mat gray_img = cv::imread(path, cv::IMREAD_GRAYSCALE);
//     // resampling using pixel area relation
//     // resize(input, output, Size, scale_factor_x, scale_factor_y, interpolation_method)
//     if(out_img_size_ != NULL)
//         cv::resize(gray_img, gray_img, (*out_img_size_), 0, 0, cv::INTER_AREA);

//     if(gray_img.empty()){
//         std::cerr << "Error reading image.\n";
//         exit('2');
//     }
//     gray_img.convertTo(gray_img, CV_32F);
//     return gray_img/255.;
// }

auto StereoImgLoader::getMonoImg() -> Image
{
  if (img_source_ == ImgSource::IS_ROSBAG)
  {
    // todo
  }
  else
  {
    ROS_WARN("Not implemented");
  }

    // if(current_frame_num >= MAX_FRAME_NUM) return false;
    // if(img_source == ImgSource::IS_CAMERA)
    // {
    //     if(!cap.read(img))
    //     {
    //         std::cout << "No Image.\n";
    //         return false;
    //     }
    //     input = img.clone();

    //     if(out_img_size_ != NULL)
    //         cv::resize(input, input, (*out_img_size_), 1., 1., cv::INTER_AREA);

    //     cv::cvtColor(input, input, cv::COLOR_RGB2GRAY);
    //     input.convertTo(input, CV_32F);
    // }
    // else if(img_source == ImgSource::IS_VIDEO_FILE)
    // {
    //     /* Read next image. Return false if failed.*/
    //     if(!cap.read(img))
    //     {
    //         std::cout << "No Image.\n";
    //         return false;
    //     }

    //     input = img.clone();
    //     cv::cvtColor(input, input, cv::COLOR_RGB2GRAY);

    //     /* If the size is fixed, adjust it. */
    //     if(out_img_size_ != NULL)
    //     {
    //         W_scale = (float)img.size().width / (float)out_img_size_->width;
    //         H_scale = (float)img.size().height / (float)out_img_size_->height;
    //         cv::resize(input, input, (*out_img_size_), 1., 1., cv::INTER_AREA);
    //     }

    //     input.convertTo(input, CV_32F);
    // }
    // else
    // {
    //     std::cerr << "There is no source of image frames!\n";
    //     exit(2);
    // }
    // current_frame_num++;
    // return true;
}

void StereoImgLoader::setResizeScale(const double & scale)
{
  static bool set_only_once = false;
  if (!set_only_once && raw_img_size_)
  {
    auto tmp_width  = static_cast<double>(raw_img_size_->width);
    auto tmp_height = static_cast<double>(raw_img_size_->height);
    auto new_width  = static_cast<int>(tmp_width  * scale);
    auto new_height = static_cast<int>(tmp_height * scale);
    out_img_size_ = new cv::Size(new_width, new_height);
    set_only_once = true;
  }
  else if (raw_img_size_ == nullptr)
  {
    ROS_FATAL("Original img size is lost.");
  }
  else
  {
    ROS_FATAL("Set output image size only once.");
  }
}

std::string cv_type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}
