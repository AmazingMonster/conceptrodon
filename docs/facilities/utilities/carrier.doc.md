<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Carrier`

<p style='text-align: right;'><a href="../utilities.md#carrier">To Index</a></p>

## Description

`Carrier` accepts a list of sequences and returns a function.
When invoked by an operation, the function instantiates the operation with the sequences.

<pre><code>   Seqs...
-> Oper
-> Oper&lt;Seqs...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the sequences.

<pre><code>size() -> sizeof...(Sequences)</code></pre>

## Type Signature

```Haskell
Carrier
 :: template<auto...> class...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class...>
struct Carrier
{
    static constexpr auto size() -> size_t;

    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We will create a `Carrier` with sequences `Sequence_0, Sequence_1, Sequence_2, Sequence_3`.
Then, we will transport the sequences to `Operation`.

```C++
/**** Items ****/
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** Result ****/
using Result = PackedCarrier::Sail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Carrier`.

```C++
static_assert(PackedCarrier::size() == 4);
```

## Implementation

```C++
template<template<auto...> class...Sequences>
struct Carrier
{
    static constexpr size_t size()
    { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Sail = Detail<Stockrooms...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGymF4iAA6QWo26QpgKBSC/lCTAARy8rw%2BqJBE2IXgctzcrWI72I6MSViutyNtzmjmQIoEE0wqjSxBNeAAXpgAPoEe1OiDLEHGmH627ETAEDYMd2YVBUSUQaVyhUKL0BCy%2B%2B70y4%2BjnErls9Ms7lw7OZuG8gVCgLYEUGcWS4Wi8W3ZqoZAAa2IqFQLCVhuNKrVbseLTovsTXiyRluBAAns8YQF7nWiE2W222dH5QwthKS2iE0nYQbgZ2jfnWXmmRnj%2BzTzmeXzUFXS%2BWxRv%2BdWK0/6wvWywFB3U8bh%2BFgDrJgB1hWc%2B2A2hl3nZtPyfVEQBACdnl3PVkwTFNMVpE5qTuAAxPBiAmW5sFUVhiUwSkcQxLCASBdEwQhKEKLZNA1yeAhv1LDCjgJDlPm%2BEEj1zTUbzvNErm7dUVwVZ0NBQq5BMvAsROLZ8uIkghVSk2VVy2Z0uHk/dLiE69VJ/SS3WktjnTMQzFM5c8i1vTdlU0ns6x0mSAjs34eIAeWeYhyRySi6QZJTzxMwtRM3B9KxcjStLdAL4mCgQfOuHjlCYJtMHQW4ADUPjsUKgX/Udsty9wtR1adZ01YhtXidE4W9Y0rL0jRSBhA8PJjayuG6tqjQ6l0zCG3rRudbyFK49CFN8u4hC8NI0iUdAACUPi8Wg3QEq5ysA5bVsyPKtoUHa3VA24UqCxoWrcYa%2Bt0l0up638Rs8gaJo%2B56ZPG96fSmmbgTmvdqLuc7LtKkFDtuKHdrq25KsbPKGqahIQCECC2VutKGCVeajLxAAVD49qpVzguQZ1H3iAgIERBCFFYF0xTZBGCG647ijO7bdtReNwcWmjThwg4PNY/KSLI%2BgYZF0XARTU08Bpum2ggFG0Zq0YQCyD1ljq67JCFjhVloThkl4PwOC0UhUE4R7LGsE11k2ZiwR4UgCE0M3VkbEBkkkfkNAADjMMwAE5I64ZIw9DrhEkSaQLY4SReBYCQNC6m27YdjheAUEAup922zdIOBYBgRAQHWAg0j5chKDQIk6HiSJWc4VRQ4ANgAWh7yRbmAZBzSkfkzF4PLCBIPB0D0fhBBEMR2CkGRBEUFR1DL0hdEGgB3IK0k4Hhzct63fftzg/L5Bu3XDW5u/7wfh9H25x7MW4IA8Vv6DtcwAhcGWLwUuWhVgQCQC3NIbcyAUAgFAmBIBgBSHGjQXa8Qi4QBiJfGI4RWjjhPrwXBzBiDjj8jEbQmAHCENIC3UkBA/IMFoAQneWAYheGAJqWgtAi7cF4FgFghhgDiFYQRKhjgABuHxL7WioXybYXtwiMlTnbWgeAYhBVIR4LAl9NJ4Eznw0gUjiAxFOo8QRRg1FGF9qsKgBhgAKAKu8feKUbZe0XsIUQ4g14eM3moS%2Be99BCJQNYaw%2Bh1FF0gKsVAaRGi8L7oiUCphnaWDMHnYx2osCRM9D0cROQXAMHcJ4ToehQjhGGFUUYg1ijZAENMPw1TMi1IYAsEYCRBp2DyQIfoUxikFA6fULpTRJiDHKYsKptgRn1L0HMNorTKntNWAoN2WwJBnw4FbUgudeD50fr3AeQ8R5j2Dp/CAuAZ7/09sA72NjVgIEwEwLACQckB0CPySOARk4aEkGYSQPds7JB7pHfQnB06kEzoA/kPcuA91DpHBOPcg6xw%2BT3LZl986F2Ljcsu4Dq4QNrrfRucCEF/w7mwTgrQWASMSH3JgD5RxcEjvyLgIcp74CIJkheshl7eOkL4pQ/id66HGofJgx8%2BHrM2dsq%2BHAb71z5LcB%2BT8Dn0sAoy5lIcv4/2gX/GEYIzDXNAeXfFJL4hN3gW2HVoxRRGEZVwLqaDGSEUoNgnexD8E0PdaQ8hlDqGGLoYwBhTCWF2zYRwrhPCaECKESI0NYiHB4Ckbwu2sjkDyJoUo%2Bol81EaPwdo7Yds9EGK9sY0xShzExoAjYvg9jHHONcTQjxPLV58tkH47edthVBOsckqwlhwkxGydE2JOR4mJJnL26waSdkZLntIqJuSE3OAgK4aZg0ykVDaXoGpjQ13pCaY0eZSwBm9G6VMvpDTF2NB6aMzdCyZnnvyJe2Zt6KnHqWSs1ekqL4712cql%2BNq1VMpZRoL%2B5yOV6sAYa25pB7mPNGDk1OYKIVMu%2BSkSOScAg/L%2BZIQa0qMW2CxUa3F8B8V1zvua01xAyXbEpS/L8EjzQSPVTmCYbKLlzy5UvLxLb17yAFR2nQIAgiivFafEFGyf152voS%2B%2BVBH70YUIx24zGmWsbdN/S1MDIMBGgziiukCtN/0o0Z0YjHVrOlU86dTzpVCDz4HQJ1mDXV2y9Swr2bmfXiJoQGwQjDmGXzDZwsQkbDHRssQW/h8bJHSJ3qm9NhjM0qN4DmzR45826O1MW3gpazFMkrdY/TdimAOKcZgFxzw3G8CbTxiQraN4CYCcJ7txhQn9pzUO%2B2I7LScB2EzSdqT0nxEyfOnJnSl1%2BBXYUvdG630TJ3TkPdC2yhjK3SeoZN693jevSMo9EyX1bd26t%2B9QC1gbFWad1OUr0WcAU0PBjTGWNciImc9lJBINAJATBuDTzKDrOQyAKO/IAgBGSHHXD2cQeJFhWi39nBMUlxg685I7zE6JGzqHSQMcuDhzMKi1OAQpM7Ph9isB6zJ6w%2BkwXUnfsjEYPyZIIAA)$Done$

## Links

- [Example](../../code/facilities/utilities/carrier/implementation.hpp)
- [Source code](../../../conceptrodon/carrier.hpp)
