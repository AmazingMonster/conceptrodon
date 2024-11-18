// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_CALMLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_CALMLY_H

#include "conceptrodon/omennivore/concepts/descend/all_calmly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyCalmly = (... || Calmly<Structures>);

template<typename...Args>
concept AnyCalmly
=   JustAnyCalmly<Args...>
||  AllCalmly<Args...>;

}}

#endif