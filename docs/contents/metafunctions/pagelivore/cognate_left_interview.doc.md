<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateLeftInterview`

## Description

`Pagelivore::CognateLeftInterview` accepts a list of predicates.
Its first layer accepts a list of variables and returns a function.
When invoked, the function first binds the variables to the front of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Predicates...
-> LeftSides...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
CognateLeftInterview ::   template<auto...> class...
                       -> auto...
                       -> auto...
                       -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateLeftInterview
{
    template<auto...>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;

        template<auto...>
        static constexpr std::make_signed_t<size_t>
        Page_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 2`.

```C++
template<auto I, auto J>
struct Equal
{
    static constexpr bool value
    {I == J};
};

template<auto...Args>
using Metafunction = CognateLeftInterview<Equal>
::Page<Args...>;

static_assert
(Metafunction<2>::Page<0, 1, 2, 2>::value == 2);
static_assert
(Metafunction<-1>::Page<0, 1, 2, 2>::value == -1);
```

## Implementation

`Pagelivore::CognateLeftInterview` is implemented based on `Varybivore::SensibleLeftInterview`. It changes the invocation order of the latter.

```C++
template<template<auto...> class...Predicates>
struct CognateLeftInterview
{
    template<auto...Interviewers>
    struct ProtoPage
    {
        template<auto...Variables>
        using Page = SensibleLeftInterview<Variables...>
        ::template ProtoRail<Predicates...>
        ::template ProtoPage<Interviewers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBJcABykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teZ0TA2FD5SNViQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxezwA9AAqcGg44ANWaN2ieAAbiR2CAhIwMtF6MFMFQCABJQRxBF4TAAd2OENBwMBBEwLBSBlpZzcTEuqAAdJyAc9xsQvA5jmiGBisTj8YTiMSyYCTAB2KzPY5K460%2BmMzDM1UMphM86soic9n3Y6HJgKBSG5TETD4US0hTcp7K468/kEY5W1BEABKTDogOdcoVTudyq16uZ%2Bo5XP8D0VoaVroFnqIyiYwA18YTQZdTUcyBNAnGmFUKWIxyjxwRYi8HyDAFouHKACJnCynWWt/zBgMJlV07W6llsw1PYDWumMAgO2O9hNeDJGD3puv%2BZse4he1BpjPMscTtiCC0xh7ducdrs9rP9tU6jXncN3yMjk8mgzmy3W213mdxkNKhcwmAY5fToT51xTVBQNoZkrRtPA7UwY8jVnM9nhbNsZWeR8h0rAAxPBiHGR0k3dIURUwbFcQJWlJRJUlmQIoiCEdINzxw%2B83A458DVfU0P05ODv3tR1nVIjct2g882OvZ1uL1F92So4Q8CwX9zzEgg%2BWTTdUxXDTlRzJUDITcYdQQwthVpUty0ratvDrWS%2Bxk/8%2B2zABWKx3ObCAVmOetjR%2BEAQBYJgAGtMAAfQyYBwnQSKWPODIAC8osSv83LclzMpy448CoSzixs04nNy5UoENcwADZqqEhCf2ZZShFUpDDVIY4mOI2Ngvs2sVhWEyyo7dtrQITYGGODQ2wvLDXKG5VaiUQaypzUbxv8ptuxm0rMpbXzlsMztMJ2jC0KBOawwHCMFN49l90wScj1EvtAKXHdVwg3Tt30857se6dKtQ4NAyOs72Kup8Hwh3DFONfjkL%2Bw9p2egDF2A6DwIkn0/Rg37xwepHkIBMHQavJ55OHIgOsI8Z2srNE0AYdA6cUgB5AgEDidSeS0t1BXRPBMUosUaKJejGJpgh2oZgRmeOdnOaIwG/2yy7byHCmo2Vt8zWQurEO51zxMgqTr1VhNNcUpqWsNtzja%2B97BqMkqLtMvMLMZoqywrNkqxrRzXdDc2hpMTzQ58vyAtjXN0GC0KIuivBYptBLmRStKUZD%2BUDpy/LCus72c8yiquTMGqy/1hrzmttS2up5j7h6/3%2BqLrL5WONbiAmqatow9CdrKxaPjzz2C/LVu%2BxLo0y9qr96pE6uxWa2vOWl7pZcbkBeswFuB9y1bMDGrvjk29s%2B/O%2BaEyHvKCtHksywnhMIEfzLyMF0VqIlKUGPOBWueVl%2BblgocRAjjWCc8DYAL3vNYB0MPiO0XriZerUTyAL7E3ByxwwBgDOOuRsaClQDWgbtduBDQydwmmYU4lh%2BbCnfsLT%2BtFv7Mj/krVBxCyqwPVh8KS5xK72igYHS%2BxwuGDngT9NwNcUEoQysI9BW9/bTTIefMhQ9lHtwoRtJRR0OGHQjkXU6wNnKk1mm5S2t1EZTlti9NGy4MyY0gggtwlijwALOiDS8pi1ZiM1HAni0YZE6wEndfG/1rGoyAqAsCuCsZQTAXjA8Vi3E9hMf3J4YIIR2NqIiZEwUPCxTvMpUWdEyQUghNSbCfiobcP8dreGn54IGxIrzAU%2BTmC0iKV/cW6Fs7XnMQE4p38uaZ3tluR2ZtemB36YaGExA8BMCFuE0Mr1gLvUxm/IWnSmHi3OLM%2BZizBFAJACAk28S3D8OkZnZ0oj1SxKcYM%2Bi/9UHuL0cdC%2B3jrqUwCXshZ9AlkrKyQ4h2EifkHOeSkzxaSMmUkpBU9JEIAAq2AhAIvKYCaFMLwRwplGYfYDBDheBOMyS4dBbisUqTUm6qBjh4hZlTAAUs07S7psAAEcvBiBlJMzS5kCx32KtEVAng/YOWkvKPE4EYmMtSS8GVNIqlfNHMQYAhsAUAFlD5MCoF4fF9QJoxLaYUkWXTpTnDZRy3Gf5gpOKeMqomQNZpmXzJFXWcQWLPAgBqpo2rdVZGZGYTeTiNDtS4O1MwYbN7b0lWuY4ZgBpnSdQhF15o3WAk9Zqn1PQBDMnwd1EAQaQ1hojXmqNuCYmNnjRYDgaxaCcHcrwPwHAtCkFQJwNw1hrAug2FsOsuKeCkAIJoatawwogHcrKdk/hEhVVlP4GdGgp2zoAJyBFrRwSQvAWASA0MGxtzbW0cF4AoEAwbB1NuraQOAsAYCIBABsAgKRLjkEoGgekdA4gRFYDsVQ076xVUkMcYAyACxSHZGYXg8EiBzNjqG/gggRBiHYFIGQghFAqHUOe0guhQ2kmIEwFInAeA1rrQ2odLbOCs0uI%2B90qACo/qqn%2BgDQGQOSDA8cCAHg330HHn2lYvAz1aDWBAJAr6UjvrIBQCAonxMgGAFIcNNBaC0WPRAaIZH4TMGIDcQjvANOwlZtEbQ3Qz39tfUjVmDBaDacw1gaIXhgAsloLQY93BeBYFCkYcQNnCLGcREhMjJZuiXB2P2sItI13NuuNEPDWmPBYDI1pPAW7XOkARHEQVShmx0kMMAa4Rgh1rCoAYFVUJ6KsxSIwHTKHhCiHEMhuD8glBqDI9h/QOWUAdssPoQWx7IBrFQCkPVLn6w/FwaYSw1gzD7rS8QaD/m%2Bs1DqFkFwTMph%2BFDSEeYZQKh6DSBkPVa3duFD1YMbbSxFu%2BYaLMQ7oauhZoYH0Fop3hiVFsNdzw7Q9BmSe1tl7Eg1gKG7dsf7%2BgSOkD3bwA9xx6OMcA8Bk%2BrGqEQFwIQEg1D/BcD4wOgraxOZMCwPEXypBR2SH8OyFdspJAaEkGYSQVUd3uSqku0H67N0BC4OyKqXAqqJCXYkbn7lJBcHciuqq4OyMHqPSe7H56hM3uE3eqjT7JPSe45%2BtgnBmgsARLKesTAdZLi4Eu9kHPm2QZIKpPQDWEN1ekA1tDzXMO6HDbh/DOniMcHreLzDB7KMPsuMcWjFZiDa91/r00hvjem/Y5xsT3H0dxv4wVy9InUBcbiM%2BqTae48jC1zr%2BsEe5NLq4MGxTynKBqcw3prTVXq83AM0ZhwVWzNTgs1Zsjtn7OOec1V9zOWvPNvwNaHoaWXNm9UEF2kVWwu1DI1FmLNw4s7GbYl5L/aZsZcwFljzuWgLJ6K%2BmBQpWyTlcqyl63tWkN29kA7jDzbndtfy%2BNqwXWou9aJwNobnARsEHQGNzrFgU2kOM2c27%2BAOtQl2fgEArgN2QQTMz2iwr2e2RQ2QH2eQoayBJ2v2iBX2EB92j2rQaB62F2%2BBswCBO2t272uQxB32cwpQf2mO6wmwwOjBa6XuEO5GHAweoeeuBuwERuJu7IGg7GKOUG6OmOSesuuOmA%2BOIwROa6G6pAW6/gxu1OsoIusos6NOdOQu3u%2B6nAUup6yeV6t6961GmequH6X6muIe/6xwLACgCIBYCIAh6o4wEG%2BAUGlusGsgNuV%2B1Wt%2BLW%2BQruBGrmHu7BEuFGSuNGBUWudhDhThVYrhP47oHG2e4m6O/gWOAmF6CulhEmL66R3GW8yAKQKQkULhS6kUbhBALqthdudA5eqm6mYQsIterRWmDexmzeae5mlm1mg%2BmAdmDmYgPeKWfenmy%2BbmPmI%2B/mmGgWyAwW0%2BhIEWvA8%2BsIS%2BCWcya%2BvAG%2B6QW%2B2Wnme%2BsufAxWR%2BZWFWja/aF%2BiGEg1%2BqGTWd%2BOg%2BQBgT%2BAB3W0QYBLag2WQLmwIQUz%2Bk202cQoB8A4BS2zg0Bq2RBegm29BOBGBx2WQsBmBWQ5B52d2eqBBsBmJvQZB2BFBb2/QOJ%2BJ8JFBAOQOSG4RpGPunA3B8RjhzhyR9oqRohaOewEhMugm0hshhOHuihW6Zgxu/g/g7k7k1OJeC6/gsoPOehkOBhtg0uOR/UxOIANOnOXA/gZcWpS6XOZcGgsoLO/gNJ%2Bhh6XJw6LO4GcpnBkh3JqWXMy2kgQAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_left_interview.test.hpp)
