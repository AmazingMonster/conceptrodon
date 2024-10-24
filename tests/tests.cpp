// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

// #define CONCEPTRODON_TEST_COMPARE_WITH_BOOST

// #include "tests/unit/emissary.test.hpp"
// #include "tests/unit/diplomat.test.hpp"
// #include "tests/unit/delegacy.test.hpp"
// #include "tests/unit/legation.test.hpp"

// #include "tests/unit/mouldivore/bind_back.test.hpp"
// #include "tests/unit/mouldivore/bind_front.test.hpp"
// #include "tests/unit/mouldivore/fold_left_first.test.hpp"
// #include "tests/unit/mouldivore/fold_left_first_2nd.test.hpp"
// #include "tests/unit/mouldivore/fold_right_last.test.hpp"
// #include "tests/unit/mouldivore/fold_right_last_2nd.test.hpp"
// #include "tests/unit/mouldivore/fold_left.test.hpp"
// #include "tests/unit/mouldivore/fold_left_2nd.test.hpp"
// #include "tests/unit/mouldivore/fold_right.test.hpp"
// #include "tests/unit/mouldivore/fold_right_2nd.test.hpp"
// #include "tests/unit/mouldivore/agent.test.hpp"
// #include "tests/unit/mouldivore/conjunction.test.hpp"
// #include "tests/unit/mouldivore/disjunction.test.hpp"
// #include "tests/unit/mouldivore/repeat.test.hpp"
// #include "tests/unit/mouldivore/repeat_2nd.test.hpp"
// #include "tests/unit/mouldivore/left_review.test.hpp"
// #include "tests/unit/mouldivore/left_review_2nd.test.hpp"
// #include "tests/unit/mouldivore/right_review.test.hpp"
// #include "tests/unit/mouldivore/independent_find.test.hpp"
// #include "tests/unit/mouldivore/independent_find_2nd.test.hpp"
// #include "tests/unit/mouldivore/look_for.test.hpp"
// #include "tests/unit/mouldivore/look_for_2nd.test.hpp"
// #include "tests/unit/mouldivore/independent_left_interview.test.hpp"
// #include "tests/unit/mouldivore/independent_left_interview_2nd.test.hpp"
// #include "tests/unit/mouldivore/independent_right_interview.test.hpp"
// #include "tests/unit/mouldivore/sieve.test.hpp"
// #include "tests/unit/mouldivore/among.test.hpp"
// #include "tests/unit/mouldivore/remove.test.hpp"
// #include "tests/unit/mouldivore/insert.test.hpp"
// #include "tests/unit/mouldivore/bind.test.hpp"
// #include "tests/unit/mouldivore/bind_2nd.test.hpp"
// #include "tests/unit/mouldivore/recur.test.hpp"
// #include "tests/unit/mouldivore/filter.test.hpp"
// #include "tests/unit/mouldivore/transform.test.hpp"
// #include "tests/unit/mouldivore/reverse.test.hpp"
// #include "tests/unit/mouldivore/find_2nd.test.hpp"
// #include "tests/unit/mouldivore/left_interview_2nd.test.hpp"
// #include "tests/unit/mouldivore/repack.test.hpp"


