// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_ROADLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_ROADLESS_H

#include "conceptrodon/omennivore/concepts/roadless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllRoadless = (... && Roadless<Structures>);

}}

#endif