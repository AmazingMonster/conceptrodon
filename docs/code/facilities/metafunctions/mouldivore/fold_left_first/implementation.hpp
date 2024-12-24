/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct FoldLeftFirst
{
    template<typename...Elements>
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Initiator, typename Element>
    struct Detail<Initiator, Element>
    {
        using type = Operation<Initiator, Element>;
    };

    // Fold twice.
    template<typename Initiator, typename First, typename Second>
    struct Detail<Initiator, First, Second>
    {
        using type
        =   Operation<
            Operation<
                Initiator, First
            >, Second
            >;
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<typename Initiator, typename First, typename Second, typename...Others>
    struct Detail<Initiator, First, Second, Others...>
    {
        using type
        = Detail<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::type;
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
    using type = std::integral_constant
    <int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -9);