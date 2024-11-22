<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IndependentCognateFind`

## Description

`Pagelivore::IndependentCognateFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
IndependentCognateFind ::   template<auto...> class...
                         -> auto...
                         -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct IndependentCognateFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = IndependentCognateFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `IndependentCognateFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct IndependentCognateFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAOyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc8dq8PuNiF4HEcAJIMLDXVmMNqoYDMSEAMXC6DBJkSVg%2BRwlR0h0NhmHhaMx2OpYMlRzpDIIRxJqCIyiYwDl4slIosauajmQuIE40wqlSxDN6BAIBYTAA1rdMjyyXd4ZkAF63Ag4gBuYi8vxNAFouCKACKnU3xxPCo0S6VIlFuBWoI4C4jjUFps30xna3X6uVnfOF5XFk3G4uq2YWq0MG12h05o5h7yRpvG0Uq1UjiUmfxWfxxiBLI5RnGA52uj03L0RdC%2Bs4BoNF96j0cm4f7/d4Khtjv2o5QInmABsd5JZLwFMwVLcNeD1OdvYjSyWR%2BPEcG1JAh1gYI4NETE5EgTD4AMAyU6iUeCEOg00QLAudYx2JMYJQg8YJnfDoITHCAOTMi4OLDNZXldFcw/Ugjm7IRMDQVkmJzIkAHkCAQeIqRpPdJXVMtiB1VA9QNeFGKOVj2PQJjeP4gsbzrYSx1FRsNJHFtn3PSFO2Y%2Bie3DfsdNVQ8BwPCdx2nWd52pR0l3dT08G9DdPzcbdNyE1C0OI49TwM217UC/dr2xMx72ix9yWRV8ZLwAtP2wb8zL/cKCPQzBQOIcDIJwkjUws1CkN%2BYL2IvYgspHSKMTvB9SXiyl4XkgQhS/EAf0wTLrMA4Dcsw7DcNg8FSoQ8qjkq61DLC/rjwgWrj3LSTK3hZSBLUvz/P3dK%2ByOMAwFOOMsOWyV/wW/cG3O0cMPyo4zBOSwtXEitpLOTbVKVHbdpHfaIyg27iqoibAPK4HBry8CYyBvCrs0%2BziIosUdJRkrVRohK6MVDF3mAUkoU5QSAK8TIjC1Ss/lO1apKrNx8cJthBEJH6UzgvDKPGgB6AAqfmBcFoXubBPmBaOAAVV8CAUI5BZFj4xaF5X%2BYV8avgYA4vGOeF2M2VIZd3MEsazbsmV3UTNSZBQJYAd1QMEQCOVIvBiWh9MXEAYlQTwbiq5pBHhJlqZOx6cUPTnUeNxFaNReiiXeYhgBJj4yfCYAjgAWVypgqC8TWGmp5kOXZLBBA8HkEoFVkg5t%2B3d2dOn4UT5PtvZ8a9OQG58SUVoIGz5o84L7J4Q0JigkepidheAHIx2UjTrMf8uc77uCXiAh%2B5zoeHBHs4x6OCfp66nqQ/nrDl9RjgVloTh/F4PwOC0UhUE4NxrGsNU1g2SMzB2HhSAEE0NfFYboAiSAxBoSQXBEg7A0P4DQ0VbxmAABwoP0JwSQvAWASA0GPR%2Bz9X4cF4AoEAY8gFP2vqQOAsAYCIBAGsAgLsCDkEoGgaEdB4iRFYFsVQKDbxRlvJII4wBkCWikBiMwvAnxEGIHgJ0QR%2BCCBEGIdgUgZCCEUCodQlDSC6CCLbB4qROA8BvnfB%2BwCX6cG4uiZhRxUBnj4QIoRIixGHwgU9CAHgOH0AdLsLgSxeAUK0CsCASB2GpE4WQCgEAIlRJAMAKQZg%2BB0EhAWSgMRLExHCC0C4JjeDZOYMQC43EYjaDYhQgB7DmYEG4gwWgeTdFYBiF4YA2ZaC0FIdwXgWBXRGHEE05KFS8AhlfJY20bF0RbAAeESEt9dHuxiA8YpHgsCWPuHgHB3TSCjOIN7JQcYoSGGAO7IwwCVhUAMMnAAangTAttuLsnyRo4QohxDqKUfIJQahLH6P0MclAH9LD6DwDEUhkAVioANtkLpUZAQnVMJYawZhCG7LkVgcFM5ujDOcBAVwUw/BBFCOEIYlQRiFAyFkAQBK9BFCpQweYwwEhBDsDixoEwuR5EJdi3eAg%2BitEZWS5ltgOU0pZRywViwAmrHWJsCQZiOD31IAQ3gRCjhOMEcI0R4iPFXlwIQEgz1/6BMAeclY/EmBYASFisBkgdgYgAJw7ESJIKBZhJC3jwf4W8DqMEcCwaQHB/8MS3i4LeFBDqUFhv8NA/wTrbzKssUQkhZDTWUNCXQsJDDbHolYbE1APiuE8M4C0FgIZEhRiYLiAwFMuAOoxFwSB0j8CyPkXoT5Kj3nSE%2BVon5ujdDJMMUwYx3SFVKpVVYjgNimHonsWeUt5bK3VuOYfetjaNBXm8ZE3xRql5BPOdQ8JBbt3xDzXE3xIAF0VrxEYOtXAx40FoGk0hEBMm6MKbk55H7imlPKQ4Z51TOR1IaZY5prT2mdOeb045Azn74FJLvUZXTn4TOQFM55sy6iWMWcsi4qytjPw2VsgBuz9mYEOX0k56cD2XP1AoW59zHmMGeR2t5aju2yF7To5%2BA7/lnMRVYYFizMWQuhdaTgcKCCdTjAJ5FqL4jorGRCnlDQXCsjFcEVkkryVpEpQ0DTdKGjaeFay3l7L%2BgadMw0flAwSULB07MSYngOh6Ec7Z8oTL5Uyp/l5%2BZ46k2cGYsQMtFaq03oznWhtkC9UtsNf4k1wSQGkAtVaygCqA1BvrVAxIcbkg7EkO6oRQQJ3JtsKmxLGb4BZsYcws9x6oncLYCW4LLiWAKBDJaEMkXZTjGbQa9F7bZCdvYy8rjvyQA7FIEOkdpi/X%2Bd0UQ6ddiHFBZYK19rnXusJXGJu%2BrO7dg7ASwerN57T0xNOwkDrqRUg3C6w6m4PWCDdxa921JAkMlZJycUr9X2SllIqQBgtNTgONLg5gFpbSxCQe2dB/pBGelDMQ2M3RqH0PbMw/M5%2BOHcn4fWXI4jvBSMZHI0c/p1H018CufRu5DynnbNY6oiQHHNHfO4zoCbfHjBApsMJ%2BAomGhdO5ouWTlgUWqrRfIpTWKrPZDU%2B4Zz%2BQiVabs55ilxRsgGb09kYzrm6hsps5ZvXZmbM6/FRZhX3K3Om5WAob%2BcrpV%2BYsQtwLpb1sdZ7FtykmoID6tkUagJ%2B703mswJakYWL5kZZAGYetOwdj%2BAQdAvBsfEjhsTc74hZXyFmtILa/wjr/AoOig6yQDrYHOq4JN%2BZOwneEM4IHkJCqpFp9rxnirKxdmZGcJIIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/independent_cognate_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/independent_cognate_find.test.hpp)
