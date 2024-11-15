// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_SAILFUL_H

#include "conceptrodon/omennivore/is_sailful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Sailful = IsSailful_v<Arg>;

}}

#endif