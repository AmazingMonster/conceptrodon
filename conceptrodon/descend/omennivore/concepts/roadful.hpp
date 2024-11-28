// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Roadful = Mouldivore::Confess<IsRoadful, Arg>;

}}

#endif