// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_CALMFUL_H

#include "conceptrodon/metafunctions/omennivore/is_calmful.hpp"
#include "conceptrodon/concepts/mouldivore/passed.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Calmful = Mouldivore::Passed<IsCalmful, Arg>;

}}

#endif