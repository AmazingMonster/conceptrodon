// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_FLOWLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_FLOWLY_H

#include "conceptrodon/omennivore/concepts/flowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllFlowly = (... && Flowly<Structures>);

}}

#endif