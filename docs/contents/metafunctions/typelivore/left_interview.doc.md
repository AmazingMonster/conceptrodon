<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::LeftInterview`

## Description

`Typelivore::LeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

<pre><code>   Arguments...
-> LeftSides...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
LeftInterview ::   typename...
                -> typename...
                -> template<typename...> class...
                -> auto
```

## Structure

```C++
template<typename...>
struct LeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = LeftInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

We will implement `LeftInterview` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct LeftInterview
{
    template<typename...>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        { static constexpr auto value {-1}; };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First>
struct LeftInterview<First>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};

template<typename First, typename Second, typename...Others>
struct LeftInterview<First, Second, Others...>
{
    template<typename...LeftSides>
    struct ProtoMold
    {
        template<template<typename...> class...Predicates>
        struct ProtoRoad
        {   
            static constexpr auto value 
            {
                []() -> std::make_signed_t<size_t>
                {
                    if constexpr 
                    ((...&&Predicates<LeftSides..., First>::value))
                    { return 0; }

                    else if constexpr 
                    ((...&&Predicates<LeftSides..., Second>::value))
                    { return 1; }

                    else if constexpr
                    (
                        LeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value != -1
                    )
                    { 
                        return 2 + LeftInterview<Others...>
                        ::template Mold<LeftSides...>
                        ::template Road<Predicates...>
                        ::value; 
                    }

                    else
                    { return -1; }
                }()
            };
        };

