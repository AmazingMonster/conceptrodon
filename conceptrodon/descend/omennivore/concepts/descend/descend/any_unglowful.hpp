// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNGLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNGLOWFUL_H

#include "conceptrodon/omennivore/is_glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unglowful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnglowful
=   Mouldivore::AnyDeceive<IsGlowful, Args...>
||  AllUnglowful<Args...>
;

}}

#endif