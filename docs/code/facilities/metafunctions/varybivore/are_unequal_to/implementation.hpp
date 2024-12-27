/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreUnequalTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr auto value
        { (...&&(Variables < Target || Target < Variables)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Variables < Target || Target < Variables)) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreUnequalTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(! Metafunction<1, 1.0>::value);
static_assert(Metafunction<0, 2, 3>::value);