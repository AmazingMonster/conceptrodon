/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct FoldLeft
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements>
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Initiator, Element>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<
                Operation<
                    Initiator, First
                >, Second
                >;
        };

        // Recursive Case:

        // Fold twice, handle the first two parameters,
        // and recurse using the rest.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            = ProtoMold
            <
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Detail<Others...>::type;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction
= FoldLeft<Subtract>
::Mold<std::integral_constant<int, 1>>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);