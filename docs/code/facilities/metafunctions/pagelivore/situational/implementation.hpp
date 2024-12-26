/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<auto IfTrue, auto IfFalse, auto...Others>
    struct ProtoPage
    { static constexpr auto value = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<auto IfTrue, auto IfFalse, auto...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoPage<IfTrue, IfFalse, Others...> 
    { static constexpr auto value = IfTrue; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v
    { ProtoPage<Args...>::value };
};

/*****************/
/**** Example ****/
/*****************/

/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<auto Initiator, auto...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator+...+Args) < 10};
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction = Situational<SumLessThanTen>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1, 2>::value == 1);
static_assert(Metafunction<10, 2>::value == 2);