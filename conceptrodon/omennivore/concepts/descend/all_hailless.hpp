// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_HAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_HAILLESS_H

#include "conceptrodon/omennivore/concepts/hailless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllHailless = (... && Hailless<Structures>);

}}

#endif