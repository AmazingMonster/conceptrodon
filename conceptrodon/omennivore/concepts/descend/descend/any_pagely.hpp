// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PAGELY_H
#define CONCEPTRODON_OMENNIVORE_ANY_PAGELY_H

#include "conceptrodon/omennivore/concepts/descend/all_pagely.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyPagely = (... || Pagely<Structures>);

template<typename...Args>
concept AnyPagely
=   JustAnyPagely<Args...>
||  AllPagely<Args...>;

}}

#endif