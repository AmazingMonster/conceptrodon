// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H

#include "conceptrodon/metafunctions/mouldivore/concepts/any_deceive.hpp"
#include "conceptrodon/metafunctions/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/all_unpegful.hpp"
#include "conceptrodon/utilities/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnpegful
=   Mouldivore::AnyDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllUnpegful<Args...>;

}}

#endif