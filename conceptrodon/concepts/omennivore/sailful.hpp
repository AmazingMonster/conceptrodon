// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAILFUL_H
#define CONCEPTRODON_OMENNIVORE_SAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_sailful.hpp"
#include "conceptrodon/concepts/mouldivore/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Sailful = Mouldivore::Confess<IsSailful, Arg>;

}}

#endif