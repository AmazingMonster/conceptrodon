// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_GLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_GLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_glowful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyGlowful
=   Mouldivore::AnyConfess<IsGlowful, Args...>
||  AllGlowful<Args...>;

}}

#endif