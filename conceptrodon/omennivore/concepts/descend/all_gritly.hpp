// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GRITLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_GRITLY_H

#include "conceptrodon/omennivore/concepts/gritly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllGritly = (... && Gritly<Structures>);

}}

#endif