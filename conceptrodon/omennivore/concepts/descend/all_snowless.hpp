// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SNOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_SNOWLESS_H

#include "conceptrodon/omennivore/concepts/snowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllSnowless = (... && Snowless<Structures>);

}}

#endif