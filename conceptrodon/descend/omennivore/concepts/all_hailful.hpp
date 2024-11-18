// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_HAILFUL_H

#include "conceptrodon/omennivore/is_hailful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllHailful = (... && IsHailful<Args>::value);

}}

#endif