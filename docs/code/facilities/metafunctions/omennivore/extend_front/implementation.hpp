/************************/
/**** Implementation ****/
/************************/

template<typename>
struct ExtendFront {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendFront<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., PreexistingElements...>;
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
using Metafunction = ExtendFront<Capsule<int, int*>>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<void, void*, int, int*>;

/**** Result ****/
using Result = Metafunction<void, void*>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
