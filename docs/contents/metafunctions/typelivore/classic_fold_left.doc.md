<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicFoldLeft`

## Description

`Typelivore::ClassicFoldLeft` accepts a list of elements.
Its first layer accepts an initiator and returns a function.
When invoked by an operation, the function left-folds the list using the operation and the initiator.
The type result of the operation is used for continuation.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type
   ..., E<sub>n</sub>&gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeft ::   typename...
                  -> typename...
                  -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct ClassicFoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class>
        alias Road = RESULT;
        
        template<template<typename...> class>
        using UniRoad = RESULT;
    };
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<typename...Args>
using Metafunction 
= ClassicFoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<std::integral_constant<int, 1>>
::Road<Subtract>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `ClassicFoldLeft` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct ClassicFoldLeft {};

// Base Case:

// Fold once.
template<typename Element>
struct ClassicFoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Fold twice.
template<typename First, typename Second>
struct ClassicFoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              typename Operation<
                Initiator, First
              >::type, Second
              >::type;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first two parameters,
// and recurse using the rest.
template<typename First, typename Second, typename...Others>
struct ClassicFoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = ClassicFoldLeft<Others...>
            ::template Mold<
                typename Operation<
                typename Operation<
                    Initiator, First
                >::type, Second
                >::type
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElzBAA6oCoRODB7evgGp6ZkC4ZExLPGJXMm2mPaOAkIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW15nWN9A2UVIwCUtqhexMjsHASYLCkG2yaBbgQAnimMrJgAdDfY9GyCCofYJhoAgmPEXg4A1G4GCgyyAAYp50KFMFQCD8TAB2KywgAihys71ebwA9BifhYmEo/nj2Oj0VifqDaOgfgINld0dtdvtMIdjmcLmwfncdowCM90Z9vtD/nigeTwZCeUdOQ8JS80fD0T9FT96XsmAcjqdzsx2QBJBiZNUkXnvJU/fm/ZTEVBEACyYIVSrhqLeptNKsZzPdaqZGtZ2uuN2eP2QAIUPwA8udiGqssaXa7FeboYjME06A6E06MwmlV4MkZlayYSac6bDoiI1GYwJmXqDUQyBz7tzniAQJqfc7S3DkYFndm3TtVerjkOPb6tZcbrTAthg6Hp29gMRMFzHnHS3mIsAfgAlVBMSnln4ptO0ZlLldrggKaet9uslHZntPtElxVekcd/2L5er6VPLO2ZbgWdoUjCgQVpa1qoGB6AXn%2B163oGQF9sSSKvm8JLYqKyoAO54DSdJjt6np%2BpcZJ4MQYykIWk7skImBoAw8FAe8SZ/KGhGihCULMsCVE0T8jHMaxspYfK77KiRX7kbq%2BqOIaxAbkqHHQba9pSVmUmDgypEajJPosvRAYznOIbCpWCTVgwKkJhxp5MOmOmOpJ8aloqIE7h2xbuR5x6RtZ9S2UcA4ed%2BFGBdGwXMmFHk/HWikNrRAnUTyLndrObYdrRIkCPBGU5veHaYd2GFoW%2Bfm6cORmfrVcmmUGFmAr%2BV4AXZrpeXuB5HpBJ6pk555HJe/7cshZnZY%2BFV%2BS%2B03ZnVZEma1o3rmxfldXBEFQVaGkUghbVjXeqH9uV/bvKSu5MWsGQAG6YASSggMS504WC%2BGEZgtEIIY6D0MqCD3TQaX4agPwpM0lzbNRpDYT8P0/CuyDXfdXUEADCOYGMtLvAtE5svdqVCRFDFMfltHE6Z4ZowkgHiRxQqAtxYK8RKbiEwQuWkyxtFUwD1FHeJ2l%2Bbjxn4wlCl4EpHVqTtsGaTNbmliLysNQL86WVFNkdaaDkDc5VWuV28U/KjRZxa6x4MyKzPisyvM0wL5umtlhk/HBsWFUrDVWdFsahZ7OYUz7Wv%2BwbxtKolkvJZRaVO0VWUPucnOiXHmYJyVAeKsVrv7oedtVjFx3m7NZ1h9JelfoZi342rzXjSNSHa7m%2BY7rnvUVo56bDYhAEC5N5yla5val9V46iz%2BNwN%2B1a2mhtb3Hupct7d3B2PI7c2nc9mIAFS73v%2B8YiSe8ACrYEIx974f537zf29X1haJmIEEQhl4WAQW4zEbCkN5xsRFf1RMj8N45NvZWDWhxIQXhYgEGjA4dCRtPItzokyLSfUxjoDbBEbYy4xAAH1mIzEEMybBtE3hthumILwmAAC0FgKFUJ9C8Dew8t4qyWpPYgwBabog2gNKgXgGAOCyL5S2XEQQ2z4qHHWBBMEgGwZgXBtACECCIazUhPxAjPBhlJDBWDBCKOjMowhTRiFHA0ZIbR2Y9HyIMUolRDA1EkMELRLRM8ILYDbO7YaXDxq8jmu8LqUCUhpCUOgS6CgvC0HSlhdBsj9E4KMQ4px5iXE/BoQATn8aXLqESonQmPDafhgjhE1iODYhR9iTGGHUWkrg/jxJtjbsyKBMC4EykwnyJojhkB4OFAkAgEAbEKEuH0wCbg8nRNyl4EJ6RMDhMxvk54iwUQcGWLQTg/heB%2BA4FoUgqBOBuGsNYM0qx1j3XMIEHgpACCaDWcsAA1gESQVwNCSC4LCQIGh/AaDMAANj%2BWYAAHEC/QnBJC8BYBIDQGhSA7L2QcjgvAFAgFhbc3ZazSBwFgDARAIBVgEBSF4DmFAIBoF2HQBIURLicFUECv5NC/mSB%2BMAZAyAfhSCuGYXg8zCAkDwJgrgMhBAiDEOwKQwr5BKDUHc0gughV4WjCkTgPB1mbO2bKxF4ZiVEuhKgKgPw6UMqZSytlHKXlmB%2BBADwFL6DEBhE/LgixeDoq0MsCASByUpEpWQUlXqfUgGAFIMwfA6BQxRRAWIsrYgRGaCcFVvAY3MGICccMsRtBMXRdc8l0pwwMFoPGjFpAsCxC8MANwYhaAou4LwLALBDDAHEEW/AiNHB3WrXszAqgrrbATeQAxGyi20DwLEaMKaPBYFlbAvAUKa2kDusQWIcyUz1qMMOowdzlhUAMNwgAangTAeFAo7OufwEVohxASrPVKlQ6gi3yv0A2lAxzLD6BHSiyAyxUA/yyNWmhGDyymEsNYMwCKF3EAFZjeAyw7CZqyC4Fikw/BCrCBEQY5RhhCtCUUbInh2h6Gw8FOYQxKhdDgw0cYrQ8N5CFbB0pDBegtGIxh0jMwJjUeQ7YSjzGFhOpWGsDYEg1UcC2XCzVnBDX0sZcy1l7LOWWogLgPl9rLlOpdZu5YANDzDAgI8kAkhAhXAyYEWEkg3lmEkH8mF/g/kZLBRwCFpAoVXKuH8rgfygUZKBe5/w7z/DGb%2BWJotiLkWopuZurFuKPX4p1cS8glB/V2upWwTgzQWA3VhDQpg6sCxcAyVcLgryeX4AbAKvQ17RWXukNexQt7ZW6BDYqpgyqa3CdE/C3gWrYt6oNWljLWWcs7jywV15VqbXertQ6wIZhnXhYxe6z1qBbUJHi2SpbE3hh9cyxZIweWuCwpoNEmmlAo1FqTXGvt52U1pozQ4PtObuR5oLbKktZaK20CrX2utDam17JbXB9tsqu09s2NchRg69nDtHXGidmw9nTtndchdS6lArp%2B9uCL26mB7oPUerUfaKsXvFdV2QtWZX3pACGgwG6gNWFfVDj9un9k/tUZwf9sjAMvosKBzr4HIOM5g7UcjfgICuCQ3oVDpQSMEcKMFcXWHZdZB45hsj9HGNUdyJxujwV1fK9Y5R%2BXXHZhofmJhmDZzBN8cHe18THA4bEHS5l7LO2hv5cKxoK1SmGxTbU3Nt1mnMDacSEzwdjnnP5bebCfzsJPmSAs0yoVHX9mcFC2iiL2K8UEt1atxLVKaUcDSyalgCgbrspusNxkYxivKbK0KwnYqJAk8EGTu9ezdDBCay11V9mbfBc4NqwlxKqS9Yd0XkvZeK/ejGGN9bPqpuBFm66zF0Xc%2B%2BoS7Pu1IBS8hLweXjJeDK8ED6aP6rYbjuRujbGlNl2r%2BpvTZm%2B7S3c35sLX9zApby2Vurdc77a64e1qogBygyLWByRl7TnXB1lShzHROFhynQg0R14GR2XR2HRw3Xmz4B3QUH3UPWPQJ1kEq2J0lRb3qxAGCGp2MC5zfViAF2Z2CmrQxD0VpxAzAwSAgywFoO13g1F0Qw4wlxYj1xlwyDlz4IV2EKVxN2l1oyFzVwN1ENVx1240kJYz0DYw13w1oyUKlxUL4wUAt3FTaw1T7zt0L2ZWL1Lx%2BD3yuEP09xKxIB90Xw01IC0ywGD2EzD0p3y0CECH8B%2BXeRhW8NhA8yCwRRT1sDCyX0WD00kH8CM38CBX%2BQyUkAyU%2BRM2qEHUCCMNCKRT93uXs25RCM6zCMiOWAXQyGcEkCAA)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_fold_left.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/classic_fold_left.test.hpp)
