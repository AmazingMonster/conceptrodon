<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-harvest">To Index</a></p>

## Description

`Pagelivore::CognateHarvest` accepts an operation and returns a function.
When invoked, the function collects the value result from its arguments and instantiates the operation with the collection.

<pre><code>   Oper
-> Es
-> Oper&lt;Es::value...&gt;</code></pre>

## Type Signature

```Haskell
CognateHarvest
 :: template<auto...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateHarvest
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will instantiate `Operation` with the value results from `std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateHarvest<Operation>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Result ****/
using Result = Metafunction<
    std::integral_constant<int, 0>, std::integral_constant<int, 1>, std::integral_constant<int, 2>, std::integral_constant<int, 2>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

```C++
template<template<auto...> class Operation>
struct CognateHarvest
{ 
    template<typename...Crops>
    using Mold = Operation<Crops::value...>; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wULcTC8RAAdOiodhbsgDAoFLcAPJpBLvHKY4ETYheBy3DzAZiggASrQAbpgJsCTAB2Cy3YG3AW3WHPeGIggAT2JzDY6NRbmIqDSCnJV0Fty8WSMtwAsp50HzAgARQnE4ikgSI%2BWKhQgEAssReTCy8mBXmcrmGqFWK7A37/Y6Av23bCqVjPTCfM6%2B/0Azk%2BsyBCI4rxYA1uNAMLZpAjKwLYOPXI4mkkfL7A4UQhHQ5FojF5ikEKk0oklsmugtB7WYFpULyZ0tRq4V0XQiVS1hO9GXYjAXP5q4aiLAHXdpi9/s5A3GukMzDM4hsjnQltmxoqy623W0dCI6ez5319s%2Bn5FoReNLFTDoABK7K8tAISMDkBRctTfD9Mi/X8FH/QCoWNE9zQYRENFIW4uDQsxMJdb0gRfO5oNgoC9hAzVl0IgCtxXHs%2BwcNs3H5QUJnQW0IlBYAzVoAB9DM5kERE2LQjRMTQ5jWMETAOLEHiBD4ggBMENCuBE24xJANjJM4mSGDkhSCGwvNRIIFj1IkqTuN4lp%2BOhQTbjMc8cI7IsABV2UAssrjmRxkC4pg8QSAgIDUhQJ183M3Ao/TbnAz8fz/ADMWWL0OFWWhOH8Xg/A4LRSFQTgGMsaxVPWTYI3MQIeFIAhNBS1YAGsAkkVENAADjMMwAE4Oq4fxWparguS5aQ0o4SReBYCQNFQrKcryjheBtVDquylLSDgWAYEQEB1gINIUXISg0CeOgEiiCdOFUFrkgAWmSSRbmAZBkHQpqzF4L9CBIPAWIw/hBBEMR2CkGRBEUFR1BW0hdAwgB3M00k4HhUvSzKatyzgCRRPbANQKhbkum67oep6XtRMxbggDxjvoYg%2BQTLhll4ZatFWCAkCOtITrICgIA5rmQGAKQsJoACEhtCBYjR2IIlacVEd4aXmGIcUCVibRMAceXSCO14CAJBhaDlyGsFiLxgCRWhaBtbheCwFhDGAcRjbwYgNccQ80cwVQNZRbZKo0kactoPBYjNZWPCwNHGzwCabdINliFiSDDTBB3g6MGrVioAxZwANTwTAYZbLLKr%2B4RRHEYGy7BtQ0eh/QHZQaxrH0EObUgVZFUaa3ruY%2BDTEKywzFmhPiG%2B9l4FWOw3ZyFwGHcTxOj0MIImGKpRgw4psgEaY/E3zJt4YBYRkSDDp7ogR%2BimReCjP%2BoZ8vyZBlXxYN9sJ/d70OY2mP9fT6nkqWwJDIw4BlUgM1eBzXxldW691HrPSkGTCmuBPq03KgzJmmdVgIEwEwLAiQID1RAJIQIqIOqBCGhoSQZhJDJCmv4ZIHV9CcDGqQCaFVUTJC4MkFqHV%2BrJH8JIHq5DUgQPRvNWwIAlqZzWptNm20sb7R5nzGmZ02CcFaCwFkXJrpMGxAYLUXAOqoi4M1d6%2BAiBjx%2BiDcugMJDSGrkoWukNdBYThkwBGNsQFgLEXNTGu0US3FxtAwm90cQO3QsY0xGgKZU05jTOmgQzCMyqjI%2BRKiEgHV5qgamoxwlGCMVwVCItQTEHFpLSGitZZayqcrVW6tNZxx1owPWBsjY5RNmbC2VstZ2zTtsDpLsZ4e0hl7H2oItYBzRsHUOssI4DKZmPWOlUE5JyUCne2Rh06gBWlnHOCh86F2LlrMuANK4ONkDXCGOVXENwzgPKwlhW6xHboQ3K2Ycg9z7kaB51hh6QNHuPV5U974Xz8BAVwn8MIrwqCfPQW9GhQvSAfRov8lh316I/AYSLz6NCvs/WFf8v4fxvnvd%2B8wX5woZmsDYQDqUjR8WjKBBNYH6IiUYkxzVkEWJIIkjBqTdnYNwfgygIDWHsOMVQrk/gOqDUCNQ2hQjwFMs4AtKRAqWayPgPIna2MskZOIGo7YmiiYsAUCyZ6LIOWVgmOY1B309CnIrkDC5oMnHXJ0EkUg7jPFI2YaA1GkM/GKJxnjVQprzWWutfCCYsScnxISIkwIKTmarXSfGrm%2BqM00ztMgD8XErUdS4jaggXFw0OLoKU8pUsZbKxqbWlWas3Za2aYIfWhs0adPNmIHpcc%2BlbIWaQfArs6IjJymM5AvtJkSUDrwGZYdxTzKjksrWqzk6py2UuGR2cmB5wLkXKUJzZBnJdTYq5dcvUGOMM3J5MzgXvO7pwHYYlflDxHgkKxE8O49AfuCyFpLl7zzRW/BFOQkWgbKJSolGLf34pxaCvFT9gOn3JdffIZLv4ErXuigBtKgbeMDbNTg%2BMI0WtuIW1EJbuWoL5SmrBpAcF4NGG8ka4qQCdVRIEQI/hepCKmlxrkPDlVBtVZI6RgrSANUkP4MhA0uRTRapIbqXA2pmFSCNQIhHIGidTcsEBb1hNEYkbp1YCcsjOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_harvest.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_harvest.test.hpp)
