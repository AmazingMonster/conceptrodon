// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_GRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"
#include "conceptrodon/mouldivore/concepts/confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Gritful = Mouldivore::Confess<IsGritful, Arg>;

}}

#endif