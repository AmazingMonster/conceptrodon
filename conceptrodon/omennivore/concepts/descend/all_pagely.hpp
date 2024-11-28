// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PAGELY_H
#define CONCEPTRODON_OMENNIVORE_ALL_PAGELY_H

#include "conceptrodon/omennivore/concepts/pagely.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllPagely = (... && Pagely<Structures>);

}}

#endif