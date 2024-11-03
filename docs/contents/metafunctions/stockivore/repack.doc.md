<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::Repack`

## Description

`Stockivore::Repack` concatenates a variable number of packed stockrooms. The result will be used to invoke an operation.
<pre><code>   ...Stockroom<sub><i>i</i></sub>&lt;Sequences<sub><i>i</i></sub>...&gt;...
->&nbsp;Operation
->&nbsp;Operation&lt;Sequences<sub><i>0</i></sub>...,&nbsp;Sequences<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Repack ::   typename... 
         -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct Repack
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT;

    template<template<template<auto...> class...> class>
    alias UniSail = RESULT;
};
```

## Example

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
template<template<auto...> class...>
struct Stockroom;

template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult = Stockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result = Repack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::UniSail<Stockroom>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Stockivore::Repack` is implemented similarly to [`Stockivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Phantom`. After all sequences are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<auto...> class...>
struct Phantom;

template<typename...>
struct Repack {};

// Base Step:

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Repack<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    using UniSail = Operation<Sequences...>;
};

// Recursive Step:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct Repack<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    template<template<template<auto...> class...> class Operation>
    using UniSail = Repack
    <
        Phantom<SequenceAs..., SequenceBs...>,
        Others...
    >::template UniSail<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAHSAA6oCoRODB7evgGkyamOAqHhUSyx8f7SdpgO6UIETMQEmT5%2BgVU1AnUNBEWRMXEJtvWNzdltwz1hfaUDFQCUtqhexMjsHASYLIkGGyb%2BbhtbO5h7bkxeRAB013vYANTIBgoK15e3JhoAggoExF4Od2UCEMRBYeysXw%2Bn0O2yYu32BAAnolGKxMK93l8fn8AQAlTCJJjIADWdxMAHYrOSACLgqFQgD0DLuFiYSjudQJIHpXxhx1OfLhJwRm1h8LOF1QGP890ebJeNxlDyeCg5RBJxFQqBYpDugvF5yuitlKteQkwAEcvIxVgpMd9fv8CHd8YSSac6qgNVqwftzVabZgFW8ZfaKRDPnco3rRfyRUchQLY4n9oapcblfLpSb5XcAPIo4hw9L26N3LypIx3OQMPBCJh0Mn%2Ban5wvFgQey3Whi27N0yE0/ufRnM/HIZapABumDVXJ50OTu0h%2ByhZf1woOi43aezmeeu7lzzVXuJmu1n1Iq%2Bj66TCYNkoPpozh9Vnu92psV6jN9TD%2BfT8uf1u1Wb5dS/GM723P8QxzfdriAwMLAUS8vjXZFUTYV48wIBA4jtZdsChbEnRdAkiWJD11VPH1hz9LtA2%2BbNdTfaiP07AMe0wJCmPzHC8L7AcIzXLdbzFDcfwlI0YL3YNbhk1s4nbBhS2jCswmAata3rRs9hbV1yPA05wLLIEQW1djgMwRjrmY%2BjOO440UMjMto2w3DiFk1Do1uEAQHXTS6wbWhTgLRSCmU0N/AjClaSi%2BcGQAKiS5KUoZRlkoAFWwIQMuStKvkSlKivy4dITMfwwkeLwsCbNw0E4xICDtUNIV5ET4zE04d3/LNjSIx0ARYs9fWitrINEuNJPTaSXwEh0cWdIafQAfQ0IcoQkiTupmgD7WIwaqOG5auHWsbOo6ybtrk2a%2BqxAbFsOlazFOhdxt/KS9vujlLVWl6tugz6Fu%2Bi1jr%2B9qprm/bFp%2B564ta17zoh275pI/1lv8F61KrIQvESPJMHQfEFC8WhnV049319Nw0Y0WyQa4OnlrMRmMci0bPixjSiZJsnm1It0KOXNxwKW7VfrokG1plMCvKjUWWFBiXjsZ2HsCcst5aZ9j0bDGVfJrQK6Eok9hveOHSodYtkGW%2BU4gICAfnQXyFDRG3mrcbnSeY3H8cJoMeduOZwQ4BZaE4ABWXg/G4XhUE4YXLGsO4FCWFYZ3MfweFIAhNBDhZiRAcPJEuDRJC4cl/A0cONDMAA2WuzAADkb/ROEkXgWAkDRaejrRSDjjheAUEBaZzjgtAWOBYBgRAQCWAhEguchKDQLY6DiCI0U4VRG9rgBaWvJDuYBkGQO4pEuMxeAJwgSDwJ2Gf4QQRDEdgpBkQRFBUdRx50PQAHciyJE4DwUOEco6537pwPMFxF7OlQFQO4O996H2Pqfc%2BxczB3AgB4Ne9BiBknKlwOYvAx4T1IBAJAq9EjrzIBQCA1DaEgGAFIZmNBSZ4UoNESB0QwgNERCA3gvDmDEERHmaI2hqhjyzqvNggg8wMFoAI3%2BpAsDRC8MAM4tBaDDxjqozYhhgDiBUfgYgUi8DTl0X3TAqhqgXDWFnMIGww4qNoHgaIRZREeCwJA34eBO56OnMQaIKRMDUgMUYNxRhc4LCoAYYACgABqeBMD/1CtHLOT9hCiHEO/LJX81CQN0AzAw0TTCJ0sPodxw9IALFQI1dIui96O10uUqwlgzB91QEE4g98gzwAWO0cKLgGDuE8C0PQIQpglDKHoPIaQBCjD8AzeZ4VegzIGAzIZtQJhLL0NszoEx1n9HiFs3Z4zshnO6McmYpzBmp1WBIMBHBI6kF7rHTgSDd4HyPifM%2BF8sEQFwLfAhGdiGkJiQsXCTAsDxAgPnEAkh/CXAAJz%2BHJJIUuZhJC127uHWuKLW4cHbqQTumdLi1y4LXRuKLG5UqLlwcOaLa5vMgQPIeI9s4xIoTPShc9YFL3oYw/Bm82CcAaCwSc5I95MEzFWLgKLLhcBLtffARBekPw/tk1%2BEhpD5KUIUlRuhmaAKYMAmOzzXnvKgRwGBC8Lh3AQXcCVUqZVyo0gqpVJdsG4Jofgwh/gzAkK5b/SeVDtR%2BriMvBhEamEuulXKIwCquC03YRsDyXCeF8NEYI0gwj%2BHiMkQ4XNsjGAEAUUoyBaiNFaJ0bmrALBDHGL7qY8xljIE2LsRsXNTjMAuL7m4jx/DvFrD7n4gJWcgkhKUOExtkT1LcriUwBJyTUnpNzVkl%2BuS9WyAKT/Puxr9CGJQNYawVTog1Phf3BpAgmktObG06wnTY49L6ZewZfbzHOAgK4PZDMpnFBOXMlICyMgXOWbkEDazplAa2Z%2BjoDAugjHA/s%2BD4UkOTEA7c/Z5ysgQZ%2BNcmD2HiGLGWI8kjLirVss%2BfGt1iaPWKuVRobBwL1UBvBSGieULMAwoGFelxJKyWKtLuSJl5IK6SGxYfBm1r2W2E5WQkOPL4B8vnnA6NwqN5bw4BK1BLAFCTjPpOT1xwfiqpBffPQm6clvx3Z/A1%2B6/6BFNea0BRKqMqIHnauBjrEG6aPvpwzdxjOKtM86HBsb/UZ38MGxTYaUCRajUKxL8RDN42WiF5aYWbbEBYIfPgdB03DwgNwlR%2Bac16PK2IiRUiS3ajkeWxRyiW2YHUZosQda9ENqbaO3graajtpUZ28c3a9G9v7bwQdnjEQjt8b0idvAp2hNnU2hdoa%2BDxKSSktJKIMm8GszqvJu6HNFJyKU4wp7KmDvfde8KuiGSOxPRUiwz7%2B6vqwDdg5fgf2jL/UEUZNzZkrKg%2BkP7qz0iA82bYNDOzuh/a%2BxhyHpyhhw5Q1cxoSOnmkbTljyjEDPM0dy3pgzRmTNCh%2BCxtVJB2OxchaQaFsLKDPMEyAMwir/D%2BHDtXMu3cOfkmpaygng95OjzpwXSQ4dUXh0bnXFFkgUUV3RVwQILj/D466ZwCFobnlX0Fxr4XcWFhBNSM4SQQA)

## Links

- [source code](../../../../conceptrodon/descend/stockivore/repack.hpp)
- [unit test](../../../../tests/unit/stockivore/repack.test.hpp)
