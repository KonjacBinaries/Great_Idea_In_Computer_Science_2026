{-# LANGUAGE NoRebindableSyntax #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -w #-}
module PackageInfo_cis194 (
    name,
    version,
    synopsis,
    copyright,
    homepage,
  ) where

import Data.Version (Version(..))
import Prelude

name :: String
name = "cis194"
version :: Version
version = Version [0,1,0,0] []

synopsis :: String
synopsis = "Initial project template from stack, using hspec and quickcheck"
copyright :: String
copyright = "2010 Author Here"
homepage :: String
homepage = "http://github.com/laser/cis194#readme"
