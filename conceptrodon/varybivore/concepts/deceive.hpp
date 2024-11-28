// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_DECEIVE_H
#define CONCEPTRODON_VARYBIVORE_DECEIVE_H

namespace Conceptrodon {
namespace Varybivore {

template<auto Predicate, typename...Elements>
concept Deceive = not Predicate(Elements::value...);

}}

#endif