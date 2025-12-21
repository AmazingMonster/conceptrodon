// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_DAWNFUL_H
#define CONCEPTRODON_OMENNIVORE_DAWNFUL_H

#include "conceptrodon/metafunctions/omennivore/is_dawnful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Dawnful = Mouldivore::Confess<IsDawnful, Arg>;

}}

#endif