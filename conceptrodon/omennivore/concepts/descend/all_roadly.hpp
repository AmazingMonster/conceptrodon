// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_ROADLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_ROADLY_H

#include "conceptrodon/omennivore/concepts/roadly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllRoadly = (... && Roadly<Structures>);

}}

#endif