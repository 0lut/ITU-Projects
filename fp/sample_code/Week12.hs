module Week12 where

import Prelude hiding (repeat, seq, strict)

seq :: Eq a => a -> b -> b
seq x y
  | x == x = y

strict :: Eq a => (a -> b) -> a -> b
strict f x = seq x (f x)

fac :: Integer -> Integer
fac n = facIter 1 n
  where
    facIter :: Integer -> Integer -> Integer
    facIter acc 0  = acc
    facIter acc n' = strict facIter (acc * n') (n' - 1)

repeat :: a -> [a]
repeat x = x : repeat x

addFirstTwo :: Num a => [a] -> a
addFirstTwo (x1:x2:_) = x1 + x2

fibs :: [Integer]
fibs = 1 : 1 : zipWith (+) fibs (tail fibs)

sieve :: [Integer] -> [Integer]
sieve (x:xs) = x : sieve [y | y <- xs, y `mod` x > 0]

primes :: [Integer]
primes = sieve [2 ..]

isPrime :: Integer -> Bool
isPrime n = elemOrd n primes

elemOrd :: Ord a => a -> [a] -> Bool
elemOrd n (x:xs)
  | n <  x    = False
  | n == x    = True
  | otherwise = elemOrd n xs
