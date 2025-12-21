// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_COOLFUL_H

#include "conceptrodon/metafunctions/omennivore/is_coolful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Coolful = Mouldivore::Confess<IsCoolful, Arg>;

}}

#endif