// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TREK_H
#define CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TREK_H

#include <functional>
#include <map>
#include "conceptrodon/mouldivore/bind_front.hpp"
#include "conceptrodon/mouldivore/trek.hpp"
#include "conceptrodon/mouldivore/bind_back.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace CompositionTests {
namespace TestTrek {




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

template<typename...Elements>
using MakeFunctionAlias = void(Elements...);

SAME_TYPE
(
    Trek<BindBack<MakeFunctionAlias>::Mold<void*, void**>::Mold>
    ::Road<std::function>
    ::Road<BindBack<std::map>::Mold>
    ::Mold<int, int*>
    ::Mold<size_t>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

SAME_TYPE
(
    Trek<BindBack<MakeFunctionAlias>::Mold<void*, void**>::Mold>
    ::Road<std::function>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>

template<typename...Elements>
using MakeMap = 
    Trek<BindBack<MakeFunctionAlias>::Mold<void*, void**>::Mold>
    ::Road<std::function>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<Elements...>;

SAME_TYPE
(
    Trek<MakeMap>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>

template<typename...Elements>
using MakeNestedMap =
    Trek<MakeMap>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<Elements...>;

SAME_TYPE(MakeNestedMap<int, int*>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif