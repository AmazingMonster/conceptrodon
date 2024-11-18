// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_SAILLESS_H

#include "conceptrodon/omennivore/concepts/sailless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllSailless = (... && Sailless<Structures>);

}}

#endif