/************************/
/**** Implementation ****/
/************************/

template<typename Operation>
struct LaboriousPress
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
        // There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
        // We invoke the corresponding template member of the operation
        // with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
        // We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = LaboriousPress
        <
            // We invoke the corresponding template member of the operation
            // with the extracted pack.
            // Then, we pass the result back to LaboriousPress for further invocations.
            typename Operation::template Mold<Contents...>
        >
        // Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = LaboriousPress<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage 
        {
            struct Slash
            {
                template<auto...>
                struct ProtoPage {};
            };

            template<auto...Agreements>
            using Page = Slash::template ProtoPage<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Operation
::Mold<int>::Page<0>::Page<1>;

/**** Result ****/
using Result = LaboriousPress<Operation>
::Mold<Capsule<int>, Shuttle<0>, Shuttle<1>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);