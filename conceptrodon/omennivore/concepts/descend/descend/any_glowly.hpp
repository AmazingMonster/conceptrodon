// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GLOWLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_GLOWLY_H

#include "conceptrodon/omennivore/concepts/descend/all_glowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyGlowly = (... || Glowly<Structures>);

template<typename...Args>
concept AnyGlowly
=   JustAnyGlowly<Args...>
||  AllGlowly<Args...>;

}}

#endif