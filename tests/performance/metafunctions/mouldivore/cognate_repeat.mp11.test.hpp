// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_REPEAT_2ND_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_REPEAT_2ND_H

#include <concepts>
#include "conceptrodon/mouldivore/cognate_repeat.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateRepeat2nd {




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int, float, double
#define ALKANE_SUFFIX
#define ALKANE_SEPARATOR    \
    ,

using SupposedCapsule = Capsule<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




#ifdef CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedCapsule

SAME_TYPE(boost::mp11::mp_repeat_c<Capsule<int, float, double>, 240>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedCapsule

SAME_TYPE(CognateRepeat<Capsule>::Page<240>::Mold<int, float, double>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#endif

}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif