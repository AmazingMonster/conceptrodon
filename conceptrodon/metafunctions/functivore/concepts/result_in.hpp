// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_RESULT_IN_H
#define CONCEPTRODON_FUNCTIVORE_RESULT_IN_H

#include "conceptrodon/metafunctions/functivore/get_return_type.hpp"
#include <concepts>

namespace Conceptrodon {
namespace Functivore {

template<typename Fun, typename Result>
concept ResultIn
= std::same_as<GetReturnType<Fun>, Result>;

}}

#endif