/************************/
/**** Implementation ****/
/************************/

template<auto Init>
struct AddTo
{
    template<auto...Variables>
    struct ProtoPage
    { 
        static constexpr auto value 
        {(Variables+...+Init)}; 
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr auto Page_v 
    {(Variables+...+Init)}; 
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Variables>
using Metafunction = AddTo<3>::Page<Variables...>;

/**** Test ****/
static_assert(Metafunction<1, 2>::value == 6);
