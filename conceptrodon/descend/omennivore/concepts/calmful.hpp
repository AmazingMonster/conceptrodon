// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Calmful = Typelivore::Clarify<IsCalmful, Arg>;

}}

#endif