<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyKindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-kindred-repack">To Index</a></p>

## Description

`Omennivore::EasyKindredRepack` accepts a list of packed vessels and returns a function.
When invoked by an operation, the function concatenates the packed vessels and instantiates the operation with the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Operation
-> Operation&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredEasyRepack
 :: typename...
 -> template<template<typename...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<auto...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<typename...> class...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<typename...>
struct KindredEasyRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
template<typename...Args>
requires (sizeof...(Args) == 4)
struct Container;

using SupposedResult_0 = Container<int, float, float*, double>;

using Result_0 = EasyKindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<Container>;

static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

using SupposedResult_1 = Sequence<0, 1, 2, 3>;

using Result_1 = EasyKindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<Sequence>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
template<template<typename...> class...>
struct Warehouse;

template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult_2 = Warehouse<Con_0, Con_1, Con_2, Con_3>;

using Result_2 = EasyKindredRepack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::Flow<Warehouse>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

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

using SupposedResult_3 = Stockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result_3 = EasyKindredRepack
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::Sail<Stockroom>;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyKindredRepack` by uniting `Cotanivore::KindredRepack`, `Sequnivore::KindredRepack`, `Stockivore::KindredRepack`, and `Warehivore::KindredRepack` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyKindredRepack` to produce partial specializations.
Hence, we create the following helper classes.

