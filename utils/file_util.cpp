#include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>

void SaveJsonInfo(const std::string &json_name, const std::string &info) {
  char real_path[PATH_MAX] = {0};
  std::string path = kCceKernelMeta + json_name + kInfoSuffix;
  std::ofstream filewrite;
  filewrite.open(path);
  if (!filewrite.is_open()) {
    return;
  }
  filewrite << info << std::endl;
  filewrite.close();
#if defined(_WIN32) || defined(_WIN64)
  if (nullptr == _fullpath(real_path, path.c_str(), PATH_MAX)) {
    MS_LOG(DEBUG) << "dir " << path << " does not exit.";
    return;
  }
#else
  if (nullptr == realpath(path.c_str(), real_path)) {
    MS_LOG(DEBUG) << "dir " << path << " does not exit.";
    return;
  }
#endif
  MS_LOG(INFO) << "real path is :" << real_path;
  if (chmod(real_path, S_IRUSR) == -1) {
    MS_LOG(DEBUG) << "modify file:" << real_path << " to read only fail.";
  }
}
