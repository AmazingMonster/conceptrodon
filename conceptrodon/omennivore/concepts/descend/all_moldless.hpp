// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_MOLDLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_MOLDLESS_H

#include "conceptrodon/omennivore/concepts/moldless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllMoldless = (... && Moldless<Structures>);

}}

#endif