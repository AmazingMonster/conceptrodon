// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_GLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_glowful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyGlowful = (... || IsGlowful<Args>::value);

template<typename...Args>
concept AnyGlowful
=   JustAnyGlowful<Args...>
||  AllGlowful<Args...>;

}}

#endif