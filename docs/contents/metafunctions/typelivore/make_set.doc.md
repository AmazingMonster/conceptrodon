<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::MakeSet`

## Description

`Typelivore::MakeSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Elements...
-> MakeMathematicalSet(Elements...)</code></pre>

## Type Signature

```Haskell
MakeSet :: template<typename...>
```

## Structure

```C++
template<typename...>
alias MakeSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
template<typename...>
struct Capsule;

using SupposedResult = Capsule<int, int*, int**>;

using Result = MakeSet<int, int*, int**, int**>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Typelivore::TypicalDiversity`:

```C++
template<typename...Elements>
using MakeSet = TypicalDiversity<>
::ProtoMold<Elements...>
::type;
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsZqQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5oERyN5YANQmgW5ejrSEAJ6n2CYaAIIPjwSYLGkGb6duBNdpjFYmAAdKC7i8JsQvA4jm4mGkFF56KcrE8Xm8Pl9MD8/gDmGxQcCAJIMBQAhyYdDYehsQQKcFPSHQghHAAq/zwoloABE8AA3BIla4gI5pLyxK7II4TdAgEC4zAAfTwWEENx%2BJLJmApVJpjAI9MC2EJLxMAHZUY8jtajhjPkxvmcFfjMEdNeTHEZqe99aRbf9AQTQQAlTATb20g0Mq02pkw5TEVBEACynnQLxtJwtGczNq8WSM/oBJ0C3OlBFlKAE%2BEaYhzuZLbnrDdjFbleAUitiTCUitQVB%2BzZbuZlcoVytVjj%2BGtJHoiwAj%2BrupCHw5t7LSnLEvIFxCFq4bdzlfLEXkwfoPuY3W55/MFNwvTzX645XJ39%2BnZ3d2reup9dMJP1vwcedF0EaNhyPeUAzHd57TeI4EyTVBU1odMzlDcM9QAsEjTHAMUWbc1uUItEnxtO0sRxAMXTdWcf1A7CCAg1soXjRMUzTGctRAr0mJY61zUtYd83nItXVOMtRyrBgaxyOtyMPM5L0zaSOy7HslX7QdFOfVtK3HFV9XVL96N4hd%2BKNFddL0tlX23O893VGyWygk9vHPE4XIbOEESRbFTJ438wINE0rK8mNn18xFkUCj1KRChRALooLGP/ZijUvKCFVIyKsxIwJLWbSiHQC34aKBQlEoEo5RMLVD0BLMskM4tCfkSsL7kK01dJKx1yrxSrQWqzLdLq4AjgaxUWUkxCOJQrizg63DsHwgFcuIjanj6srnSG4ERvuJ5xsmpgAGtMCETAZtLOzNzfRz92U0bHjlFqFrapamKSlaXjWgKiqeAB6AAqMHwYhoGXlBsHWWwIRWXBqHgYh1GQeR540TMPYGAOLxjh%2BC46BMo7MdeOCqKdCqg2BaM4xZaL/K2x4TqELw0mKSlMKRG6y0Z2K3AiAg/SFkGRcEMHwW6siWYLCbudoXnTouq6MsFwRxYIMWjlF7XdalwHHjmRxkEVHslDaCBpIUIEzcNNwFeFo42Y5zIubDHm7mWFEOFWWhOH8Xg/A4LRSFQTgm0saxpXWTYJOxnhSAITRfdWM6AjMYEzTMSQAA5c/8DQAE5/DMDQklz4J/Y4SReBYCQNA0Uhg9D8OOF4BQQCb5OQ990g4FgGBEBAdYCDFYWKAgNAPjoBIoiBThVFzpIAFokkkI5gGQKUpGBMxeEpQgSBVPR%2BEEEQxHYKQZEERQVHUXvSF0LhSAAd2IeFOB4P2A6DlOw84AAeQuOPI4/YjhL1XuvTe28ji7zMEcCAHgZ70GICcBOyxeA9y0KsCASBp6blQeQSgBDZ6JGAFIVINBFaCkoLEf%2BsQIitGFNwXgjDmDEGuIA2I2gfxf14NPSMgCGC0BYaHLAsQvDADhLQWgndWGkCwCwQwwBxCP3wMQBiAp5Gh0wKobUFxtiJyFvUf%2BVxYgf04R4LA/8CDEDwPXBRu5Yhu25O8FRVwjAp1WFQAwwAFAADU8CYFfoAvE/Cb7CC5FfaQZ95BKDUP/Z%2B%2BgVEoGsNYfQeBYid0gKsVAaRGjyJXjKSSpgo6WDLrwVAu57FYByRAVYdgGLOAgK4aYfgX5hAiMMKoowX7FGyAIdpegBmNAWCMRIL8mkgQEP0KYnhOh6GmY0OZgxumLD6bYSY7QFkFCmds8ZvTJmNNjlsCQP8OCB2bv/NuEDl5rw3lvHekg96INwEfNBuwuCYKTt41YCBMBMCwIkBppB06SECMCIugQzSSA0JIHOSRG7%2BCSEXfQnBa6kHroELgwIkhcArkXXOBL/CSC4P4aFSRrmPzbh3Luvze64KHngkeICLjEKnqgFBc8F4cFaCwPkZoV5MCOAcFRcCi7Alxbomsx9ZQvziRfcQ184l30SY/XQqR36f1YRcq5LcqlALZSycB/LBXCtFQYQsXBJXSsQcgwhCR0GBDMD87BfcWWkKIZPL1owzVCrFUYG1XAm7ULeHuOhDCmGcIiew5h3DeEOAiYI/UwjRH/wkVImRciIlKI8dscReBNEgW0f/PRBi3gRJMdXUO5jLHXGsQWrB9jHGJ2ca49xRhPGgEZXwPxgTgmhPCQoxV0SJCxNkGqh%2BodNUpK8WUqwlhMnZPgHkgpOQiklNLAu6wlSw41KMvUxp9Rml%2BFabJYZnTZKHKWP0zIgzci7I6eke9Yz1kTKWSemZTRtmXp6Ke1ZN7NlzHmfkZ9IG1kVA/d8tYGwzkwervqm5nAjj%2BotYGiaNqpXAg0G82VnyMFYL%2BaQAFQLRigurpi7Fkr4VmgpWaM0gQEWSHXi/A1AD262Hpe6pl8AWWj3Hhy31xB55sE4Py6BLAFB8ilHyLDWIJgH3wyfBVsglUxMiVOpJIBgjarSPwvVf8aVGrHhcMBVBUPEBYJJ6Tsn5OlQmParljqCOBECG67x/d8HObIUJnzqCQAyY5oqOTRdFQKYIGbKz68%2BB0HDZ3CA9DH5xpjQolLXCeF8IUSmwQaaxG8EzdIsQOaFF5q7U2xRRatFhjLfo5Ahiq2CFMY/OtzDG22JbRE9tSg3HKK7fOTzvimD%2BKCSEsJjAImjsvuOzTCTp06B03O4w6Sl3mKPWHddAh5FA1HDuiprcD11NXf%2B79LgL1Pr0F0qDRyRmvpyH%2B0ZOQgOTJOys39F2plfre/Md9N39kDD/RB575zYNxxB4hozrcUMSY3lJmTRxQvAgi3hj5zrvlEcZf8wFwLKAXKoyAMwkq3P%2BELmSxubmzQV2pVDzjndu7EfBWaPedGuBSCLrR6FXAzToo4IESHhrOM8YufvanAuMc4NWLuLIzhJBAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/typelivore/make_set.hpp)
- [unit test](../../../../tests/unit/typelivore/make_set.test.hpp)
