<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsMoldful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-moldful">To Index</a></p>

## Description

`Omennivore::IsMoldful` accepts a type.
It returns true if the type is a packed `Mold` and returns false if otherwise.

<pre><code>   Type
-> Type == Mold&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsMoldful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsMoldful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsMoldful_v {RESULT};
```

## Examples

```C++
template<typename...>
struct MoldLike;

static_assert(IsMoldful<MoldLike<int, int*>>::value);
static_assert(! IsMoldful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxCAA7KQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSXaYDplCBEzEBNk%2BfgG2mPZFDPWNBCWRMXGJtg1NLbntCmP9YYPlwwkAlLaoXsTI7BwEmCzJBjsmAMxuBACeyYysmMfYJhoAgtPEXg4A1ACSCgCynuhUXlo9weJgSFje0yYjmQbzQDGmmFUyWIb2iqE8bwAbmIvJg3qCLFQxEpQQARY7gskU4HAnZ7A43E50/ZQxmnC5XNgAOh5t1hBgUCjeHkETDmZDe50uzG5POw9DYggUt2Bz1eBE%2BPz%2BAKBJxFDXFxzc8t2jAICh5XJVRzujwJEIa0NhAgRSJRaIx2O8eIJBBeNwS5KOlMD1LtjwA9AAqGOxuPxiPA6Oxt4AFUw0yFccTkfjeezNMezIZRqlnMwlpVjzV71%2BtHQoQA1oyrOGno68MgAPpMQVxAgQL51/6Ao3DptssIEUhvKdR63YEAgL24pZh9tQzs9vtNCBgMCa4c6o1T25LleYNfBjgrWicACsvD8HC0pFQnDc1msELWGx9ZiOHhSAITQbxWRsQHvMwuQSMxJAADng%2B8NAATigjQADZ4KOfROEkXgWAkDQNFIZ9X3fDheAUEASJAl8b1IOBYBgRAQDWAhki8acKAgNA9joOIImuThVHgjCAFoMMkN5gGQGEpC5MxeEwfAiGIPB0D0fhBBEMR2CkGRBEUFR1Ho0hdECAB3YgmGSTgeFvB8n1At9OAAeS4ziNVQKg3lEiSpJkuS3gUsw3ggDx%2BPoFFzEApZeDorQVggJA%2BOSASyB4tKMpAYApDMPg6B2YhqIgaIXOiMJGjOezeEq5hiDONzom0Go6KAvjFQINyGFoGqzKwaIvGANwxFoajuF4LAWEMYBxAGvBiDavBMQzFzERqLitiAqdOhc2g8GiGzGo8LAXL9PBCMm0hVuINElFJXZZoOoxQJWKgDGABQADU8EwSy3OlWrDOEURxAM7T5CUNQXIs/RZpQL9LH0Q7qMgFZUGSboJvE6Z0GOUlTEsawzHI271KwNGIBWapamcCBXAmPxAhCOYygqPQCgyAQmc5tJuYYAZ2eGQJae6Xpxk8Vo9DFuoZiFoZ4lFmZeeVvoFYWJWad/TYJEcjhH1IlyKL8sTJOk2T5MkRTwtwQgSHxACuHi4C3pWBBMCYLB4mp0gIMkI4uRQo4EkkDRJDgjDiPvDCUNwjh8NIQjAK5DCuCwlD4PT%2B8AnvYOMKNsyKKomjXfo5KWJStjPK48hKGy6KhLYThGhYTEEnEph%2BVmkKUK5LguVfFT7YprTZF08HpEh4yYbM3QCus2zav1w2yN4CiPI4ri3h8t5W/bzvu6MXv%2B8H8LIvS6LHaOMwXcShiq4buI6941AouGfeO%2BQAwjC4FCuBIjQWgxVSrlTMvVaqwMIGNWaq1BwwNOpmh6n1Fyg1hqjVoONYG01npbFfPgJatRVoTSHqoTaOxga7TvGZA6R1qqnTwQldSV0gK3XupgR6M0jAvVAOXPgn0fp/QBkDa6kMJ76SnrIGeplXzz3hq9ImVhka0KphjLGmQcZ4wJookmZM4gUzWujDoXRMguAYO4KWuQWbmI1hzfI/NuiqxSA4zItiRbGOWgICWzRLHMw8XTHo8s2aKxlirXxoT1bBM1nrVY6xdbO3jqvY2nA97EDbh3Lu38e5/1PhoW2qkHaxWdglN2pAPZe2GL7ahidk593DgkPOCQEhHAjpIKSgQ16uUorYUu98K7wCruxLyL8n7ECblsVugUWAKExDCTEOSGTTGUgU0egQxFgwkSDaRsMQA4UXnZSaK9nJF3cjXbyvlJnSWmbMrECzWTTHPm/S%2BcRr5HDvm9RiqUnkZRGd86Ky5kDJGSF2eZKEuyLIID2NJUlCrALiKAiqVVGpQKRU1FqbUEFvy6sg/q%2BDMBDRGmNCaQEcHcMYaQAhy1iHrTIcgLalDBB7RoYdY6ZwGHnWYcDNhaQOFPW4WEXhSV%2BFMC%2Br9f6gNGDA3WXpCQkijLQxkToXZ8jjBIxsCo%2BAajsacAjHjRGxNLCk3XuTDShjfay3pozcJ1iGxRLsc4womQnFc26G4pW/jxZhJyH4i1gTImlBCWrSW3qIlNDdTEhQOt9JHMLuRFJly3jXLmXcnYDyIB2zUtfYpZckru09t7Sg%2BsakgDMH3I4Rx7zIQCMRctCQsKxvXpwEutFSn%2BwSIpBpXApAoXqcHLgSRqFHGOXG7pfT9ZKQbV0kp5cVi3XSM4SQQA%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_moldful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_moldful.test.hpp)
