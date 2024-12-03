// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_WILLLESS_H
#define CONCEPTRODON_OMENNIVORE_WILLLESS_H

#include "conceptrodon/wiy.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Willless = not requires 
{typename Wiy<Structure::template Will>;};

}}

#endif