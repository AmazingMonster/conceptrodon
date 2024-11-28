// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PAGELESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_PAGELESS_H

#include "conceptrodon/omennivore/concepts/descend/all_pageless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyPageless = (... || Pageless<Structures>);

template<typename...Args>
concept AnyPageless
=   JustAnyPageless<Args...>
||  AllPageless<Args...>;

}}

#endif