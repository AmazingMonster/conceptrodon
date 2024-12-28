<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-conceal">To Index</a></p>

## Description

`Mouldivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<typename...> class... 
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class>
struct Conceal
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**, int***>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Conceal<Operation>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int***>
::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Mouldivore::Conceal`:

```C++
template<template<typename...> class Operation>
struct Conceal
{
    template<typename...Elements>
    struct ProtoMold
    { using type = Operation<Elements...>; };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCUmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMgTcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctw8DC2YmBJgA7FYrrdubdYc94YiCCi0WwsRjsC9GAQFFSuTyaXSCLdlMRUEQALKedDAnm3dkWW5eLJGXnCvWBAAiJLJFIEiIlYKlCjFVMCBvZFqhnKBcu5fIhCOhQtRzFFWIdr2lssuuqNEWAt01tHQ5qtKrVqCT2uhEadLsC2C9rLZnrdrJ%2B/z%2BgN%2Be1u2FUrGemE%2BZ2BNcrraurLMgQi%2BK8WHNbjQTMwaSjBfL1yO1oStoYLYOgP9AqDwtDmOxk6uCvppLnjSLXYrdyEXjSxUw6AASpgFF5aEqvsC4yazxfMlfb/fH6nZ%2BTD2hCICFIW5gL2UDwIgsDBEOV1vTbGd1UwFoqC8JkPmfK4V0hNcQ3RMVLmIYAZW3S5XwTZDUPQhwcj/RlmVoRF9wAykyJAEAs0RIiSPzQsy2Pac7m/B8n07cjjQTETfyhK0qKYNCMLYtxgMg2C1IIA4NLg9iQGDQMEJPA5bgAFTvMSl2pFpHGQAB9JhCQSAgIAmdAOIUdF7NItxpJA2530vG871EnFli9DhVloTh/F4PwOC0UhUE4NxrGsW4FHWTZm3MQIeFIAhNAi1YAGsAkkDENAADjMMxkmSLh/CqyquDZNlpCijhJF4FgJA0DRSDihKko4XgFBAfqCviiLSDgWAYEQEB1gINIvBAigIDQJ46ASKJ0U4VRKoANgAWkOyRbmAZBkFuKQMTMXgr0IEg8DcrgZEEEQxHYKR3vkJQ1EK0hdDegB3ck0k4HhIui2LAeG4lVpWpVUCoW4DpOs6Lqum7yrMW4IA8Lb6GIPUey4ZZeEmrRVggJBNrSbayHW%2BnGZAYApDMPg6FBYgxogWJAdiCJWiRSHeCF5hiCRYlYm0TAHDF0hNsjYkGFoUWptILBYi8YA3DEWgxu4XgsBYQxgHETX8GIeXHAANzvQHMFUeXVu2PLgPqQHaDwWJySljwsEBghiDwHrjdIB3iFiT8LTBc2faMQrVioAwSIANTwTAQf3OK8v4D7RHEH6C7%2BlR1E14H9HNlBUssfRfbGyBVlQccciN47XNk0xLGsMwhqj0OsCbiBVjsW2chcBh3E8To9DCCJhiqUY3uKbIBGmPxV8ydeGAWEZEje8faIEfoplngoj/qCfT8mQZF8WFfbDvze9DmNp9%2BXw%2Bx8yrYJGhjgMUBpw04GjI6p1zqXWurdPGEBcBPRJjlcmlNk6rAQJgJgWBEij1IKVSQgQMTJECG1DQkgzCSEOn1fwh1UgdS6qQHquUMSHS4IdSqyRmqHX8JIBqRDDrAM1sNUa418rJxmvNWmi1EarXIJQFmxNdpsE4K0Fgds2THSYHiAwJouDJAxFwCqD18BECHnoUun1i7SFLoocugNdCczBkwCGxsAFAMGrweG0jkao3RhArR5sbp6IMRofGhMGbE1JoEMwFNRFTRpnTVARMEiyI2ok8Jox8Tm10VwfqNBHwJD5gLTWEsRaKxKVLGWcsFYR2VlKVW6tAba11vrWghtFamwTtsBK1sJ4OyNglZ2rtQSK09h1BKPs/Yi0Dl0ymodw55SjjHJQcczZGETqAOJfA04KEztnXOitzFF2%2BlY2QNiAaVxAJzbRxg642AmSPFubcBAdy7paHuVhLD9w8YPF6jtm49Bvn4CArhX5vQXhUA%2Beg16NFBekHejRP5LCvr0W%2BAxYXH0aGfe%2BEKv5vxfhfLez95gP0heTNYGw/5ko6m4kBHAwEY3OpknRQSKr43gSYyJyDYnUzQRgrBlAAH0MYXo0hbJ/DJFaoEMhFCeECKGpwYRE0xGzQWktJGKT5E7T2hwFRmMWAKDttdO2uiMQBgmEYhBL0zGyAscc36ZyK4JV0MERxziob6BhnKjxnAEbLVWrcFGaM9UGqNSas1SoCZpMZpEwIMSqbTUkZqpmcio3ExAIai8tljXJFsuG2yqgzpc3ybzSgRSErlI1nlCtlTbaK1qYIepGtumYB1nrA2Rs8odLWTMrWeAba0T6U7F2yA3YjMEF7TWEz/ZImmcHOZitFmx3jms%2BMYjU5MAzlnHOIYDk2qORIE5ggHV2KSNXJO7zrAN1iA8xKTyGBGx2K5WuvdPkDwSEPP5OCMWT2BdPWF4Kl5IrhSUHIsLoU5ERU/b9qLz75EJdBpod9IOHyJbBueR8kMktxWSjKFLvquNhoI0BBbzr6sNbcbNpr4QTDZcYkgnK42oNIOgzBowcF0O6pcvRgRAj%2BEajwvqPG2RsK9YlBVtgRHxuWCVEAkh/CEJamyPqlVJD1S4NVMw/COqBEI/Kka3Kioeo4PdUTQiDPScjgUyekggA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/conceal/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/conceal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/conceal.test.hpp)
