// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_WILLFUL_H
#define CONCEPTRODON_OMENNIVORE_WILLFUL_H

#include "conceptrodon/omennivore/is_willful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Willful = Typelivore::Clarify<IsWillful, Arg>;

}}

#endif