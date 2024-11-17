// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_COOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Coolful = Typelivore::Clarify<IsCoolful, Arg>;

}}

#endif