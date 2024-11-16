// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GRITLESS_H
#define CONCEPTRODON_OMENNIVORE_GRITLESS_H

#include "conceptrodon/graphite.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Gritless = not requires 
{typename Graphite<Structure::template Grit>;};

}}

#endif