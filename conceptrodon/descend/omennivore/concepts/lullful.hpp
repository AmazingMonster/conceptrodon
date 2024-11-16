// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_LULLFUL_H
#define CONCEPTRODON_OMENNIVORE_LULLFUL_H

#include "conceptrodon/omennivore/is_lullful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Lullful = Typelivore::Clarify<IsLullful, Arg>;

}}

#endif