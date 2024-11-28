// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H
#define CONCEPTRODON_TYPELIVORE_IS_DIFFERENT_H

#include <type_traits>

namespace Conceptrodon {
namespace Typelivore {

template<typename Target, typename...Elements>
struct IsDifferent
{ static constexpr bool value
{(...&&(not std::is_same_v<Elements, Target>))}; };

template<typename Target, typename...Elements>
constexpr bool IsDifferent_v 
{(...&&(not std::is_same_v<Elements, Target>))};

}}

#endif