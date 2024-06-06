#ifndef MODEL_S21_MODEL_PERCEPTRONE_
#define MODEL_S21_MODEL_PERCEPTRONE_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum image { lable, pixel };

std::vector<std::vector<unsigned char>> ParseCsv(const std::string& filename,
                                                 size_t image_resolution);

#endif  // MODEL_S21_MODEL_PERCEPTRONE_
