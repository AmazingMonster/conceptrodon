namespace Mouldivore {

/**** FoldLeft ****/
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

/**** BindFront ****/
template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};

}

#include "boost/mp11.hpp"

using namespace boost;
using namespace mp11;

struct Subtract
{
    template<typename A, typename B>
    using fn = mp_value<A::value - B::value>;
};

using V = mp_value<1>;

using Arg_0 = mp_value<3>;
using Arg_1 = mp_value<4>;
using Arg_2 = mp_value<3>;

using L = mp_list<Arg_0, Arg_1, Arg_2>;

template<typename...Args>
using BindAnother = Mouldivore::BindFront
<
    Mouldivore::FoldLeft<Subtract::fn>
    ::Mold<V>
    ::Mold
>
::Mold<Args...>;

static_assert(std::same_as<
    BindAnother<Arg_0, Arg_1>::Mold<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);