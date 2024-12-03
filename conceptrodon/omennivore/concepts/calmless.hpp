// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALMLESS_H
#define CONCEPTRODON_OMENNIVORE_CALMLESS_H

#include "conceptrodon/cay.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Calmless = not requires 
{typename Cay<Structure::template Calm>;};

}}

#endif