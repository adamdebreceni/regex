#include <regex>
#include <string>
#include <iostream>
#include <vector>

int main() {
  std::regex re("group(.)(?:\\.(.))?.*");
  std::smatch result;

  std::string content = "group1.1:toA(one)\ngroup1.1:toA(two)\ngroup1.2:toA(three)\ngroup2:toA(four)\ngroup2:toA(five)";

  std::vector<std::string> segments = {
      "group1.1:toA(one)", "group1.1:toA(two)", "group1.2:toA(three)", "group2:toA(four)", "group2:toA(five)"
  };

  for (const auto& segment : segments) {
    std::regex_match(segment, result, re);

    bool first = true;
    std::string group;
    for (int i = 1; i < result.size(); ++i) {
      if (!first) group += ", ";
      first = false;
      group += result[i];
    }

    std::cout << "str = '" << segment << "'  group = '" << group << "'" << std::endl;
  }
}
