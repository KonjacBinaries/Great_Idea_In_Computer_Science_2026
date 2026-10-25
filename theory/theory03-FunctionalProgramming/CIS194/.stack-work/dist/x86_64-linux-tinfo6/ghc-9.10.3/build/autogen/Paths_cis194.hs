{-# LANGUAGE CPP #-}
{-# LANGUAGE NoRebindableSyntax #-}
#if __GLASGOW_HASKELL__ >= 810
{-# OPTIONS_GHC -Wno-prepositive-qualified-module #-}
#endif
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -w #-}
module Paths_cis194 (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where


import qualified Control.Exception as Exception
import qualified Data.List as List
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude


#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir `joinFileName` name)

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath




bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath
bindir     = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/bin"
libdir     = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/lib/x86_64-linux-ghc-9.10.3-56e0/cis194-0.1.0.0-Ks4t2sbZ2GaEDQY2wRZtnT"
dynlibdir  = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/lib/x86_64-linux-ghc-9.10.3-56e0"
datadir    = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/share/x86_64-linux-ghc-9.10.3-56e0/cis194-0.1.0.0"
libexecdir = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/libexec/x86_64-linux-ghc-9.10.3-56e0/cis194-0.1.0.0"
sysconfdir = "/home/konja/Main Vault/Great Idea in Computer Science/Homework/2026.10.13 - Projects/Great_Idea_In_Computer_Science_2026/theory/theory03-FunctionalProgramming/CIS194/.stack-work/install/x86_64-linux-tinfo6/42a3644cbfc9aae2e4695fc7572948fa8dd08d10d22b6f0fe13f135e356201b3/9.10.3/etc"

getBinDir     = catchIO (getEnv "cis194_bindir")     (\_ -> return bindir)
getLibDir     = catchIO (getEnv "cis194_libdir")     (\_ -> return libdir)
getDynLibDir  = catchIO (getEnv "cis194_dynlibdir")  (\_ -> return dynlibdir)
getDataDir    = catchIO (getEnv "cis194_datadir")    (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "cis194_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "cis194_sysconfdir") (\_ -> return sysconfdir)



joinFileName :: String -> String -> FilePath
joinFileName ""  fname = fname
joinFileName "." fname = fname
joinFileName dir ""    = dir
joinFileName dir fname
  | isPathSeparator (List.last dir) = dir ++ fname
  | otherwise                       = dir ++ pathSeparator : fname

pathSeparator :: Char
pathSeparator = '/'

isPathSeparator :: Char -> Bool
isPathSeparator c = c == '/'
