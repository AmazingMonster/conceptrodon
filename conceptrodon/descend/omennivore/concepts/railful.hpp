// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_RAILFUL_H

#include "conceptrodon/omennivore/is_railful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Railful = Typelivore::Clarify<IsRailful, Arg>;

}}

#endif