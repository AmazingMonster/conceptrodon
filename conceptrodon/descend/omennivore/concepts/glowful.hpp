// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_GLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Glowful = Typelivore::Clarify<IsGlowful, Arg>;

}}

#endif