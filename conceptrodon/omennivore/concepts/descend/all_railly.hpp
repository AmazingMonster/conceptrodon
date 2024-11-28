// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_RAILLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_RAILLY_H

#include "conceptrodon/omennivore/concepts/railly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllRailly = (... && Railly<Structures>);

}}

#endif