/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class...Predicates>
struct Situational
{
    // Primary template will only be selected
    // when no specialization is available.
    // In our case, it is when
    // (...&&Predicates<IfTrue, IfFalse, Others...>::value) evaluates to false.
    template<typename IfTrue, typename IfFalse, typename...Others>
    struct ProtoMold
    { using type = IfFalse; };

    // This partial specialization will be selected
    // if (...&&Predicates<IfTrue, IfFalse, Others...>::value) is true.
    template<typename IfTrue, typename IfFalse, typename...Others>
    requires (...&&Predicates<IfTrue, IfFalse, Others...>::value)
    struct ProtoMold<IfTrue, IfFalse, Others...> 
    { using type = IfTrue; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** SumLessThanTen ****/
// `SumLessThanTen` is the predicate
// that we will pass to `Situational`.
template<typename Initiator, typename...Args>
struct SumLessThanTen
{
    static constexpr bool value
    {(Initiator::value+...+Args::value) < 10};
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Situational<SumLessThanTen>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 1>
>);

static_assert(std::same_as<
    Metafunction
    <
        std::integral_constant<int, 10>,
        std::integral_constant<int, 2>
    >::type,
    std::integral_constant<int, 2>
>);