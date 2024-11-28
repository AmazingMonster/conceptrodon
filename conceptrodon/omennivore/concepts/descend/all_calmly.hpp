// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_CALMLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_CALMLY_H

#include "conceptrodon/omennivore/concepts/calmly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllCalmly = (... && Calmly<Structures>);

}}

#endif