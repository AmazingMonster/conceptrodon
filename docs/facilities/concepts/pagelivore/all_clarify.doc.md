<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllClarify`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-clarify">To Index</a></p>

## Description

`Pagelivore::AllClarify` accepts a class template predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Pred, Vs...
-> (...&&Pred&lt;Vs&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0<***>::value)` and `(...&&Pred_0<***>::value) && (...&&Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** fun ****/
template<auto...Args>
requires (...&&Pred_0<Args>::value)
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0<Args>::value) && (...&&Pred_1<Args>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BAGykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSH%2BwDUysSY6AD6GsdH%2B7smGgCCBJgsKQavJgDMbkxeRAAdMCfthHk9ZsQvA5TucrhpwSYAOxWZ7HdHHWZMRzIY5oBizTCqFLEY4xVCeY4ANzEXkwx2RFgIUMwyIAIj9UU92ZzEc8DkdYRdLlxbkcHs9Xu9Pqzfv8gSDvmDnpDoQQhVcuIiUeCMZimji8QJCcTSeTKTTvPTGcy6Tzvlz7Y7%2BXdjlQvAwxYcJS83h9sbK/gDUMDAU9iMAFKDwecAI5ePDnBTHCCh8yJdNnYUI37hyOgkAgS10lbg/Emklkim0N0eiCllHnAibT1UMRKXlIjnPcFS/1fOXB0N5qNKmOYeOJzDJ1Mg6qZuHXH5uEcFou0zArBnz6optM7xJZzXL1dKwvFzdl42vU1Vynuhj1xlNlvHW2yqxdvlPAWHY4AFWndU7h9XZdmObBiGIEhwSxHFLiYBQlBaagPWXLUlXrUsHQ4NZaE4AJeD8DgtFIVBODcaxrExDYtmtMxvh4UgCE0XC1gAaxAAJEkBAAORIpACJFEkkABOb5hIY/ROEkXgWAkDQNFIYjSPIjheAUEAlJYkjcNIOBYBgRAQA2AgUgBchKDQd46HiSJWB2VR%2BIAWhE45gGQXEpEBMxeAuQgSDwdA9H4QQRDEdgpBkQRFBUdRdNIXQuFIAB3YgmBSTgeDwgiiNYsjOAAeQBcz1VQKhjicxJXMkdzPOObyzBTDwbPoUlzEYlZeB0rQ1ggJBrJSWyyAoCBBuGkBgCkMw%2BDoV5iE0iAYnymJwmaABPLLeFW5hiHWwqYm0OodKY6y2EEQqGFoTaEqwGIvGAP5aFoTTuF4LAWEMYBxFuqd6ipad8qJOoAR2JjwlefCEtoPAYnSvaPCwfLmTweS3tIAHiHJJQ2TeL6YaMVi1ioAxIwANTwTAUsKlJGC26LhFEcQotC%2BQlDUfKkv0L6UCoyx9FhzTIDWVAUl6V7nNmdAfjZUxLGsMxVMx4ggsB4Wuh6LIXAYdxPHaPRQgWcpKj0QpMgEKY/GSs3eiGY3RmS2p6gEfpJj1vJHe6Y6GjmO2RgSR25ktvQsRaP2lgDtYFFo7YJByjhCOU/K1Mqly3I8rzJB8lNcAC9qGK4LrmKJtYEEwJgsASetSE4yRvkBcSkUkDRJDMSREkU7jROkjhZNIeTvjMQFvkSJFeO%2BXiAgCLgJNE3ik4StSNK04vdL6oz%2BpMkqLNG8a2vsthOCqmq8QMIwGtEwEuEBUj/KIFXguS1nwuZ6RWdijmEt0Ga0oyrb48TipXgalipmQBMccqqdqpuWQGfYAF8r432aqgVq8RtyDyLj1PSm897xEsmNFBQ02ooDgVwUSXAlI0FoPNRay0Eo7Q2vTBhe0DpHQcPTM6jACCXWuvlO6D0novXph9fGOxSL4HOP9QGCVgbIFBvTCG3R8owzhhtRGYjuoqzRkxTG2NMC40%2BkYAmoA158FJgoCmVMaZ03Rs/JmkU36yA/vFUi39uaEzllYfmKihbV1FuLTgksCDS2%2BLLPmFhFbAOVqrXxUcvbOz8BAVwwdkqGzKP7U26RzbZHdlbVIWTbZGwyZ7TWLsg65JDvE3ort5jpIjiHcpuQ8mh1qYsE2hd1ibFjh0qGgDk6cCgSfWBX0EHXxuBAXO990GF26iXUgZcK6jGrpxChSkoZ9wHgEQEYkAiiTMHs6ovEZ4iQXqpTgy9tJE30hvJAplSr4NwcQA%2BOxmgsDciwBQVJcRUjIYCGUsw/L4HvkFEKsgX4OIZs4zmIBvipXSplN6AC8qLyKtvMqFVVDvM%2Bd835/z1QQBakQtBHVviYKuTgwhw0HmUuIV8lIKRLg/NEpcPFlxMVvzmvEWhK01p7SYby/ah1jocJQedbhV0briMwPdR6YghHoxEUYjRpAJHewBq9W%2BqgQavAUYIJR0NYbw3Wuo5GWj6a6PSPovGRjwgmN6mYpg5NKbU1psRJidiIoSEcTFdmLidAwvccYcJAsYixLImLLIr1dhS15vLSwkSyLRKwGGp2vRta6yaQbHW4d2n5KKFkFJebsk5odhrb2ZSBiFtTT7AYJaA7jErRUwOtain1I6dHLpkUkWnOAQM9lxwPlfOpLigMswc5ApINMsla9S7l0rpQeOGyYVD2OQxMw66uC8Q0IkXZPaCrqVsCvLBKwOIgDrlfCeARW7fACNuhiwke7fGRWcg9x746%2BT3UvVevU1iYwyM4SQQA%3D)

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<1>());
```

