// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNTYPICAL_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNTYPICAL_H

#include "conceptrodon/concepts/omennivore/untypical.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllUntypical = (... && Untypical<Structures>);

}}

#endif