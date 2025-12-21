// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_MOLDFUL_H

#include "conceptrodon/metafunctions/omennivore/is_moldful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Moldful = Mouldivore::Confess<IsMoldful, Arg>;

}}

#endif