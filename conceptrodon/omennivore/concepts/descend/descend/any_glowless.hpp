// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_GLOWLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_glowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyGlowless = (... || Glowless<Structures>);

template<typename...Args>
concept AnyGlowless
=   JustAnyGlowless<Args...>
||  AllGlowless<Args...>;

}}

#endif