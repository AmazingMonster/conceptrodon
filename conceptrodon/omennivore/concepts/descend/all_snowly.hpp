// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SNOWLY_H
#define CONCEPTRODON_OMENNIVORE_ALL_SNOWLY_H

#include "conceptrodon/omennivore/concepts/snowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept AllSnowly = (... && Snowly<Structures>);

}}

#endif