// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_WILLLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_WILLLY_H

#include "conceptrodon/omennivore/concepts/willly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllWillly = (... && Willly<Structures>);

}}

#endif