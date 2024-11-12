<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicFoldLeftFirst`

## Description

`Typelivore::ClassicFoldLeftFirst` accepts a list of elements and produces a function.
When invoked by an operation, the function left-folds the list with the first element as the initiator.
The type result of the operation is used for continuation.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>..., E<sub>n</sub>
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       E<sub>0</sub>, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
   &gt;::type
   ..., E<sub>n</sub>&gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeftFirst ::  typename...
                      -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct ClassicFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
        
    template<template<typename...> class>
    alias UniRoad = RESULT;
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

template<template<typename...> class...Args>
using Metafunction 
= ClassicFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<Subtract>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `ClassicFoldLeftFirst` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct ClassicFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct ClassicFoldLeftFirst<Initiator, Element>
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

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct ClassicFoldLeftFirst<Initiator, First, Second>
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

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct ClassicFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = ClassicFoldLeftFirst<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuBACeaYysmAB0d9j0bIIKx9gmGgCCE8ReDgDUbgMCiyyAAYp50KFMFQCKC8MQJn8TAB2KzIgAixysn3eHwA9Hi/hYmEoAST2LjcQS/uDaOg/gItjdcbt9odMMdThcrmw/gBJBjZJhEMh/c6XZi8h57RgEV6476/AgAoEg2mQ6Gw%2BETTkCoUi0h/aVPOWBN441G4v7WsV7A7CjknVn2o5O7mS253V5/ZCqv4AeUuxGFOXlnxtf0V/3RmBadCtNpR2I%2BEYjXiyRjF3KR4dT1uO6IDQZDAl1gscwpIhuNsteIBA4sdyYjKMxgWTCetzvZnO7Dt77uud2ZZp9quHH2AxEwMueYZTNvTEWAfwASqgmPSC38Y3HaJzJ9PZwQFMO6w3uVjKRirzjPtT1WKAO54Jksu09t0S6788t4Suio2Ho0tqBCGkBP5CJgaAMOg85RsqgIkmqEJQjCcIIqabh6hWBogZhhpQTBcFmtezY2n2rqnB%2B/ZfjynojtgY7IUWCQlgw84RghO6xkw8a5vmloCamS6Zo2OYLnm26BmxjScp2eZZt%2BvIycGcknApim/vqVb4TqwlSWa9aNoR0ECHBBmpueja3pJSI3u2lLCZRjrUWytFcspDHer6yETlOM4mi8pHCaJK7rpuSKBIWu58fuJyHoFsqnl6RkXpctmtpl96Equ0EbFkABumBkkoIBOfihKPgQL5bIaCCGOg9BiggJU0JhLVHn8aStNcuwIqQVKEo1fzTsgBUlWFLUldOEzMp8LkDl52m4bpEG8hhEzgYOvJEeZ21ecO/oEK1CLwQQPz/EhwKvuqaFaphZY6aKm1gX8e2wYax2nSljFkQpi1OjRVHrd5o6%2BcCrFqaGIV2dxsX8XZSaaYuGYruJKP5tFKrIbdqGaq98mWXmoNQ%2BxRN2VppOqeTGnE1pK3/nhhP0y2aUme9ZmwZjVns9yX0nQkv089ZwMlRFJFuDT6lvI5wlZXLHwA2LvYq3RHpnuD453Ilx7BeadlTRLUUxbx8YJQFeua9gxmXorCsdveABULuu27eJUq7AAq2BCF7rse87bvB4HSs4mYgQRL6XhYFFbgwVsaQnvO77uSDO0lR8B30US52XcqQheLEF1MA4/2hWjSkcvL2MTOg9YRLsU5iAA%2BjBcyCJyjeGh89aFWIXiYAAtBYfcD46ssdg5jsfIDbkuq5oPW8xwITsQwD67iU0ALK8VQXgMA4OQSdu10oXS92E3TcMEPXICN5gze0G3Agd1h3d/FwryDcJdcN4Ij9gzP3bi0TuJwP6BG/gpP%2B98AFPxfgwN%2BXdBCGkkFA3%2Bt9/5NyAQgpB4CUF/EgbDLGNsQASwPOvYWpF7afCmoXNIxRMDoDygoLwtA5Q4lrpg2B2DW4gMMO/AhQ8kjyhoR8I2mBWHsJNn8XeLR96H3Um4Quxdgxl2oTPOYjhkAt2QgkAgEAYEKGuLo4KbgWFsLevQxhzDJGWNeMsLEHBVi0E4P4XgfgOBaFIKgTgbhrDWEjOsTYJVzCBB4KQAgmhnGrAANYBAABw3H8AANgSSkqQ/hkQpMkEkQI2T9CcEkLwFgEgNAaFIJ47xviOC8AUCACpUSvHONIHAWAMBEAgHWAQNIXgwIUAgGgfYdAEhRGuJwVQ6Sh45L%2BMAZAyBP6SBuGYXgTDCAkDwPXVI/BBAiDEOwKQMhBCKBUOoZppBdCpCfMGNInAeAuLcR46JPjOD%2Bj6b05UqAqB/EmSk6ZkhZnzMWcsv4EAPDDPoMQJEEcuDLF4E0rQqwIBICGWkEZZABmovRSAYAUgzB8DoP1epEBYjPNiBEVoZw7m8HJcwYgZx/SxG0NBJpEShkmn9AwWgVLzlYFiF4YAbgxC0HqdwXgWAWCGGAOIXl8IWV4GKqK7xmBVD5V2NS8gADXHnNoHgWIwZ6UeCwM8i6eBSlitIMVYgsRMiYBjJKowuqjDRNWFQAwG8ABqeBMBPhkp4iJOzhCiHEIcwNJy1DPMufoKVKAAmWH0Hq%2BpkBVioCTjkUVQ864FlMJYawZhqlWuIJsyR8BVh2Hlc4CArhph%2BFSGECIwwqijFSMUbIAga16FbY0BYIxEjjHqBWpokx2ieE6HoctR8BD9DaD2ptfbbDDo7eMYds6liwrWBsLYEgHkcHcZU55NSflTJmXMhZUgQUQFwOsqFYTYXwpdasVqm5RgQDiSASQgQbh5ORJIDQkgzCSBSeU1JSRCkcGKaQUp4SbgZLSUkBJXAUn%2BEkFwfweSUn7vOTUupDTIkutaR05FXT3l9PIJQLFkKxlsE4K0FghVkRDyYMxTMXAkg3C4DcZV%2BARSbL0IGvZIbpBhqUBG85uh8XXKYLcsVO691VN4DUt5PS%2BkMm%2BbR%2BjjHmMrlY%2BxzjoLwVoshdCwIZg4V4eaUilFqAIUJDI4M6zhnRjqYY75IwrGuAVJoOwoWlBSXnNpZSjVAX6WMuZQ4DV7LZScu5c8vlAqhW0BFRqiVUqZXePwGNRwirnkqrVdsCJD9tXeN1fqylRrtjeNNeaiJVqbVKHtal5c%2BG3VME9d631EoNX8eDQcoTshw1nO8eJ6Nzqc1WHjSVpNr6fFptfpwTNt9s1xosPmhThbi1TbLQOydfgq2wSXSEWCq7m3pEyG23Io6CgtrO92htiwTsTsaNOkd%2BRa09EHc947865hTEu29n7gw7u9u3RukJIPtVyYPZwP4znNOue02xjjGhQVXpFMZu95nEWPswM%2BxI03tUQag2xjQ2SND%2BAQykVjGhajyZebU2wuGEUtLaZ07pHy7MUdGeMjgtGZksAUIVBZhUdPsgmKs7jGytlHKDfsiQfXjkicGzoEAwRJPSfuWByHWHXkkc%2BWp4gLA%2BcC6FyLh0iIwUOfRcZwIZmmeWZQJbyFHPHejEFwwluwukgt1FwQXRBuckEu8wiXzZKKX0qC2HhlTKWUResxyrlPL0uYH5YK4VoqIkpcdRV8Vcqj7ZfObl8a6qLWFeeSVg1ZxysmqLdV3gtXbUNcdU1izfB3UKC9T6v1XXZACd69LgbkaVcjeMMthNsRNszcaKKvEf8xt5oLQkItWAJ%2BPZyC4fbf29D1oqMD67JQcgHa7TkL747ttPcXZv/tvQp0rqB3O8dF/XsP/mHftdZbglbvXRDp52uOAw/9wCvzoLn8J7jcD7ijhLjejCrbg%2BqQE%2BlgHjjuoTiAGYGxoECTn%2BoEDkoEIEHklwOkphtUpwDho0rAfEihjcB%2BlwIEAkshhHP4BoCkgBmBoED/kQfTnbjuisoQQpsQZjjEpakLGvpIEAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_fold_left_first.hpp)
- [unit test](../../../../tests/unit/typelivore/classic_fold_left_first.test.hpp)
