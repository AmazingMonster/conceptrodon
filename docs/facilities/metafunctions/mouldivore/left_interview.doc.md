<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-left-interview">To Index</a></p>

## Description

`Mouldivore::LeftInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Es..., Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Es..., Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Es..., Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
LeftInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct LeftInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
/****  Metafunction ****/
template<typename...Args>
using Metafunction = LeftInterview<std::is_same>
::Mold<Args...>;

/**** Tests ****/
static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

`Mouldivore::LeftInterview` is implemented based on `Typelivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<typename...> class...Predicates>
struct LeftInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Typelivore::SensibleLeftInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template ProtoMold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQSkkEADqgKhE4MHt6%2BASlpGQJhEdEscQlSQXaYDplCBEzEBNk%2BfoG2mPaOAvWNBMVRsfGJVQ1NLbntCmP94YNlw5UAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYya6MyHiYCjeHZ5fXJ39H3wu5yBZgAzOFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GB5nBDEhXmhsLcyGm6CwVGxuJ%2BhxuABUkZ08AA3EjsEBCRjpGL0EKYKgEACSgniLLeAHdPgdAcw2ApkkxNgymbRWeyYQB2KyXYEETAsZIGfUkxFPOWYAB01upl2mxC8DhuXIYPL5AuFouI4swEtx2uBNyDN31huNmFNBqNTBNcLNjFYVptoOwN0hTAUCmtluUxEw%2BFE%2BqxKcDwftjoIN1zqCIACVUEx0KWgyYA5dgx2Q1Hw6amRbs7aLp2y2iK1XiDXUABZTxN9vDrUWG7TGN4ZBpgTTTCqZLEG5MLxEG4ssReTCLgC0XFbd1hS5vd5pQ4XoejsfhfcT2YuwDzBsYBDFji87Dl46RGDcM60OgMKgnc46TlBTZwj%2Bf5sIIWbJjioI6s%2BLaareOFPh2r49nG3YxhGcafmwA4pmmBiZtmub5mulFAc2NxgeEwA3PWjawfB1Z1g2yFuCxBbsXR2G4Q%2BRG6pcpGUb25qJjcABieDENMg7lk6Lpupg/KCiK%2BrepKJKadpBCDq2uEkRR75KU5NFJpa2IMRmmE5nmklFoOHZ6ZWwmoPxc54YunEOWGynUaptHWsZwh4FgHEgZ2QUIUQSFRcGdl5elC7Lg0jjrmgrr6jue4HkeJ7eOeuXDnZjVFTCACsVhtXcEBLDcF4eeSIAgCwTAANaYMi6TABE6CoiS6QAF4TTZJaFa1%2BH2etrV4FQG4Vduu4wmtW3BlAA5mP45j%2BBJbH%2BXCSVCCl7zZqQGlaTpKZDXVZ5LEsLUnfleYEOsDA3Bod5areCkRSdHadEo/1bYDmDA8QoNXhDD7Ha1N49Yj%2BGEZtTUEY%2B0NFc5VEfvFbmoZg/4YQFC7cRBSGCVl06ziStP04B0mkxFcmyelFORjFLnU9JnlMda3PoYBjNBszvFhWzIVhVzv503L3nUvJQIk3reqOZT8YWm91mvabalcuV6CW652YAPIEAg8RpRcmUGXgvJGR6plihZcJWdMr02wIds3M7rvaXzupthFIvkWLJsO1hUveTdhbvArxUOk6auiZxzXY4nVMJglloPU97tFZlIU5dj%2BUttjgUlWue1blV%2B6Hqgx6ng1Ld5fHsN5R1JhdT1fUDQQ6BDSN42TXg035nNcKLctOcA8PI%2BdjtHeVYd%2BOtWdNoXVdmfsSSVepS95sfdgX3979R9FcjqOg%2BDOGQ8RO9w7QSg3D3uVTuh9B7rRPu5M%2BF0L53TcNfZ61pQ41HDtiR%2B9Vn5gJxtqG4QMQY3GvF/LGQJMFFXhueIBm4D7EBfguCAND1pex9klf25lfQkijm7WOMNf7BiGhTPihc4QwIQe5Va3CeE3D4cbSCnN7oekejfLC9DWpoLPDcMAYBYTwQxiQhcf1dHE3vAY1quC0Y3DMDCSwzpuTe3dCZL0Po/Rwg4THJRxiipSOTgIxsJJhE6zERI4cni3znhynIwUCiRGb0CaoqiRjxGwyIcov%2BCN3FDyXKY9GBD7wk2MbjfRCSOyCxasUsmL5jYqXLjTTWPMa5M3ArxVmWj2ZhLcLLAC/iZJFwNkLBOFSk4hMqf2NO6ZpaWnaQzAJwYlbeJgs0guPiUI1O1nzQ2PSnxJNpP8bZXxgS/F2DcIUYYeargENKfYgJ9k7P%2BICI2ydRaDLilUyWoyM6%2BVutnMRmVmEOIsnHImXZ7lPOGZaFhji3Y5zrhObKnN0rFwSaXK2FdsD0G1tExWDSZHQTZoyJ4ao2R5iGowuxnozKOJJCi2pXCPEgH4QssSfjqULmCeGFpsi3BgslJwpResinrLKUGRFqdLSUrRVMjFPEsVzLgmy6CFLUUdNWbJflxCrjXIBHsuk2BVCsCNOeXZWz1UXI2WCCEUIGpPNROiTEtlDUHMgijJgVAvAEm6KDA1FwhUSxlsQYA7sZlTkdc611mQ2Y/LJYHNwg0QB4AUJNRMg4hqtIuL6zp/NNW3HpO8QC5zTjAhXKVZEXl4g2UuBAQNDRg21AECScIBB9ioJAK0utr0627FbYIfYHb627Ebd9C1hF4JmD%2BnrAta4i2ZhLcCctQaXXVoYCSNkKVG3NsEN29tgDO0brbb2z6IB%2B2CWaVeEdFgOArFoJwNqvA/AcC0KQVAnA3DWGsMuNYGwGpgh4KQAgmgz0rFGiANqkhLQaAABxmDMAATkg1wNqYHQNcE1JqaQF6OCSF4CwCQGgNCkBvXeh9HBeAKBADhn9t6z2kDgLAGAiAQBrAIMkQ85BKBoENHQeIkREycFUKB/wF5/CSBuMAZA64pCWjMLwViRBiApT0PwQQIgxDsCkDIQQigVDqHI6QXQXBSASnRMkTgPBz2Xuvb%2B%2B9nBHaHkY5WVAu0eN8YE0JkT%2BDgMWIgB4Nj9A9x4i4EsXgZGtArAgEgVjyR2NkAoBAMLEWQDACkGYPgdAzLEYgDEczMRwiNAREZ3gmXmDEARI7GI2gahka/axuWjsGC0By1prAMQvDADcGIf%2BuXSBYBGkYcQ9WtJldZO8cz24aiHi2F%2ButnRzNqhiOiQrHgsDmbRHgTD3BeAsniDENImAHhdeAGqIwv6VhUAMH6gAapKR25p2vyeEKIcQKmbvqbUOZnT%2BhDDGGfZYfQ3tiOQBWKgZIbriMcAvOSLRphLDWDMPh9bxAZOpXgCsao86XAMHcJ4VoehQhzFKOUPQqR0huomH4XTBPCgMAGLjxYHQuh1BmMTvQyO3W9CaJToYFRbD04x7kXTK5Wc4/ZxIJHb7NhC/0KZ3D5mCM3Ac/xwTwnRNuZuBAXAhASCWNBH5gLh2Viu0bMMHqpAAOSFBJaSDoJkMaEkGYJI2G2r%2BEg%2BLtDGGQCa8tP4Lg/hQOQYQ/4IDsHzdBDw7wAjRGSPfsO5RmjIW6PWaY1FmL3nONsE4I0FgLJNQXiYJ5CCXBIOWi4CByT%2BBpOyd0zdxT93pCPaUM9rTuhEv6aYIZ1bJmOBXsl1pgjVmGOHhuHZmXvG5c594nngvIHleefC95jXw7tfkeC6F1AXn4jMei8v6fwx0xGDz1wHDNBaApcoOlrT%2BXsvtbP4V4rpWHDtcqwBartXzMNaay12gbXVsdYNO9nrd78B5lqHW2BzvWG2QFG3awm1QzvWm1mwRHmy2DvSWxWy/Vh02yUB2x/x4kj2OyYDOwuyu0/wrzu2U2r1kCe00zvQbzewOwhysC%2B2m1%2B0NwByB04FBxnnB0%2BwsGhxD1h3h0Gz%2Bxp362cAgFcAZ102xxKEF1JwKCJ25xJ1IDJzdTZwWA5yZzpz6DEMEPnRZ1mEkJUMZy5xyHkL510PmDxz81WHWFFwsNQw72Dwsw4EH0c0E231H3z0Lw0GV1V2kw1y1wjwX110wH1wSEN1Q3Q1IEw1BHzyt01DakgyQ1BGtySEkF03sND1sHD0Cwoyo1o3oxszX0Tw4y4w4DTycxYAUBZHXBZDH3DGmGLzV3hzk1kErxINU3kFrwoJ0Fdz0wM1yzbzsKl0szj1s3szKIqKqJqPYkrA8w3wiw11BH838KC0oyXxX0ixY1mO833WQGSGSGRGqMg2RFqIIGRFUAEyS0PzdmPwyyy0Kwv1uKKxKzKzv2Xyqxqzqz/0wEa2a1a2By/U6x/wQN4H/36yAKG1UBG31AgNFCgN4BgOy3gMWxk2QLWw2y2wwO6ywIXz4BOwUHO19Eu0YGu2aOIMSDaPIJe26IMBoM4O%2BxiEYP%2B0B0yGB22EGloKhxh3iD4IZK0LdVR3RyMKxzR2UPMIUJkMyE0MUMyBFOpzUJ6EMMx1506CEIYB0JlNUIVJ505z6HVLFwUBF2U36LMy704BlzGMqOPEmKLGmO8PV180WKyN%2BlID1ywBCLb3CMwyg0tFBFBDajgxSOwx9M1C9073w04DD1Ix1yNxAEkDajN0Q01Gw1A0kBgy4HAwuid1BGNLDMIyWL/Sdwk1DJD3DLzKdNh3SGcEkCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/left_interview/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/left_interview.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/left_interview.test.hpp)
