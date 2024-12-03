// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_MOLDLESS_H
#define CONCEPTRODON_OMENNIVORE_MOLDLESS_H

#include "conceptrodon/moy.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Moldless = not requires 
{typename Moy<Structure::template Mold>;};

}}

#endif