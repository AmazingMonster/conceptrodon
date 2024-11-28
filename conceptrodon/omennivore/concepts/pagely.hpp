// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PAGELY_H
#define CONCEPTRODON_OMENNIVORE_PAGELY_H

#include "conceptrodon/diplomat.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Pagely = requires 
{typename Diplomat<Structure::template Page>;};

}}

#endif