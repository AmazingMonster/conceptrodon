// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_MOLDLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_MOLDLY_H

#include "conceptrodon/omennivore/concepts/moldly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllMoldly = (... && Moldly<Structures>);

}}

#endif