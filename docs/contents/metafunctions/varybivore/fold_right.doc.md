<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::FoldRight`

## Description

`Varybivore::FoldRight` accepts a list of variables.
It produces a function that accepts an initiator and whose first layer accepts an operation.
The function right-folds the list using the operation and the initiator.
<pre><code>   V<sub>0</sub>, V<sub>1</sub>..., V<sub>n</sub>
-> Initiator
-> Operation
-> Operation&lt;V<sub>0</sub>, ...
   Operation&lt;V<sub>n-1</sub>,
   Operation&lt;V<sub>n</sub>,
       Initiator
   &gt;::value
   &gt;::value
   ...&gt;::value</code></pre>

## Type Signature

```Haskell
FoldRight ::   auto...
            -> auto...
            -> template<auto...> class...
            -> auto
```

## Structure

```C++
template<auto...>
struct FoldRight
{
    template<auto...>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail
        {
            static constexpr auto value
            {RESULT};
        };
        
        template<template<auto...> class...>
        static constexpr auto Rail_v
        {RESULT};
    };
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

template<auto...Args>
using Metafunction 
= FoldRight<1, 3, 4>::Page<Args...>;

static_assert(Metafunction<3>::Rail<Subtract>::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the number of parameters.

- **Base Case:** Handles several numbers directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<auto...Variables>
struct FoldRight {};

// Base Case:

// Fold once.
template<auto Variable>
struct FoldRight<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            { Operation<Variable, Initiator>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct FoldRight<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value 
            { 
                Operation<First,
                Operation<Second,
                    Initiator
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Write out the last two folds, handle the first two parameters,
// and recurse using the rest to obtain the initiator.
template<auto First, auto Second, auto...Others>
struct FoldRight<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct Detail
        {
            static constexpr auto value
            {
                Operation<First,
                Operation<Second,
                    FoldRight<Others...>
                    ::template Page<Initiator>
                    ::template Rail<Operation>
                    ::value
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxcpK4AMngMmAByPgBGmMQSGgDspAAOqAqETgwe3r566ZmOAmER0SxxCQCc/raY9sUMQgRMxAS5Pn6BdQ3Zza0EpVGx8YkpCi1tHflBEwND5ZUgNQCUtqhexMjsHASYLKkGeyYAzG5MXkQAdDcAaq14TDH0CqfYJhoAghPEXg4A1AAxTzoABKeGACAI/xMSSsSQAIqcrF8Pp8APTo/4WJhKf7nJQgNFozFAkH/ATbK5ovYHI6YU7nS6of73YiPZ4Mk7vL4/P7Q4G0MEQqGMtkc%2BhvYlwtH/OX/WmHJjHM4XIj/ACSDCyypIUq%2B8v%2BfIBymIqCIyiYwAZBvlsJRn0NhsV9MZLuVXKZ1xub3%2ByAMCgU/wA8ql4srsvrHU65cboQjMC06LKYzCZbbU/K5o5kH6BBNMKpUsR/mqWQA3MReG3RzNy%2B0hsPECMCMUPJ70Uia7WOXXEN4gECV7yYNNIk4OzOw8cOlMx90qtwLz1lm7U7l%2BgMKNefYDETD7RgEV7cudOryZIz/UFMOgwk4I/4JpO0Rm7/eHwTbn2nidn6fIsSGYKvsSqLquNzvgebBflGhoXuEwD/Ja1r3o%2BprmqgKGelBn7HmuUp/qiiKAaiXykoK6AKgA7ngVI0qBrqqsyQJ4MQExdmW/xCJgaAMOgUZxmSQrgpCBCMoCbEcdxvECAJp7EZO8rLoyXFajqRD9gptZGgQvwmmaFpWjWhr2mezqMR6bqWeBzIERu/q4kGobho0cGpkJz63q%2BwGmemOmZtmdF5gwBZFiWXHDtWMK%2BamDbmXWcouc2blnJJ7EEKQCWJclLYMIyPF8egWWxYlhrqb2mnZXWA5DlWJllaZ3KDlFDWJQBREBXaJGddVKlnP1XqoPZ2Cbk5O57tBR4njyXVyghV43nepyPl5yZnLhMH4T%2B7ydX5M5ATpg0QVcm3Te582Xkh2FochhlYcZb6TXh37rrts49bO5FYqCvGbJk5ajgS7CHaSADq7J7BSlwKggo4BtCBDUSy/BCgoXYIIY6D0LDo40BlNEsqkrSsIm8ToySWJY/8%2B7IP9o4LUhBBwzTmATAqLKoDESYMLj/zhBpJDUl8x0sel0lcYVcmcXZNzBsz5OCXp/LCcKYkSVJmUyUVXby3D7EjdKSlyqL6oVY8VXaYaQkYUZ1r/v5maDabw07WNgaNq5kZWx5ysAmtPlzWmxt1kFuZ8WFxalixrXVX5IeNblqVuOLmVx6mSfe24Uv8SVQeNZRomimcevk4bpWNf8g7Lshj1nObfYXZXhrVzZo5La%2BJdNnlTfN3KLX1enMa1bHFdTs1dUjkPY6kUHHVfUHztt6pstve7r1nbBPsxoz17ebdAdPR%2BW2vYRIfz4dFl0lZzHeqdz0n03u83Std2YdhR9TV%2Bhu9Z9oMAFSAKAcA9EJIgEABVsBCHAUA0B5FgEIP/nAz4xIzAnHCP6LwWB7xuD4tsVIx4owMWvrZdUnwZbqisNpISQgvDc2bA4I2Z4w4hUjhFGOg9gINkdAAWmxDPX%2BB0yKfBdjuYgwAZpol3gAWUTEwKgXgGAOGyDFFBD5VZF3EmcII/wThdkkLVD%2BG1xGn1/AvMOAB9Jy8QCAQFkS0BRSjk4nFqh3AqdC9JMEYRPVqaFX48K4CsZEHA1i0E4AAVl4H4DgWhSCoE4G4aw1gjQbC2KOcwJweCkAIJoEJawADWIBwmSCuBoSQXAkgnA0OEjQZh/D%2BDMAADkafoTgkheAsESBoUg0TYnxI4LwBQIBuk5JiSE0gcBYAwEQCADYBBUiXHIJQNABw6DxEiKTTgqhGn%2BB4f4SQ/xgDIFzFIK4ZheCYHwJpPA6A9D8EECIMQ7ApAyEEIoFQ6gxmkF0EEaizZUicB4KEiJUTclxM4MGS4CzoSoCoP8bZuz9mHOOf8U5Zh/gQA8Ks%2BgJYMmBN4KMrQawIBIBWakNZZAKAQDJRSkAwApBmD4HQPY7FKAxDBTEcIrQACegLeCcuYMQblwYYjaF4qMrJKytrBgYLQXlXysAxC8MAc4tBaBDO4LwLALBDDAHEAqti4q8CAw1bEwsf09h8vIIIeoYLaB4BiM2IVHgsBgr0ngTpmrSCA2IDEDImAEw6qMPaowuS1hUAMBI24eBMDURctErJ9zhCiHEC8pN7y1Bgp%2BfoXVKAkmWH0A6oZkA1ioAIdkDVPCJjyQRKYSw1gzB9J9eyLAxaIBrDsEa5wEBXDTD8EEUI4RhgVFGEEQoWQBB9oKBkCdDAFgjASLMeoXamiTHaJ4ToehO3KIEP0No86R2LtsGuqdsw10HqWIE9YmxtgSGBRwSJPSwX9PhTsvZByjknJKeiiAuBCAkBhGg/F2Sw1rDhkwLACR22kEKZIE4VwqgnCSJIMpZhJD%2BA0NU/wVRWkcHaaQTpmSriBH8I0qojSuD%2BGKVwcJiHai9N4P0wZwyQNjOJdMklsyoWLKpTSnFGy2CcFaCwcsSQeFMDGleLgVQrhcFKRcq5JAbl3NkI81N0h01KEzV83QjK/lMABZq%2B9j6GPgo4JC%2BZMNYWlmICJsTEnHJSZk3JjQGKsXkpxYBk4ZgVgErDRM0lqBsXxCWdSoLHnRjCdEzwxz9KqhcG6TQWgLKhkQHZV8gVPKrWZaFSKsVDgrVSqPDKuVYLFXKtVeqq12rdX6tifgWmjgTVgvNXTS1Xrwh7DCV8%2B1jqeUup2LE91nqsk%2Br9UoQNtXEL%2BYjVaBQ0bY3xqtUmtTzyNOyAzZ82Jumc2hrrVYAtvW22lvLfmTgVaCA1v2w2pt8QW1s3gB25dO6/A9v4qe4I/EL2jrSDOxoH3x2NG%2B0e7djQ93rryP2noK7wfA63SejdMxj3zCHYsUdHbUm3qvd1kzz7OA2bs%2BJyTSFpOydKRiv9mkvPAcJXk0g4HIOUHvfhwjMmylJFo0kSpkg0P7KCKZpjtgWO0/Y/ATjczoWhb4%2BszZHBhNIpYAocsuZyyk/pBMBT/6W0qYeSmtbrz5Baa2zoEAej9OGaBbh3HXz%2BkWehRSOF8uDmK%2BV/8VXMn1fQkxeFilXmTi%2BdY0SgLKAfc4ql6H0YyvUipAse7ixnurG2f2Uy5L5M2Ucq5UK7LmfhWivFYVoL0rZXyvq5gJVKqxBVa9TV4Ng2tWGuUc1r5rXLg7CyZ121PWHVOu5QNt17IRu8DG/6ybwbptsb4JG%2BbMa41hgTbwFbeuJDrbeUbrNpvdvGHzTYI7j24mndCpwdE1a831ssI2xjzabkPZLdDl7Lh3uI6h4OsoC7p1FGyADv72Q4dLt6LuhHSHLdZ7MHc9VHN/M9AYD7OYfdcAw9O9a9NJBAnHUFG3fHJ3f4F3FXNXD0dmX9RTXFIDAPEXMDTACDUYaDbrFnEAMwGTE4E4cJGpcpTDegpIUjJ9NAgZIXEZUDGDEASQcJBDcJRpOpKoSQKoSpJDLgPRbrE4VAvpTgPzNje9c5DghQrgkg71cmbIfgoAA)

## Links

- [source code](../../../../conceptrodon/varybivore/fold_right.hpp)
- [unit test](../../../../tests/unit/varybivore/fold_right.test.hpp)