```C++
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::KindredRepack` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIJIAzABspAAOqAqETgwe3r4BwVk5jgLhkTEs8Ykp6XaYDnlCBEzEBAU%2BfkG2mPblDK3tBJXRcQlJabZtHV1FvQqzoxHjNZP1AJS2qF7EyOwc5skRyN5YANQmyW7IS%2BhYVNfYJhoAgsen55hXN16OtEIAE9nq8PmYTgwzl5Ltc3MRDMBMApQe8wQB6ABU2MxFw8bQYeAAbiR2CAANIRdDETDoABKmAyTGQAGsLjjMeiwcw2AomQc8agCcTSVdAlY0e8CJgWBkDNK4QQgRlGKxMAA6TWot5LYheBx4pgZBReejXCUfKUyuVMBU3JUqnkarXJF7vXX6ggXSkMam0hn8tkmcXBgAi5rBGPRFwsTCUhqUIEjVtl8swiutacVytVbE16ueFzOcYUgsETFWZAuDtzzvV2HobEEKNdYI9Bp9fvpjOZLLhHnLlbhDZljAICnzoNbaJD7wu8%2Brmdt6ftS7tbhrTsnrqLBgUpYA8iqEYNtQuLu2vaHMG06GDz8GLefz14ckZqznfqGLkeEra8sOjZjhOLovMkT4LmGEaSm857Sqmy4Zgh66bmq27YLuJb5m8wA0qOzZngur4RMAFx0qgTDoF%2BFzXretBwjheFNuO6EgCANbQR8gThuByZvOi0YMsgew5ESPxuHG7B8fBNoKmiNz3guMlZvaOZbqBmH7mWt6RMQbykIp87KYhqmOmhGnFlpA46QkNiGR%2BZl5pqI7MTqpBXHOSlqeZ9ZAYIFgKAZnlGd5TnqgeBAIAkKLyW6OoEHqHZUjS3aBv2sgVrpHw3C5Y46uh7nWZltmAfhBABQVP6RdF6GRrOsFKWuK4bk12aOXWhaWYex7/gIhHzpeNE3hW9HBWKEHPhcxHvjW1GdilAa9vZD4KWNk3zhJxqms1uWCPlmrubt5UgQWrpBQ160LhFUXECdy2Qa6bHGdKZEUegcK/ieAGtrxY1Qb9loXYuyHNc9oOhR1O5ddhuGYGVLZxS%2Bb6keRlHUbRI0MbD8OsexOacf9Fp1eGMFYjiFxCJgACOXiEiSNJsfN/o9qy7I4ly7xOnyzI/JTNN06Kj7Sa1NxMP8qC1e6CWehTCD/AQZoA2CYNtbWkvxYlXpM6lvbjYTfECTGkkJlJMEq6uINwmLRDoZppZ814jAHO51sS5qABq7R4EwsT0AjbbS0lvoLSzfY3A7TvNZ7xDe77yK1dOXETcDsmgyLEni7bXU/j1p6J%2Beg0Y3ef31Zd02kbN1zfp9vUMHC0ex37CfJ/rMFwen5sZzbFl7idjFw8x/tjeXr1o1XQ10VjTHAbjHFK9xBMpqnSHL6ZtYu5nPclhT1OO1CmDuahbAXAAKjmG/d%2BqDc%2B372qDdri2snCEf73CZ8qu519x3dP1xULY2d07q7LOvcc5/jzojBchdhrFyBv/IGSMSIOR%2BOPGup41oPTcEsf8yAAD6oglhwnuGxFgTAWSYFwTkYAkR0C4IIEQvAAAvCh9Df4QC/n7TYzd7Kt0Bu3S2FtV5dzdqdDC0NNT93hv1KayNR5UXHkXeiNxJGD1nvjeePEibvENkJESxJxKSSTGbVq8k3D2SAZvURdsd400jvpcx6dgFby0i/A4dkxpOKvl7G%2BmA3IeSBp4jhmAArnTghDfM11oqRkTvfZKzM0rh13nY%2Bu3i477VEe5VxwSUkxx8RVUC7lIm3XVvA/hQiLGX06qAtB31IEDUDleGBo04Gl3WiPSuyRvwP1DvdeccJenPiEHLAgCso6pPoOkz%2B4zgk/2wKEy6V1qrFK1Bgvpj12JNTkR9XOtTOIPgXkrABHdHGWKqVhCR2NB7SJHqjeRnSJ6Y2UZcmeoEnrqKJgcrRbwVamIcQIjcEML4iLOS4pJ%2B97FHP%2BUfA%2BFxPEgvtmCtx8yQrtVPhCoG0LT7uICZYoJfj7KBOmSE8x4TNRFJitlOKsTg7xKWok2x4K376QuHi2ZmTEXZJuCfGwLKiVsqqjdWZdVk6AJOZUqG1Sdl9XzlAhpDzYH7OTogman5x7dLSqs34ZjNUFwIOgNiERpRImIJQjlAyVraoQQs%2Bp%2BqQCkPIZQvA1DaR0KIXqtiORmGurOua9a2DHB4IIawrB7q7VkIoVQmh3qQ22s9Swqc2B2HTJ1Fwg6vrJr%2BrwIGuMwbiFhodZGl1ubQ1xu9WBRNQSAqpoLDqh6cz00Cpqisq1azsBPU2bc7Z4DdkA32ZoviZSVItX%2BXCiV5z1QqOAtc2Rtz0ZNKngPF5oi3kqgJp8viUFSYcgpkQVkIoGYUjiTrVmHIOZvC5vyXmu6WT7pQfVZWxyR2nLHfudWg0JLEBjgkRe3yO6ktEQHTW3oj2PyDCGddpNoyxnjBJRMwsoWPqEaOsRvcQHb1aKgVkxBUCoBYIfMVwKX0nSyUPDWMt1V0rcBhrDOGWDPw5UKxOpTGoIdY0h59KHx3wrAV9aVdSLxysUTw1pk12mqvuTU6VVGGPcJLv2tuLHymIaHchu2aHX0XOngRGV84R5CBGnOyeTytMsVeXjVdGif06KaHosSJsjGAx%2BdlS1g6TLDvY%2BKzjGmrHZ2oyybDuH0WuZQgR9TszrF%2BYCywbFwXmqqfEeqLJ%2BLIUecI154jHLiUAP/eS6JVK5UUafuHa9UXnNJf5ZF2jVh6V7zcfy8lJSRMpyHaKp9nm1POO6t2vj9loGTxLkqoisiOldJAz0zV/Ta0bXaF%2B4g9GGUHEmTY2rMyCoNoa82y6zx20gwpo8twkm64/RbhBvhimWvKbc/F1DnWYYmdI8q0i%2Bm6CGf25O5saiLMfPk4DTdgMybYguAAdXaJgBAt7GZjcDGzbEZ6L082B6D8H9M71fNa%2BU/98K31yvdmDrNis0d/vatjoDhWwNWFO1GI2MHDHwaU2xlrmOiNhcRzSBAuwlD4ahUz9L%2BYiqVlI9SrsoG4Qg7Zxz5q/PdKMb/k19HF3ufE9u51njtdpF9cxgNgZYmVTUUO%2BlQc0vZMtJ%2B38%2Bn5vGdK58zd63473vjmnUggAYrQVAAB3V7d5jOLo%2B2Zue32rOCRs7dfR9m6dZl%2BSlhXGOrdY5V2LsHEugvnbc4AnnHXbdaQT%2Bz18wTkXNdT%2BnhLUuEjJYxUTtWyv1Ql%2BIFljFOWlkUrvgVqHlHs9J4NzZPS/L2%2B5%2Bq24Gv%2BSMmNuWQBmcIrLshcV5XzP4Xs7650wJoDQmteap1yg%2B5ZOBmTZbc%2BXH4OziS4ypWJbg%2B2Xrcb5OCb6ywYXBd%2B7rtvGjtgRO6bqPqfJ/g1j8zqv9uHtDed1dw9wUXnW9xxj93eWJh/T%2BwxG3QAEkFAABZTwdAKgU0GHTkKnWiJoL0QMWkK4VIDQZA2gd6Qgh9afJ0ZvIDBA4g1A00YVATHBIsAQJYTAVQDIYgC4WIHDWgC4IkMQR2caKgMQJQQmMUN/X9BnQvb/dLbSYqKsaFfMI6QXOVGglAtApRAfY/XSUqVRUCbUR8RggNZghgVg9gzg7gzwPggQ1HaWdMT5cQqzeAhQZQJgJEDQjAs9Q2bAg0PA%2BRQg1wpEEwMgpeS3WsKgmWBAwIzADQhgzNZAEwswjgrgng6w7wVHYQ2gUQhw3hcgi3K7DjCLDlIFfMIJFQ6glwtwmI%2BgmrSOHJRueOfQpjcUIwrNRI6UcwlIqw/g9I8aOwsQ3I7RZw25Dw09LAm8HAi4PwggjQTtEIyQmPcImJVQhQEY%2Bg8fVohItAUwjo5Iyw3gnowQx8TI7IzRRww5BYiPZzM3aPMI9SWfFnXvTnG46QmfOPavbQqJWKQDSI1Yt6WIm4J4o/Q3JtADZoiwTY9otgvY1Iw42wvUews4wY/iYYkaUY9mcY6UXw3sfA4I2YzGeYtPdqCIg0BAukNE9YpOSE7YpIiw2EmwoQkQxE80c4wnS2SPcvKQ9ca7LjIjHdTDfzWjfPCpNLDPEjPLH40k1YikzQyrXDebFbGXOItoYwmk3Yuk7ohkx8fonIynIY8mbAOMIEMnTwvIu4nyVw1kKo8omWQ0hQY01vJ%2Bd4EAKYrwX2Noh2AWA9LfG4S0lka0xrCnCQokmfP0607UGkGmPAGkUsCAScMwVIcwVINQkggEtwMMpEBGNiOEzYSUr0O0h0mlY9MOdM3sAM/Q501090hI/EQwCHQ9IskXX0sszMwM5EkM%2B4jM5ECM3eaM5EC4OMrUBMpMsk/4mo0sq0zM7bEAHMvMi4Asn0ic/01sist4F0jIN0wEBI7PesxcrsoVcfdsivTsls7sxOSMrwPs2M%2BMxMhMskmUuEfc6c2cqWIDBcx0ks/c9Wdczcj069Xcj8x808g8pOZEgHDkCCjE/UwHE%2BZEccU06CyCyCs9WA8mJ3aMpYec1QVgOUH4MY0I14%2B4t4YgYAUjC8q8gcuNVAKgfMCAYi0izYL8ceSQXM18mWGvH9PTLwDIUoZmE0WgAgXBDQaiDim4Q1dyKgV3W0CSqSggTEdydAXYOOKcL5G5ZEU0QS4S8ed8xs8ba4saPNAgbixWNwQ1Z4dyXrUNIy3CuESSiiAgGS%2ByzEcyyy21aykyxSzclcP%2BdZTtG4USl/PieI3BEsBIAgCAPNBQNUEKlsNwBkfizSzJbi3i7sBKoS54XMi48CnebYqibAbC1MPCqCy4tzPNe1CNJ1KNYtWNJheNV0bCEisi3smMyi2q6i2i%2BihQRiquZi1isjA0LJTi2RIQZK7IPijS3BLgaiQam4DQdyLgdyMwdyZIFSviNStKqa7So0rfDk3VW1Q1TAY1U1BbZqcSi4DQcy/xPag1X0Ng46lbOEBai4MwFygy0NKkO6pQE6uEFapjXyt6BUuo47IKlUrNGKpQDoCKktaKuMOEeKiap6kanisa1KhGjKpw8mE%2BcHYgPKgq3ChCkqqfRY%2B494kkr0IEn9eXQinyUm5YoDIE9Ki4qmlCIvG3Mm1nRPXPSaymz/VWEmn/Mffq8mpHCXXBF6pm48mmum9igQRmtk4mqW/LIDAcbmiWigxWuclW8W%2BW80sKdmlW361S4a0apQVGgSsW6iCm/y2WuassSawqWWpau236wKmCdaiaswaiHS4XPSnfc8Bmi662hgRmuZK6hcBmrgA3e2u28W%2BtMaBm8WrQ4Ol2vLNie/N3UXEW3PVamCYK0KyGyKmG2K%2BG82p2pGlKkuwS2OzKr5bKp3XYDoBALCnC%2BgAm5muLQohLdmuUujNW/I7kzutm6WgakrWjOW8PD/NrUUru4er0Hu1WnWye1LMLEnGWee7WiegezzOcvmce4xKe1ega6mBezeju7etio%2BqmMWnmg%2B1cwaXew2ta425G02yu3BZIaa0e%2BU%2BlIS9lK%2BxG4%2Bsu4%2BlOi49282j%2Bra%2B0na/SoGeewO6TK%2BwO0O%2ByeeyOn%2BgBq%2B2O/Pde%2Bbd%2Bgw9ZZ7WUr%2B3u12wGPO/cMKqG2NIuuG9S8BpKl%2B8a8B9G8CDgbYWgTgfwXgPwDgLQUgVATgMxSwawC8BugUY4HgUgAgTQNh7YFkAIMwdUQIMwSQAADlUf8A0AAE5/AzANBUhVHkh9BOBJBeAWAJANA5qeG%2BGBGOBeAFAQA5rpHeG2HSA4BYAYBEAQBdgCANyHKKAIA0BZQ6AEgog1ROBVBVHUgABaVISQC4YAZABIqQdUMwXgWkQgEgPAfVBa/gQQEQMQdgKQGQQQRQFQdQFx0gXQBat3BEDITgHgdhzh7hmR/hzgA8f4Pxi4aii4SJmJuJhJpJi4FJz2iADwYJ%2BgTgiRzYXgZxrQbYCAJAIJjIEJsgAJ5Z1ZkAYAKQJamgAS6KSgWIVp2ICIdoIEBp3gE55gYgIEA8WIbQHAi50gIJ5iA8BgWgc5yprAWILwYACSWgLIp5rAUhIwcQL5vs5oMSBxyptgmzaUJ5g6jhypwEWIBEG5jwLAVphKPAcx7gXgMSYgbgpQa8EF4AQEIwGR7YSStwhQd2PATAN3X8HhyRvJ4QUQcQYp1lsptQVp6p/QREFAawawfQPAWIBxyAbYVADIQYaF6J%2B4KuUwYRywPR3gVAAlmOLAcViAbYRoZoZwCAVweYPwBasIVYaoWoPQUoXIAQI1y17Ia1hgMYc1yYBa3VwYYYOYTwboPQN1loZYJ1iYRIV15YW14NkYAN9YINnVsRopppjgLh0gax1VzgXpqJ2J%2BJxJ5JyQVJgc3ATJqZiELgGZqRyl7YKKSiSYbV0geRlIdULR5IQISQDQSQFRwgjQfwVILR4xjgUx0gcx5ILgdUVILgAxrR1Rkd/wSQLgfwet9IJNtpux2wRxktlxhZzxxZ7xzp/4cgSgDZyZsJtgTgdoFgIkQIaJpgTCd8LgLR9UQdvhjJogDVvQVlgpjl6QLlpQHlyp3QJa2po0C5uNhN%2Bd2xjp3x/4bpqgWFYgE9s9i94sK9m9u9gc8ZlZyZq4CEMwYtuZ1xjdvdhIHdwJ3DVDyYY9096J%2BD7ZrRrgOavZ6UW6Q54505m5p5q5s5u5h5hwJ5l5scN5j51p7535/5wFvF0gYFxEMFvh/AGkSF5EVp2F4SeFkTxF1plFtFoEDFw4Ph7F3FyRglolzAEl8TkiSlvgAwUiulhlplp5l99lop992Qblipvhn9/lilxVqwSwEVsV%2BASV6VvIWV%2BVzpdz6wFV/h9V7J2TiVvoAYPIFwX0UNkIX0CNi1haq1wYBLtLvIZLl16LnAv1kYBL31gQD1lYKoQNn1kNr1ooMNjobLqNnYPYA4CQQDlpyp2xqDmD89y90ia9299UYSiAPNx99DgdrD0t0gctrARIKtpF3t/tm95twIGdwIQIZIFtyQOJha4Dzgex5d7Dtd%2BADdnxvxgjvD4gA9w4Y9gZlgBQIkBIokXrtMJYdJ/AR97J592QV9uzkp%2BQT9pznQEAIxv9%2BpvFlrxN1pkDrdr0Hpq7%2BJm7u7vgx75cTCsZoj1Zkb5IMb1dtxpZtHyZ07vHyYO7ni3BB7rR3BJ7wS2HvgOgOjhxiAI5yp1j5jkT5n25%2B5x5kT7jwQXjz5yTzAH5v5sQYTyRsT0FzT3gKTvLqFuT1QOFw4SR5T5F0VtTjTrFmOHT/FhIfTwz0F4z7H6l8z%2Blxlx0azz72ziQez0pv73lwH1z4wIVzzlFrV3zmVzgdEYhYL5Vmx8LzVnz3LvVvwA1%2BLqr41xL9AOru1soPIDL%2B1wYSP11/oPL4ryrwoMPoroYf1s18rmrzoUPir8N7PyN5rhr/YWN7toDiHlN2Hi4eH%2B7pH6UFHobkgEbot2Z8bybytuNubkAMwG95IZIfwTRqdyxgfwIAx8Htrnbpdpx8bmtwIVJpbrgKQLRxb%2BtrgYIJF5IVrmx6f/buNtJyf3fxd/f0gAlnIZwSQIAA)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/easy_kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/easy_kindred_repack.type.test.hpp)
