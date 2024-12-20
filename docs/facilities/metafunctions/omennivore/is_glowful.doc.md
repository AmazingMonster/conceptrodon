<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsGlowful`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-is-glowful">To Index</a></p>

## Description

`Omennivore::IsGlowful` accepts a type.
It returns true if the type is a packed `Glow` and returns false if otherwise.

<pre><code>   Type
-> Type == Glow&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsGlowful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsGlowful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsGlowful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct GlowLike;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct GritLike_1;

static_assert(IsGlowful<GlowLike<GritLike_0, GritLike_1>>::value);
static_assert(! IsGlowful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsGlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class Sunlight,
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Sunshines
>
struct IsGlowful<Sunlight<Sunshines...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKAOK0qADuVC8tDu9xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXmCLFQxEowQARI4QskUkEg7a7fbXB5HNwg15s150vZMA7HTkM5l87nXXk7Lk8k6i/ki%2BlCgWS2W886XNgAOjVN1hBgUCjVKo1yC1OvVh2wmqY2t1%2BsNlpNZotxtNBvNRr1tqd2teQi8DFoeGACAIpFZ7MF4tDwolMrD8ujUYj4YFSuYqoddpdVudNsd1tT7vTbpzruzmbVXvhCDCmAUNJNIKeLwIH2%2BvwBQOZZd9/oI7e9Cgr4Xzt1rTPBkKa0NhAgRSJRaIx2O8eIJBGe10S5MOlPX1KZDwA9AAqI/Hk%2Bnvcgw/H14AFSrBAUrxP5/3p9fT5pDwT0rF8Zjv7jcoAd%2BUqRj%2BiYXMmmBZmm0F5rBhYZvaRYwbmCHDo8K4Nq8Pz/KEADWwpWLu9xfqBIGkRRf6AWBioQVc8ElshcGoYxiGDihRZ1phbxfMQhD4ZgAD6Gg7qCn5UcBCpkVJlFAdJYZJvRLFIWxDEqQWrEaeptwPPWPF8f0eAEYJXCiVx3J4MggnOnEBAQJ8OGtsCxyOQJzK8fxRlCYE2EGQJJk3DcIAgAuuKLKJUKWdZ2q2RAYBgE2jmAs5bhhN2JrBaFmDhZuHDLLQnAAKy8H4HBaKQqCcCyljWJCqzrEuZiHDwpAEJoeXLHhICFWYKqJGYkgAByDYVGgAJw9RoABsg2HPonCSLwLASBogSleVlUcLwCggIEbVlXlpBwLAMCICAqwECkXiBhQEBoLsdBxBEVycKog1TQAtFNkivMAyAwlIKpmLwmD4EQfHoHo/CCCIYjsFIMiCIoKjqAdpC6FwpB/MQTApJwPD5UVJXtRVnAAPLXVdjaoFQrxvZ932/f9ryA2YrwQB4D30Ci5jNYsvD7VoywQEg90pI9ZC3WLEsgMAUhmHwdDbMQO0QNEJPRGEzSnPjvCa8wxCnGT0TaJgDi66Q91sIIZM%2BjraNYNEXjAG4Yi0Dt3C8FgLCGMA4gO3gxBm44mJViTiJm9dmwtWltQk760Q44bHhYCTK54MtnukKHxBokopI7L7vpGO1yxUAYwAKAAangmB/GTEEW9DwiiOICPN8jagkxj%2Bi%2Byg1jWPoeDRDtkDLKgKT1B7H1jOgRykqYNWWGYG05xDYdj10wdZC4DDuJ47R6CElbzMMmOFJkAiTH45/pJfDBzEM8SY3Y28CL0EwH3kL%2B1G/DTjIZMoT89AzE/rkG%2BtgAGPwqGfZYCh6obAkITDgxVSDrV4JtOm70vo/T%2BgDSQQN2a4EICQfETUuD81aqXZYCBMBMCwPECAnV/CHBVGNQ4iQAiSAGlNVahUppjXmhwRapBlrNRVFNLgM0xqDSkYVSQXBCrsKmmgkmm1tq7SoQdYWp0RbnUptdcglBpbc2emwTgzQWCYkSB9JgZojAszGiqLgKpyqgxIRDKGshYZt2kB3JQXc0a6AVtjXGutkGoPQaTDgFNLrXVeDTV4ljrG2PscARxzjXHs05uLbmZDDhmEoYLQ6eiTFxCMXdVAXNhjJJsU6IwXAxpcECDQWgytVbqzRvrbWFtumG2Nqbc2WcraMAILbWg9tyqO2dq7Wg7sLbeyLpsKZgdt6hw9m41QkdtgW1jgVNGCck6nBTssgWfFM4tRznnTABcfZGGLqAbRfAK7V1rvXRuWdm4%2BPhn42QndUblWCb3Eui8rCWCHiPeA49J5ZGnrPeeoLrArwwWvPAWBR5MK3g4HeEBXDXyPnvaBCxb5FCyPikl98iVnyxfUD%2BrQv4QNfti9%2BUCT7AJfgA8lkDZhspgc/OBCD4YROJmjTBtTUn1PSY0zJGgiFg1IbzChAtqGkFofQ4YmL9kiLEU4jQkhEhKMSIkQ43DJDfUxlE9RthNHFJ0fAPRF0qYVLKcQMxmxLGMxYAoTEMJMTSoZGMEG8rPGYy%2Ba3H5iN5ABIBToEAc1Ql409sK1RoryYGOprTD1P0vU%2BqxP6oUYxslVNyXEfJhwimlyOqLYtEtnU1u5iFZAKQUiCT9WNQSAaCDWWICwb6is2lxA6RrLWhtekjqNibYOFsRk2ztiTaZLs3Yexaos%2B5pzSD4CDti9Z4ctnICjrswQccDnDyOSctO5yLZXPSDcwu9ywiPKFs8pglca51wbowJu3jw0SF%2BUjaN3c43AuMAPcFCcMXQqnpwPcs9%2B5LwsMiiqqL0VQppTivFDKCXoCpc/VId96hcovvUHDIDf7Mv/n0LlTLaWsqAXykBnLMMcp5XR4lAq1iIIoUIyJajOBJJ7Z671vr83bELRAYh4N8lKq0ULGhdCGGUGQdqhITjDiHEKqNBRq01OJBmimjanANF7RVV1fVQMDVcCkGNPViR2FcGSPsw4IqDNbRkx1IRwN9MYMM25xYywc4ZGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_glowful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_glowful.test.hpp)
