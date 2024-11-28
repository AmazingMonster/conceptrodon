// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PAGELESS_H
#define CONCEPTRODON_OMENNIVORE_ALL_PAGELESS_H

#include "conceptrodon/omennivore/concepts/pageless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllPageless = (... && Pageless<Structures>);

}}

#endif