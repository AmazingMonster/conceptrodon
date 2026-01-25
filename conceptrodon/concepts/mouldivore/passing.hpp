// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_PASSING_H
#define CONCEPTRODON_MOULDIVORE_PASSING_H

namespace Conceptrodon {
namespace Mouldivore {

template<typename Element, template<typename...> class Predicate>
concept Passing = static_cast<bool>(Predicate<Element>::value);

}}

#endif