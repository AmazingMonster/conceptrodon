// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_SAILFUL_H

#include "conceptrodon/omennivore/is_sailful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllSailful = (... && IsSailful<Args>::value);

}}

#endif