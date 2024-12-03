// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HAILLY_H
#define CONCEPTRODON_OMENNIVORE_HAILLY_H

#include "conceptrodon/hay.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Hailly = requires 
{typename Hay<Structure::template Hail>;};

}}

#endif