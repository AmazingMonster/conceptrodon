// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_FAKE_H
#define CONCEPTRODON_MOULDIVORE_FAKE_H

namespace Conceptrodon {
namespace Mouldivore {

template<typename Element, template<typename...> class Predicate>
concept Fake = not Predicate<Element>::value;

}}

#endif