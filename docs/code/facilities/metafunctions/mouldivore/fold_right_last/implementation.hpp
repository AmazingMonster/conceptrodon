/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct FoldRightLast
{
    template<typename...Elements >
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Element, typename Initiator>
    struct Detail<Element, Initiator>
    {
        using type = Operation<Element, Initiator>;
    };

    // Fold twice.
    template<typename First, typename Second, typename Initiator>
    struct Detail<First, Second, Initiator>
    {
        using type
        =   Operation<First,
            Operation<Second,
                Initiator
            >
            >;
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<typename First, typename Second, typename...Others>
    struct Detail<First, Second, Others...>
    {
        using type
        =   Operation<First,
            Operation<Second,
                typename FoldRightLast<Operation>
                ::template Detail<Others...>
                ::type
            >
            >;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -1);