// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ROADLESS_H
#define CONCEPTRODON_OMENNIVORE_ROADLESS_H

#include "conceptrodon/legation.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Roadless = not requires 
{typename Legation<Structure::template Road>;};

}}

#endif