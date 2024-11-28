// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_HAILLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_HAILLY_H

#include "conceptrodon/omennivore/concepts/hailly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllHailly = (... && Hailly<Structures>);

}}

#endif