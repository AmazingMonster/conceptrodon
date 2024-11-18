// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_WILLLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_WILLLESS_H

#include "conceptrodon/omennivore/concepts/willless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllWillless = (... && Willless<Structures>);

}}

#endif