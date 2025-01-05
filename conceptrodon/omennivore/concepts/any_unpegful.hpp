// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H

#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/omennivore/concepts/all_unpegful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnpegful
=   Mouldivore::AnyDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllUnpegful<Args...>;

}}

#endif