        template<template<typename...> class...Agreements>
        using Road = ProtoRoad<Agreements...>;
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSUqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxidIKjc2tuR3j/YNlFaMAlLaoXsTI7BzmAMzhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2fI4%2BhYVHcPzyeBEwLGSBmBpzcBGuyUYrEwADokf8nuNiF4HEcQpgqAQAJKCeIANzwmAA7gCTAB2KxPI70o7A0HgzCQ6Gw5hsJEIlGPBlHNEYghHZTEVBEACynnQAP51NpfP5DKZYKYELOKpZbJhcK5yJ22COByYCgU3NFmHwomBCl5SoZgsxovFqAASqgmDK6faTjSBY1HMgjQJxphVMliEcmBdUEciWIvO95QBaLjUgAipwsvszOwVsp9mrVrI1INV6qhOs5iP1huNpu5j2AxEwIMYBFtBoL9q86SMR3dno%2B6ZFYqIg5lZybLbbgjNtaz3Zzi6eS6LFfZuprCMexGAnfu3vpvfCwCOUto6GHo5dF8nbl3%2B%2B5/zzlKpufzQLLWo1VfhRwAMTwYhxl5R1hWxXECWBYgSXJSEgJAgheXlNdv2LbUOXhblIOEPAsAPJdwJvSVpSXVCjyVdcSyhdCNz/PUeQNI0DAbJELStYtCMo/liOdccPS9RV7XlBklx9f01TwIM0AYUNw0jaMiDjBMkx4n0KOEiSlRMfwrH8dMICWI5kzuf10BAEAWCYABrTAAH10mACJ0Hs5CznSAAvBz3MPLTtLEmlxICpU8CoYM5OBBSTnUkKGSgZ8zAANnMJKOOkrjIVwoR8MwecEVIQDgNAg1LPjbxMCWJZgri%2BlRJbAh1gYI4NCzZdV1i2quiUGravqzBGuIZrUzajNeokjMjPGwKP16sbXw6/zlTomjqMwrdn2Y%2Bt8unVs2DnO0fRPfsJ2vfi3UEyFdtnDtNvuBatPmz8tLW38sMYx9uK046zzvM6x1QO8rr3fKX3zd8V0BR5Xsrd73kQ8ZCs3asjiEWoBHQJGGO3AB5AgEHiL7iNw6DiVJCkzgRghCrR2TMaOPGCZAu63wVfkYeR7CkWy3Kvt4gh0SdAGgcozSJI5lb1urO6WJNfL0utPLDvtPiAYnOa/Tqzr%2BakmSQyiiMoxjFSKpipaRKC7WNL03TDOM0zmO%2BSzrLsxy8Gcy03MhLyfOVvrLfN2qwoi%2BTDemgKEuRZLUoVzKzh5gjuUKqm7jK1SqvD7T%2BsG5rWrzdqodqn1uveYPZNDyNM4kyOeWj5LY5tLKcTwxOkRp9GGEnbA04qjOrYC7OmqONN87Gxai/tEujjL/WwwjKufQgBeApJwlYPJyFGcJln%2B9qyzqPPMj4%2BbnLW6YvyJ%2B0/eVoHS6zgbvKd8Dy%2Be8TI4wDAU4RxG3eJOq3%2BNJ%2BmXtpBqQ8zAnEsFiZupN17wTOFvZmC4AEBWvsyYsh9LxN1xKfR%2BSDn4T1QeWd46t74tk4jaJ%2Bl8JKvxLNmYBcoIbjyofSEu9DArZlAUNEyI86GMPwRbO2mcnoa1mkw%2B0Es0H0ThjLbajZmx7XbHzI6fYzynS/iRC6norryJuqDLsD0GGiMLstSRq1saNhBn7H6GCrzqPOkDKcIMWYPWEU8AA9AAKi8d4nxbiASeK8QAFWwEIQJ3i/HuJ8VEjxESoYvAYAcLwxxIQXDoDcFCX5TFSy5juSxXYnjWIlANJgVAvAJJ6NeVeME4IUzcOEam09BAeMKvUrxLSmkeN5JZBxD4nELhcaiAM0l7Jy3iMhJ4EAimNFKeUzIkJWmdNKiAEhbgnYgDwAoRy8JU4gHKm/L%2B6izDVQerMQMIzTRjIBJM4pMy6gCEhESVA%2BEdkrLWRsrZbAdl7KTDsXM38uDHIsBwFYtBOD%2BF4H4bgvBUCcDcNYawAo1gbCTGYHYPBSAEE0MClYNkAhUgRDsAAHElKkOwSUaCJaSgAnDsfQnBJC8BYBIDQGhSCQq0KQGFHBeAKBAKyzFHAtArDgLAGAiAQBrAIMkC45BKBoFBHQeIkR4ScFUMS5MSVJBHGAMgIMUgERmF4JaQgJB8J6H4IIEQYh2BJAtfIJQagsWkF0FwUgZJiBMGSJwHgIKwUQqdVynGFxpXClQOFNVSUNVap1XqyQBqjgQA8Aq%2BgldUUAt4AKoVpAIBIHlckRVZAKAQDzQWkAwApBmD4HQGCvKIAxCdTEcITRrjet4I25gxBrg4xiNoWoAr0Xyv2gQHGDBaAtsFbwLAMQvDADcGIWgvKoWkCwNZIw4gJ3LuAn2vARI8pOrDLUC4Wx0X1K6E6q4MQPWdo8FgJ1As8BMqXbu4gMQ0iYHTCCQwwArhGCxSsKgBh9wADVyY4w5K2mQlrRDiFtbIRQKh1AbpdfoL9KB4WWH0HgGIvLIArFQMkHoi7kzfC/qYSw1gzActQM%2B4gvN4ArBqHcvwEBXBTD8K60I4QhjlBGK6goGQBBsb0Pxno8xhiVE6N0eoEwWieDaHoRjPQ%2BjNDEzxiTsxJhydyK6jTAwuMLF4wxpFmwJC%2Bo4OCtlAbOBHAjVG7Vurh5xvARAXAJrU1oqWBmv9KwCaehGEZUguLJA7ARDSqkkgNCSDMJIJKLL/BJSpXSjgDLSBMrRQiJKXAkqEqpYSrL/hJBcH8DSpKlmN1cp5XyjFf7s1ipzRK4NMqi0lpTcqtgnAmgsCJFSZMTBZb9i4FShEXAEQcuNUQWjFlXV2qtTB6Qdr4OOqQyASt7rPWtrMxZ9l0LOBBqlRcI4YaozEC6z1vrxoBtDZGxoBNSb80pogTsI5XmJ3CtzagZN8RZXFo%2B/dkYnXuvJgu%2BWqlXBWU0FoDWyg9aN3tubRBuHnbu29ocBBwd7YR1jqdVOmdc7aALogyur966OX4BbHUXdi6xuqEPcCCDp7QUbovVe64N6tgcvvY%2B9Fz7X1KA/au79p4asAaYMB0D4Gl0zegza%2BbcGHWIY5boStBhf1kasBhi9OGAv4cI5wYjBBJzpjVxRqjNG6O4ck9u5wLHO5CY453VTiw%2BNpAE1kLT7GUgu9E/p8TCmuhW96DJu3lumPKb06UX3Omg/u4UzJx3hnVjrBMwCpLW2rMcGO6d3r/WzyDeG6NhNrmJuPfTdV17PnMB%2BYSAFxnKW0tDci1SYrVJSVRZi4VsrVHOCVf5TVkV4rJUhu%2By1pVKqOCdc1UcFgCgiRBiJHnlk4wjX4Am2a6bshZsy8g/ahDTrdC0rW16qFm3/Xld2410N4UJ9aun7PuMC%2BuLCkTb9gtj2diebL1m%2BrI/C1ypfym3ZZAZIZIeyefKleyRfAgEZE7TVKtSHQmaHBtJtTtBHZArtHtPtNHD7IdTHcdUnTAadWdedRddFInNddnSdLdCnPdDdA9ZAI9enQkRnDlZnZtNnO9WjLnXgHnN9fnYnIXV7PgQDBQEDckMDRgCDKXa1CQWXQQRbBXHQEAWlFXYwdDGwTXejTlAjTIRdNxJ2Y3SwSjaFM3AiTQxTTIFwW3GPe3dAePCTETTIYPBw4oH3NTP3KTAQMPYPcwzwuPVwp3WwaPHID3XTOw0zRPZFcIxnNPM/DPa/KfGfOfB/G0J/IvEgEvD/TNbFUgXzLAavMzOvFbIbHYHYQISLMHClHYKkbLTvHbblWwKrLIqqQLEAKLDLLgJ7JKJ7KlTLZKDQKkJLHYU/LveoposzQ1WozlbvT/bI59dIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/typelivore/left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/left_interview.test.hpp)
