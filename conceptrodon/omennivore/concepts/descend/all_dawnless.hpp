// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_DAWNLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_DAWNLESS_H

#include "conceptrodon/omennivore/concepts/dawnless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllDawnless = (... && Dawnless<Structures>);

}}

#endif