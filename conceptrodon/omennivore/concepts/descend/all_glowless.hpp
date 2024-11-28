// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_GLOWLESS_H

#include "conceptrodon/omennivore/concepts/glowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllGlowless = (... && Glowless<Structures>);

}}

#endif