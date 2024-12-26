/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct FoldLeft
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables>
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Initiator, Variable>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
            {
                static constexpr auto value 
                { 
                    Operation<
                    Operation<
                        Initiator, First
                    >::value, Second
                    >::value
                };
            };

            // Recursive Case:

            // Fold twice, handle the first two parameters,
            // and recurse using the rest.
            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {
                static constexpr auto value
                {
                    FoldLeft
                    ::ProtoPage<
                        Operation<
                        Operation<
                            Initiator, First
                        >::value, Second
                        >::value
                    >::template Page<Others...>
                    ::value
                };
            };
        };

        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldLeft<Subtract>::Page<1>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3, 4, 3>::value == -9);