// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_RAILLY_H
#define CONCEPTRODON_OMENNIVORE_RAILLY_H

#include "conceptrodon/delegacy.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Railly = requires
{typename Delegacy<Structure::template Rail>;};

}}

#endif