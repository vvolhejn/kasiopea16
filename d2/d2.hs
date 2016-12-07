{-# LANGUAGE ScopedTypeVariables #-}
import Control.Applicative
import Control.Monad

solve :: [Int] -> (Int, Int) -- neni, je
solve [] = (0, maxBound)
solve (x:xs) = (f1, x + min f0 f1)
    where (f0, f1) = solve xs

oneCase = do
    _n :: Int <- read <$> getLine
    a :: [Int] <- (map read) . words <$> getLine
    putStrLn $ show $ snd $ solve a

main = do
    t <- read <$> getLine
    replicateM_ t oneCase