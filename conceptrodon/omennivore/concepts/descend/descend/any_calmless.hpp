// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_CALMLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_CALMLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_calmless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyCalmless = (... || Calmless<Structures>);

template<typename...Args>
concept AnyCalmless
=   JustAnyCalmless<Args...>
||  AllCalmless<Args...>;

}}

#endif