// #include "tests/unit/pagelivore/bind_back.test.hpp"
// #include "tests/unit/pagelivore/bind_front.test.hpp"
// #include "tests/unit/pagelivore/fold_left_first.test.hpp"
// #include "tests/unit/pagelivore/fold_right_last.test.hpp"
// #include "tests/unit/pagelivore/fold_right_last_2nd.test.hpp"
// #include "tests/unit/pagelivore/fold_left.test.hpp"
// #include "tests/unit/pagelivore/fold_right.test.hpp"
// #include "tests/unit/pagelivore/fold_right_2nd.test.hpp"
// #include "tests/unit/pagelivore/agent.test.hpp"
// #include "tests/unit/pagelivore/conjunction.test.hpp"
// #include "tests/unit/pagelivore/disjunction.test.hpp"
// #include "tests/unit/pagelivore/repeat.test.hpp"
// #include "tests/unit/pagelivore/repeat_2nd.test.hpp"
// #include "tests/unit/pagelivore/left_review.test.hpp"
// #include "tests/unit/pagelivore/left_review_2nd.test.hpp"
// #include "tests/unit/pagelivore/right_review.test.hpp"
// #include "tests/unit/pagelivore/independent_find_2nd.test.hpp"
// #include "tests/unit/pagelivore/independent_find.test.hpp"
// #include "tests/unit/pagelivore/terse_find.test.hpp"
// #include "tests/unit/pagelivore/terse_find_2nd.test.hpp"
// #include "tests/unit/pagelivore/look_for.test.hpp"
// #include "tests/unit/pagelivore/look_for_2nd.test.hpp"
// #include "tests/unit/pagelivore/independent_left_interview.test.hpp"
// #include "tests/unit/pagelivore/independent_left_interview_2nd.test.hpp"
// #include "tests/unit/pagelivore/independent_right_interview.test.hpp"
// #include "tests/unit/pagelivore/terse_left_interview.test.hpp"
// #include "tests/unit/pagelivore/terse_left_interview_2nd.test.hpp"
// #include "tests/unit/pagelivore/terse_right_interview.test.hpp"
// #include "tests/unit/pagelivore/terse_right_interview_2nd.test.hpp"
// #include "tests/unit/pagelivore/left_interview.test.hpp"
// #include "tests/unit/pagelivore/left_interview_2nd.test.hpp"
// #include "tests/unit/pagelivore/right_interview.test.hpp"
// #include "tests/unit/pagelivore/right_interview_2nd.test.hpp"
// #include "tests/unit/pagelivore/among.test.hpp"
// #include "tests/unit/pagelivore/segment.test.hpp"
// #include "tests/unit/pagelivore/insert.test.hpp"
// #include "tests/unit/pagelivore/bind.test.hpp"

// #include "tests/unit/typelivore/conditional.test.hpp"
// #include "tests/unit/typelivore/among.test.hpp"
// #include "tests/unit/typelivore/find.test.hpp"
// #include "tests/unit/typelivore/find_2nd.test.hpp"
// #include "tests/unit/typelivore/sensible_left_interview.test.hpp"
// #include "tests/unit/typelivore/sensible_left_interview_2nd.test.hpp"
// #include "tests/unit/typelivore/sensible_right_interview.test.hpp"
// #include "tests/unit/typelivore/look_for.test.hpp"
// #include "tests/unit/typelivore/look_for_2nd.test.hpp"
// #include "tests/unit/typelivore/are_distinct.test.hpp"
// #include "tests/unit/typelivore/are_distinct_2nd.test.hpp"
// #include "tests/unit/typelivore/are_distinct_3rd.test.hpp"
// #include "tests/unit/typelivore/left_interview.test.hpp"
// #include "tests/unit/typelivore/left_interview_2nd.test.hpp"
// #include "tests/unit/typelivore/right_interview.test.hpp"
// #include "tests/unit/typelivore/amid.test.hpp"
// #include "tests/unit/typelivore/amidst.test.hpp"
// #include "tests/unit/typelivore/erase.test.hpp"
// #include "tests/unit/typelivore/upend.test.hpp"
// #include "tests/unit/typelivore/flip.test.hpp"
// #include "tests/unit/typelivore/contains.test.hpp"
// #include "tests/unit/typelivore/set_contains.test.hpp"
// #include "tests/unit/typelivore/conjure_set.test.hpp"
// #include "tests/unit/typelivore/make_set.test.hpp"
// #include "tests/unit/typelivore/diversity.test.hpp"
// #include "tests/unit/typelivore/are_unique_2nd.test.hpp"
// #include "tests/unit/typelivore/are_unique_3rd.test.hpp"
// #include "tests/unit/typelivore/reconformed_left_interview.test.hpp"
// #include "tests/unit/typelivore/unconformed_left_interview_2nd.test.hpp"
// #include "tests/unit/typelivore/fold_left_2nd.test.hpp"
// #include "tests/unit/typelivore/fold_left_first_2nd.test.hpp"


