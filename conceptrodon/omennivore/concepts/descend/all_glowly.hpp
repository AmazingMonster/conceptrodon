// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GLOWLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_GLOWLY_H

#include "conceptrodon/omennivore/concepts/glowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllGlowly = (... && Glowly<Structures>);

}}

#endif