sumEvenSquaresRecursive :: [Integer] -> Integer
sumEvenSquaresRecursive [] = 0
sumEvenSquaresRecursive (x:xs)
    | even x    = x * x + sumEvenSquaresRecursive xs
    | otherwise = sumEvenSquaresRecursive xs


sumEvenSquares :: [Integer] -> Integer
sumEvenSquares xs =
    sum (map (\x -> x * x) (filter even xs))