// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PAGELY_H
#define CONCEPTRODON_OMENNIVORE_PAGELY_H

#include "conceptrodon/pay.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Pagely = requires 
{typename Pay<Structure::template Page>;};

}}

#endif