// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_SAME_H
#define CONCEPTRODON_TYPELIVORE_IS_SAME_H

#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename Target, typename...Elements>
struct IsSame
{ static constexpr bool value
{(...&&std::is_same_v<Elements, Target>)}; };

template<typename Target, typename...Elements>
constexpr bool IsSame_v 
{(...&&std::is_same_v<Elements, Target>)};

}}

#endif