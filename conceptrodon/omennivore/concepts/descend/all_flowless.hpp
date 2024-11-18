// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_FLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_FLOWLESS_H

#include "conceptrodon/omennivore/concepts/flowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllFlowless = (... && Flowless<Structures>);

}}

#endif