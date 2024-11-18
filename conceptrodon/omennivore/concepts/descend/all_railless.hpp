// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_RAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_RAILLESS_H

#include "conceptrodon/omennivore/concepts/railless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllRailless = (... && Railless<Structures>);

}}

#endif