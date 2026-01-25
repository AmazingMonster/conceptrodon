// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_PAGEFUL_H

#include "conceptrodon/metafunctions/omennivore/is_pageful.hpp"
#include "conceptrodon/concepts/mouldivore/passed.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Pageful = Mouldivore::Passed<IsPageful, Arg>;

}}

#endif