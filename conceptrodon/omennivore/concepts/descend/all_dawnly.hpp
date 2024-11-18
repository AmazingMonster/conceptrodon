// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_DAWNLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_DAWNLY_H

#include "conceptrodon/omennivore/concepts/dawnly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllDawnly = (... && Dawnly<Structures>);

}}

#endif