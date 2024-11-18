// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_COOLLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_COOLLY_H

#include "conceptrodon/omennivore/concepts/coolly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllCoolly = (... && Coolly<Structures>);

}}

#endif