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

  std::string_view target = "toA";

  auto searcher = std::boyer_moore_searcher(target.cbegin(), target.cend());

  for (const auto& segment : segments) {
    std::regex_match(segment, result, re);

    if (std::search(segment.cbegin(), segment.cend(), searcher) != segmend.cend()) {
      std::cout << "Routing '" << segment << "' to A" << std::endl;
    } else {
      std::cout << "Routing '" << segment << "' to null" << std::endl;
    }

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
