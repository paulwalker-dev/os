{ stdenv, fetchurl, ... }:
stdenv.mkDerivation rec {
  pname = "mk";
  version = "2017-03-23";
  src = fetchurl {
    url =
      "https://github.com/9fans/9fans.github.io/raw/aa002e281828ff129def5a27492b366100675de9/plan9port/unix/mk-with-libs.tgz";
    hash = "sha256-fNixG1V/tccZizpzMXpng821s083yeZ1wdIY52X8NM8=";
  };
  installPhase = ''
    mkdir -p $out/bin
    cp mk/mk $out/bin/mk
  '';
}
