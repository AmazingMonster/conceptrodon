/************************/
/**** Implementation ****/
/************************/

template<typename>
struct ExtendBack {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendBack<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<PreexistingElements..., NewElements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ExtendBack<Capsule<int, int*>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, void, void*>;

/**** Result ****/
using Result = Metafunction<void, void*>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
