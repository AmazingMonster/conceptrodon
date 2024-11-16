// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Flowful = Typelivore::Clarify<IsFlowful, Arg>;

}}

#endif