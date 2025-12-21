// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_HAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_hailful.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Hailful = Mouldivore::Confess<IsHailful, Arg>;

}}

#endif