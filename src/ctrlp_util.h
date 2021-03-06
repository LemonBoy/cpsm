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

// CtrlP-specific support utilities.

#ifndef CPSM_CTRLP_UTIL_H_
#define CPSM_CTRLP_UTIL_H_

#include <functional>
#include <set>
#include <string>

#include <boost/utility/string_ref.hpp>

#include "str_util.h"

namespace cpsm {

// Returns an item substring function (see MatcherOpts::item_substr_fn) for
// the given CtrlP match mode.
std::function<boost::string_ref(boost::string_ref)> match_mode_item_substr_fn(
    boost::string_ref mmode);

// Appends a set of Vim regexes to highlight the bytes at positions in item for
// the given highlight mode.
void get_highlight_regexes(boost::string_ref mode, boost::string_ref item,
                           std::set<CharCount> const& positions,
                           std::vector<std::string>& regexes);

}  // namespace cpsm

#endif /* CPSM_CTRLP_UTIL_H_ */
