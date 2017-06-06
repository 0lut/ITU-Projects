module Week02 where

import Prelude hiding (gcd, sqrt)

gcd :: Integer -> Integer -> Integer
gcd x y = if y == 0 then x else gcd y (x `mod` y)

fac :: Integer -> Integer
fac n
  | n <  0    = error "negative parameter"
  | n == 0    = 1
  | otherwise = n * fac (n - 1)

fac' :: Integer -> Integer
fac' n
  | n < 0     = error "negative parameter"
  | otherwise = facIter 1 n
      where
        facIter :: Integer -> Integer -> Integer
        facIter acc n'
          | n' == 0   = acc
          | otherwise = facIter (acc * n') (n' - 1)

fib :: Integer -> Integer
fib n
  | n == 1    = 1
  | n == 2    = 1
  | otherwise = fib (n - 2) + fib (n - 1)

pow' :: Integer -> Integer -> Integer
pow' = undefined

pow :: Integer -> Integer -> Integer
pow x y
  | y == 0    = 1
  | even y    = sqr (pow x (y `div` 2))
  | otherwise = x * pow x (y - 1)
  where
    sqr :: Integer -> Integer
    sqr n = n * n

countChange :: Integer -> Integer
countChange amount = cc amount 50
  where
    next :: Integer -> Integer
    next n
      | n == 50 = 25
      | n == 25 = 10
      | n == 10 =  5
      | n ==  5 =  1
      | n ==  1 =  0

    cc :: Integer -> Integer -> Integer
    cc a n
      | a == 0          = 1
      | a < 0 || n == 0 = 0
      | otherwise       = cc (a - n) n + cc a (next n)

sqrt :: Float -> Float
sqrt x = newton 1.0
  where
    newton :: Float -> Float
    newton guess
      | isGoodEnough guess = guess
      | otherwise          = newton (improve guess)

    isGoodEnough :: Float -> Bool
    isGoodEnough guess = (abs (guess*guess - x)) / x < 0.001

    improve :: Float -> Float
    improve guess = (guess + x/guess) / 2.0