// #include "tests/unit/varybivore/conditional.test.hpp"
// #include "tests/unit/varybivore/among.test.hpp"
// #include "tests/unit/varybivore/find.test.hpp"
// #include "tests/unit/varybivore/find_2nd.test.hpp"
// #include "tests/unit/varybivore/sensible_left_interview.test.hpp"
// #include "tests/unit/varybivore/sensible_right_interview.test.hpp"
// #include "tests/unit/varybivore/look_for.test.hpp"
// #include "tests/unit/varybivore/look_for_2nd.test.hpp"
// #include "tests/unit/varybivore/are_distinct.test.hpp"
// #include "tests/unit/varybivore/are_distinct_2nd.test.hpp"
// #include "tests/unit/varybivore/is_same_3rd.test.hpp"
// #include "tests/unit/varybivore/is_same_4th.test.hpp"
// #include "tests/unit/varybivore/is_same_5th.test.hpp"
// #include "tests/unit/varybivore/left_interview.test.hpp"
// #include "tests/unit/varybivore/right_interview.test.hpp"
// #include "tests/unit/varybivore/amidst.test.hpp"
// #include "tests/unit/varybivore/amid.test.hpp"
// #include "tests/unit/varybivore/rise.test.hpp"
// #include "tests/unit/varybivore/fold_left.test.hpp"
// #include "tests/unit/varybivore/fold_left_first.test.hpp"
// #include "tests/unit/varybivore/fold_right.test.hpp"
// #include "tests/unit/varybivore/fold_right_2nd.test.hpp"
// #include "tests/unit/varybivore/contains.test.hpp"
// #include "tests/unit/varybivore/set_contains.test.hpp"
// #include "tests/unit/varybivore/diversity.test.hpp"
// #include "tests/unit/varybivore/are_overlapping.test.hpp"
// #include "tests/unit/varybivore/are_unique.test.hpp"
// #include "tests/unit/varybivore/are_unique_2nd.test.hpp"
// #include "tests/unit/varybivore/are_unique_3rd.test.hpp"
// #include "tests/unit/varybivore/make_set.test.hpp"

// #include "tests/unit/omennivore/among.test.hpp"
// #include "tests/unit/omennivore/among_2nd.test.hpp"
// #include "tests/unit/omennivore/among_3rd.test.hpp"
// #include "tests/unit/omennivore/among_4th.test.hpp"
// #include "tests/unit/omennivore/among_5th.test.hpp"
// #include "tests/unit/omennivore/zip.test.hpp"
// #include "tests/unit/omennivore/zip_2nd.test.hpp"
// #include "tests/unit/omennivore/zip_3rd.test.hpp"
// #include "tests/unit/omennivore/zip_4th.test.hpp"
// #include "tests/unit/omennivore/insert_types.test.hpp"
// #include "tests/unit/omennivore/oust_types.test.hpp"
// #include "tests/unit/omennivore/modify_types.test.hpp"
// #include "tests/unit/omennivore/flatten.test.hpp"

// #include "tests/unit/cotanivore/repack.test.hpp"

#include <cstddef>
template<auto>
struct Decl;

template<auto I>
struct Tester { using type = Tester<I>; };

template<auto I>
struct Tester1 { using type = Tester1<I + 1>; };

template<auto I>
struct Tester2 { using type = Decl<I + 1>; };

template<auto I>
struct Tester3 
{ 
    template<auto...> 
    struct ProtoPage
    { using type = Tester3<I + 1>::template ProtoPage<>::type; };

    template<typename...> 
    struct ProtoMold
    { using type = Tester3<I + 1>::template Mold<>::type; };
};

template<typename Element>
struct Tester4
{ 
    template<auto...> 
    struct ProtoPage
    { using type = typename Element::type; };
};

template<typename Element>
struct Tester5
{
    template<typename...>
    using Mold = Element::type;
};

template<size_t I>
constexpr size_t Tester6 = Tester6<I - 1> + 1;

template<>
constexpr size_t Tester6<0> = 0;

// template<typename>
// struct Tester7
// {
//     using type = Tester7::type;
// };

// template<typename...>
// struct Tester8
// {
//     template<typename...>
//     using Mold = Tester8<>::Mold<>;
// };

// template<typename...>
// struct Tester9: Decl<0>
// {};

template<template<auto...> class...>
struct HoldDecl {};

template<typename...>
struct Tester10: HoldDecl<Decl>
{};





int main()
{ 
    Tester<5> a;
    Tester1<0> b;
    Tester3<0> c;
    Tester4<int> d;
//    Tester5<int> e;

    auto f = Tester6<10>;
    return 0; 
}