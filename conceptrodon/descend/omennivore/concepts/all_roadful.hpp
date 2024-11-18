// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllRoadful = (... && IsRoadful<Args>::value);

}}

#endif