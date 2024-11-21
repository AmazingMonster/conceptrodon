// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GRITLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_GRITLESS_H

#include "conceptrodon/omennivore/concepts/gritless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllGritless = (... && Gritless<Structures>);

}}

#endif