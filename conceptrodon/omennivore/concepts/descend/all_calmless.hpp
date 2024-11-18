// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_CALMLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_CALMLESS_H

#include "conceptrodon/omennivore/concepts/calmless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllCalmless = (... && Calmless<Structures>);

}}

#endif