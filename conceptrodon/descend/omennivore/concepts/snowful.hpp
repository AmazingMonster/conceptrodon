// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Snowful = Typelivore::Clarify<IsSnowful, Arg>;

}}

#endif