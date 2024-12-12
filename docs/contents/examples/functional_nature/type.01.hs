-- typename
data Typename

-- auto
data Auto

-- *...
data Ellipsis a = Empty | Cons a (Ellipsis a)

-- template<*>
data Template a

-- template<template<typename...> class...>
newtype TeTeTyElEl = Template (Ellipsis (Template (Ellipsis Typename)))