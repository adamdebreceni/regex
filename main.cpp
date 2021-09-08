#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <range/v3/view/tail.hpp>
#include <range/v3/view/cache1.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/core.hpp>
#include <range/v3/view/transform.hpp>

#ifdef __APPLE__
#include <experimental/functional>
template<typename It, typename Hash, typename Eq>
using boyer_moore_searcher = std::experimental::boyer_moore_searcher<It, Hash, Eq>;
#else
#include <functional>
template<typename It, typename Hash, typename Eq>
using boyer_moore_searcher = std::boyer_moore_searcher<It, Hash, Eq>;
#endif

enum class CasePolicy {
  CASE_SENSITIVE,
  IGNORE_CASE
};

struct CaseAwareHash {
  explicit CaseAwareHash(CasePolicy policy): policy_(policy) {}
  size_t operator()(char ch) const {
    if (policy_ == CasePolicy::CASE_SENSITIVE) {
      return static_cast<size_t>(ch);
    }
    return std::hash<int>{}(std::tolower(static_cast<unsigned char>(ch)));
  }

 private:
  CasePolicy policy_;
};

struct CaseAwareEq {
  explicit CaseAwareEq(CasePolicy policy): policy_(policy) {}
  bool operator()(char a, char b) const {
    if (policy_ == CasePolicy::CASE_SENSITIVE) {
      return a == b;
    }
    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
  }

 private:
  CasePolicy policy_;
};
using Searcher = boyer_moore_searcher<std::string_view::const_iterator, CaseAwareHash, CaseAwareEq>;

int main() {
  std::regex re("group(.)(?:\\.(.))?.*");
  std::smatch result;

  std::string content = "group1.1:toA(one)\ngroup1.1:toA(two)\ngroup1.2:toA(three)\ngroup2:toA(four)\ngroup2:toA(five)";

  std::vector<std::string> segments = {
      "group1.1:toA(one)", "group1.1:toA(two)", "group1.2:toA(three)", "group2:toA(four)", "group2:toA(five)"
  };

  std::string_view target = "toA";

  CasePolicy policy = CasePolicy::CASE_SENSITIVE;
  Searcher searcher(target.cbegin(), target.cend(), CaseAwareHash{policy}, CaseAwareEq{policy});

  for (const auto& segment : segments) {
    std::regex_match(segment, result, re);

    if (std::search(segment.cbegin(), segment.cend(), searcher) != segment.cend()) {
      std::cout << "Routing '" << segment << "' to A" << std::endl;
    } else {
      std::cout << "Routing '" << segment << "' to null" << std::endl;
    }

    auto to_string = [] (const auto& submatch) -> std::string {return submatch;};
    std::string group = ranges::views::tail(result)  // only join the capture groups
       | ranges::views::transform(to_string)
       | ranges::views::cache1
       | ranges::views::join(std::string(", "))
       | ranges::to<std::string>();

    std::cout << "str = '" << segment << "'  group = '" << group << "'" << std::endl;
  }
}