## Implementation

```C++
template<template<auto...> class Predicate, auto...Variables>
concept AllClarify = (...&&Predicate<Variables>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQgAMwAbKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcoPB70wULcTC8RAAdOiodhbsgDAoFLdlMRMPhRKDSLdkWj0QA1Vp4JgxegKTHAtAMLZpAi3S60WhuAzEPBUACetyhABFbhB0ajzMk5YTiXhSQjobTBQymZiQCAAG5iLyYZZQqxXYG/f5nc1HW4AFUwE3xX2tludZp%2BNsV6AA%2BhpPlarrDnvDEZTUDKWVcJsQvA4CUSfRpgSYAOymy63TO3OaOZDYgQTTCqNLEW4xVCeW767yYMVpggxhEp8Um5PN1vu66ehPerj%2Bg6AoMQ1VIlHhjGJbDA6Oxrle3tt9NZ7MtXP5hiF4ul8uV6uGusWBuG1MtxLpk8doEeu5ULwMft7Qdg4OQ6FhmWXYjAZmT4FEgCOXh4ES%2BI8nyApCsKiLzho5Kft%2BEa/lcbKbiWZYVrQty3gwEDGmmRIEBs95UGISitu2nZDiGb5jh%2BX4/lOVwAUBIHcry/J0iK0E9rB3L0YhWJynKbHgZxUHQvOXBwfxE6MZcKGglu6GVthuGphYBFEbcR6qlYFFXl2dz2hMD6AjmyrekweLxAQ1B3oiXCYrhxpnhwqy0JwAS8H4HBaKQqCcG41jWNm6ybLW5iJDwpAEJobmrAA1iAATJKiAAcyRSAEKbJJIACciQ5WYiT6Jwki8CwEgaLBPl%2BQFHC8AoICwbFvluaQcCwDAiAgOsBBpCi5CUGgTx0PEkSsNsqgZQAtLltzAMgeZSKiZi8EqRCCugej8IIIhiOwUgyIIigqOobWkLoUkAO7EEwaScDw7med5cX%2BZwADyKIDVyqBULc03JHNkgLUttwrWYUoeKN9ClpFXDLLwrVaKsEBICNaRjWQFAQBjWMgMAUhmHwdCgsQTUQDEb0xOErTCo9vA08wxDCh9MTaJgDgM6QI2vAQH0MLQ9MXVgMReMASK8k13C8FgLCGMA4gi8BnOOLqDpvUWnMots0XhKCHkXbQeAxHdLMeFgb0NnglUy6Q6vEOWSjimCCvG0YcWrFQBjftSeCYNdH1pIw3O7cIojiEdYenWob1XfoCsoMFlj6CbTWQKsqCcjk0szRM6ASqYljWGYdUO1tGsZz0qs5C4DDuJ4nR6KE4TDFUoxScU2QCNMfid5k3cMAsIwJFJdg1wI/RTI3BRj/UE9NJMgyt4sHe2Evvd6HMbTD%2B3o%2BrAoYVbBIz0cF5pC1bw9UA7N82LctkirVKuCECQYrFQjSOe6sCCYEwWAJFwqQJKkhEiogKimSQGhJBmEkMkaqKU8qlQ4OVUglVEhmFRCkFMaVEhpQCAELghU8ppQvm9eqjVmoxU9h1bqaNerfUGjjPGsMJpsE4IDYG2IDBGHBnlVEXBUR%2BQ2iQPA20pJh32pHaQ0clCxwuroYmt17oM1PufS%2B70OBfX6iiW4f0b5A3mjiBWfCBFCKhqgGG8R34YMRtQtqqN0aWMxrDIauNnH42MUYLgeUuCwRoLQMmFMqYXSZnTbmYSWZsw5lzO2vNGD80FsLPyotxaS1oNLaKcs3bbBSSrBweB1bS2EaobWoJub63qG9Y2ps6YW1yUjQUttooOydpgF28sjDu1AA4vgPsFB%2BwDkHEOdtJER0OjI2QMdzp%2BUUQnD2RcrApxqenIBWdGi53zoXZOFhS5X3LmIyuQDx4FOcBAVwm8pItwqCPPQXdGiXPSAPRou8lhz16JPDeM8%2B7V1OYveYK9bljy%2BfkH529l43L3ifNYGxj4I2Qeo8hnADFcK8cAUxgi/QQBfptGxn97Eox/n/ABlBEpVVgobVB6CAionygEPKZgGVmGSGlIhuUyEXQobYKhyN2qdR6n1H6biWHjUmpwVoLB5osAULqPMuofGomHBMda%2BBNpiJ2rIKREzjryDkTMnQSRSDKIejLNRr1OWfUYb9f6qgpUyrlQqpVXIIDQxcdYyKiQ7G8scSgDxrjmF%2BtGLKtIaRvTyryt6J13pbUyNJvEYJ1NaYswiUm1m7NVbc3iYIAWQs3qpIlmIDJ3NsldIaaQfARIClFM1qU5AOsKmCCqUbE2ZthT1Ktk07mrTMjtNdl08IPSUZ9KYL7f2gdg4%2BWimMg6EhJknT1XHQ1PDjA7NTjEVZmds4Fk4DsfOSdi6WD2f5A5WAN2/MaHXBuoLm711eWve5ORHkPrKICqF7yF5T3aN8re88/mfrvaPdeAxHngoA9Cw%2BsLDpmo5XVZFMbbjStlVWR18ITLYtVW/eGXrv6kF/v/UYQDKUVSSJgtlxUzAUa4GlDQyR6UwavpwShLUcMgLAUQ/BMDEgBBo8VHKyDEjmtgw1Al8VkFrXo5or%2BDjVgOyyM4SQQA)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/all_clarify.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_clarify.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/all_clarify/implementation.hpp)
