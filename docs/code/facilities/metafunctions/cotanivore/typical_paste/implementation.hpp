/************************/
/**** Implementation ****/
/************************/

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <tuple>

/**** Container ****/
template<typename...>
struct Container {};

/**** SupposedResult ****/
using SupposedResult = Container<int, float, float*, double>;

/**** Result ****/
using Result = TypicalPaste
<
    Container<>,
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);