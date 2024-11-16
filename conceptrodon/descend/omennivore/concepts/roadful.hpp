// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Roadful = Typelivore::Clarify<IsRoadful, Arg>;

}}

#endif