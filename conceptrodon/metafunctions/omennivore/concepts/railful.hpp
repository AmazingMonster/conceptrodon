// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_RAILFUL_H
#define CONCEPTRODON_OMENNIVORE_RAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_railful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Railful = Mouldivore::Confess<IsRailful, Arg>;

}}

#endif