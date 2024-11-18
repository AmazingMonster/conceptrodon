// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SAILLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_SAILLY_H

#include "conceptrodon/omennivore/concepts/sailly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllSailly = (... && Sailly<Structures>);

}}

#endif