// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_GLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllGlowful = (... && IsGlowful<Args>::value);

}}

#endif