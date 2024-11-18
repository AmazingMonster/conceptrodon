// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALMLY_H
#define CONCEPTRODON_OMENNIVORE_CALMLY_H

#include "conceptrodon/camellia.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Calmly = requires 
{typename Camellia<Structure::template Calm>;};

}}

#endif