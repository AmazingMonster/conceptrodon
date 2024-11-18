// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_RAILFUL_H

#include "conceptrodon/omennivore/is_railful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllRailful = (... && IsRailful<Args>::value);

}}

#endif