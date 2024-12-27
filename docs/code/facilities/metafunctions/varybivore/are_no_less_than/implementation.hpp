/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreNoLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target))) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreNoLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<5, 6, 7, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);