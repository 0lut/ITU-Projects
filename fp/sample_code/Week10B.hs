module Week10B (
  Set,
  empty,       -- Set a
  add,         -- Ord a => Set a -> a -> Set a
  makeSet,     -- Ord a => [a] -> Set a
  contains,    -- Ord a => Set a -> a -> Bool
  union,       -- Ord a => Set a -> Set a -> Set a
  mapSet,      -- Ord b => (a -> b) -> Set a -> Set b
  card         -- Set a -> Int
) where

data Set a = Nil | Node a (Set a) (Set a)
             deriving Show

empty :: Set a
empty = Nil

add :: Ord a => Set a -> a -> Set a
add Nil     y = Node y Nil Nil
add s@(Node x left right) y
  | y < x     = Node x (add left y) right
  | y > x     = Node x left (add right y)
  | otherwise = s

makeSet :: Ord a => [a] -> Set a
makeSet = foldl add empty

contains :: Ord a => Set a -> a -> Bool
contains Nil _ = False
contains (Node x left right) y
  | y < x      = contains left x
  | y > x      = contains right x
  | otherwis e = True

union :: Ord a => Set a -> Set a -> Set a
union s1  Nil = s1
union Nil s2  = s2
union (Node x left right) s2 = ((left `union` right) `union` s2) `add` x

card :: Set a -> Int
card = length . makeList

makeList :: Set a -> [a]
makeList Nil                 = []
makeList (Node x left right) = makeList left ++ [x] ++ makeList right

mapSet :: Ord b => (a -> b) -> Set a -> Set b
mapSet f = makeSet . map f . makeList
