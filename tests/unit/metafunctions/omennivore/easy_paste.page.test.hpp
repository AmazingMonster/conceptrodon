// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_PASTE_PAGE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_EASY_PASTE_PAGE_H

#include <concepts>

#include "conceptrodon/omennivore/easy_paste.hpp"
#include "conceptrodon/carrier.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestEasyPastePage {




/******************************************************************************************************/
template<size_t>
struct Operation
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Operation<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Carrier<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Carrier<Operation<
#define SHEEP_SUFFIX    \
    >::Page>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(EasyPaste<SHEEP_SPROUT(240)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif