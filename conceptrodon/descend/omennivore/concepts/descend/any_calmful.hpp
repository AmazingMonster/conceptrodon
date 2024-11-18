// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_calmful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyCalmful = (... || IsCalmful<Args>::value);

template<typename...Args>
concept AnyCalmful
=   JustAnyCalmful<Args...>
||  AllCalmful<Args...>;

}}

#endif