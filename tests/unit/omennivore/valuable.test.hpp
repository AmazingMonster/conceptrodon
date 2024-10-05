// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TEST_VALUABLE_H
#define CONCEPTRODON_OMENNIVORE_TEST_VALUABLE_H

#include "conceptrodon/omennivore/concepts/valuable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestValuable {




struct Tester
{
    static constexpr bool value = true;
};


struct Tester_1
{
    static bool value() {return true;};
};


struct Tester_2
{
    using value = int;
};


struct Tester_3
{
    bool value;
};


struct Tester_4
{
    bool const value;
};


VALID(Valuable<Tester>);
INVALID(Valuable<Tester_1>);
INVALID(Valuable<Tester_2>);
INVALID(Valuable<Tester_3>);
INVALID(Valuable<Tester_4>);




}}}

#endif