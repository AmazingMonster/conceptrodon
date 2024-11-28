// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_COOLLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_COOLLESS_H

#include "conceptrodon/omennivore/concepts/coolless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllCoolless = (... && Coolless<Structures>);

}}

#endif