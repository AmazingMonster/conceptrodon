// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PAGELESS_H
#define CONCEPTRODON_OMENNIVORE_PAGELESS_H

#include "conceptrodon/diplomat.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Pageless = not requires 
{typename Diplomat<Structure::template Page>;};

}}

#endif