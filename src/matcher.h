// cpsm - fuzzy path matcher
// Copyright (C) 2015 Jamie Liu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPSM_MATCHER_H_
#define CPSM_MATCHER_H_

#include <set>
#include <string>
#include <vector>

#include <boost/utility/string_ref.hpp>

#include "match.h"

namespace cpsm {

struct MatcherOpts {
  // If true, the query and all items are paths.
  bool is_path = true;

  // The currently open file.
  std::string cur_file;

  enum class QueryPathMode {
    // Match path separators like any other character in the query.
    NORMAL,
    // All query characters between two path separators must match within a
    // single path component.
    STRICT,
    // Allow query characters to span path components if no path separators
    // appear in the query; otherwise treat them strictly.
    AUTO,
  };
  QueryPathMode query_path_mode = QueryPathMode::AUTO;
};

class Matcher {
 public:
  explicit Matcher(boost::string_ref query, MatcherOpts opts = MatcherOpts(),
                   StringHandler strings = StringHandler());

  // If the query represented by this matcher matches the given item, fills the
  // given match object with information about the match and returns true.
  // Otherwise returns false.
  //
  // If match_positions is not null, it will be filled with the indices of all
  // matched bytes in item. (Note that the number of matched bytes may not be
  // the same as the number of bytes in the query, or the same between
  // different items.) This may degrade performance significantly.
  //
  // If buf and buf2 are not null, they will be used as temporary buffers.
  // Clients performing many matches can improve performance by reusing buffers
  // between matches.
  bool match(boost::string_ref const item, MatchBase& m,
             std::set<CharCount>* match_positions = nullptr,
             std::vector<char32_t>* const buf = nullptr,
             std::vector<char32_t>* const buf2 = nullptr) const;

 private:
  void match_path(std::vector<boost::string_ref> const& item_parts,
                  Scorer& scorer) const;

  void match_key(std::vector<char32_t> const& key,
                 std::vector<char32_t>::const_iterator query_key,
                 Scorer& scorer, std::set<CharCount>* match_positions,
                 std::vector<CharCount> const& key_char_positions) const;

  bool match_char(char32_t item, char32_t query) const;

  MatcherOpts opts_;
  StringHandler strings_;
  std::vector<char32_t> query_;
  std::size_t query_key_begin_index_;
  bool is_case_sensitive_;
  bool require_full_part_;
  std::vector<boost::string_ref> cur_file_parts_;
  boost::string_ref cur_file_key_;
};

}  // namespace cpsm

#endif /* CPSM_MATCHER_H_ */
