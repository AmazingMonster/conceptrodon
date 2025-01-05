// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_TYPICAL_H
#define CONCEPTRODON_OMENNIVORE_ALL_TYPICAL_H

#include "conceptrodon/omennivore/concepts/typical.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllTypical = (... && Typical<Structures>);

}}

#endif